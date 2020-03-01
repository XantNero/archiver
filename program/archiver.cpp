#include <stdlib.h>
#include <stdio.h>
#include "adaptive_huffman.h"

void archivate(char* file_name, char* archive_name) {
    FILE* input_file, *output_file;
    huffman_tree* root;
    huffman_tree** array;
    input_file = fopen(file_name, "rt");
    if(!input_file) {
        printf("Cant open file\n");
        return;
    }
    char symbol;
   

    root = initialize_tree(BYTE_SIZE, NULL);
    array = make_array(root);

    int count = 0;
    char code[16];
    char coded_letter[8];
    int last = 0;
    rewind(input_file);
    //char extension[] = {".bin"};
    //archive_name = (char*)realloc(archive_name, strlen(archive_name) + strlen(extension) + 1);
    //char* temp;
    //temp = archive_name + strlen(archive_name);
    //strcpy(temp, extension);

    output_file = fopen(archive_name, "wb");
    if (!output_file) {
        fclose(input_file);
        printf("Cant create archive file\n");
        return;
    }

    symbol = fgetc(input_file);
    while (!feof(input_file)) {
        count = 0;
        get_code(count, code, array[find_symbol_leaf(array, symbol)]);
        for (last, count--; last < 8 && count >= 0; ++last, --count) {
            coded_letter[last] = code[count];
        }
        while (last == 8) {
            unsigned char letter = 0;
            for (int i = 1, j = 7; j >= 0; i *= 2, --j) 
                 letter += i * coded_letter[j];
            fwrite(&letter, sizeof(unsigned char), 1, output_file);
            for (last = 0; last < 8 && count >= 0; ++last, --count) {
                coded_letter[last] = code[count];
            }
        }
        change_tree(array, find_symbol_leaf(array, symbol));
        symbol = fgetc(input_file);   
    }
    fclose(input_file);
    fclose(output_file);
}

