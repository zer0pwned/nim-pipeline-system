nim-pipeline-system
===================

[![](https://img.shields.io/github/license/zer0pwned/nim-pipeline-system)](https://github.com/zer0pwned/nim-pipeline-system/blob/main/LICENSE) ![Build Status](https://github.com/zer0pwned/nim-pipeline-system/workflows/build/badge.svg)

Here is what we can do.
* Automatically build and test your NIM project on Windows/Linux/MacOS and NIM v1.2.0/v1.4.8/v1.6.0 with the power of Github Action.
* Leverage the up-to-date nimble to lock and sync all your dependencies.
* See [.github/workflows/test.yml](https://github.com/zer0pwned/nim-pipeline-system/blob/main/.github/workflows/test.yml) for full example.


## Story

This is an example project for the NIM CI/CD pipeline system based on Github Actions. We rely on the new feature of nimble, lock and sync to keep track of the correct version of nim package dependencies. We provide a basic working scheme for you to leverage the power of Github CI/CD system and the new nimble.

In order to use our scheme, you need to install nimble v0.14.0 (at least). Nimble v0.14.0 can only be installed through directly running `nimble install https://github.com/nim-lang/nimble@#head` so far. It also relies on NIM v1.6.0 so you need to use [choosenim](https://github.com/dom96/choosenim) before and after the new nimble installation.

In this repository, we create a simple nimble project by running `nimble init` to initialize a hybrid nimble project. We use a prefect example from [nim-protobuf-serialization](https://github.com/status-im/nim-protobuf-serialization) where the up-to-date version does not compile anymore due to the broken dependency of [nim-faststreams](https://github.com/status-im/nim-faststreams).

The funny story is `nim-protobuf-serialization` used to work on my local project but not anymore if anyone wants to install the package freshly unless pin to certain commit. So using lock file is definitely a better option as it defines the commit of all the package dependencies. With the lock file, others or the Github Actions can easily install the correct version of all dependencies without the needs of pin every dependency of your project. 


## Typical usage
On development machine 1

```
$ choosenim 1.6.0
$ nimble install https://github.com/nim-lang/nimble@#head
# In case you want to use 1.4.6 instead
# Do not override your new nimble file!!
$ echo N | choosenim 1.4.8 
$ nimble init
# Do whatever you need, development, testing, etc. 
# Lock the dependencies before you push to remote. 
$ nimble lock
```

On development machine 2 or on Github Action
```
$ choosenim 1.6.0
$ nimble install https://github.com/nim-lang/nimble@#head
# In case you want to use 1.4.6 instead
# Do not override your new nimble file!!
$ echo N | choosenim 1.4.8 
# use nimble -l sync if you want to store dep locally
$ nimble sync
```


## Caveat

So far the new nimble sync does not work on Windows due to the checksum mismatch issue. See https://github.com/zer0pwned/nim-pipeline-system/issues/1 and https://github.com/nim-lang/nimble/issues/957. 

Current workaround: stick with old version nimble on Windows without sync feature.

## Further Reading

If you want a customized version of nimble build system where you need to modify nim source code, you should checkout [nimbus-build-system](https://github.com/status-im/nimbus-build-system) from `status-im`. They are very experienced at using nim ecosystem.
