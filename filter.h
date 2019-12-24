#ifndef FILTER_H_
#define FILTER_H_

typedef struct { unsigned char r, g, b; } PIXEL;

typedef struct {
  PIXEL *data;       // pointer to an array of width*height PIXELs
  int width, height; // width and height of image
  int max_color;     // largest value of a color
} PPM_IMAGE;

typedef struct {
  int *data;       // pointer to an array of n*n integers
  int n;                     // size
  int scale;                 // scale of kernel
} KERNEL;

// Read and write PPM file
PPM_IMAGE *read_ppm(const char *file_name);
void write_ppm(const char *file_name, const PPM_IMAGE *image);

// Read kernel
KERNEL *read_kernel(const char *file_name);

// Filter image
PPM_IMAGE *filter_image(const char *file_name, const PPM_IMAGE *image, const KERNEL *kernel);
int is_pixal_there(int pixal_postion_row, int pixal_postion_col, int image_row, int image_col);


// Free image and kernel
void free_image(PPM_IMAGE *p);
void free_kernel(KERNEL *p);

 #endif