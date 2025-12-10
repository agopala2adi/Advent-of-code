# Build Instructions for Ubuntu 22.04

## Prerequisites

Install required dependencies:
```bash
sudo apt update
sudo apt install -y build-essential cmake wget tar
```

## Building the Project

Download and extract OR-Tools:
```bash
wget https://github.com/google/or-tools/releases/download/v9.14/or-tools_amd64_ubuntu-22.04_cpp_v9.14.6206.tar.gz
mkdir ortools
tar -xzf or-tools_amd64_ubuntu-22.04_cpp_v9.14.6206.tar.gz -C ortools/ --strip-components=1
```

Build and run:
```bash
mkdir build
cmake -S . -B build
cmake --build build --config Release && ./build/day10soln
```

## Notes
- OR-Tools is required for this project to run part-2. Ensure it is downloaded and extracted as shown above.
- The build process uses CMake to configure and compile the project.
- Ensure that the path to the OR-Tools installation is correctly set in the `CMakeLists.txt` file.
- The build type is set to `Release` by default for optimized performance.
- Other platforms are not officially supported; adjustments may be necessary.
- The provided instructions are tailored for Ubuntu 22.04; other distributions may require different package names or versions.
- Visit [OR-Tools Releases](https://github.com/google/or-tools/releases) page for the using the suitable package for your distro and platform.
