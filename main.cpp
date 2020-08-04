#include "Png_Image.h"
#include <iostream>
int main(){
    Png_Image png(200, 100, 4);
    for (int row = 0; row < 1; row++) {
        for (int col = 0; col < 1; col++) {
            png.getNum(row, col, 0) = 255.99 * float(col)/float(png.width());
            png.getNum(row, col, 1) = 255.99 * float(row)/float(png.height());
            png.getNum(row, col, 2) = 255.99 * 0.25;
            png.getNum(row, col, 3) = 255;
        }
    }
    unsigned char a = png.data[0];
    unsigned char b = png.data[1];
    unsigned char c = png.data[2];
    unsigned char d = png.data[3];
    png.write("test.png");
    return 0;
}