
#include <stdlib.h>
#include <bfptr.h>
#include <string.h>

int main() {
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

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}