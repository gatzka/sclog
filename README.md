# sclog - An ANSI C conformant logging library.
## License
Copyright (c) 2019 Stephan Gatzka. See the [LICENSE](LICENSE) file for
license rights and limitations (MIT).

## Build Status
[![Travis CI](https://travis-ci.org/gatzka/sclog.svg?branch=master)](https://travis-ci.org/gatzka/sclog)
[![codecov](https://codecov.io/gh/gatzka/sclog/branch/master/graph/badge.svg)](https://codecov.io/gh/gatzka/sclog)
[![Quality Gate](https://sonarcloud.io/api/project_badges/measure?project=org.gatzka.sclog&metric=alert_status)](https://sonarcloud.io/dashboard?id=org.gatzka.sclog)

## Howto Build
sclog is always built using cmake. The CMakeLists.txt is written
platform independently so you can choose any cmake aware environment,
even Visual Studio.

There are several cmake options that let you configure which parts
should actually put into the library. For instance, if you compile for
POSIX conformant environments, you can choose if you want to include the
code for a `syslog` log sink. Please either look into the
[CMakeLists.txt](src/CMakeLists.txt) file or run a graphical cmake
frontend for more information.

sclog lets you choose if you want to build a static or dynamic library.
The default is static. If you want a shared library, execute:
```
cmake -DBUILD_SHARED_LIBS=ON <path-to-sclog-project>
```


