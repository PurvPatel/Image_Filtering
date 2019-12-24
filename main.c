//file readwrite PPM
#include "filter.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  // Process input parameters
  if (argc!=4)
    {
      printf("Usage ./filter in_file kernel out_file\n");
      return 1;
    }
  const char *input_file = argv[1];
  const char *kernel_file = argv[2];
  const char *output_file = argv[3];
  
  // Read image.
  PPM_IMAGE *goal = read_ppm(input_file);

  // Read Kernel
  KERNEL *kernel = read_kernel(kernel_file); 

  printf("%d %d \n", goal->width, goal->height);
  // Compute image
  PPM_IMAGE *new_image =
  filter_image(output_file, goal, kernel);
  printf("%d %d \n", kernel->scale, kernel->n);
  // Write image
  write_ppm(output_file, new_image);

  // Free memory
  free_image(goal);
  free_image(new_image);
  free_kernel(kernel);

  return (0);
}