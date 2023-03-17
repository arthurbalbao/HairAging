#pragma once
#include "CoreMinimal.h"
#include "PreOpenCVHeaders.h"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "PostOpenCVHeaders.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/Material.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/SavePackage.h"
#include <fstream>
#include <string>
#include <sstream>


using namespace cv;
using namespace std;

#define TEXSIZE 2048
UTexture2D* createTexFromImg(Mat img, FString pckgName, FString texName, bool bIsBGRA);
Mat readImage(std::string filename);
UMaterialInstanceConstant* createMatInstance(FString matPath, FString instanceName, FString pckgName);
bool checkImgDims(std::string filename, int width, int height);
