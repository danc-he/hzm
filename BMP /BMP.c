/*
 ============================================================================
 Name        : BMP.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmpfile.h"


#define Y 540
#define X 960
int main(int argc, char *argv)
{

    BMP *pb = malloc( sizeof (BMP) );

    char *file = "test2.bmp";
    char *save = "save.bmp";

    int x, y;
    uint8_t r, g, b;
    if (bmp_load(pb, file)) {
        printf("Open finish.\n");
    }
    else{
        printf("Open failed!\n");
    }

    for (y = 0; y < Y; y++){
        for (x = 0; x < X; x++)
            bmp_setpixel(pb, x, y, 0, 0, 0);
    }
    if (bmp_save(pb, save)){
        printf("Save finish.\n");
        printf("File name:");
        while ( *save != '\0'){
            printf("%c", *save);
            save++;
        }
        printf("\n");
    }
    else{
        printf("Save failed! \n");
    }


    bmp_free(pb);
    return EXIT_SUCCESS;
}
