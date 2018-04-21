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
  int totalDotCount = 0;
  Scalar markingColor = Scalar(0, 200, 0);

  // Read image
  img = imread(argv[1], CV_LOAD_IMAGE_COLOR);

  // Convert to binary image
  inRange(img, Scalar(200, 200, 200), Scalar(255, 255, 255), threshImg);

  // Remove small regions
  Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(1, 1));
  erode(threshImg, threshImg, element);
  dilate(threshImg, threshImg, element);

  // Find contours
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  findContours(threshImg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  // Iterate through contours and count dots
  int dotCount = 0;
  int last_square_index = 0;
  for(int i = 0; i < contours.size(); i++){
    // Check if contour is top-level (outer edge of dice)
    if (hierarchy[i][3] == -1){
      // Reset counter when new square is found
      dotCount = 0;
      last_square_index = i;
    } else {
      // Increment dotCount
      dotCount += 1;

      // Check if contour is last dot in square
      if ((i == contours.size() - 1) || (hierarchy[i + 1][3] == -1)){
          // Increment total dot count
          totalDotCount += dotCount;

          // Write count beside square
          stringstream stream;
          stream << dotCount;
          Moments m = moments(contours[last_square_index]);
          putText(img, stream.str(), Point(m.m10 / m.m00 + 100, m.m01 / m.m00), FONT_HERSHEY_PLAIN, 2, markingColor, 2);
      }
    }
    drawContours(img, contours, i, markingColor, 2, 8, hierarchy, 0, Point());
  }

  // Write sum on image
  stringstream stream;
  stream << "Sum: " << totalDotCount;
  putText(img, stream.str(), Point(30, 50), FONT_HERSHEY_PLAIN, 2, markingColor, 2);


  // Display image
  namedWindow(argv[1], WINDOW_AUTOSIZE);
  imshow(argv[1], img);
  waitKey(0);

  // Save to file
  imwrite(argv[2], img);

  return 0;
}
