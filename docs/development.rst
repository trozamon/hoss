***************
Developing Hoss
***************

Principles
==========

* Hoss must be easy to use and administer. Minimize dependencies on external
  services and libraries. Upgrades for minor and patch versions should incur
  zero downtime.
* Hoss should be `bug free`_
  
Design
======

Hoss is designed as a super cool "everything is active" system. It's stateless;
killing all the schedulers and then starting them should not cause any
interruption in service other than (potentially) the need to re-perform some
builds.

Managing Scheduler State
------------------------

Here's the basic flow of an external message into hoss:

#. ``hoss-schedulerd`` receives the message
#. ``hoss-schedulerd`` writes the message to MongoDB, noting that it is working
   on it
#. ``hoss-schedulerd`` attempts to schedule the build
#. ``hoss-schedulerd`` writes the message to MongoDB, noting that it is working
   on it or that it is scheduled

.. _bug free: https://www.joelonsoftware.com/2000/08/09/the-joel-test-12-steps-to-better-code/
