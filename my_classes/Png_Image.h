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
        imgSize = w * h * n;
    }
    Png_Image(Png_Image& other) = delete;
    Png_Image& operator=(Png_Image& other) = delete;

    void saveColor(color clr, int row, int col, int alpha=1){
        getIdx(row, col, 0) = clr.x * color_rate;
        getIdx(row, col, 1) = clr.y * color_rate;
        getIdx(row, col, 2) = clr.z * color_rate;
        getIdx(row, col, 3) = alpha * color_rate;
    }

    void saveColorSeq(color clr, int alpha=1){
        *(data + curIdx++) = clr.x * color_rate;
        *(data + curIdx++) = clr.y * color_rate;
        *(data + curIdx++) = clr.z * color_rate;
        *(data + curIdx++) = alpha * color_rate;
        curIdx %= imgSize;
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
    int imgSize;
    int curIdx = 0;
    const double color_rate = 255.999;
    unsigned char& getIdx(int row, int col, int rgba){
        return *(data + (row * data_w + col) * data_n + rgba);
    }
};
#endif //RAY_TRACING_PNG_IMAGE_H
