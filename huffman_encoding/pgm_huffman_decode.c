// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

// Main program to encode a pgm image.

// Include header files
#include "libpnm.h"
#include "read_huffman_encoded_data.h"
#include "huffman_decode_image.h"


// Function that validates the command line inputs from the user
int validateArguments(int argc, char *argv[]){
    // Check if there are the correct number of arguments
    printf("Number of arguments: %d\n", argc);
    if(argc != 3){
        printf("Error: Incorrect number of arguments.\n");
        printf("Usage: %s <image_compressed_file_name> <image_output_file_name>\n", argv[0]);
        return 1;
    }
    return 0;
}

// Main function to run the program
int main(int argc, char *argv[]) {

    printf("In Main\n");
    // Validate arguments
    if(!validateArguments(argc, argv)){
        printf("All arguments are valid.\n");
    }else{
        return 0;
    }

    // Initialize variables
    int image_width;
    int image_height;
    int max_gray_value;
    int number_of_nodes;
    struct node *node_array;
    long int length_of_encoded_image_array;

    printf("variables initialized\n");
    
    // Read the encoded data
    unsigned char *encoded_image = read_huffman_encoded_data(argv[1], &image_width, &image_height, &max_gray_value, &number_of_nodes, &node_array, &length_of_encoded_image_array);

    printf("\nGenerated Huffman Nodes:\n");
    for (int i = 0; i < number_of_nodes; i++) {
        printf("Node %d: Left = %d, Right = %d\n", i + 1, node_array[i].left_value, node_array[i].right_value);
    }


    //print_encoded_image(encoded_image, length_of_encoded_image_array);

    // Decode image data
    struct PGM_Image *decompressed_pgm_image = huffman_decode_image(image_width, image_height, max_gray_value, number_of_nodes, node_array, length_of_encoded_image_array, encoded_image);

    printf("Height: %d\n",decompressed_pgm_image->height);
    // Store decoded image
    save_PGM_Image(decompressed_pgm_image, argv[2], true);

    return 0;
}