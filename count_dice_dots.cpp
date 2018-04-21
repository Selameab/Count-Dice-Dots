/*
 * File:   count_dice_dots.cpp
 * Author: Selameab
 */

#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
  // Check args
  if( argc != 3)
  {
    cout <<"Usage: count_dice_dots input_image output_image" << endl;
    return -1;
  }

  // Variables
  Mat img, threshImg;

  // Read image
  img = imread(argv[1], CV_LOAD_IMAGE_COLOR);

  // Display image
  namedWindow(argv[1], WINDOW_AUTOSIZE);
  imshow(argv[1], img);
  waitKey(0);

  // Save to file
  imwrite(argv[2], img);

  return 0;
}
