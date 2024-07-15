#ifndef BFPTR_BFPTR_H
#define BFPTR_BFPTR_H

/*
    This function sets the prefix for the brainfuck "," instruction.

    By default, when you use "," in your brainfuck code, the thread
    stops waiting for a character to be introduced.

    To make this clearer, you can set a prefix with this function.

    If you do not run this function, the prefix by default will be "".

    If you want a line break before each input, you will need to use this
    function to set it.

    @param char *prefix:
        The prefix to set for your input instructions.
*/
__attribute__((unused)) void brainfuck_input_prefix(char *prefix);

/*
    This function runs brainfuck on an existing pointer,
    it modifies the passed pointer according to the brainfuck
    code you passed.

    You'd usually use this if you want to manage your
    code with brainfuck, but please don't do this
    in any serious application.

    You are in charge of allocating and freeing the pointer,
    you define memory size.

    @param void *ptr:
        The pointer to run the code on, internally treated
        as <unsigned char *>.

    @param int limit:
        The bounds of the pointer, when the current pointer
        points over the limit, it goes back to 0, if it points
        under 0 it goes to the limit again, as per the brainfuck
        rules.

    @param char *code:
        The code to run on the previously provided
        pointer.

    @exception CODE_ERROR:
        There are non-matched loops ([]) in your brainfuck
        code.

    @exception MEMORY_ERROR:
        An error occurred while allocating memory for the
        loop stack.

    Learn how brainfuck works:
        https://gist.github.com/roachhd/dce54bec8ba55fb17d3a
*/
__attribute__((unused)) void brainfuck_on_ptr(void *ptr, int limit, char *code);

/*
    This function runs brainfuck on a managed pointer,
    it allocates a 30000-byte pointer and runs the
    provided code on it.

    You'd usually use this function to process
    brainfuck standalone and see its output.

    The function allocates and frees the pointer
    automatically, and it evaluates the code
    using brainfuck_on_ptr.

    @param char *code:
        The code to run on the managed pointer.

    @exception CODE_ERROR:
        There are non-matched loops ([]) in your brainfuck
        code.

    @exception MEMORY_ERROR:
        An error occurred while allocating memory for
        either the loop stack or the managed pointer.

    Learn how brainfuck works:
        https://gist.github.com/roachhd/dce54bec8ba55fb17d3a
*/
__attribute__((unused)) void brainfuck(char *code);

#endif
