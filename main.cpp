#include <iostream>
#include <lz4.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void compress(Mat image) {
  const char *raw_image_data = (const char *) image.data;
  const size_t raw_image_size = image.dataend - image.datastart;
  const size_t max_compressed_image_size = LZ4_compressBound(raw_image_size);
  char *compressed_image = (char *) malloc(max_compressed_image_size);
  if (compressed_image == NULL) {
    cerr << "Failed to compress image" << endl;
    return;
  }

  const int compressed_image_size = LZ4_compress_default(raw_image_data, compressed_image, raw_image_size, max_compressed_image_size);
  cout << static_cast<float>(compressed_image_size) / raw_image_size << endl;
  // compressed_image = (char *) realloc(compressed_image, compressed_image_size);
  free(compressed_image);
}

int main() {
  VideoCapture cap(1); // weird jetson camera is in 0 slot -Simon, 7/31
  Mat myImage;
  while (cap.isOpened()) {
    cap >> myImage;
    GaussianBlur(myImage, myImage, Size(7, 7), 1.5, 1.5);
    compress(myImage);
  }
}
