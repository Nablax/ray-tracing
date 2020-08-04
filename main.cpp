#include "Png_Image.h"
int main(){
    Png_Image png(1800, 900, 4);
    for (int row = 0; row < png.height(); row++) {
        for (int col = 0; col < png.width(); col++) {
            png.getIdx(row, col, 0) = 255.99 * float(col)/float(png.width());
            png.getIdx(row, col, 1) = 255.99 * float(row)/float(png.height());
            png.getIdx(row, col, 2) = 0.25 * 255.99;
            png.getIdx(row, col, 3) = 255;
        }
    }
    png.write("test.png");
    return 0;
}