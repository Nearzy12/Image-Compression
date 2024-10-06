// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

#include "read_huffman_encoded_data.h"

// Read encoded data from file given a file name
unsigned char *read_huffman_encoded_data(char *compressed_file_name_ptr, int *image_width, int *image_height, int *max_gray_value, int *number_of_nodes, struct node **huffman_node, long int *length_of_encoded_image_array){

    FILE *compressed_file;

    // Open the file for reading
    compressed_file = fopen(compressed_file_name_ptr, "r");

    // Check if the file is ready to write too and was opened correctly
    if (compressed_file == NULL) {
        printf("Error opening file!\n");
    }

    // Read all the single value parameters from the file
    fscanf(compressed_file, "%d", image_width);
    fscanf(compressed_file, "%d", image_height);
    fscanf(compressed_file, "%d", max_gray_value);
    fscanf(compressed_file, "%d", number_of_nodes);

    printf("Width: %d\n", *image_width);
    printf("Height: %d\n", *image_height);
    printf("Max_Gray: %d\n", *max_gray_value);
    printf("Number of Nodes: %d\n", *number_of_nodes);

    // Allocate memory to srote huffman nodes
    struct node *node_array = malloc(*number_of_nodes * sizeof(struct node));

    // Loop through all the huffman nodes and read them from file
    for(int i = 0; i < *number_of_nodes; i++){
        fscanf(compressed_file, "%d", &node_array[i].left_value);
        fscanf(compressed_file, "%d", &node_array[i].right_value);
        printf("Node %d: Left = %d, Right = %d\n", i + 1, node_array[i].left_value, node_array[i].right_value);
    }

    // We need to red the length of the encoded file so we can allocate the correct memory
    fscanf(compressed_file, "%ld", length_of_encoded_image_array);
    printf("%ld\n", *length_of_encoded_image_array);

    // Allocate memory for the encoded image
    unsigned char *encoded_image = malloc(*length_of_encoded_image_array * sizeof(unsigned char));
    fseek(compressed_file, 2, SEEK_CUR);

    // Read the data from the encoded file
    fread(encoded_image, 1, *length_of_encoded_image_array, compressed_file);

    // Close file and return encoded image data
    fclose(compressed_file);

    // Have the huffman nodes point to the right data!
    *huffman_node = node_array;

    return encoded_image;

}