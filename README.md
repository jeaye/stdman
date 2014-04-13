C++ stdlib man pages
======
cppman is a tool that parses archived HTML files from [cppreference](http://cppreference.com) and generates groff-formatted manual pages for Unix-based systems. The goal is to provide excellent formatting for easy readability.

### Installation
There's no need to compile cppman if you just want to install the man pages. Instead, just run:
```bash
make install 
```

### Building/Generating
Should you want to build the source to make modifications and/or generate your own man pages, simply:
```bash
make && ./bin/cppman
```

### Compilation/Generation Dependencies
* C++11 (recommended GCC 4.8 or clang 3.4)
* [elinks](http://www.elinks.cz)
    * An advanced and well-established feature-rich text mode web browser.
