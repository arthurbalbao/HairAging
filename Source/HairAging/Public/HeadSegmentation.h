#pragma once
#include "CoreMinimal.h"
#include "HairAgingUtils.h"
#include "PreOpenCVHeaders.h"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "PostOpenCVHeaders.h"
#include <fstream>
#include <string>
#include <sstream>
const int K = 8;
const float normalWeight = .75f; // empirically defined value that scales some normal directions, providing a more accurate segmentation for our purposes
using namespace cv;
using namespace std;

Mat modifyNormalMap(Mat img); // preprocessing done on the baked normal map, resulting in a image similar to 4(a) in our paper
Mat applyClustering(Mat img, Mat* centroids, FString subjectName); //K-Means Segmentation
Mat Segmentation(std::string path, Mat* centroids, FString subjectName); //Segmentation main loop