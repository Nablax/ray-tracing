#include "stb_image.h"
#include "stb_image_write.h"
class Png_Image {
public:
    unsigned char* data;
    int data_w, data_h, data_n;
    bool foreign;
public:

    Png_Image(unsigned char* data, int w, int h, int n) {
        this->data = data;
        data_w = w;
        data_h = h;
        data_n = n;
        foreign = false;
    }

    Png_Image(const char* filename){
        data = stbi_load(filename, &data_w, &data_h, &data_n, 0);
        foreign = true;
    }

    Png_Image(Png_Image& other) = delete;
    Png_Image& operator=(Png_Image& other) = delete;

    unsigned char& getIdx(int row, int col, int rgba){
        return *(data + (row * data_w + col) * data_n + rgba);
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
};