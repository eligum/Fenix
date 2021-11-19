# Fenix [![License](https://img.shields.io/github/license/eligum/Fenix)](https://github.com/eligum/Fenix/blob/master/LICENSE)

Project based on the [Hazel](https://github.com/TheCherno/Hazel) engine.

---

## Getting Started
This project uses [CMake](https://cmake.org/) to generate build files, version **3.16** or higher is required.

<ins>**1. Downloading the repository:**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/eligum/Fenix.git`. If you forgot to clone it recursively, use `git submodule update --init` to clone the necesserary submodules.

Next you can manually generate the build files with the following commands:

```console
cd Fenix
mkdir -p build
cmake -S . -B build -DWARNINGS_AS_ERRORS=FALSE -DCMAKE_BUILD_TYPE=Debug
```

Or use the provided script `gen-project.sh`, which by default sets the build mode to *Debug*.

<ins>**2. Configuring the dependencies:**</ins>

All the project dependencies are included as submodules.

---

## Short term goals
*Note: this is subject to change at any time!*

- Learn Vulkan while making a game engine
- Fast 2D rendering
- Phisically-Based 3D rendering
- Support for Linux and Windows
    - Native redering API support (OpenGL, Vulkan)

## Usage examples
### Basic usage
```c++
int main()
{
    std::cout << "Hello World!" << std::endl;
}
```
