#include "Png_Image.h"
#include "types.h"
int main(){
    Png_Image png(1800, 900);
    for (int row = 0; row < png.height(); row++) {
        for (int col = 0; col < png.width(); col++) {
            color a = color(255.99 * float(col)/float(png.width()), 255.99 * float(row)/float(png.height()), 0.25 * 255.99);
            png.saveColor(a, row, col);
        }
    }
    png.write("helloworld.png");
    return 0;
}