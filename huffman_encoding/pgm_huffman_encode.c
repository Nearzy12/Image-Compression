// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

// Main program to encode a pgm image.

// Include header files
#include "libpnm.h"
#include "generate_pixel_frequency.h"
#include "generate_huffman_nodes.h"
#include "huffman_encode_image.h"
#include "store_huffman_encoded_data.h"

// Function that validates the command line inputs from the user
int validateArguments(int argc, char *argv[]){
    // Check if there are the correct number of arguments
    if(argc != 3){
        printf("Error: Incorrect number of arguments.\n");
        printf("Usage: %s <image_input_file_name> <image_compressed_file_name>\n", argv[0]);
        return 1;
    }
    return 0;
}

// Main function to run the program
int main(int argc, char *argv[]) {
  
    // Save input file name
    char *input_file_name = argv[1];
    // Create a PGM image structure
    struct PGM_Image pgm_image;
    // Creates location for number of none zero elements in frequency array once it gets created.
    int *number_of_non_zero_values;
    number_of_non_zero_values = (int *)malloc(sizeof(int));
    *number_of_non_zero_values = 0;


    // Validate arguments
    if(!validateArguments(argc, argv)){
        // printf("All arguments are valid.\n");
    }else{
        return 0;
    }

    // Load image from file
    load_PGM_Image(&pgm_image, input_file_name);
    printf("Loaded image from file\n");

    int max_gray_value = pgm_image.maxGrayValue;

    // Pointer to long int array holding all the frequency of each pixel value - Q1
    long int *frequency_array = generate_pixel_frequency(&pgm_image, number_of_non_zero_values);
    printf("Generated frequency array\n");

    // Printing the array - for testing! remove from final
    int array_size = pgm_image.maxGrayValue + 1;
    // printf("number of non zero values: %d \n", *number_of_non_zero_values);
    // for (int i = 0; i < array_size; i++) {
    //     printf("index: %d  value: %ld \n", i, frequency_array[i]);
    // }
    
    // Generate the huffman nodes - Q2
    struct node *node_array = generate_huffman_nodes(frequency_array, max_gray_value, *number_of_non_zero_values);

    // Output the generated Huffman nodes
    printf("\nGenerated Huffman Nodes:\n");
    for (int i = 0; i < *number_of_non_zero_values - 1; i++) {
        printf("Node %d: Left = %d, Right = %d\n", i + 1, node_array[i].left_value, node_array[i].right_value);
    }

    printf("    Number of non zero values: %d \n", *number_of_non_zero_values);

    printf("Generated Huffman nodes\n");

    int number_of_huffman_nodes;
    if(*number_of_non_zero_values == 1){
        number_of_huffman_nodes = *number_of_non_zero_values;
    }else{
        number_of_huffman_nodes = *number_of_non_zero_values -1;
    }
    unsigned long int length_of_encoded_array = 0;
    // Encode image using the generated huffman nodes - Q3
    unsigned char *encoded_image_data = huffman_encode_image(&pgm_image, node_array, number_of_huffman_nodes, &length_of_encoded_array);

    printf("Encoded image data completed\n");
    // Save the encoded image to file using compressed file name - Q4
    store_huffman_encoded_data(argv[2], pgm_image.width, pgm_image.height, pgm_image.maxGrayValue, number_of_huffman_nodes, node_array, length_of_encoded_array, encoded_image_data);

    // Free the dynamically allocated memory
    free(number_of_non_zero_values);
    free(frequency_array);
    free_PGM_Image(&pgm_image);
    free(node_array);

    return 0;
}

// int main(int argc, char *argv[]) {
//     // Example test variables
//     struct PGM_Image input_pgm_image;

//     create_PGM_Image(&input_pgm_image, 10,1,5);

//     input_pgm_image.image[0][0] = 4;
//     input_pgm_image.image[0][1] = 0;
//     input_pgm_image.image[0][2] = 0;
//     input_pgm_image.image[0][3] = 4;
//     input_pgm_image.image[0][4] = 1;
//     input_pgm_image.image[0][5] = 5;
//     input_pgm_image.image[0][6] = 2;
//     input_pgm_image.image[0][7] = 0;
//     input_pgm_image.image[0][8] = 0;
//     input_pgm_image.image[0][9] = 3;

//     int number_of_nodes = 5; // Example number of nodes

//     long int length_of_encoded_image_array = 0;

//     // Create a temporary array of nodes
//     struct node *huffman_node = malloc(number_of_nodes * sizeof(struct node));
//     if (huffman_node == NULL) {
//         printf("Memory allocation failed\n");
//         return 1; // Return with an error code
//     }

//     // Initialize the nodes with some example data
//     huffman_node[0].left_value = 3;
//     huffman_node[0].right_value = 5; 

//     huffman_node[1].left_value = 1;
//     huffman_node[1].right_value = 3; 

//     huffman_node[2].left_value = 2;
//     huffman_node[2].right_value = 4; 

//     huffman_node[3].left_value = 1;
//     huffman_node[3].right_value = 2; 

//     huffman_node[4].left_value = 0;
//     huffman_node[4].right_value = 1; 

//     // Call huffman_encode_image function
//     unsigned char *encoded_image = huffman_encode_image(&input_pgm_image, huffman_node, number_of_nodes, &length_of_encoded_image_array);

//     // Print some information or perform further tests
//     // print_encoded_image(encoded_image, length_of_encoded_image_array);

//     store_huffman_encoded_data(argv[2], input_pgm_image.width, input_pgm_image.height, input_pgm_image.maxGrayValue, number_of_nodes, huffman_node, length_of_encoded_image_array, encoded_image);

//     // Free dynamically allocated memory
//     free(encoded_image);
//     free(input_pgm_image.image); // Assuming you have dynamically allocated image data
//     free(huffman_node);

//     return 0;
// }
