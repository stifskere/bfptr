
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

Now you can use the functions this library exposes, which are 2, `brainfuck_on_ctx`
which runs brainfuck on a specified context and `brainfuck` which
runs brainfuck on a default isolated context.

### brainfuck_on_ctx

This function asks for a `bfptr_context` which is defined the following
way in the `bfptr.h` file.

```c
typedef struct {

    /*
         You can or either pass `NULL` or a pointer,
         if you pass `NULL`, the code will generate a 30_000
         position array for you and will free it automatically.
    */
    unsigned char *memory;

    /*
        The memory_size is only required if you pass
        a pointer to memory, otherwise you can set this
        to a negative value such as -1.
        Doing so will make the program understand that you
        didn't pass a memory pointer.
    */
    int memory_size;

    /*
        The code is always required, and it's what will be
        interpreted by the function itself.
    */
    const char *code;

    /*
        The output is a `char *` that stores the current memory
        address when the `.` instruction is used in the brainfuck
        code.

        The output should be big enough to store all the printed
        data, the output can also be null and stdout will be used
        instead.

        The function will automatically
        NULL terminate it with a '\0' as per the C standard on
        strings.

        This pointer will be moved, so make sure to store a
        copy.
    */
    unsigned char *output;

    /*
        If this boolean value is set to <true>,
        the error will be returned instead of thrown.
    */
    bool return_error;

    /*
        Set the prefix for the input instruction,
        by default when the code is waiting for an input
        character, you won't get notified.

        To get notified, set the input_prefix which will be
        printed every time an `,` in the brainfuck code, and
        before the input instruction.

        You can set it to NULL, so no prefix prints
        before input.
    */
    const char *input_prefix;

    /*
        If set to true, this waits for the program
        to finish before any stdout if this is false,
        the output will be printed directly when the
        instruction `.` is found.
    */
    bool defer_output;

} bfptr_context;
```

This structure acts as a context for your brainfuck execution,
now, the `brainfuck_on_ctx` function has the following signature:

```c
bfptr_exception *brainfuck_on_ctx(bfptr_context ctx);
```

The function returns a `bfptr_exception` pointer which is null
on two cases, there was no error or the return_error option
is disabled, which will lead to the program exiting with code `-1`.

if there was an error and the return_error is true in the context
an instance of `bfptr_exception` is returned, this instance
must be freed after consumption by using `free()` on the result.

The structure looks like this in the `bfptr.h` file

```c
typedef union {

    /*
        The error code, you can check
        the definitions in the documentation
        of <bfptr_error_code>
    */
    bfptr_error_code code;

    /*
        A more specific reason for the error.
    */
    char *reason;

} bfptr_exception;
```

The `bfptr_error_code` is an enum which acts as a generic error
definition, the values are the following: 


> Invalid parameters were passed to
> the execution context.
> 
>    `BFPTR_INVALID_PARAMETERS = 1 << 0`

> Invalid or badly formatted brainfuck
> most probably an unclosed loop.
> 
> `BFPTR_CODE_ERROR = 1 << 1`


> Generic allocation error, not enough
> space for an internal pointer allocation
> or the memory itself if managed.
>
> `BFPTR_MEMORY_ERROR = 1 << 2`

### brainfuck

The `brainfuck` function has the following signature

```c
bfptr_exception *brainfuck(char *code);
```

The `code` parameter is the code to be run, delimited by `\0` as
per the C standard.

This function runs `brainfuck_on_ctx` with a default context, which
is the following

```c
(bfptr_context){
    .memory = NULL, // a default 30000 position array that's freed automatically.
    .memory_size = -1, // no size override specified for the context.
    .output = NULL, // stdout as default.
    .return_error = false, // will throw on error.
    .code = code, // the parameter you passed as code.
    .defer_output = true, // will wait for stdin before output.
    .input_prefix = NULL // nothing is printed before input.
}; 
```

## Good to know

You have more information on the code comments, hovering the mouse
over the function names. This library is not maintained as it's just made
as a joke, so if you have any issue, I might or might not see it.