//__asm__(".code16gcc");
#include "utils/utils.h"
extern void io_hlt(void);


#define COL8_000000		0
#define COL8_FF0000		1
#define COL8_00FF00		2
#define COL8_FFFF00		3
#define COL8_0000FF		4
#define COL8_FF00FF		5
#define COL8_00FFFF		6
#define COL8_FFFFFF		7
#define COL8_C6C6C6		8
#define COL8_840000		9
#define COL8_008400		10
#define COL8_848400		11
#define COL8_000084		12
#define COL8_840084		13
#define COL8_008484		14
#define COL8_848484		15

void set_color_panel();
void boxfill8(unsigned char*, int , unsigned char, int, int, int, int);

void main(void)
{
//    cli();
    set_color_panel();
//     char* p = 0xa0000;
//     for (int i = 0; i <= 0xaffff; i++) {
//     	write_mem8(i, 15);
//     	write_mem8(i, i & 0x0f);
//        *(p + i) = 10;
//        *(p + i) = i & 0x0f;
//     }

    char *vram;
    int xsize, ysize;
    vram = (char *) 0xa0000;
    xsize = 320;
    ysize = 200;

    boxfill8(vram, xsize, COL8_008484,  0,         0,          xsize -  1, ysize - 29);
    boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 28, xsize -  1, ysize - 28);
    boxfill8(vram, xsize, COL8_FFFFFF,  0,         ysize - 27, xsize -  1, ysize - 27);
    boxfill8(vram, xsize, COL8_C6C6C6,  0,         ysize - 26, xsize -  1, ysize -  1);

     boxfill8(vram, xsize, COL8_FFFFFF,  3,         ysize - 24, 59,         ysize - 24);
    boxfill8(vram, xsize, COL8_FFFFFF,  2,         ysize - 24,  2,         ysize -  4);
    boxfill8(vram, xsize, COL8_848484,  3,         ysize -  4, 59,         ysize -  4);
    boxfill8(vram, xsize, COL8_848484, 59,         ysize - 23, 59,         ysize -  5);
    boxfill8(vram, xsize, COL8_000000,  2,         ysize -  3, 59,         ysize -  3);
    boxfill8(vram, xsize, COL8_000000, 60,         ysize - 24, 60,         ysize -  3);

    boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
    boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
    boxfill8(vram, xsize, COL8_FFFFFF, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
    boxfill8(vram, xsize, COL8_FFFFFF, xsize -  3, ysize - 24, xsize -  3, ysize -  3);


    while (1);
     for (;;) {
     	io_hlt();
     }
}

void set_color_panel(){
    char* rgb = {
            0x00, 0x00, 0x00,
            0xff, 0x00, 0x00,
            0x00, 0xff, 0x00,
            0xff, 0xff, 0x00,
            0x00, 0x00, 0xff,
            0xff, 0x00, 0xff,
            0x00, 0xff, 0xff,
            0xff, 0xff, 0xff,
            0xc6, 0xc6, 0xc6,
            0x84, 0x00, 0x00,
            0x00, 0x84, 0x00,
            0x84, 0x84, 0x00,
            0x00, 0x00, 0x84,
            0x84, 0x00, 0x84,
            0x00, 0x84, 0x84,
            0x84, 0x84, 0x84
    };

//    int eflags;
//    eflags = read_eflags();
//    cli();
    //0x03c8端口设置0号调色板
    outb(0x03c8,0);
    for (int i = 0; i < 16; ++i) {
        outb(0x03c9,*(rgb++));
        outb(0x03c9,*(rgb++));
        outb(0x03c9,*(rgb++));
    }
    int c = 0;
//    restore_eflags(eflags);
    return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
    int x, y;
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++)
            vram[y * xsize + x] = c;
    }
    return;
}