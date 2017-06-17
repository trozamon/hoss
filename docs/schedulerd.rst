# Hoss Scheduler
The hoss scheduler does a lot:

* schedules builds across builders
* stores job history
* accepts commands over HTTP to run jobs

The scheduler can be configured to optionally use the following
for high availability (HA) support:

* etcd

The scheduler can be configured to store job history in:

* MongoDB

## Scheduling Loop
`hoss-schedulerd` schedules jobs upon receiving heartbeats from
`hoss-builderd` or upon receiving a request to run a build. The
scheduler will try to make intelligent allocation of resources;
a Ruby job will, for example, attempt to be scheduled on a node
with the **least** amount of resources free (to preserve resources
for CPU-intensive builds), while C++ jobs will take as many resources
as possible.

## High Availability
We all hate it when services go down, and your internal
build farm should not be an exception! Your developers deserve
nice things!

`hoss-schedulerd` runs in a hot-warm+ configuration. One daemon
will do the scheduling, but all are aware of the state of the
cluster. All of the running daemons can accept requests for jobs,
and non-hot schedulers will forward them to the hot scheduler.

## Storing Job history
Jobs can be in a few states:

* Scheduling
* Running
* Complete

As soon as a valid build request comes in, any scheduler - even
warm schedulers - throw in a database entry for a job in the
"scheduling" state.

## Developer-maintained Build Definitions
The hoss scheduler can be configured with a whitelist of repos to build
on an ad-hoc basis, trusting build configuration committed in the repo.

## Configuration
Directives are:

* address - the address to bind to and (if configured) advertise in etcd.
  defaults to 0.0.0.0:0
* etcd - the etcd address to publish address info to and use for leader
  election
