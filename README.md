# Huesy

## Quick Start

### 1. Initialize Git Submodules ###

```
git submodule update --init --recursive
```

### 2. Install `cmake` (https://cmake.org/)

#### Option 1:
Windows / Mac / Linux:

Visit https://cmake.org/download/ and download/install the relevant library.

#### Option 2:

Windows:
```
N/A
```

Mac:
```
brew install cmake
```

Linux:
```
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get update

# cmake not yet installed:
sudo apt-get install cmake

# already installed
sudo apt-get upgrade
```

### 3. Run `cmake`

For convenience, you can run the following command from the project's root:
```
./config
```

### 4. Build

For convenience you can run the following command from the project's root:
```
./build
```

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
