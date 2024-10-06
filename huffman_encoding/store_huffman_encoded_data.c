// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

#include "store_huffman_encoded_data.h"
#include <stdio.h>

// Stores Huffman encoding data to file
void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned  char *encoded_image){

    // Create a file and write to it
    FILE *compressed_file;

    // Open the file using the file name in function parameter
    compressed_file = fopen(compressed_file_name_ptr, "w");

    // Check if the file is ready to write too and was opened correctly
    if (compressed_file == NULL) {
        printf("Error opening file!\n");
    }

    // Print all the single value parameters to the file
    fprintf(compressed_file, "%d\n", image_width);
    fprintf(compressed_file, "%d\n", image_height);
    fprintf(compressed_file, "%d\n", max_gray_value);
    fprintf(compressed_file, "%d\n", number_of_nodes);

    // Loop through all the huffman nodes and save them to the file
    for(int i = 0; i < number_of_nodes; i++){
        fprintf(compressed_file, "%d %d\n", huffman_node[i].left_value, huffman_node[i].right_value);
    }

    fprintf(compressed_file, "%ld\n", length_of_encoded_image_array);

    // Save the encoded image
    fwrite(encoded_image, sizeof(unsigned char), length_of_encoded_image_array, compressed_file);
    
    // Close the file to end the program
    fclose(compressed_file);
}