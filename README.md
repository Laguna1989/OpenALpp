OpenALpp
========
[![Tests](https://github.com/Laguna1989/OpenALpp/actions/workflows/test_verification.yml/badge.svg)](https://github.com/Laguna1989/OpenALpp/actions/workflows/test_verification.yml)

OpenALpp is a modern OOP C++14 audio library built on [OpenAL Soft](https://github.com/kcat/openal-soft)
for Windows, Linux and web (emscripten).
It supports loading of wav, mp3, FLAC and ogg files via [libnyquist](https://github.com/ddiakopoulos/libnyquist).

Compiler compatibility
----------------------
* Microsoft Visual C++ 2019
* clang++ from version 8
* g++ from version 9
* emscripten g++ version 9

How to build
------------
1. `git clone https://github.com/Laguna1989/OpenALpp.git && cd OpenALpp`
2. `mkdir build && cd build`
3. `cmake ..`
4. `cmake --build . --target OpenALpp_*`
