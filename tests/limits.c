
#include <stdlib.h>
#include <bfptr.h>

int main() {
    unsigned char *memory = (unsigned char *)malloc(1);
    *memory = 0;

    bfptr_exception *error = brainfuck_on_ctx((bfptr_context){
            .memory = memory,
            .memory_size = 1,
            .output = NULL,
            .return_error = true,
            .code = "-+",
            .defer_output = false,
            .input_prefix = NULL
    });

    bool success = *memory == 0 && error == NULL;

    free(memory);

    if (error != NULL)
        free(error);

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}