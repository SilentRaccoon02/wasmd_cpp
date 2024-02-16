#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

extern "C" {
uint8_t *testArray(uint8_t *inData, uint16_t length);
uint8_t *processImage(uint8_t *inPointer, uint16_t width, uint16_t height);
}

uint8_t *testArray(uint8_t *inPointer, uint16_t length) {
    uint8_t *outPointer = static_cast<uint8_t *>(malloc(length * sizeof(uint8_t)));

    for (uint16_t i = 0; i < length; ++i) {
        outPointer[i] = inPointer[i] * 2;
    }

    return outPointer;
}

uint8_t *processImage(uint8_t *inPointer, uint16_t width, uint16_t height) {
    Mat inImage(height, width, CV_8UC4);
    size_t inSize = height * width * 4 * sizeof(uint8_t);
    memcpy(inImage.data, inPointer, inSize);

    Mat gray;
    Mat canny;
    Mat blurred;
    cvtColor(inImage, gray, COLOR_RGBA2GRAY);
    medianBlur(gray, blurred, 5);
    Canny(blurred, canny, 80, 240);

    vector<Mat> channels;
    Mat empty = Mat::zeros(Size(blurred.cols, blurred.rows), CV_8UC1);
    channels.push_back(canny);
    channels.push_back(empty);
    channels.push_back(empty);
    channels.push_back(empty);

    Mat red;
    Mat outImage;
    cvtColor(gray, outImage, COLOR_GRAY2RGBA);
    merge(channels, red);
    add(outImage, red, outImage);

    size_t outSize = outImage.total() * outImage.elemSize();
    uint8_t *outPointer = static_cast<uint8_t *>(malloc(outSize));
    memcpy(outPointer, outImage.data, outSize);
    return outPointer;
}
