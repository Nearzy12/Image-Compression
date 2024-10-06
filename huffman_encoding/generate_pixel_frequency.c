// Samuel Near
// Snear2
// CS4481 
// Assignment 2
// Febuary 29, 2024

// Function to generate the pixel frequencies in a pgm image
// Counts the number of non zero pixel values in the image

#include "generate_pixel_frequency.h"

// Reads all pixels in the provided PGM image and record the frequency of occurrence of each pixel values in the allocated array 
long int *generate_pixel_frequency(struct PGM_Image *input_pgm_image, int *number_of_non_zero_values_in_the_frequency_array){

    // printf("Generating Pixel Frequency\n");
    int pixel_value;
    int array_size = input_pgm_image->maxGrayValue + 1;
    // Dynamically allocate the frequency array that we will be adding values too
    long int *frequency_array = (long int*)malloc(array_size * sizeof(long int));

    // Initialize all the values in the array to zero. To start each color has a frequency of 0
    for (int i = 0; i < array_size; i++) {
        frequency_array[i] = 0;
    }
    printf("    Array initialized to zeros\n");

    // Loop through each pixel from the pgm image: update frequency array for each pixel and the number of non zero pixels
    for (int row = 0; row < input_pgm_image->height; row++){
        for (int col = 0; col < input_pgm_image->width; col++){
            
            pixel_value = input_pgm_image->image[row][col];
            // This means that this pixel value is unique, we need to increase the number of non zero values by 1
            if(frequency_array[pixel_value] == 0){
                // None zero value, increment by 1
                // printf("    New Value! Row: %d Col: %d Pixel Value: %d\n", row, col, pixel_value);
                *number_of_non_zero_values_in_the_frequency_array = *number_of_non_zero_values_in_the_frequency_array + 1;
                
            }
            // update the frequency array
            frequency_array[pixel_value] = frequency_array[pixel_value] + 1;
            // printf("    Row: %d Col: %d Pixel Value: %d\n", row, col, pixel_value);
        }
        // printf("    Finished looping through row: %d image width: %d image height: %d\n", row, input_pgm_image->width, input_pgm_image->height);
    }
    return frequency_array;
}