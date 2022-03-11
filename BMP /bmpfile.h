#ifndef __BMPFILE_H__
#define __BMPFILE_H__
#include <stdint.h>
/* BMP 对象的类型定义 */
typedef struct {
    int   width;   /* 宽度 */
    int   height;  /* 高度 */
    int   stride;  /* 行字节数 */
    int   cdepth;  /* 像素位数 */
    void *pdata;   /* 指向数据 */
} BMP;


#pragma pack(1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportan;

} BMPFILEHEADER;
#pragma pack()

int  bmp_load(BMP *pb, char *file);
int  bmp_save(BMP *pb, char *file);
void bmp_free(BMP *pb);
void bmp_setpixel(BMP *pb, int x, int y, int r, int g, int b);
void bmp_getpixel(BMP *pb, int x, int y, int *r, int *g, int *b);

#endif
