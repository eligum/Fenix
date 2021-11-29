# Fenix [![License](https://img.shields.io/github/license/eligum/Fenix)](https://github.com/eligum/Fenix/blob/master/LICENSE)

Project based on the [Hazel](https://github.com/TheCherno/Hazel) engine.

---

## Getting Started
This project uses [CMake](https://cmake.org/) to generate build files, version **3.16** or higher is required. Fenix is currently being developed on a Linux enviroment, support for other platforms is officially untested although it's being made with Windows compatibility in mind.

<ins>**1. Downloading the repository:**</ins>

Start by cloning the repository with:

```sh
git clone --recursive https://github.com/eligum/Fenix.git
```
If you forgot to clone it recursively, use `git submodule update --init` to clone the necesserary submodules.

Next you can manually generate the build files with the following commands:

```sh
cd Fenix
mkdir build
cmake -S . -B build -DWARNINGS_AS_ERRORS=FALSE -DCMAKE_BUILD_TYPE=Debug
```

Or use the provided script `gen-project.sh`, which by default sets the build type to *Debug*. Only supported on Linux for now.

<ins>**2. Configuring the dependencies:**</ins>

All the project dependencies are included as submodules. All you need is an OpenGL capable GPU. If you are on Linux gtk-3 is needed for file dialogs.

---

## Features
- Fast 2D renderer
- ECS-driven scene components
- Settings, properties and view panels

## Short term goals
*Note: this is subject to change at any time!*

- Learn Vulkan while making a game engine
- Phisically-Based 3D rendering
- Support for Linux and Windows
    - Native redering API support (OpenGL, Vulkan)

## Usage examples
**TODO:** Add entity script code snippet, enjoy the little HelloWorld program for now ;)
```c++
#include <iostream>

int main()
{
    std::cout << "Hello, world!" << std::endl;
}
```

## Releases & Changelogs
See the [Changelog](https://github.com/eligum/Fenix/blob/master/docs/CHANGELOG.md) page.
