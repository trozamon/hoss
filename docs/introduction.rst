************
Introduction
************

What is hoss?
=============

Depending on who you ask, ``hoss`` is either "yet another stupid piece of
software for continuous integration" or "the greatest thing since sliced
bread." I intend ``hoss`` to be:

* A simple CI server for those who want that
* A rich, extensible, highly available CI/CD "service" for those who want that
* Anything in-between

Quick Start
===========

Let's do a real quick example. Open up a bunch of terminals and move to a
directory where you don't mind creating some files and having a build take
place. Run these commands::

    mkdir builds
    echo 'job:
  name: libgit2
  build: cmake

  source:
    uri: https://github.com/libgit2/libgit2
    type: git' > builds/libgit2.yml

    hoss-schedulerd

This will start the job scheduler. To start the builder, just run::

    hoss-builderd

Now that everything is running, all you need to do to trigger a build is run::

    hoss build libgit2

That will trigger the scheduler to start a build for the 'libgit2' job. If you
want to see a pretty web UI that shows this, you can open http://localhost:8080
in a browser and view the progress.

High-level hoss
===============

Hoss is simple. A "job" or a "build" consist of the following:

1. Source
2. Build Instructions

"Job" and "build" are used interchangeably throughout the documentation to mean
the same thing. A workflow consists of multiple jobs, probably with
dependencies on each other.

Jobs
----

A job operates on a single source to:

* Compile, test, and package a set of code
* Run one or more ansible playbooks
* Build an RPM
* Upload an artifact to a server via SFTP
* Run some sort of arbitrary command

Jobs can also be configured to run in a given list of environments in order to
ensure all operating systems or compilers or runtimes are supported as needed.
In addition, since a lot of native builds have multiple possible build
configurations, jobs can be run with sets of parameters (similar to a matrix
job in Jenkins). Finally, jobs can depend on other jobs or artifacts produced
by other jobs.

Workflows
---------

Workflows are provided as an abstraction to group jobs together. They can be
depended on just like jobs, but they don't really bring much else to the table.

Deploying hoss
==============

Hoss consists of two server binaries - ``hoss-schedulerd`` and
``hoss-builderd`` - and one client binary - ``hoss``. The client binary is
optional if you're a beast with ``curl`` or if you don't ever feel like
manually triggering builds. With that said, it is pretty useful to use the
client binary in VCS post-commit hooks to inform hoss that there is a new
commit.

``hoss-schedulerd`` may use other services to run:

* MongoDB

Simplest Deployment
-----------------

* 1 hoss scheduler
* 1 hoss builder

Super Duper Big Deployment
--------------------------

* 3-5 MongoDB nodes
* 2+ hoss schedulers
* 2+ hoss builders
