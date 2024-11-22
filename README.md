# README.md

## Building the Project

1. **Install CMake**: [CMake's official website](https://cmake.org/download/).

2. **Create a Build Directory**:
```bash
mkdir build
cd build
```

3. **Run CMake**: Configure the project using CMake. This will generate the necessary build files.
```bash
cmake ..
```

4. **Build the Project**: Use the generated build files to compile the project.
```bash
cmake --build .
```

5. **Ensure there is no memory leak**: I personnaly use drmemory
```bash
drmemory -quiet .\game.exe
```
