# WinrarBrutForcer

## Description

This program is made to break Winrar passwords. It is able to run on Windows and Linux, all you have to do is to install [conan](#installing-conan), [cmake](#installing-cmake) and [Winrar](https://www.win-rar.com/start.html).
For now, conan is useless because I don't use any library. Ideally, this project will have a dedicated window in the future.
All is said in it's title: this program can test every possible solutions to break the Winrar password. By every possible solutions, I mean that it can test every printable string.
A set of flags is available:
```
-a  Enables all printable characters
-l  Enables lowercase letters (enabled by default)
-u  Enables uppercase letters
-n  Enables numbers
-s  Enables symbols
```
You can choose your combination in terms of your needs.

### Warning
The more characters you add, the slower the execution time. A good processor is advised. To speed up the execution time, I have some ideas but it will be added in the future.

_This project only made for fun and I'm not aiming to break every single winrar password :). Anyway you'll need A LOT of time to just break a 4-char password... (to be improved soon)_

## Getting started

### Installing conan
Conan is a dependency manager used by our program to make it works. To compile it, you need to [install it](https://conan.io/downloads.html) if this isn't already installed on your machine. Then, there _will be_ some remote links to add to conan.

### Installing cmake
The compilation is made with CMake. This program is needed to compile the project. Follow [this link](https://cmake.org/install/) to download it if this isn't already installed on your machine.

### Compiling the project
To compile your project, execute the following command according to your OS:

Windows: ```./compile_win.bat```

Linux: ```./compile_unix.sh```

Your brut forcer will be found in the root directory of the project as ```RarBrutForce(.exe)```.
