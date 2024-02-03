#include <cstdint>
#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

extern "C" {
uint8_t *processImage(uint8_t *image, uint16_t width, uint16_t height);
}

uint8_t *processImage(uint8_t *image, uint16_t width, uint16_t height) {
    Mat inMat(height, width, CV_8UC4);
    memcpy(inMat.data, image, width * height * 4 * sizeof(uint8_t));

    Mat canny;
    Mat outMat;
    Canny(inMat, canny, 80, 240);
    cvtColor(canny, outMat, COLOR_GRAY2RGBA);

    size_t outImageSize = outMat.total() * outMat.elemSize();
    uint8_t *outImage = static_cast<uint8_t *>(malloc(outImageSize));
    memcpy(outImage, outMat.data, outImageSize);
    return outImage;
}
