# Continuous Deployment
In order to support continuous deployment, the following deployment
tools are supported:

* ansible

## Example
Say you have a relatively simple web project, with a frontend and a backend.
Say that your frontend developers always do "hallway usability tests" - they
always get someone else to check their changes before merging to `master`.
By using `ansible` to deploy and adding your frontend and backend build jobs
as inputs, `hoss` will deploy every permutation of these two projects. That way,
a frontend developer doesn't have to bring someone to their machine - their
branch is deployed automatically on push.