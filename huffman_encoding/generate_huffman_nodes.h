// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

#ifndef GENERATE_HUFFMAN_NODES_H
#define GENERATE_HUFFMAN_NODES_H

// Define the struct node
struct node {
    int left_value;
    int right_value;
};

// Function prototypes
long int get_sum_of_frequency(long int *pixel_frequency, int array_size);
int get_index_of_smallest_frequency(long int *pixel_frequency, int array_size);
struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array);

#endif /* GENERATE_HUFFMAN_NODES_H */
