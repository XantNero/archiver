#include <stdlib.h>
#include <stdio.h>
#include "adaptive_huffman.h"


void unarchivate(char* archive_name, char* unarchive_name) {
    FILE *input_file, *output_file, *f;
    //char extension[] = {".bin"};
    // archive_name = (char*)realloc(archive_name, strlen(archive_name) + strlen(extension) + 1);
    // char* temp;
    // temp = archive_name + strlen(archive_name);
    // strcpy(temp, extension);
    input_file = fopen(archive_name, "rb");
    if(!input_file) {
        printf("ere\n");
         exit(0);
    }
       
    output_file = fopen(unarchive_name, "wt");
    if (!output_file) {
        fclose(input_file);
        printf("ere\n");
        exit(0);
    }
    huffman_tree* root = initialize_tree(BYTE_SIZE, NULL);
    huffman_tree* tree;
    huffman_tree** array = make_array(root);
    int count = 0;
    tree = array[find_symbol_leaf(array, 0)];
    unsigned char symb;
    do  {
        
        if (feof(input_file))
            break;
        if (count == 0 && tree->left != NULL && tree->right != NULL) {
            count = 8;
            fread(&symb, sizeof(unsigned char), 1, input_file);
            tree = unarchive_symbol(symb, count, tree);
            
        }
        else if (count == 0) {
             count = 8;
             fread(&symb, sizeof(unsigned char), 1, input_file);
             tree = unarchive_symbol(symb, count, root);
        }   
        else {  
            tree = unarchive_symbol(symb, count, root);
       }
            
        if (tree->left == NULL && tree->right == NULL) {
            fputc(tree->symbol, output_file);
            //putchar(tree->symbol);
            change_tree(array, find_symbol_leaf(array, tree->symbol));
        } 
    } while (!feof(input_file));
    fclose(input_file);
    fclose(output_file);
   
}

