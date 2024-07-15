#include "../include/bfptr.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef BF_EXCEPTION
    #undef BF_EXCEPTION
#endif

#define BF_EXCEPTION(code, reason) \
    printf(code " BRAINFUCK ERROR: " reason); \
    exit(-1)

__attribute__((unused)) void brainfuck_on_ptr(void *ptr, int limit, char *code) {
    int loop_count = 0;
    int loop_check = 0;
    for (char *copy = code; *copy != '\0'; copy++) {
        if (*copy == ']')
            loop_check--;

        if (*copy == '[') {
            loop_count++;
            loop_check++;
        }
    }

    if (loop_check != 0) {
        BF_EXCEPTION("CODE_ERROR", "Loops don't match.");
    }

    unsigned char *first_mem = ptr;
    unsigned char *mem = ptr;

    int *loop_idx_stack = malloc(sizeof(int) * loop_count);
    int stack_top = 0;

    if (loop_idx_stack == (void *)0) {
        BF_EXCEPTION("MEMORY_ERROR", "Failed to allocate loop stack.");
    }

    int code_len = 0;
    for (char *copy = code; *copy != '\0'; copy++, code_len++);
    for (int i = 0; i < code_len; i++) {
        if (code[i] == '+')
            (*mem)++;
        else if (code[i] == '-')
            (*mem)--;
        else if (code[i] == '<')
            mem = (unsigned char *)((long)mem <= (long)first_mem ? (long)first_mem + (limit - 1) : (long)mem - 1);
        else if (code[i] == '>')
            mem = (unsigned char *)((long)mem >= (long)first_mem + (limit - 1) ? (long)first_mem : (long)mem + 1);
        else if (code[i] == '[') {
            loop_idx_stack[stack_top++] = i + 1;
        } else if (code[i] == ']') {
            if (*mem != 0)
                i = loop_idx_stack[stack_top - 1] - 1;
            else
                stack_top--;
        }
        else if (code[i] == '.')
            putchar(*mem);
        else if (code[i] == ',')
            *mem = (char)getchar();
    }

    free(loop_idx_stack);
}

__attribute__((unused)) void brainfuck(char *code) {
    unsigned char *mem = (unsigned char *)malloc(30000);

    if (mem == (void *)0) {
        BF_EXCEPTION("MEMORY_ERROR", "Couldn't allocate 30000 bytes for memory pointer.");
    }

    for (int i = 0; i < 30000; i++)
        mem[i] = 0;

    brainfuck_on_ptr(mem, 30000, code);

    free(mem);
}