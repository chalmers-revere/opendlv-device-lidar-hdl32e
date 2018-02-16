## OpenDLV Microservice to interface with VelodyneLidar HDL32e units

This repository provides source code to interface with a VelodyneLidar HDL32e
unit for the OpenDLV software ecosystem.

[![Build Status](https://travis-ci.org/chalmers-revere/opendlv-device-lidar-hdl32e.svg?branch=master)](https://travis-ci.org/chalmers-revere/opendlv-device-lidar-hdl32e) [![License: GPLv3](https://img.shields.io/badge/license-GPL--3-blue.svg
)](https://www.gnu.org/licenses/gpl-3.0.txt)


## Table of Contents
* [Dependencies](#dependencies)
* [Usage](#usage)
* [Build from sources on the example of Ubuntu 16.04 LTS](#build-from-sources-on-the-example-of-ubuntu-1604-lts)
* [License](#license)


## Dependencies
No dependencies! You just need a C++14-compliant compiler to compile this
project as it ships the following dependencies as part of the source distribution:

* [libcluon](https://github.com/chrberger/libcluon) - [![License: GPLv3](https://img.shields.io/badge/license-GPL--3-blue.svg
)](https://www.gnu.org/licenses/gpl-3.0.txt)
* [Unit Test Framework Catch2](https://github.com/catchorg/Catch2/releases/tag/v2.1.1) - [![License: Boost Software License v1.0](https://img.shields.io/badge/License-Boost%20v1-blue.svg)](http://www.boost.org/LICENSE_1_0.txt)


## Usage
This microservice is created automatically on changes to this repository via Docker's public registry for:
* [x86_64](https://hub.docker.com/r/chalmersrevere/opendlv-device-lidar-hdl32e-amd64/tags/)
* [armhf](https://hub.docker.com/r/chalmersrevere/opendlv-device-lidar-hdl32e-armhf/tags/)
* [aarch64](https://hub.docker.com/r/chalmersrevere/opendlv-device-lidar-hdl32e-aarch64/tags/)

To run this microservice using our pre-built Docker multi-arch images to connect
to a VelodyneLidar HDL32e unit broadcasting data to `0.0.0.0:2368` and to publish
the messages according to OpenDLV Standard Message Set into session 111 in
Google Protobuf format, simply start it as follows:

```
docker run --init --rm --net=host chalmersrevere/opendlv-device-lidar-hdl32e-multi:v0.0.1 opendlv-device-lidar-hdl32e --hdl32e_ip=0.0.0.0 --hdl32e_port=2368 --cid=111 --verbose
```

## Build from sources on the example of Ubuntu 16.04 LTS
To build this software, you need cmake, C++14 or newer, and make. Having these
preconditions, just run `cmake` and `make` as follows:

```
mkdir build && cd build
cmake -D CMAKE_BUILD_TYPE=Release ..
make && make test && make install
```


## License

* This project is released under the terms of the GNU GPLv3 License

