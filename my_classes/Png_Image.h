//
// Created by cosmos on 8/4/20.
//

#ifndef RAY_TRACING_PNG_IMAGE_H
#define RAY_TRACING_PNG_IMAGE_H
#include "stb_image.h"
#include "stb_image_write.h"
#include "types.h"
class Png_Image {
public:
    Png_Image(int w, int h, int n = 4) {
        data = new unsigned char[w * h * n];
        data_w = w;
        data_h = h;
        data_n = n;
    }
    Png_Image(Png_Image& other) = delete;
    Png_Image& operator=(Png_Image& other) = delete;

    unsigned char& saveColor(color clr, int row, int col, int alpha=255){
        getIdx(row, col, 0) = clr.x;
        getIdx(row, col, 1) = clr.y;
        getIdx(row, col, 2) = clr.z;
        getIdx(row, col, 3) = alpha;
    }
    int width() { return data_w; }
    int height() { return data_h; }
    int channel() { return data_n; }
    void write(const char* filename){
        stbi_write_png(filename, data_w, data_h, data_n, data, data_w * 4);
    }
    ~Png_Image(){
        stbi_image_free(data);
    }
private:
    unsigned char* data;
    int data_w, data_h, data_n;
    unsigned char& getIdx(int row, int col, int rgba){
        return *(data + (row * data_w + col) * data_n + rgba);
    }
};
#endif //RAY_TRACING_PNG_IMAGE_H
