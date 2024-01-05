
#include "pbm.h"
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
void bandw(PPMImage *inputIm, const char * filename);
void gray(PPMImage *inputIm, const char * filename, int max);
void rem(PPMImage *inputIm, const char * filename , char string[]);
void isolate(PPMImage *inputIm, const char * filename, char string[]);
void sepia(PPMImage *inputIm, const char * filename);
void thumbnail(PPMImage *inputIm, const char * filename, int scale);
void nUP(PPMImage *inputIm, const char * filename, int scale);
void mirror(PPMImage* image, const char * filename);
int main( int argc, char *argv[] )
{
char output[100];//Creates a character array to store the output file name
char s[10];//Creates a characterarray to store the option name 
char input[100];//creates a character array to store the input file name
char arg[100];//creates a character array to store the argument of option. Either int arguments or string arguments. 
int c;
int flag = 0;
int flag_o = 0;
char *n_ptr;
char *g_ptr;
char *arg_ptr;
while((c = getopt(argc, argv, ":bg:i:r:smt:n:o:")) != -1){
    if(optarg == NULL && c == ':'){//Checking if the options that require an argument on the command line actually have one. 
        printf("Missing argument for option %s\n", argv[argc-1]);
        exit(1);
    }
    switch (c)
    {
    case '?':{//The case if you mention a wrong argument. That means, something that is not there in, ":bg:i:r:smt:n:o:"

        printf("Usage: ppmcvt [-bgirsmtno] [FILE]\n");
        exit(1);
    }
    case 'r':{
        if(flag == 1){
            printf("Error: Multiple transformations specified\n");
            exit(1);
        }
        flag = 1;
        int blue = strcmp("blue", optarg);
        int red = strcmp("red", optarg);
        int green = strcmp("green", optarg);
        if(green != 0 && red != 0 && blue != 0){
            printf("Error: Invalid channel specification: (%s); should be 'red', 'green', or 'blue'\n", optarg);
            exit(1);
        }
        strcpy(s, "r");//Copies string r into character array s. 
        strcpy(arg, optarg);//Arg stores the string argument that is supposed to be after the transformation r on the command line. 
        break;
    }

    case 'i':{
        if(flag == 1){
            printf("Error: Multiple transformations specified\n");
            exit(1);
        }
        flag = 1;
        int blue = strcmp("blue", optarg);
        int red = strcmp("red", optarg);
        int green = strcmp("green", optarg);
        if(green != 0 && red != 0 && blue != 0){
            printf("Error: Invalid channel specification: (%s); should be 'red', 'green', or 'blue'\n", optarg);
            exit(1);
        }
        strcpy(s, "i");
        strcpy(arg, optarg);
        break;
    }
    
    case 'g':{
        if(flag == 1){
            printf("Error: Multiple transformations specified\n");
            exit(1);
        }
        flag = 1;
        long g = strtol(optarg, NULL, 10);
        if(g <= 65536 && g > 1){
            strcpy(s, "g");
            strcpy(arg, optarg);//String copy optarg into arg.
            break;
        }else{
            printf("Error: Invalid max grayscale pixel value: %s; must be less than 65,536\n", optarg);
            exit(1);
        }
        
        
    }

    case 'n':{
        if(flag == 1){
            printf("Error: Multiple transformations specified\n");
            exit(1);
        }
        flag = 1;
        long n = strtol(optarg, &n_ptr, 10);//String to long function to convert the "optarg" to a n (ld) of base 10
        if(n < 1 || n > 8){
            printf("Error: Invalid scale factor: %ld; must be 1-8\n", n);
            exit(1);
        }
        strcpy(s, "n");
        strcpy(arg, optarg);
        break;
        
    }
    case 'b':{
        if(flag == 1){
            printf("Error: Multiple transformations specified\n");
            exit(1);
        }
        flag = 1;
        strcpy(s, "b");//String s has the different transformations that you can do. 
        break;
        
        
    }

    case 'o':{
        flag_o = 1;
        if(flag_o == 1){
            strcpy(output, optarg);//Storing the argument in the string called output
            break;
            
        }
        
    }

    case 's':{
        if(flag == 1){
            printf("Error: Multiple transformations specified\n");
            exit(1);
        }
        flag = 1;
        strcpy(s, "s");
        break;
        
    }

    case 'm':{
        if(flag == 1){
            printf("Error: Multiple transformations specified\n");
            exit(1);
        }
        flag = 1;
        strcpy(s, "m");
        break;
        
    }

    case 't':{
        if(flag == 1){
            printf("Error: Multiple transformations specified\n");
            exit(1);
        }
        flag = 1;
        long n = strtol(optarg, &n_ptr, 10);
        if(n < 1 || n > 8){
            printf("Error: Invalid scale factor: %s; must be 1-8\n", optarg);
            exit(1);
        }
        strcpy(s, "t");
        strcpy(arg, optarg); 
        break;
        
    }
    
}
}
if(flag_o == 0){
    printf("Error: No output file specified\n");
    exit(1);
}
if(optind == argc){
    printf("Error: No input file specified\n");
    exit(1);
}

strcpy(input, argv[optind]);
int a = strcmp(s, "b");
PPMImage *ppm = read_ppmfile(input);
if(strcmp(s, "b") == 0){//The if statement to filter out which method will be called depending on the string stored in s. s has the option of in the command line ":bg:i:r:smt:n:o:".
    bandw(ppm, output);
}else if(strcmp(s, "g") == 0){
    long n = strtol(arg, NULL, 10);
    gray(ppm, output, n);
}else if(strcmp(s, "i") == 0){
    isolate(ppm, output, arg);
}else if(strcmp(s, "r") == 0){
    rem(ppm, output, arg);
}else if(strcmp(s, "s") == 0){
    sepia(ppm, output);
}else if(strcmp(s, "m") == 0){
    mirror(ppm, output);
}else if(strcmp(s, "t") == 0){
    long n = strtol(arg, NULL, 10);
    thumbnail(ppm, output, n);
}else if(strcmp(s, "n") == 0){
    long n = strtol(arg, NULL, 10);
    nUP(ppm, output, n);
}

}

void bandw(PPMImage *inputIm, const char * filename)
{
    int height = inputIm->height;
    int width = inputIm->width;
    int maxval = inputIm->max;
    PBMImage *outputIm = new_pbmimage(width, height);//allocates space for the outputIm. 
    int red;
    int green;
    int blue;
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            red = inputIm->pixmap[0][h][w];
            green = inputIm->pixmap[1][h][w];
            blue = inputIm->pixmap[2][h][w];
            int average = (red + green + blue)/3;//Computes the average calculation of R, G, and B
            int max = inputIm->max/2;
            if(average > max){//Comparson to select whether the pixel is a black or a white. 
                outputIm->pixmap[h][w] = 0;
                fprintf(stderr, "%d" , 1);
            }else if(average <= max){
                outputIm->pixmap[h][w] = 1;
                fprintf(stderr, "%d", 0);
            }
        }
        fprintf(stderr, "\n");
    }
    write_pbmfile(outputIm, filename);
    del_pbmimage(outputIm);//deallocates space after storing transformation in "filename.pbm"
    
}

void gray(PPMImage *inputIm, const char * filename, int max){
    int height = inputIm->height;
    int width = inputIm->width;
    int maxval = inputIm->max;
    PGMImage *PGM = new_pgmimage(width, height, maxval);
    PGM->max = max;
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            int r = inputIm->pixmap[0][h][w];
            int g = inputIm->pixmap[1][h][w];
            int b = inputIm->pixmap[2][h][w];
            int average = (r + g + b)/3;//Does the average calculation of R, G, and B as suggested by the name "average"
            int calculation = (average*max)/inputIm->max;//performing the grayscale calculation for the transformation to a PGM. 
            PGM->pixmap[h][w] = calculation;
            fprintf(stderr, "%d ", calculation);
        }
        fprintf(stderr, "\n");
    }
    write_pgmfile(PGM, filename);
    del_pgmimage(PGM);
}

void rem(PPMImage *inputIm, const char * filename, char string[]){
    int height = inputIm->height;
    int width = inputIm->width;
    int maxval = inputIm->max;
    PPMImage *PPM = new_ppmimage(width, height, maxval);
    PPM->max = maxval;
    int rcomp = strcmp(string, "red");//Doing a comparison of the argument and red, green, and blue. 
    int gcomp = strcmp(string, "green");
    int bcomp = strcmp(string, "blue");
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            int r = inputIm->pixmap[0][h][w];
            int g = inputIm->pixmap[1][h][w];
            int b = inputIm->pixmap[2][h][w];

            if(rcomp == 0){
                PPM->pixmap[0][h][w] = 0;//Removing R
                PPM->pixmap[1][h][w] = g;
                PPM->pixmap[2][h][w] = b;
                
            }
            if(gcomp == 0){
                PPM->pixmap[0][h][w] = r;
                PPM->pixmap[1][h][w] = 0;//Removing G
                PPM->pixmap[2][h][w] = b;
            }
            if(bcomp == 0){
                PPM->pixmap[0][h][w] = r;
                PPM->pixmap[1][h][w] = g;
                PPM->pixmap[2][h][w] = 0;//Removing B
            }
        }
        fprintf(stderr, "\n");
    }
    write_ppmfile(PPM, filename);
    del_ppmimage(PPM);
}


void isolate(PPMImage *inputIm, const char * filename, char string[]){
    int height = inputIm->height;
    int width = inputIm->width;
    int maxval = inputIm->max;
    PPMImage *PPM = new_ppmimage(width, height, maxval);
    PPM->max = maxval;
    int rcomp = strcmp(string, "red");//Doing a comparison of the argument of red, green, and blue. 
    int gcomp = strcmp(string, "green");
    int bcomp = strcmp(string, "blue");
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            int r = inputIm->pixmap[0][h][w];
            int g = inputIm->pixmap[1][h][w];
            int b = inputIm->pixmap[2][h][w];
            if(rcomp == 0){
                PPM->pixmap[0][h][w] = r;//Isolating R
                PPM->pixmap[1][h][w] = 0;
                PPM->pixmap[2][h][w] = 0;
            }
            if(gcomp == 0){
                PPM->pixmap[0][h][w] = 0;
                PPM->pixmap[1][h][w] = g;//Isolating G
                PPM->pixmap[2][h][w] = 0;
            }
            if(bcomp == 0){
                PPM->pixmap[0][h][w] = 0;
                PPM->pixmap[1][h][w] = 0;
                PPM->pixmap[2][h][w] = b;//Isolating B
            }
        }
        fprintf(stderr, "\n");
    }
    write_ppmfile(PPM, filename);
    del_ppmimage(PPM);
}

void sepia(PPMImage *inputIm, const char * filename){
    int height = inputIm->height;
    int width = inputIm->width;
    int maxval = inputIm->max;
    PPMImage *PPM = new_ppmimage(width, height, maxval);
    PPM->max = maxval;
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            float r = inputIm->pixmap[0][h][w];//Storing the RGB values in a floating point number
            float g = inputIm->pixmap[1][h][w];
            float b = inputIm->pixmap[2][h][w];
            PPM->pixmap[0][h][w] = (0.393)*r + (0.769)*g + (0.189)*b;//The formula to convert old RGB pixels to new ones. 
            PPM->pixmap[1][h][w] = (0.349)*r + (0.686)*g + (0.168)*b;
            PPM->pixmap[2][h][w] = (0.272)*r + (0.534)*g + (0.131)*b;
            if(PPM->pixmap[0][h][w] > maxval){//Makes sure that the value of R, G, or B does not exceed the maximum value of file.  
                PPM->pixmap[0][h][w] = maxval;
            }
            if(PPM->pixmap[1][h][w] > maxval){
                PPM->pixmap[1][h][w] = maxval;
            }
            if(PPM->pixmap[2][h][w] > maxval){
                PPM->pixmap[2][h][w] = maxval;
            }
            fprintf(stderr, "%d ", PPM->pixmap[0][h][w]);
        }
        fprintf(stderr, "\n");
    }
    write_ppmfile(PPM, filename);
    del_ppmimage(PPM);
    
}

void thumbnail(PPMImage *inputIm, const char * filename, int scale){
    int height = ((inputIm->height)/scale);
    int width = ((inputIm->width)/scale);
    fprintf(stderr, "%d\n", width);
    int maxval = inputIm->max;
    PPMImage *PPM = new_ppmimage(width, height, maxval);
    PPM->max = maxval;
    for(int h = 0; h < (PPM->height)-1; h++){
        for(int w = 0; w < (PPM->width)-1; w++){
            PPM->pixmap[0][h][w] = inputIm->pixmap[0][h*scale][w*scale];//Picks and stores every nth pixel from inputimage pixmap to PPM pixmap. 
            PPM->pixmap[1][h][w] = inputIm->pixmap[1][h*scale][w*scale];
            PPM->pixmap[2][h][w] = inputIm->pixmap[2][h*scale][w*scale];
        }
        fprintf(stderr, "\n");
    }
    write_ppmfile(PPM, filename);//Calls the write function in pbm.c
    del_ppmimage(PPM);
}



void nUP(PPMImage *inputIm, const char * filename, int scale){
    int height = inputIm->height;
    int width = inputIm->width;
    int maxval = inputIm->max;
    PPMImage *PPM = new_ppmimage(width, height, maxval);
    int heightoffset = height/scale;
    int widthoffset = width/scale;
    for(int i = 0; i < height; i = i + heightoffset){//Increments the height with the help of the offset. (in order to have exactly the number of images as "scale" on the height and the width)
        for(int j = 0; j < width; j = j + widthoffset){//Increments the width with the help of the offset. 
            for(int h = 0; h < height/scale; h++){
                for(int w = 0; w < width/scale; w++){
                    PPM->pixmap[0][h][w] = inputIm->pixmap[0][h*scale][w*scale];//Creates a thumbnail image on the top left of the screen for red
                    PPM->pixmap[1][h][w] = inputIm->pixmap[1][h*scale][w*scale];//Creates a thumbnail image on the top left of the screen for green
                    PPM->pixmap[2][h][w] = inputIm->pixmap[2][h*scale][w*scale];//Creates a thumbnail image on the top left of the screen for blue

                }
            }
        }
    }

    write_ppmfile(PPM, filename);
    del_ppmimage(PPM);
}

void mirror(PPMImage* inputIm, const char * filename){
int width = inputIm->width;
int height = inputIm->height;
int max = inputIm->max;
PPMImage* outputIm = new_ppmimage(width, height, max);

for(int i = 0; i < height; i++){
    for(int j = 0; j <= width/2; j++){//For loop going to the middle of the image. 
        int red = inputIm->pixmap[0][i][j];
        int green = inputIm->pixmap[1][i][j];
        int blue = inputIm->pixmap[2][i][j];

        outputIm->pixmap[0][i][j] = red;//Lets pixels in the left half of inputIm be the same in outputIm. 
        outputIm->pixmap[1][i][j] = green;
        outputIm->pixmap[2][i][j] = blue;

        outputIm->pixmap[0][i][width-j-1] = red;//Copies the start leftmost pixels of the code to rightmost side. (red)
        outputIm->pixmap[1][i][width-j-1] = green;//Copies the start leftmost pixels of the code to rightmost side. (green)
        outputIm->pixmap[2][i][width-j-1] = blue;//Copies the start leftmost pixels of the code to rightmost side. (blue)
    }
}
write_ppmfile(outputIm, filename);//Calls the function from pbm_aux.c to allocate memory for the PPM image transformation done above. 
del_ppmimage(outputIm);//Deallocates the memory allocated above, since the output file has already been outputted. 
}


