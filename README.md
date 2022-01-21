OpenALpp
========
[![Tests](https://github.com/Laguna1989/OpenALpp/actions/workflows/test_verification.yml/badge.svg)](https://github.com/Laguna1989/OpenALpp/actions/workflows/test_verification.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

OpenALpp is a modern OOP C++14 audio library built on [OpenAL Soft](https://github.com/kcat/openal-soft)
for Windows, macOS, Linux and web (emscripten). It supports loading of wav, mp3, FLAC and ogg files
via [libnyquist](https://github.com/ddiakopoulos/libnyquist).

How to build
------------

1. `git clone https://github.com/Laguna1989/OpenALpp.git && cd OpenALpp`
2. `mkdir build && cd build`
3. `cmake ..`
4. `cmake --build . --target OpenALpp_Lib`

Code Example
----------

```
#include "oalpp/sound_context.hpp"
#include "oalpp/sound_data.hpp"
#include "oalpp/sound.hpp"

SoundContext ctx;
SoundData buffer { "audio.mp3" };
Sound snd { buffer, ctx };
snd.play();
```

How to include OpenALpp in your project
---------------------------------------

CMakeLists.txt

```
FetchContent_Declare(
        openalpp
        GIT_REPOSITORY https://github.com/Laguna1989/OpenALpp.git
        GIT_TAG master
)

FetchContent_MakeAvailable(openalpp)

add_executable(MyProject main.cpp)
target_link_libraries(MyProject OpenALpp_Lib)
```

CMake Options
-------------

* `OALPP_ENABLE_UNIT_TESTS` - Enable unit tests - default `ON`
* `OALPP_ENABLE_INTEGRATION_TESTS` - Enable integration test - default `ON`
* `OALPP_STATIC_LIBRARY` - Build OpenALpp and dependencies as static library - default `OFF`

Compiler compatibility
----------------------

* Microsoft Visual C++ 2019
* clang++ from version 8
* g++ from version 9
* emscripten g++ version 9

Dependencies
------------

* CMake 3.19
* One of the compatible compilers

All other dependencies (openal-soft and libnyquist) are automatically fetched via CMake.
