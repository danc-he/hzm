
#include <stdio.h>
#include <stdlib.h>
#include "bmpfile.h"

int  bmp_load(BMP *pb, char *file)
{
    BMPFILEHEADER *pheader = (BMPFILEHEADER *)malloc(sizeof(BMPFILEHEADER));
    FILE *fp = fopen(file, "rb");
    if (fp == NULL){
        return 0;
    }

    fread(pheader, 1, sizeof(BMPFILEHEADER), fp);

    pb->width = pheader->biWidth;
    pb->height = pheader->biHeight;
    pb->cdepth = pheader->biBitCount;

    pb->stride = (pheader->biWidth * pheader->biBitCount + 31) / 32 * 4;

    uint8_t *data = (uint8_t *)malloc(pb->stride * pb->height);

    fread(data, 1, (pb->stride * pb->height), fp);
    pb->pdata = data;

printf("Source BMP Info :\n");
    printf("bfType             = %d \n", pheader->bfType);
    printf("bfSize             = %d \n", pheader->bfSize);
    printf("bfReserved1        = %d \n", pheader->bfReserved1);
    printf("bfReserved2        = %d \n", pheader->bfReserved2);
    printf("bfOffBits          = %d \n", pheader->bfOffBits);
    printf("biSize             = %d \n", pheader->biSize);
    printf("biWidth            = %d \n", pheader->biWidth);
    printf("biHeight           = %d \n", pheader->biHeight);
    printf("biPlanes           = %d \n", pheader->biPlanes);
    printf("biBitCount         = %d \n", pheader->biBitCount);
    printf("biCompression      = %d \n", pheader->biCompression);
    printf("biSizeImage        = %d \n", pheader->biSizeImage);
    printf("biXPelsPerMeter    = %d \n", pheader->biXPelsPerMeter);
    printf("biYPelsPerMeter    = %d \n", pheader->biYPelsPerMeter);
    printf("biClrUsed          = %d \n", pheader->biClrUsed);
    printf("biClrImportan      = %d \n", pheader->biClrImportan);
    printf("\n");
    printf("\n");
    printf("BMP Info: \n");
    printf("width        =   %d\n", pb->width);
    printf("height       =   %d\n", pb->height);
    printf("cdepth       =   %d\n", pb->cdepth);
    printf("stride       =   %d\n", pb->stride);
//    printf("pdata       =    %d\n", pb->pdata);


    fclose(fp);

    return 1;
}


int  bmp_save(BMP *pb, char *file)
{

    BMPFILEHEADER save;
    save.bfType = 19778;
    save.bfSize = (sizeof( BMPFILEHEADER)  + (pb->stride * pb->height));
    save.bfReserved1 = 0;
    save.bfReserved2 = 0;
    save.bfOffBits = sizeof (BMPFILEHEADER);
    save.biSize = 40;
    save.biWidth = pb->width;
    save.biHeight = pb->height;
    save.biPlanes = 1;
    save.biBitCount = pb->cdepth;
    save.biCompression = 0;
    save.biSizeImage = pb->stride * pb->height;
    save.biXPelsPerMeter = 2835;
    save.biYPelsPerMeter = 2835;
    save.biClrUsed = 0;
    save.biClrImportan = 0;

    FILE *fp_write = fopen(file, "wb");


    if (fp_write == NULL)
    {
        printf("open file failed!\n");
        return 0;
    }

    fwrite(&save, 1, sizeof(BMPFILEHEADER), fp_write);
    fwrite(pb->pdata, 1, save.biSizeImage, fp_write);




    fclose(fp_write);
    return 1;
}

void bmp_free(BMP *pb)
{
    free(pb);
}

void bmp_setpixel(BMP *pb, int x, int y, int r, int g, int b)
{
    int width = pb->width;
    int height = pb->height;
    int location = 3 * ((height - y - 1)*width + (x -1));
    *(uint8_t *)(pb->pdata + location)     = r;
    *(uint8_t *)(pb->pdata + location + 1) = g;
    *(uint8_t *)(pb->pdata + location + 2) = b;

}

void bmp_getpixel(BMP *pb, int x, int y, int *r, int *g, int *b)
{
    int width = pb->width;
    int height = pb->height;
    int location = 3 * ((y - 1)*width + (x -1));
    *r = (uint8_t)(pb->pdata + location);
    *g = (uint8_t)(pb->pdata + location + 1);
    *b = (uint8_t)(pb->pdata + location + 2);
}
