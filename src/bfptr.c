#include "../include/bfptr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THROW_BFPTR_EXCEPTION(t_code, t_reason) \
    if (context.return_error) { \
        bfptr_exception *ex_mem = \
            (bfptr_exception *)malloc(sizeof(bfptr_exception)); \
        \
        ex_mem->code = t_code; \
        ex_mem->reason = t_reason; \
        \
        return ex_mem; \
    } else { \
        printf("BRAINFUCK " #t_code " EXCEPTION: " t_reason); \
        exit(-1); \
    }


ATTR_UNUSED bfptr_exception *brainfuck_on_ctx(bfptr_context context) {
    bool ctx_has_memory = context.memory != NULL;

    if (!ctx_has_memory) {
        if (context.memory_size > 0) {
            THROW_BFPTR_EXCEPTION(
                BFPTR_INVALID_PARAMETERS,
                "memory_size is set for NULL memory."
            )
        }

        context.memory = (unsigned char *)malloc(30000);
        memset(context.memory, 0, 30000);
    } else if (context.memory_size <= 0) {
        THROW_BFPTR_EXCEPTION(
            BFPTR_INVALID_PARAMETERS,
            "memory_size is not set for non NULL memory."
        )
    }

    int loop_count = 0;
    int loop_check = 0;
    int dot_count = 0;

    for (const char *copy = context.code; *copy != '\0'; copy++) {
        if (*copy == ']') {
            if (loop_check <= 0) {
                THROW_BFPTR_EXCEPTION(
                    BFPTR_CODE_ERROR,
                    "Loop ending was found before any loop start."
                )
            }

            loop_check--;
        }

        if (*copy == '[') {
            loop_count++;
            loop_check++;
        }

        if (*copy == '.')
            dot_count++;
    }

    if (loop_check != 0) {
        THROW_BFPTR_EXCEPTION(
            BFPTR_CODE_ERROR,
            "Loop endings do not match with loop starts."
        )
    }

    unsigned char *f_ptr = context.memory;

    unsigned char *defer_output_buffer = NULL;

    if (dot_count > 0 && context.defer_output)
        defer_output_buffer = (unsigned char *)malloc(dot_count);

    unsigned char *f_defer_output_buffer = defer_output_buffer;

    int *loop_idx_stack = malloc(sizeof(int) * loop_count);
    int stack_top = 0;

    if (loop_idx_stack == NULL) {
        THROW_BFPTR_EXCEPTION(
            BFPTR_MEMORY_ERROR,
            "Failed to allocate loop stack."
        )
    }

    unsigned long code_len = strlen(context.code);
    for (int i = 0; i < code_len; i++) {
        switch (context.code[i]) {
            case '+':
                (*context.memory)++;
                break;
            case '-':
                (*context.memory)--;
                break;
            case '<':
                context.memory = (
                    context.memory == f_ptr
                        ? f_ptr + context.memory_size - 1
                        : context.memory - 1
                );
                break;
            case '>':
                context.memory = (
                    context.memory == f_ptr + context.memory_size - 1
                        ? f_ptr
                        : context.memory + 1
                );
                break;
            case '[':
                loop_idx_stack[stack_top++] = i + 1;
                break;
            case ']':
                if (*context.memory != 0)
                    i = loop_idx_stack[stack_top - 1] - 1;
                else
                    stack_top--;
                break;
            case '.':
                if (context.defer_output) {
                    if (defer_output_buffer != NULL)
                        *(defer_output_buffer++) = *context.memory;
                }
                else if (context.output == NULL)
                    putchar(*context.memory);
                else
                    *(context.output++) = *context.memory;
                break;
            case ',':
                if (context.input_prefix != NULL)
                    printf("%s", context.input_prefix);

                int ch = getchar();

                if (ch == EOF) {
                    free(loop_idx_stack);

                    if (defer_output_buffer != NULL)
                        free(defer_output_buffer);

                    THROW_BFPTR_EXCEPTION(
                        BFPTR_MEMORY_ERROR,
                        "Error occurred while running ',' instruction."
                    )
                }

                *context.memory = (char)ch;
                break;
        }
    }

    if (defer_output_buffer != NULL)
        *defer_output_buffer = '\0';

    free(loop_idx_stack);

    if (!ctx_has_memory)
        free(f_ptr);

    if (f_defer_output_buffer != NULL) {
        if (context.output == NULL)
            printf("%s", f_defer_output_buffer);
        else
            for (unsigned char *cpy = f_defer_output_buffer; *cpy != '\0'; cpy++)
                *(context.output++) = *cpy;

        free(f_defer_output_buffer);
    }

    if (context.output != NULL)
        *context.output = '\0';

    return NULL;
}


ATTR_UNUSED void brainfuck(const char *code) {
    brainfuck_on_ctx((bfptr_context){
        .memory = NULL,
        .memory_size = -1,
        .output = NULL,
        .return_error = false,
        .code = code,
        .defer_output = true,
        .input_prefix = NULL
    });
}