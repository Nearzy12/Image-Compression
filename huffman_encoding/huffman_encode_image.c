// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

# include "huffman_encode_image.h"

#define UNASSIGNED_CODE 0x0
// #define UNASSIGNED_CODE 0b0

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

void edit_bit(unsigned char *encoded_image_data, long int bit_location, unsigned int bit) {
    // Calculate the byte index and bit index within that byte
    long int byte_index = bit_location / 8;
    int bit_index = bit_location % 8;

    // Create a mask to set or clear the bit
    unsigned char mask = 1 << bit_index;

    // Set or clear the bit based on the boolean value
    if (bit == 1) {
        encoded_image_data[byte_index] |= mask; // Set the bit
        // printf("saving 1 to memory");
    } else {
        encoded_image_data[byte_index] &= ~mask; // Clear the bit
        // printf("saving 0 to memory");
    }

    // printf(" at bit location: %d\n", bit_location);
}

// Function that returns the code structure index in the code array for the passed pixel value, return -1 if pixel value not found
int get_code_index_from_pixel_value(int pixel_value, int array_size, struct code *code_array){
    // Loop through array and return the index of the pixel_value
    for(int i = 0; i < array_size; i++){
        if(code_array[i].pixel_value == pixel_value){
            return i;
        }
    }
    // if no value is found return -1
    return -1;
}

// Function that will set the pixel_value of a code at the first available location
int set_pixel_value(int pixel_value, int array_size, struct code *code_array){
    // Loop through array and update the pixel value at the first free space
    for(int i = 0; i < array_size; i++){
        if(code_array[i].pixel_value == -1){
            code_array[i].pixel_value = pixel_value;
            return 0;
        }
    }
}

void generate_huffman_codes(struct code *code_array, struct node *huffman_node, int number_of_nodes, int number_of_symbols){
    /*/ We need some way to store the huffman codes for each symbol
    For this I will make a structure that stores the pixel value, code length, and code
    The index of the loop is the value of the loop
    If the value in the huffman node is 1,2 then the nodes we are building the code for is 1 and 2 */

    // The only way we know what codes to match which pixel_value, is from the nodes. So we need
    // to loop though each node and check the left and right values. To know if we have added this value or not 
    // we need to initialize the pixel values to a number they can't be like -1.
    for(int i = 0; i < number_of_symbols; i++){
        code_array[i].pixel_value = -1;
        code_array[i].length = 0;
        code_array[i].code = UNASSIGNED_CODE;
    }

    // Now loop through every node and assign the pixel values
    // The order that each code is stored in the array doesn't matter as each will have it's own pixel value
    int left_value_return, left_value;
    int right_value_return, right_value;
    for (int j = number_of_nodes-1; j >= 0; j--){
        left_value = huffman_node[j].left_value;
        right_value = huffman_node[j].right_value;
        left_value_return = get_code_index_from_pixel_value(left_value, number_of_symbols, code_array);
        right_value_return = get_code_index_from_pixel_value(right_value, number_of_symbols, code_array);

        // The left pixel value does not exist in any code so add it 
        if(left_value_return == -1){
            set_pixel_value(left_value, number_of_symbols, code_array);
        }
        // The right pixel value does not exist in any code so add it
        if(right_value_return == -1){
            set_pixel_value(right_value, number_of_symbols, code_array);
        }
    }

    // At this point all the codes have pixel_values.
    printf("    Number of nodes: %d number of symbols: %d\n", number_of_nodes, number_of_symbols);
    // Now create the actual codes using the huffman nodes, we need to start from the end of the list of nodes
    for(int k = number_of_nodes-1; k >= 0; k--){
        
        // printf("===================================\n");
        // // Print out all the pixel values and their codes
        // for(int r = 0; r < number_of_symbols; r++){
        //     printf("Pixel Value: %d Code Value: %u Code Length: %d\n", code_array[r].pixel_value, code_array[r].code, code_array[r].length);
        // }
        

        // find the code in the code array for the left and right values of the node
        left_value = huffman_node[k].left_value;
        right_value = huffman_node[k].right_value;

        // We know these values will be in the code array from the previous loop
        left_value_return = get_code_index_from_pixel_value(left_value, number_of_symbols, code_array);
        right_value_return = get_code_index_from_pixel_value(right_value, number_of_symbols, code_array);


        if(left_value_return == -1 || right_value_return == -1){
            printf("Something Went wrong, not all symbols were added in code array\n");
        }

        // printf("Left Code Return Value: %d\n", left_value_return);        
        // printf("Right Code Return Value: %d\n", right_value_return);

        if(code_array[left_value_return].code == UNASSIGNED_CODE && code_array[right_value_return].code == UNASSIGNED_CODE){
            // They both have empty codes set the left value as 0 and the right value as 1
            // printf("Both values are unassigned codes\n");
            // printf("code array [0].pixel: %d .length: %d code:%u\n", code_array[left_value_return].pixel_value, code_array[left_value_return].length, code_array[left_value_return].code);


            if(number_of_symbols == 1){
                code_array[left_value_return].code = 0b0;
                code_array[left_value_return].length++;
            }else{
                code_array[left_value_return].code = 0b0;
                code_array[right_value_return].code = 0b1;

                code_array[left_value_return].length++;
                code_array[right_value_return].length++;
            }

            // printf("code array [0].pixel: %d .length: %d code:%u\n", code_array[left_value_return].pixel_value, code_array[left_value_return].length, code_array[left_value_return].code);
        }
        else if(code_array[left_value_return].code == UNASSIGNED_CODE){
            // Right value has a code and the left doesn't, copy code to left and add 0 and 1
             code_array[left_value_return].code = code_array[right_value_return].code;
            // add a 0 to the left value - bitwise AND with negation of 1 after logical shift left
            code_array[left_value_return].code <<= 1;
            code_array[left_value_return].code &= ~(1);

            // add a 1 to the end of the right value, shift the bits left and then bitwise OR with ~(1111111....0) which is (0000...1)
            code_array[right_value_return].code <<= 1;
            code_array[right_value_return].code |= 1;

            // update lengths
            code_array[right_value_return].length = code_array[right_value_return].length + 1;
            code_array[left_value_return].length = code_array[right_value_return].length;

        }
        else if(code_array[right_value_return].code == UNASSIGNED_CODE){
            // Left value has a code and the right doesn't, copy code to right and add 0 and 1
            code_array[right_value_return].code = code_array[left_value_return].code;
            // add a 0 to the left value - bitwise AND with negation of 1 after logical shift left
            code_array[left_value_return].code <<= 1;
            code_array[left_value_return].code &= ~(1);

            // add a 1 to the end of the right value, shift the bits left and then bitwise OR with ~(1111111....0) which is (0000...1)
            code_array[right_value_return].code <<= 1;
            code_array[right_value_return].code |= 1;

            // update lengths
            code_array[left_value_return].length = code_array[left_value_return].length + 1;
            code_array[right_value_return].length = code_array[left_value_return].length;
        }
        else{
            printf("For some reason one of the code values wasn't empty we shouldn't be here...\n");
        }
    }
}

// Function that encoded image using huffman encoding
unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int number_of_nodes, long int *length_of_encoded_image_array){

    // Generate huffman codes from huffman nodes, start from the last node and work backwards
    // The number of codes will be for every symbol which is number of huffman nodes + 1
    // printf("number of nodes: %d\n", number_of_nodes);
    int number_of_symbols;
    if(number_of_nodes > 1){
        number_of_symbols = number_of_nodes + 1;
    }else{
        number_of_symbols = 1;
    }

    // Create an array of codes, each element will be a code for each respective pixel
    // There is 1 code for every unique symbol therefore number of symbols in image is the same as number of codes
    struct code *code_array = malloc((number_of_symbols) * sizeof(struct code));

    // Generate all huffman codes
    generate_huffman_codes(code_array, huffman_node, number_of_nodes, number_of_symbols);



    // Now that we have an array containing all the pixel values and codes we need to loop though the image and create the codes

    // Loop though the image
    // Loop through every pixel of the image
    *length_of_encoded_image_array = 0;
    for(int row = 0; row < input_pgm_image->height; row++){
        for(int col = 0; col < input_pgm_image->width; col++){
            // Get the pixel value
            int pixel_value = input_pgm_image->image[row][col];

            // Find the huffman code that corresponds to the pixel value
            int code_index = get_code_index_from_pixel_value(pixel_value, number_of_symbols, code_array);

            if(code_index != -1){
                // The huffman code for the pixel value was found, Now add it to the unsigned char array
                unsigned int code = code_array[code_index].code;
                int code_length = code_array[code_index].length;
                *length_of_encoded_image_array = *length_of_encoded_image_array + code_length;
            }
            // The pixel value was not found to match any of the huffman codes 
            else{
                printf("Pixel value %d not found in Huffman codes. \n", pixel_value);
            }
        }
    }
    // Convert the length of the encoded data from bits to bytes
    *length_of_encoded_image_array = (*length_of_encoded_image_array + 7) / 8;
    printf("    Number of BYTES needed for the image data: %d\n", *length_of_encoded_image_array);

    // Now we know exactly ho wmany bits we need to store the encoded image, this will be used to alloate memory for encoded_array
    // unsigned char *encoded_image_data = malloc(input_pgm_image->width * input_pgm_image->height * sizeof(unsigned char));
    unsigned char *encoded_image_data = (unsigned char *)malloc(*length_of_encoded_image_array);

    // Now that we have the array allocated with the space we need we can start adding the codes to memory
    long int current_bit_position = 0;
    for(int row = 0; row < input_pgm_image->height; row++){
        for(int col = 0; col < input_pgm_image->width; col++){
            // Get the pixel value
            int pixel_value = input_pgm_image->image[row][col];

            // Find the huffman code that corresponds to the pixel value
            int code_index = get_code_index_from_pixel_value(pixel_value, number_of_symbols, code_array);

            if(code_index != -1){
                // The huffman code for the pixel value was found, Now add it to the unsigned char array
                // Insert the code into the file at the current bit location
                unsigned int code = code_array[code_index].code;
                int code_length = code_array[code_index].length;
                // printf("Code: %u, Length: %d\n", code, code_length);

                // Start from the most significant bit and iterate to the least significant bit
                for (int i = code_length - 1; i >= 0; i--) {
                    // Extract the i-th bit using bitwise AND with a mask
                    unsigned int mask = 1 << i;
                    unsigned int bit = (code & mask) ? 1 : 0;

                    // Print the bit
                    // printf("Bit value: %u :", bit);
                    edit_bit(encoded_image_data, current_bit_position, bit);
                    current_bit_position = current_bit_position + 1;
                }
                // printf("\n");

            }
            // The pixel value was not found to match any of the huffman codes 
            else{
                printf("Pixel value %d not found in Huffman codes.\n", pixel_value);
            }
        }
    }
    // print_encoded_image(encoded_image_data, current_bit_position/8);
    printf("    Number of bits used to encode image: %d\n", current_bit_position);
    return encoded_image_data;
} 


