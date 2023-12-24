OpenALpp
========
[![codecov](https://codecov.io/gh/Laguna1989/OpenALpp/branch/master/graph/badge.svg?token=X68KWFTRZG)](https://codecov.io/gh/Laguna1989/OpenALpp)
[![Tests](https://github.com/Laguna1989/OpenALpp/actions/workflows/test_verification.yml/badge.svg)](https://github.com/Laguna1989/OpenALpp/actions/workflows/test_verification.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

OpenALpp is a modern OOP C++20 audio library built on [OpenAL Soft](https://github.com/kcat/openal-soft)
for Windows, macOS, Linux and web (emscripten). It supports loading of wav, mp3, FLAC and ogg files
via [libnyquist](https://github.com/ddiakopoulos/libnyquist).

How to build
------------

1. `git clone https://github.com/Laguna1989/OpenALpp.git && cd OpenALpp`
2. `mkdir build && cd build`
3. `cmake ..`
4. `cmake --build . --target OpenALpp_Lib`

How to measure Code Coverage with [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage)
-----------

```
OpenCppCoverage.exe
    --sources <absolute path>\OpenALpp\impl\
    --excluded_sources <absolute path>\OpenALpp\test\
    --excluded_sources <absolute path>\OpenALpp\ext*
    --excluded_sources <absolute path>\OpenALpp\cmake-build-debug*
    .\path\to\unit_tests\OpenALpp_UnitTests.exe
```

Code Example
----------

```
#include "oalpp/sound_context.hpp"
#include "oalpp/sound_data.hpp"
#include "oalpp/sound.hpp"

using namespace oalpp;

SoundContext ctx;
SoundData buffer { "audio.mp3" };
Sound snd { buffer };
snd.play();

while (snd.isPlaying()) {
    snd.update();
}
```

Common Pitfalls
------------

* `Sound` has a dependency on `SoundContext`. You need to keep the `SoundContext` alive as long as you want to use
  sounds.
    * Note that this does not apply to `SoundData`, which can be created independently of `SoundContext`.
* Sound has a dependency to the `SoundData` that is passed in the constructor. You need to keep the `SoundData` alive as
  long as any `Sound` might access it.
    * You can bundle `SoundData` and `Sound` together in your implementation.
    * Alternatively you can write your own `SoundDataManager` to avoid creating multiple `SoundData`s for the same file.
* Your sound will stop after some seconds, even if the audio file contains a longer sound. `Sound`s do not update
  themselves. You need to call `update()` regularly.

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
* `OALPP_ENABLE_APPROVAL_TESTS` - Enable approval tests - default `ON`
* `OALPP_ENABLE_INTEGRATION_TESTS` - Enable integration test - default `ON`
* `OALPP_STATIC_LIBRARY` - Build OpenALpp and dependencies as static library - default `ON`

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

All other dependencies (`openal-soft` and `libnyquist`) are automatically fetched via CMake.
