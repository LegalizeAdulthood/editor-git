[![CMake workflow](https://github.com/LegalizeAdulthood/editor-git/actions/workflows/cmake.yml/badge.svg)](https://github.com/LegalizeAdulthood/editor-git/actions/workflows/cmake.yml)

# Managing Versions Programmatically with LibGit2

Sample code for the video
[Managing Versions Programmatically with LibGit2](https://www.youtube.com/watch?v=Vrc95KdNHHA).

# Obtaining the Source

Use git to clone this repository, then update the vcpkg submodule to bootstrap
the dependency process.

```
git clone https://github.com/LegalizeAdulthood/editor-git
cd editor-git
git submodule init
git submodule update --depth 1
```

# Building

A CMake preset has been provided to perform the usual CMake steps of
configure, build and test.

```
cmake --workflow --preset default
```

Places the build outputs in a sibling directory of the source code directory, e.g. up
and outside of the source directory.

# wxWidgets Dependencies for Linux

This sample code uses wxWidgets to create a GUI application.  On Linux,
you will need to install a bunch of prerequisistes on your system before
the code will build successfully.  Execute this command in the top-level
source directory to install the dependencies:

```sh
sed '/#/d' .github/workflows/wx-requirements.txt \
| xargs sudo apt-get install --no-install-recommends -y
```

[Utah C++ Programmers](https://meetup.com/utah-cpp-programmers)\
[Past Topics](https://utahcpp.wordpress.com/past-meeting-topics/)\
[Future Topics](https://utahcpp.wordpress.com/future-meeting-topics/)
