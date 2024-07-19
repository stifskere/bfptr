
#include <stdlib.h>
#include "../../CTests/lib/bfptr.h"

int main() {
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

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}