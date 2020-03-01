#include "adaptive_huffman.h"
#include <stdlib.h>

huffman_tree* initialize_tree(int count, huffman_tree* p) {
    static short int number;
    if (number == BYTE_SIZE)
        number = 0;
    huffman_tree* root;
    root = (huffman_tree*)malloc(1 * sizeof(huffman_tree));
    if (!root)
        exit(0);
    root->weight = count;
    root->parent = p;
    if (count == 1) {
        root->symbol = (char)number;
        root->left = NULL;
        root->right = NULL;
        number++;
        return root;
    }
    root->left = initialize_tree(count / 2, root);
    root->right = initialize_tree(count / 2, root);
    return root;
}
void func(huffman_tree* root, int height, huffman_tree* array[]) {
    static int index = 510;
    if (index == -1)
        index = 510;
    if (height == 1) {
    
        array[index--] = root;
        return;
    } 
    func(root->right, height - 1, array);
    func(root->left, height - 1, array);
}

huffman_tree** make_array(huffman_tree* root) {
    huffman_tree** array;
    array = (huffman_tree**)malloc(511 * sizeof(huffman_tree*));
    for (int i = 1; i <= 9; i++) {
        func(root, i, array);
    } 
    return array;
}



void swap(huffman_tree** array, int a, int b) {
    if (array[a]->parent->left == array[a])
        array[a]->parent->left = array[b];
    else 
        array[a]->parent->right = array[b];
    if (array[b]->parent == NULL)
        ;
    else if (array[b]->parent->left == array[b])
        array[b]->parent->left = array[a];
    else 
        array[b]->parent->right = array[a];
    
    huffman_tree* tmpr = array[a]->parent;
    array[a]->parent = array[b]->parent;
    array[b]->parent = tmpr;
    
    tmpr = array[a];
    array[a] = array[b];
    array[b] = tmpr;
}

int find_next(huffman_tree** array, int start_index) {
    if (start_index == 510)
        return start_index;
    for (int i = start_index  + 1; i <= 510; ++i) {
        if (array[start_index]->parent == array[i])
            return i;
    }
    return -1;
}

void change_tree(huffman_tree** array, int index) {
    int i;
    array[index]->weight++;
    if (index == 510)
        return;
    for (i = index + 1; i <= 510; ++i) {
        if (array[index]->weight - 1 != array[i]->weight)
            break;
    }
    if (array[index]->weight - 1 == array[i - 1]->weight) {
        swap(array, index, i - 1);
        index = i - 1;
    }
    
    change_tree(array, find_next(array, index));
}

int find_symbol_leaf(huffman_tree** array, unsigned char symbol) {
    for (int i = 0; i <= 510; ++i)
        if (array[i]->symbol == symbol)
            return i;
    return -1;
}

void get_code(int& count, char code[], huffman_tree* tree) {
    do {
        if (tree->parent-> right == tree) 
            code[count++] = 1;
        else 
            code[count++] = 0; 
        tree = tree->parent;
    } while (tree->parent != NULL);
}

huffman_tree* unarchive_symbol(unsigned char& letter, int& count, huffman_tree* root) {
    while (root->left != NULL && root->right != NULL && count) {
        field* fl;
        fl = (field*)&letter;
        if (fl->i)
            root = root->right;
        else 
            root = root->left;
        letter <<= 1;
        count--;
    }
    return root;
}