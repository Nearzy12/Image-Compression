// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

// Program that gets all the huffman nodes from the frequency array

#include "generate_huffman_nodes.h"
#include <stdlib.h>
#include <stdio.h>

// Function to return the largest frequency in the frequency array
long int get_sum_of_frequency(long int *pixel_frequency, int array_size){

    long int frequency_sum = 0;
    // Loop through frequency array and return the largest number
    for(int i = 0; i < array_size; i++){
        frequency_sum = frequency_sum + pixel_frequency[i];
    }
    return frequency_sum;
}

// Function to return the index value of the smallest value in the array
int get_index_of_smallest_frequency(long int *pixel_frequency, int array_size){
    // There are many gray values /  colors that have a frequency of zero, we don't want to include these
    int index_of_min = 0;
    long int min_frequency = pixel_frequency[0];

    for(int i = 1; i < array_size; i++){
        if(pixel_frequency[i] < min_frequency ){
            min_frequency = pixel_frequency[i];
            index_of_min = i;
        }
    }

    return index_of_min;
}

struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array)
{
    // Allocate memory and create array to store 
    struct node *node_array = malloc((number_of_non_zero_values_in_the_frequency_array - 1) * sizeof(struct node));

    int min_index, min_index_1, min_index_2;
    int array_size = max_gray_value + 1;
    long int min_value, min_value_1, min_value_2, sum_of_frequency;

    // Get the largest frequency so we can use that to update the values of the min values we get back
    sum_of_frequency = get_sum_of_frequency(pixel_frequency, array_size);

    printf("    Sum of all frequencies: %d \n", sum_of_frequency);

    // Loop through the pixel frequency array and any value that has a frequency of zero set to largest value
    for(int j = 0; j < array_size; j++){
        if(pixel_frequency[j] == 0){
            pixel_frequency[j] = sum_of_frequency + 1;
        }
    }

    // Each iteration of the loop will add a huffman node to the array of nodes
    for(int i = 0; i < number_of_non_zero_values_in_the_frequency_array-1; i++){
        // Find the two smallest frequencies
        min_index_1 = get_index_of_smallest_frequency(pixel_frequency, array_size);
        min_value_1 = pixel_frequency[min_index_1];

        // Update value
        pixel_frequency[min_index_1] = sum_of_frequency + 1;

        min_index_2 = get_index_of_smallest_frequency(pixel_frequency, array_size);
        min_value_2 = pixel_frequency[min_index_2];

        // Update value
        pixel_frequency[min_index_2] = sum_of_frequency + 1;

        // Update the array of nodes
        // The left child is always the index that is smaller
        // Frequency array at the smaller index needs to be updated to hold the two frequencies added together
        // printf("index1: %d val1: %d index1: %d val2: %d \n", min_index_1, min_value_1, min_index_2, min_value_2);
        if(min_index_1 < min_index_2){
            node_array[i].left_value = min_index_1;
            node_array[i].right_value = min_index_2;
            pixel_frequency[min_index_1] = min_value_1 + min_value_2;
        }
        else{
            node_array[i].left_value = min_index_2;
            node_array[i].right_value = min_index_1;
            pixel_frequency[min_index_2] = min_value_1 + min_value_2;
        }
    }

    // Special Case for when there is only 1 value in the frequency array
    if(number_of_non_zero_values_in_the_frequency_array == 1){
        min_index = get_index_of_smallest_frequency(pixel_frequency, array_size);
        min_value = pixel_frequency[min_index];
        // Just set both value in the node to the pixel value
        pixel_frequency[min_index] = sum_of_frequency + 1;

        // We wont be using the node array allocated earlier
        free(node_array);
        printf("    Number of non zero value in image: %d, pixel value: %d\n", number_of_non_zero_values_in_the_frequency_array, min_index);
        struct node *node_array_single_value = malloc((number_of_non_zero_values_in_the_frequency_array) * sizeof(struct node));

        node_array_single_value[0].left_value = min_index;
        node_array_single_value[0].right_value = min_index;
        return node_array_single_value;
    }
    return node_array;
}
