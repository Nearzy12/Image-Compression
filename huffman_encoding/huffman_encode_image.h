// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

#ifndef HUFFMAN_ENCODE_IMAGE_H
#define HUFFMAN_ENCODE_IMAGE_H

#include "libpnm.h"
#include "generate_huffman_nodes.h"

// Define the struct code
struct code
{
    int pixel_value;
    int length;
    unsigned int code;
};


// Function prototypes
unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int number_of_nodes, long int *length_of_encoded_image_array);


#endif /* HUFFMAN_ENCODE_IMAGE_H */
