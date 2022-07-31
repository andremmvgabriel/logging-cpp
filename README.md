- [I. Introduction](#i-introduction)
- [II. Platforms](#ii-platforms)
- [III. Requirements](#iii-requirements)
- [IV. How to use it](#iv-how-to-use-it)
  - [Build and run examples](#build-and-run-examples)
  - [Build and run tests](#build-and-run-tests)
- [V. Notes](#v-notes)

----------------------

# I. Introduction

Yes, it is exactly what you are thinking, another dumb guy that has decided to reinvent the wheel. Indeed, it might seem a dumb idea but I had my reasons. You see, I am mostly a self-taught person and most of my coding experience came from reading coding books, reading other people’s code, and through trial and error in personal projects. That is exactly the point of this project. The objective is not to compete with other competing projects, it is instead to gather more project development experience by applying my knowledge and understanding of how should a logger work, and try to reach the same point that other have already achieved.

This logging library is based on Python's logging library working mechanisms, which I made use of quite a lot over the past year. I tried to make this library as simple, efficient, and dynamic as possible, for my experience of course. If you are interested to use it, feel free to do so, and hope you like it.

# II. Platforms

This library was developed to be used in both Linux and Windows platforms.

However, it has only been tested on the Linux platform. Windows testing will be done as soon as possible.

# III. Requirements

This library was developed using C++20 to make use of the newest methodologies.

* C++20
* [fmt](https://github.com/fmtlib/fmt)
* [google testing](https://github.com/google/googletest)

# IV. How to use it

This logging library is very simple to be used. If you want to learn a bit more about the multiple usage cases, please access the examples within the examples directory. There are several comments through the code that should guide you. Have fun!

## Build and run examples

To build the examples scripts execute the command `cmake --build . --target examples`. Once done, the examples executables are created in the examples directory with a ".example" termination/extension.

To run the example simply execute the command `./name_of_example.example`.

## Build and run tests

To build the tests scripts execute the command `cmake --build . --target tests`. Once done, the examples executables are created and instantly run. The console/terminal should present the results of the tests.

# V. Notes

Some tests still have to created, and others updated.
