#pragma once
#include <iostream>
#include <random>
#include "PreOpenCVHeaders.h"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "PostOpenCVHeaders.h"
#include "Interfaces/IPluginManager.h"
#include "HairAgingUtils.h"
#include "HeadSegmentation.h"


int mapping_default[] = { 6,1,4,2,3,7,0,5 }; //mapping used for mapcluster2region when the default head segmentation is chosen

#define NUM_REGIONS 5 // Actual number of regions we use in our simulation (temporal, parietal, frontal, occipital and vertex)
enum regionnum {
TEMPORAL = 0,
FRONTAL = 1,
PARIETAL = 2,
VERTEX = 3,
OCCIPITAL = 4,
FACE = 5,
NECK = 6,
OTHER = 7
};

enum male_sigma1 { //SDs for male model, following the aging rates observed by Tobin[2008]
MALE_TEMPORAL = 18,
MALE_VERTEX = 15,
MALE_OCCIPITAL = 11,
MALE_OTHERS = 13
};

enum female_sigma1 { //SDs for females, where parietal and frontal are the first regions to gray [Acer et al. 2020]
	FEMALE_TEMPORAL = 11,
	FEMALE_VERTEX = 11,
	FEMALE_OCCIPITAL = 9,
	FEMALE_OTHERS = 14
};


using namespace cv;


UTexture2D* createParameterTexture(Mat labels, float agingScale, int* mapcluster2region, bool bIsMaleCharacter, bool bUseDefaultSeg, FString characterName);
Mat initDefaultCentroids();
float calcL2(Vec3f default_centroid, float* centroid);  //calculates the eucledian distance between a given default centroid and the new centroid
int findMostSimilarRegion(Mat defaultCentroids,float* centroid); // finds the region with the most similar values 
void determineHeadRegionforClusters(Mat new_centroids, int* mapcluster2region); //as K-Means does not returns the same cluster order, we must identify which cluster corresponds to the region
