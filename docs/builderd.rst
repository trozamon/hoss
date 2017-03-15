# Build Daemon

## Supported Build Systems
In order to support various build systems, some code is bundled. Supported
build systems are:

* CMake 2.8.12
* CMake 3.5.0

These are all implemented as plugins.

### npm
During the build process, hoss will automatically check for and report
outdated dependencies (also for ruby).

### terraform
Support running terraform thingies to provision dev infra.
