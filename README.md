# RIO (Radu IO)
RIO is a simple header only C library for I/O operations for personal use. It provides a lightweight interface for reading, writing, creating, and managing files. This library makes it easy to perform file operations.

## Usage

Create only **one** additional C/C++ file:
```c
#define _RIO_IMPLEMENTATION_
#include "rio.h"
```
After that use the "rio.h" file as a common header file. If you want to use the wrapper within one translation unit add also:
```c
#define RIO_STATIC
```
before including the file so every function becomes static by default.

## License
[MIT](https://mit-license.org/)