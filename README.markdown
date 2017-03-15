# Hoss

## Summary
A continuous integration service. From a developer perspective, it
provides:

* Simple configuration via YAML
* Build descriptions can be checked into source repos (or not, whichever works!)
* Native integration with your build system
* Native integration with your unit test framework
* The ability to build from master, build branches, build patches, etc.

From a sys-admin perspective, it provides:

* An easy-to-maintain service
* Configurable security backends
* Multi-master highly available, if desired
* Easy to containerize
* Rich metrics and status API

## Design
### Platform/Language Support
Aim for supporting the following operating systems:

* CentOS
* Debian
* Fedora
* FreeBSD
* Gentoo
* Mac OS
* OpenBSD
* OpenSUSE
* Ubuntu
* Windows

For supported operating systems, there should always be an available branch.

Aim for supporting as many languages and locales as possible.

### Services (daemons)
In order to scale and facilitate High Availibility (HA), `hoss` is written
as a collection of daemons (aka microservices). These daemons are:

* `hoss-schedulerd` - schedules build jobs
* `hoss-notifierd` - monitors source repositories (try to avoid using this)
* `hoss-builderd` - runs build jobs

`hoss` can depend on the following services to run:

* `etcd` - for leader election
* MongoDB (for storing build history):

Run as many `hoss-schedulerd` instances as you need. Run as
many `hoss-builderd` instances as you want build hosts. 

See [Scheduler Design](doc/schedulerd.markdown) for more in-depth
discussion of scheduler design, and [Builder Design](doc/builderd.markdown)
for more in-depth discussion of builder design.

### Builds
Builds are scheduled based on features. Sample features are:

* lang::cpp::gcc::5.1.0
* lang::cpp::gcc::5
* lang::java::openjdk::1.8
* lang::ruby::mri::2.3.0

## Reference Architecture
### Smallest
This reference architecture assumes you want the simplest build farm
ever - probably just a single machine.

1. Install `hoss`
2. Run `hoss-schedulerd`
3. Run `hoss-builderd`
4. Profit!

### Biggest
The reference architecture assumes you are using kubernetes and running
everything in docker containers. It's web scale! It's over 9000!

1. Setup kubernetes
2. Setup mongodb, in kubernetes
3. Setup etcd, in kubernetes
4. Run 2 or more `hoss-schedulerd` instances, in kubernetes
5. Run 2 or more `hoss-builderd` instances, in kubernetes
