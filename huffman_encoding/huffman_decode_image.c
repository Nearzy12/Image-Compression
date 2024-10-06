// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024


#include "libpnm.h"
#include "huffman_decode_image.h"
#include "read_huffman_encoded_data.h"

void print_binary(unsigned char byte) {
    for (int i = 0; i < 8; i++) {
        printf("%d", (byte >> i) & 1);
    }
}

void print_encoded_image(unsigned char *encoded_image_data, long int length_in_bytes) {
    for (int i = 0; i < length_in_bytes; i++) {
        print_binary(encoded_image_data[i]);
        printf(" ");
    }
    printf("\n");
}

int print_tree(struct huffman_tree_node *huffman_tree, int tree_size){
    printf("========================================================\n");
    for(int i = 0; i < tree_size; i++){
        printf("Tree index: %d, pixel value: %d left_index: %d right_index: %d\n", i, huffman_tree[i].pixel_value, huffman_tree[i].left_node, huffman_tree[i].right_node);
    }
    printf("========================================================\n");
}

// Returns the index of the tree where the passed value is, returns -1 if the value wasn't found in the tree
int get_index_of_value_in_tree(struct huffman_tree_node *huffman_tree, int tree_size, int value){

    // Loop through the tree and return the index of the value in the tree
    for(int i = 0; i < tree_size; i++){
        if(huffman_tree[i].pixel_value == value){
            return i;
        }
    }
    return -1;
}

// Returns the index of the next open space for a node to be put into tree.
int get_index_of_empty_location_in_tree(struct huffman_tree_node *huffman_tree, int tree_size){

    // Loop through the tree and return the index of the value in the tree
    for(int i = 0; i < tree_size; i++){
        if(huffman_tree[i].pixel_value == -1 && huffman_tree[i].left_node == -1 && huffman_tree[i].right_node == -1){
            return i;
        }
    }
    return -1;
}

// Read a bit at bit_location from data
int read_bit_at_location(unsigned char *encoded_image, long int bit_location) {
    if (bit_location < 0) {
        printf("Error: Bit location cannot be negative\n");
        return -1; // or handle error in your application logic
    }

    long int byte_index = bit_location / 8;
    int bit_index = bit_location % 8;

    unsigned char byte = encoded_image[byte_index];
    // printf("bit locatio: %d byte: %d bit offset: %d\n", bit_location, byte, bit_index);
    return ((byte >> bit_index) & 1);
}

// Program that decodes an huffman encoded pgm image from file
struct PGM_Image *huffman_decode_image( int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *node_array, long int length_of_encoded_image_array, unsigned char *encoded_image){
    
    // Allocate memory for return image and create it
    struct PGM_Image *extracted_pgm_image = malloc(sizeof(struct PGM_Image));
    create_PGM_Image(extracted_pgm_image, image_width, image_height, max_gray_value);

    int number_of_symbols = 0;

    // Special case for when there is only 1 pixel value in the image
    if(number_of_nodes == 1){
        if(node_array[0].left_value == node_array[0].right_value){
            number_of_symbols = number_of_nodes;
        }
        else
        {
            number_of_symbols = number_of_nodes + 1;
        }
    }
    else
    {
        number_of_symbols = number_of_nodes + 1;
    }

    // This is the max tree size .. at most you would have number of internal nodes to match each leaf node plus the root
    int tree_size = number_of_nodes + number_of_nodes + 1;
    printf("Tree size: %d", tree_size);

    // Create an array of huffman_tree_node objects
    struct huffman_tree_node *huffman_tree = malloc((tree_size) * sizeof(struct huffman_tree_node));
    
    // Initialize the all the tree nodes to be -1
    for(int i = 0; i < tree_size; i++){
        huffman_tree[i].left_node = -1;
        huffman_tree[i].right_node = -1;
        huffman_tree[i].pixel_value = -1;
    }

    // Loop through from the last huffman node
    // initialize the tree pointers to point to the node
    // tree[0] is the root of the tree
    // value -2 will repersent the root node value
    int tree_index_of_first_value = 1;
    int tree_index_of_second_value = 2;

    int insert_location_for_first_huffman_value = 0;
    int insert_location_for_second_huffman_value = 0;

    int first_huffman_value = 0;
    int second_huffman_value = 0;

    // Set the root value to 2 so we don't add nodes to that location
    huffman_tree[0].pixel_value = -2;

    // Add the value from the first huffman node startgin with the left value to the tree
    // update tree values
    huffman_tree[tree_index_of_first_value].pixel_value = node_array[number_of_nodes-1].left_value;
    huffman_tree[tree_index_of_second_value].pixel_value = node_array[number_of_nodes-1].right_value;

    huffman_tree[0].left_node = 1;
    huffman_tree[0].right_node = 2;

    // loop though every node in the list of huffman nodes and add them to the root node, start from the end
    // skip last node as it was already added to set up algorithm, start from n-2
    for(int j = number_of_nodes-2; j >= 0; j--){
        
        // Initialize first and second huffman values
        first_huffman_value = node_array[j].left_value;
        second_huffman_value = node_array[j].right_value;
        // Step 1: find index location in the tree that is storing the first value in the huffman node.
        tree_index_of_first_value = get_index_of_value_in_tree(huffman_tree, tree_size, first_huffman_value);

        // Make that node an internal node, save the index
        huffman_tree[tree_index_of_first_value].pixel_value = -2; // set to internal

        // Now find the next location to add a new node to the tree
        insert_location_for_first_huffman_value = get_index_of_empty_location_in_tree(huffman_tree, tree_size);

        // Add first value at this new location
        huffman_tree[insert_location_for_first_huffman_value].pixel_value = first_huffman_value;

        // Update pointer and set the left value of the original internal node to be the location of this new node
        huffman_tree[tree_index_of_first_value].left_node = insert_location_for_first_huffman_value;

        // Get insert location for second huffman value in the node
        insert_location_for_second_huffman_value = get_index_of_empty_location_in_tree(huffman_tree, tree_size);

        // Add the second huffman node value at this location
        huffman_tree[insert_location_for_second_huffman_value].pixel_value = second_huffman_value;

        // Update the pointer and set the right value of the node to this new location
        huffman_tree[tree_index_of_first_value].right_node = insert_location_for_second_huffman_value;

        // print out the nodes
    }

    print_tree(huffman_tree, tree_size);

    // Now that we have the tree built lets loop though every pixel location and get the decoded pixel value from file
    int decoded_pixel_value = 0;
    long int bit_location = 0;
    int pixel_value;
    unsigned int bit_read;
    struct huffman_tree_node current_node;

    // print_encoded_image(encoded_image, length_of_encoded_image_array);

    for (int row = 0; row < image_height; row++){
        for (int col = 0; col < image_width; col++){
            // printf("row: %d col: %d\n", row, col);
            // Read the data at the current position
            
            current_node = huffman_tree[0];
            // printf("Current Node left child  Pixel Value: %d\n", huffman_tree[current_node.right_node].pixel_value);
            // While current leaf != -1
            while(current_node.left_node != -1 && current_node.right_node != -1){
                // printf("current node left value: %d current node right value %d\n", current_node.left_node, current_node.right_node);
                
                // Read a single bit of data
                bit_read = read_bit_at_location(encoded_image, bit_location);
                if(bit_read == 0){
                    // Bit is a 0
                    // Go to left child node and declare it as the current node
                    // printf("Bit was a 0\n");
                    current_node = huffman_tree[current_node.left_node];
                }
                else{
                    // Bit is a 1
                    // printf("Bit was a 1\n");
                    current_node = huffman_tree[current_node.right_node];
                }
                bit_location = bit_location + 1;
            }

            // Leaf node found set pixel value
            // printf("Leaf node found, pixel value: %d\n", current_node.pixel_value);
            extracted_pgm_image->image[row][col] = current_node.pixel_value;
        }
    }

    return extracted_pgm_image;
}