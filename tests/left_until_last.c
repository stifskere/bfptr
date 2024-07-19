
#include <stdlib.h>
#include <bfptr.h>

int main() {
    unsigned char *memory = (unsigned char *)malloc(2);
    unsigned char *memory_f = memory;
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

    free(memory_f);

    if (error != NULL)
        free(error);

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}