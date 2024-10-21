# Huesy

## Getting Started

### 1. Installation

#### Vendor Libraries

Make sure that the submodules are properly initialized and updated. From the root directory run:

```
git submodule update --init --recursive
```

#### Cmake

Visit https://cmake.org/download/ and download the latest binary distribution for your system.

### 2. Compiling

```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make
```
