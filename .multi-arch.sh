#!/bin/sh

VERSION=$1

cat <<EOF >/tmp/multi.yml
image: chalmersrevere/opendlv-device-lidar-hdl32e-multi:$VERSION
manifests:	
  - image: chalmersrevere/opendlv-device-lidar-hdl32e-amd64:$VERSION
    platform:
      architecture: amd64
      os: linux
  - image: chalmersrevere/opendlv-device-lidar-hdl32e-armhf:$VERSION
    platform:
      architecture: arm
      os: linux
  - image: chalmersrevere/opendlv-device-lidar-hdl32e-aarch64:$VERSION
    platform:
      architecture: arm64
      os: linux
EOF
manifest-tool-linux-amd64 push from-spec /tmp/multi.yml
