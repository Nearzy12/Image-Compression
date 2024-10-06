// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

#include <stdio.h>
#include <stdlib.h>

#ifndef HUFFMAN_DECODE_IMAGE_H
#define HUFFMAN_DECODE_IMAGE_H

#include "libpnm.h"
#include "read_huffman_encoded_data.h"

// Structure definition for huffman_tree_node
struct huffman_tree_node {
    int left_node;
    int right_node;
    int pixel_value;
};

// Returns the index of the tree where the passed value is, returns -1 if the value wasn't found in the tree
int get_index_of_value_in_tree(struct huffman_tree_node *huffman_tree, int tree_size, int value);

// Returns the index of the next open space for a node to be put into tree.
int get_index_of_empty_location_in_tree(struct huffman_tree_node *huffman_tree, int tree_size);

// Read a bit at bit_location from data
int read_bit_at_location(unsigned char *encoded_image, long int bit_location);

void print_binary(unsigned char byte);

void print_encoded_image(unsigned char *encoded_image_data, long int length_in_bytes);

// Program that decodes an huffman encoded pgm image from file
struct PGM_Image *huffman_decode_image(int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *node_array, long int length_of_encoded_image_array, unsigned char *encoded_image);

#endif /* HUFFMAN_DECODE_IMAGE_H */
