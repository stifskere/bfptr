#include <bfptr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT(condition, name) \
    printf("%d. ", test++); \
    if (!condition) { fprintf(stderr, name " - FAILED.\n"); exit(-1); } \
    else { printf(name " - SUCCEEDED.\n"); }

int test = 0;

bool increment_first() {
    unsigned char *memory = (unsigned char *)malloc(1);
    *memory = 0;

    bfptr_exception *error = brainfuck_on_ctx((bfptr_context){
            .memory = memory,
            .memory_size = 1,
            .output = NULL,
            .return_error = true,
            .code = "+++++",
            .defer_output = false,
            .input_prefix = NULL
    });

    bool success = *memory == 5 && error == NULL;

    free(memory);

    if (error != NULL)
        free(error);

    return success;
}

bool right_until_first() {
    unsigned char *memory = (unsigned char *)malloc(2);
    for (int i = 0; i < 2; i++) memory[i] = 0;

    bfptr_exception *error = brainfuck_on_ctx((bfptr_context){
            .memory = memory,
            .memory_size = 2,
            .output = NULL,
            .return_error = false,
            .code = "+>>",
            .defer_output = false,
            .input_prefix = NULL
    });

    bool success = *memory == 1 && error == NULL;

    free(memory);

    if (error != NULL)
        free(error);

    return success;
}

bool left_until_last() {
    unsigned char *memory = (unsigned char *)malloc(2);
    unsigned char *mem_f = memory;
    for (int i = 0; i < 2; i++) memory[i] = 0;

    bfptr_exception *error = brainfuck_on_ctx((bfptr_context){
            .memory = memory,
            .memory_size = 2,
            .output = NULL,
            .return_error = false,
            .code = "<+>>",
            .defer_output = false,
            .input_prefix = NULL
    });

    bool success = memory[1] == 1 && error == NULL;

    free(mem_f);

    if (error != NULL)
        free(error);

    return success;
}

bool hello_world() {
    unsigned char *output = (unsigned char *)malloc(14);
    unsigned char *output_f = output;

    bfptr_exception *error = brainfuck_on_ctx((bfptr_context){
            .memory = NULL,
            .memory_size = -1,
            .output = output,
            .return_error = false,
            .code = "-[------->+<]>-.-[->+++++<]>++.+++++++..+++.[--->+<]>-----."
                    "---[->+++<]>.-[--->+<]>---.+++.------.--------.-[--->+<]>.",
            .defer_output = false,
            .input_prefix = NULL,
    });

    bool success = strcmp((const char *)output_f, "Hello World!") == 0 && error == NULL;

    free(output_f);

    if (error != NULL)
        free(error);

    return success;
}

int main() {
    ASSERT(increment_first(), "INCREMENT FIRST BY 5")
    ASSERT(right_until_first(), "GO RIGHT UNTIL START")
    ASSERT(left_until_last(), "GO LEFT UNTIL END")
    ASSERT(hello_world(), "PRINT HELLO WORLD!")
}