# suvorov-bot

[![Build Status](https://travis-ci.org/alkurbatov/suvorov-bot.png?branch=master)](https://travis-ci.org/alkurbatov/suvorov-bot)

- [suvorov-bot](#suvorov-bot)
    - [About](#about)
    - [Build requirements](#build-requirements)
        - [Windows](#windows)
        - [Linux](#linux)
        - [OS X](#os-x)
    - [Build instructions](#build-instructions)
        - [Windows](#windows)
        - [Linux and OS X](#linux-and-os-x)
    - [Coding Standard](#coding-standard)
    - [License](#license)

About
-----

Starcraft 2 Terran bot.

Build requirements
------------------

* Download and install (the password is iagreetotheeula) at least one of the following map packs:
  * [Ladder 2017 Season 3](http://blzdistsc2-a.akamaihd.net/MapPacks/Ladder2017Season3_Updated.zip)
  * [Ladder 2017 Season 4](http://blzdistsc2-a.akamaihd.net/MapPacks/Ladder2017Season4.zip)
  * [Ladder 2018 Season 1](http://blzdistsc2-a.akamaihd.net/MapPacks/Ladder2018Season1.zip)
* Download and install [CMake](https://cmake.org/download/).

### Windows
* Download and install [Visual Studio 2017](https://www.visualstudio.com/downloads/)

### Linux
* Install 'gcc-c++'.
* Install the 'make' utility.

### OS X
* Install XCode commandline tools.

Build instructions
------------------

### Windows

```bat
:: Get the project.
$ git clone --recursive https://github.com/alkurbatov/suvorov-bot.git
$ cd suvorov-bot

:: Create build directory.
$ mkdir build
$ cd build

:: Generate VS solution.
$ cmake ../ -G "Visual Studio 15 2017 Win64"

:: Build the project using Visual Studio.
$ start Suvorov.sln

:: Launch the bot with the specified absolute path to a SC2 map, e.g.
$ bin\Debug\Suvorov.exe C:\Users\alkurbatov\Ladder2017Season3\InterloperLE.SC2Map
```

### Linux and OS X

```bash
# Get the project.
$ git clone --recursive https://github.com/alkurbatov/suvorov-bot.git && cd suvorov-bot

# Create build directory.
$ mkdir build && cd build

# Generate a Makefile.
# Use 'cmake -DCMAKE_BUILD_TYPE=Debug ../' if debuginfo is needed
$ cmake ../

# Build.
$ make

# Launch the bot with the specified absolute path to a SC2 map, e.g.
$ ./bin/Suvorov "/Users/alkurbatov/work/tmp/Ladder2017Season3/InterloperLE.SC2Map"
```

Coding Standard
---------------

We follow slightly modified [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
See [.travis/lint.sh](.travis/lint.sh) for details.

License
-------

Copyright (c) 2017

Licensed under the [MIT license](LICENSE).
