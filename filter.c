//file readwrite PPM
#include "filter.h"
#include <stdlib.h>
#include <stdio.h>

PPM_IMAGE *filter_image(const char *file_name, const PPM_IMAGE *image, const KERNEL *kernel){

	PPM_IMAGE *filtered_image = malloc(sizeof(PPM_IMAGE));

	filtered_image->width = image->width;
	filtered_image->height = image->height;
	filtered_image->max_color = image->max_color;

	PIXEL *blocks = malloc(sizeof(PIXEL)*(image->width*image->height));
	filtered_image->data = blocks;

	int image_row = image->height, image_col = image->width;
	int kernel_size = kernel->n;
	int kernel_scale = kernel->scale;
	int accumlatorR = 0;
	int accumlatorB = 0;
	int accumlatorG = 0;

	for(int i = 0; i < image_row; i++){
		for(int j = 0; j < image_col; j++){
			accumlatorR = 0;
			accumlatorB = 0;
			accumlatorG = 0;

			// Convolution on pixal i,j with kernal
			// Uses zero-padding, ie lazy approach to pixals that are out-of-bounds
			for(int k = 0; k < kernel_size; k++){
				for(int l = 0; l < kernel_size; l++){
					if(is_pixal_there(i + k - kernel_size/2, j + l - kernel_size/2, image_row, image_col) == 1){
						accumlatorR += image->data[(i + k - kernel_size/2) * image_col + j + l - kernel_size/2].r * kernel->data[k * kernel_size + l];
						accumlatorG += image->data[(i + k - kernel_size/2) * image_col + j + l - kernel_size/2].g * kernel->data[k * kernel_size + l];
						accumlatorB += image->data[(i + k - kernel_size/2) * image_col + j + l - kernel_size/2].b * kernel->data[k * kernel_size + l];
					}					
				}
			}

			//writing new pixals to filtered image data structure, set negative color values to zero
			if(accumlatorR < 0)
				filtered_image->data[i * image_col + j].r = 0;
			else
				filtered_image->data[i * image_col + j].r = (unsigned char) (accumlatorR / kernel_scale);

			if(accumlatorG < 0)
				filtered_image->data[i * image_col + j].g = 0;
			else
				filtered_image->data[i * image_col + j].g = (unsigned char) (accumlatorG / kernel_scale);
			
			if(accumlatorB < 0)
				filtered_image->data[i * image_col + j].b = 0;
			else
				filtered_image->data[i * image_col + j].b = (unsigned char) (accumlatorB / kernel_scale);	
		}
	}

	return filtered_image;
}

int is_pixal_there(int pixal_postion_row, int pixal_postion_col, int image_row, int image_col){
	if(0 <= pixal_postion_row && pixal_postion_row < image_row){
		if(0 <= pixal_postion_col && pixal_postion_col < image_col){
			return 1;
		}
	}

	return 0;
}


void free_image(PPM_IMAGE *p)
{
	free(p->data);	
	free(p);
	return;
}

void free_kernel(KERNEL *p)
{
	free(p->data);	
	free(p);
	return;
}