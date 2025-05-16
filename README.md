# ImKanban
[![Build and test](https://github.com/pawelk5/ImKanban/actions/workflows/cmake-multi-platform.yml/badge.svg?event=push)](https://github.com/pawelk5/ImKanban/actions/workflows/cmake-multi-platform.yml)
## About

This project is a simple desktop app written using SFML and Dear ImGui for managing Kanban boards.

## Building
### Requirements
- CMake >= 3.24
- C++ compiler that supports C++20 (tested with VS2022, G++ and Clang)

### Linux

First, install SFML dependencies using your package manager:

```bash
sudo apt update && sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libfreetype-dev \
        libxi-dev \
        libudev-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev \
        libdrm-dev \
        libgbm-dev
```

Then, you can use the `build.sh` script or build manually:
```bash
mkdir -p build
cd build
cmake -B . -S ..
make
```

## Documentation

See the [docs](docs) folder for more details.

## Credits

This project uses following open source libraries and fonts:

- [Dear ImGui](https://github.com/ocornut/imgui)
- [SFML](https://github.com/SFML/SFML)
- [imgui-sfml](https://github.com/SFML/imgui-sfml)
- [IconFontCppHeaders](https://github.com/juliettef/IconFontCppHeaders)
- [nlohmann/JSON](https://github.com/nlohmann/json)
- [googletest](https://github.com/google/googletest)
- [Noto Sans](https://github.com/notofonts)
- [FontAwesome 6 Free](https://github.com/FortAwesome/Font-Awesome)

## License

This project is licensed under the GNU GPL-3.0 [license](LICENSE).
