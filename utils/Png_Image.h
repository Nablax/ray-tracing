//
// Created by cosmos on 8/4/20.
//

#ifndef RAY_TRACING_PNG_IMAGE_H
#define RAY_TRACING_PNG_IMAGE_H
#include "stb_image.h"
#include "stb_image_write.h"
#include "utility.h"
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

    void saveColor(color clr, int row, int col, int samples_per_pixel = 1){
        double crate = color_scale / samples_per_pixel;
        getIdx(row, col, 0) = clamp(clr.x * crate, 0, 255);
        getIdx(row, col, 1) = clamp(clr.y * crate, 0, 255);
        getIdx(row, col, 2) = clamp(clr.z * crate, 0, 255);
        getIdx(row, col, 3) = alpha_scale;
    }

    void saveColorSeq(color clr, int samples_per_pixel = 1){
        double crate = color_scale / samples_per_pixel;
        *(data + curIdx++) = clamp(clr.x * crate, 0, 255);
        *(data + curIdx++) = clamp(clr.y * crate, 0, 255);
        *(data + curIdx++) = clamp(clr.z * crate, 0, 255);
        *(data + curIdx++) = alpha_scale;
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
    const double color_scale = 255.999, alpha_scale = 255.999;
    unsigned char& getIdx(int row, int col, int rgba){
        return *(data + (row * data_w + col) * data_n + rgba);
    }
};
#endif //RAY_TRACING_PNG_IMAGE_H
