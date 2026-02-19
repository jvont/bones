# bones

bones is a lightweight C++ game engine

## Requirements

```sh
sudo apt-get install build-essential git make \
  pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
  libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
  libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
  libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
  libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev libthai-dev \
  libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev \
  libunwind-dev libusb-1.0-0-dev
```

## Building

```shell
cmake -S . -B build/ -G Ninja
cmake --build build/
```

running tests (optional):

```shell
ctest 
```

## Usage

```cpp
#include <bones/core/app.h>

// TODO
```
