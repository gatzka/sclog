# sclog - An ANSI C conformant logging library.
## License
Copyright (c) 2019 Stephan Gatzka. See the [LICENSE](LICENSE) file for
license rights and limitations (MIT).


[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fgatzka%2Fsclog.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2Fgatzka%2Fsclog?ref=badge_large)

## Build Status
[![Github action](https://github.com/gatzka/sclog/workflows/CI%20build/badge.svg?branch=master)](https://github.com/gatzka/sclog/actions)
[![Coverity](https://scan.coverity.com/projects/19467/badge.svg)](https://scan.coverity.com/projects/gatzka-sclog)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/gatzka/sclog/master/LICENSE)
[![codecov](https://codecov.io/gh/gatzka/sclog/branch/master/graph/badge.svg)](https://codecov.io/gh/gatzka/sclog)
[![Quality Gate](https://sonarcloud.io/api/project_badges/measure?project=org.gatzka.sclog&metric=alert_status)](https://sonarcloud.io/dashboard?id=org.gatzka.sclog)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/gatzka/sclog.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/gatzka/sclog/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/gatzka/sclog.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/gatzka/sclog/context:cpp)
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2Fgatzka%2Fsclog.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2Fgatzka%2Fsclog?ref=badge_shield)

[![Open Hub](https://img.shields.io/badge/Open-Hub-0185CA.svg)](https://www.openhub.net/p/sclog)

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

## Documentation

The generated [doxygen](http://www.doxygen.nl/) documentation can be found
[here](https://gatzka.github.io/sclog/doc/html).