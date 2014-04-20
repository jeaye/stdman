C++ stdlib man pages
======
stdman is a tool that parses archived HTML files from [cppreference](http://cppreference.com) and generates groff-formatted manual pages for Unix-based systems. The goal is to provide excellent formatting for easy readability. stdman has been tested on Linux and OS X.

![Sample](res/sample.gif)

### Installation
There's no need to compile stdman if you just want to install the man pages. Instead, just run:
```bash
./configure
sudo make install # sudo required for permission setting via install(1)
```
If you need to pass options to configure, you can do so. See `./configure --help` for more updated information.

### Building/Generating
Should you want to build the source to make modifications and/or generate your own man pages, simply:
```bash
make generate # will build stdman and generate man pages
```
**NOTE**: `make generate` expects sources will be in the `./reference/en/cpp` directory by default. See `./configure --help` to modify this.

### Compilation/Generation Dependencies
* C++11 (recommended GCC 4.8 or clang 3.4 or greater)
* elinks (recommended 0.12pre6 or greater)
* gzip (recommended 1.3.12 or greater)

**NOTE**: Generation not tested on Windows/cygwin.
