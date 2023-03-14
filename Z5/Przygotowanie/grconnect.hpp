#ifndef GRCONNECT_HPP
#define GRCONNECT_HPP
#define MAX 800   
int read_file(int image_arr_pgm[MAX][MAX],int *width,int *height, int *grey_scale, char *image_file_name);
int write_file(int image_arr_pgm[MAX][MAX],int *width,int *height, int *grey_scale, char *image_file_name);
int negative( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height, int *grey_scale);
int threshold( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height, int *grey_scale);
int level_changing( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height, int *grey_scale);
int blur( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height);
int normalize( int image_arr_in[MAX][MAX], int image_arr_out[MAX][MAX],int *width,int *height, int *grey_scale);
void image_display(char *image_file_name);
#endif