#ifndef functions_h
#define functions_h
#define MAX 800    

int read_file_v2(int **&tab_image_arr_in, int **&tab_image_arr_out, int *width, int*height, int *grey_scale, char *image_file_name);

int write_file_v2(int **tab_image_arr_in,int *width,int *height, int *grey_scale, char *image_file_name);

int negative_v2( int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height, int *grey_scale);

int normalizev2( int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height, int *grey_scale);

int thresholdv2( int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height, int *grey_scale);

int level_changingv2( int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height, int *grey_scale);

int blurv2( int **tab_image_arr_in, int **tab_image_arr_out,int *width,int *height);

int conversion (int **tab_image_arr_in,int *width,int *height, int *grey_scale, char *image_file_name);

void image_display(char *image_file_name);






               
#endif