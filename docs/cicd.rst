# CI + CD
## Example
You are AirBNB. You want to ensure `chronos` builds on a variety
of platforms, but you only run it on your platform.

Your CI job has an array of features to build across like:

```json
{
    "arch": ["amd64", "x86"],
    "lang::java::openjdk": ["1.7", "1.8"],
    "os": ["fedora::24", "fedora::23", "centos::7"]
}
```

Your CD job has a much more constrained set of features, since
you only deploy onto your CentOS 7 infrastructure with Java 8:

```json
["arch::amd64", "lang::java::opendjdk::1.8", "centos::7"]
```