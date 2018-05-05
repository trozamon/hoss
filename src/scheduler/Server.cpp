#include "Parser.hpp"
#include "Server.hpp"
#include "core/InMemoryDocStore.hpp"
#include <boost/filesystem.hpp>
#include <functional>
#include <thread>

using hoss::core::Log;
using hoss::core::HttpServer;
using hoss::core::InMemoryDocStore;
using hoss::core::linesep;
using hoss::scheduler::Parser;
using hoss::scheduler::Scheduler;
using hoss::scheduler::Server;
using std::thread;

Server::Server() :
        docStore{new InMemoryDocStore()},
        scheduler{docStore},
        httpApi1{httpServer, scheduler},
        log{Log::getLogger("Server")}
{
}

Server::Server(const SchedulerConfiguration &conf) :
        _conf{conf},
        docStore{new InMemoryDocStore()},
        scheduler{docStore},
        httpApi1{httpServer, scheduler},
        log{Log::getLogger("Server")}
{
}

int Server::run()
{
        configure();

        thread sched{std::bind(&Scheduler::run, &scheduler)};
        thread http1{std::bind(&HttpServer::run, &httpServer)};

        sched.join();
        return 0;
}

void Server::configure()
{
        for (auto dir : _conf.defDirs())
        {
                log.info() << "Loading defs from " << dir << linesep;
                loadJobDefs(dir);
        }
}

void Server::loadJobDefs(const std::string &dir)
{
        using namespace boost::filesystem;
        using std::ifstream;

        Parser parser;

        parser.jobHandler([this](JobDefinition job) {
                        scheduler.addJobDefinition(job);
        });

        for (auto &ent : directory_iterator(dir))
        {
                log.info() << "Loading " << ent.path().native() << linesep;
                ifstream s{ent.path().native()};
                parser.parse(s);
        }
}
