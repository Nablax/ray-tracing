#include "Png_Image.h"
int main(){
    unsigned char* data = new unsigned char[200 * 100 * 4];
    Png_Image png(data, 200, 100, 4);
    for (int row = 0; row < png.height(); row++) {
        for (int col = 0; col < png.width(); col++) {
            png.getIdx(row, col, 0) = (unsigned char)(255.99 * float(col)/float(png.width()));
            png.getIdx(row, col, 1) = (unsigned char)(255.99 * float(row)/float(png.height()));
            png.getIdx(row, col, 2) = 0.2;
            png.getIdx(row, col, 3) = 255;
        }
    }
    png.write("test.png");
    return 0;
}