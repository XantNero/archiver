#define BYTE_SIZE 256

struct field {
    unsigned int skip: 7;
    unsigned int i : 1;
};

struct huffman_tree {
    unsigned char symbol;
    unsigned int weight;
    int index;
    huffman_tree *left, *right, *parent;
};

huffman_tree* initialize_tree(int count, huffman_tree* p);
void func(huffman_tree* root, int height, huffman_tree* array[], huffman_tree* hash[]);
void swap(huffman_tree** array, int a, int b);
int find_next(huffman_tree** array, int start_index);
huffman_tree** make_array(huffman_tree* root, huffman_tree* hash[]);
void change_tree(huffman_tree** array, int index);
int find_symbol_leaf(huffman_tree** array, unsigned char symbol);
huffman_tree* unarchive_symbol(unsigned char& letter, int& count, huffman_tree* root);
void get_code(int& count, char code[], huffman_tree* tree);