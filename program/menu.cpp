#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archiver.h"
#include "adaptive_huffman.h"


int main(int argc, char* argv[]) {
    if (strcmp("arc", argv[1]) == 0) {
        archivate(argv[2], argv[3]);
    }
    else if (strcmp("unarc", argv[1]) == 0) {
        unarchivate(argv[2], argv[3]);
    }
    return 0;
}