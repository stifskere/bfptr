
# BFPTR, Run brainfuck on your pointers.

This library exposes two functions that evaluate brainfuck
on runtime.

This library is mostly unmaintained due to its nature, and not
meant to be used in production.

## Installation

Go to the releases section of this repository, and download both files,
you want the `bfptr.h` which contains the definitions and the
documentation for the functions and the `libbfptr.a` which is the
library binary, containing the declarations of these functions.

You can do the following if you use cmake.

```cmake
# assuming that you have your .h files here.
include_directories(${CMAKE_SOURCE_DIR}/include)

# link the directory containing the library.
link_directories(${CMAKE_SOURCE_DIR}/libs)

# add your project source files before linking the library.

# link this static library
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE bfptr)
```

## Usage

When you have it linked you will have the `bfptr.h` header
available for use.

```c
#include <bfptr.h>
```

And you can use the functions it exposes which are `brainfuck_on_ptr` and
`brainfuck`.

### brainfuck_on_ptr

The `brainfuck_on_ptr` function has the following signature

```c
void brainfuck_on_ptr(void *ptr, int limit, char *code);
```

And it will run the brainfuck code on your pointer,
which will modify it as per your brainfuck code.

The `void *ptr` parameter is treated internally as `unsigned char *` as per
the brainfuck rules, and it's the memory you run your brainfuck code on.

The `limit` parameter defines the bounds for this pointer,
if you move with `<` behind 0 the pointer will
point back to limit, and the same, if you move
with `>` beyond the limit it will point back to 0.

The `code` parameter is the code to be run, delimited by `\0` as
per the C standard.

### brainfuck

The `brainfuck` function has the following signature

```c
void brainfuck(char *code);
```

This function allocates a 30000-byte buffer and runs your brainfuck code in
that pointer using the `brainfuck_on_ptr` function.

The `code` parameter is the code to be run, delimited by `\0` as 
per the C standard.

## Good to know

You have more information on the code comments, hovering the mouse
over the function names. This library is not maintained as it's just made
as a joke, so if you have any issue, I might or might not see it.