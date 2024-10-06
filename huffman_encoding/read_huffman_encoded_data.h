// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

#ifndef READ_HUFFMAN_ENCODED_DATA_H
#define READ_HUFFMAN_ENCODED_DATA_H

#include <stdio.h>
#include <stdlib.h>

// Define a structure for Huffman tree nodes
struct node {
    int left_value;
    int right_value;
};

// Function prototype to read encoded data from file
unsigned char *read_huffman_encoded_data(char *compressed_file_name_ptr, int *image_width, int *image_height, int *max_gray_value, int *number_of_nodes, struct node **huffman_node, long int *length_of_encoded_image_array);

#endif /* READ_HUFFMAN_ENCODED_DATA_H */
