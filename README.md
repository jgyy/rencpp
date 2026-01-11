# rencpp

A text adventure game written in C++ with Qt.

## Requirements

- CMake 3.16 or higher
- Qt5 (Core, Gui, Widgets components)
- C++17 compatible compiler
- Git

## Building and Running

### 1. Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get install cmake qt5-default qt5-qmake qtbase5-dev
```

**macOS (with Homebrew):**
```bash
brew install cmake qt5
```

**Windows:**
Download and install CMake and Qt5 from their official websites.

### 2. Clone the Repository

```bash
git clone <repository-url>
cd rencpp
```

### 3. Build the Project

```bash
mkdir build
cd build
cmake ..
make
```

### 4. Run the Game

```bash
./bin/rencpp
```

Or from the root directory:
```bash
./build/bin/rencpp
```

## Project Structure

- `src/` - Source code files
- `resources/` - Game resources and story files
- `qml/` - QML files
- `CMakeLists.txt` - CMake build configuration
