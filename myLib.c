#include "myLib.h"

u16* videoBuffer = (u16*)0x6000000;

void setPixel(int row, int col, u16 color) {
    videoBuffer[row * 240 + col] = color;
}

void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 161);
}

void drawRectangle(int row, int col, int width, int height, u16 color) {
    for (int r = 0; r < height; r++) {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[(row + r)*240 + col];
        DMA[3].cnt = ((u16)(width)) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
    }
}

void drawImage3(int row, int col, int width, int height, const u16* image) {
    for (int r = 0; r < height; r++) {
        DMA[3].src = &image[r * width];
        DMA[3].dst = &videoBuffer[(row + r)*240 + col];
        DMA[3].cnt = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
    }
}

void delay(int n) {
    volatile int size = 0;
    for(int i=0; i<n*4000; i++)
    {
        size = size + 1;
    }
}