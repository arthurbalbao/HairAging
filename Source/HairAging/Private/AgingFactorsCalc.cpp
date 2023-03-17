
#include "AgingFactorsCalc.h"

UTexture2D* createParameterTexture(Mat labels, float AgingScale, int* mapcluster2region, bool bIsMaleCharacter, bool bUseCustomSegmentation,FString characterName) {

	Mat paramImg(TEXSIZE, TEXSIZE, CV_8UC1, Scalar(0));


	float* b1Sigma = new float[NUM_REGIONS];
	if (bIsMaleCharacter) { //define the parameter standard deviation according to gender and head region, in order to speed up/slow down aging
		b1Sigma[TEMPORAL] = MALE_TEMPORAL;
		b1Sigma[FRONTAL] = MALE_OTHERS;
		b1Sigma[PARIETAL] = MALE_OTHERS;
		b1Sigma[VERTEX] = MALE_VERTEX;
		b1Sigma[OCCIPITAL] = MALE_OCCIPITAL;
	}
	else{
		b1Sigma[TEMPORAL] = FEMALE_TEMPORAL;
		b1Sigma[FRONTAL] = FEMALE_OTHERS;
		b1Sigma[PARIETAL] = FEMALE_OTHERS;
		b1Sigma[VERTEX] = FEMALE_VERTEX;
		b1Sigma[OCCIPITAL] = FEMALE_OCCIPITAL;
	}

	for (int i = 0; i < NUM_REGIONS; i++) //also multiply by the AgingScale, allowing for early/late greyers
		b1Sigma[i] *= AgingScale;

	if (bUseCustomSegmentation) { //if using custom segmentation, reshape the labels to 2048x2048 format
		labels.convertTo(labels, CV_8U);
		labels = labels.reshape(1, TEXSIZE);
		labels = labels.t();
	}
	else { //otherwise, just load the default cluster label img from file
		mapcluster2region = &(mapping_default[0]);
		FString filename = "/labels.png";
		FString ContentPath = IPluginManager::Get().FindPlugin(TEXT("HairAging"))->GetContentDir(); //get plugin content dir
		FString path = ContentPath + filename; 
		labels = imread(std::string(TCHAR_TO_UTF8(*path)), cv::IMREAD_GRAYSCALE); //read img with cluster idx for each pixel
	}
	std::default_random_engine generator;
	std::normal_distribution<float> b1_temporalDist(0.0, b1Sigma[TEMPORAL]);
	std::normal_distribution<float> b1_vertexDist(0.0, b1Sigma[VERTEX]);
	std::normal_distribution<float> b1_frontalDist(0.0, b1Sigma[FRONTAL]);
	std::normal_distribution<float> b1_parietalDist(0.0, b1Sigma[PARIETAL]);
	std::normal_distribution<float> b1_occipitalDist(0.0, b1Sigma[OCCIPITAL]);
	

	for (auto y = 0; y < TEXSIZE; y++) {  //read the cluster index for each pixel and sample from the appropriate distribution.
		for (auto x = 0; x < TEXSIZE; x++) {
			int cluster_idx = labels.at<uint8>(y, x);
			int headregion = mapcluster2region[cluster_idx]; //the previous calculated mapping determines the correct region for each pixel
			switch (headregion) { 
			case TEMPORAL:
				paramImg.at<uint8>(y, x) = uint8(abs(floor(b1_temporalDist(generator))));
				break;
			case VERTEX:
				paramImg.at<uint8>(y, x) = uint8(abs(floor(b1_vertexDist(generator))));
				break;
			case OCCIPITAL:
				paramImg.at<uint8>(y, x) = uint8(abs(floor(b1_occipitalDist(generator))));
				break;
			case PARIETAL:
				paramImg.at<uint8>(y, x) = uint8(abs(floor(b1_parietalDist(generator))));
				break;
			case FRONTAL:
				paramImg.at<uint8>(y, x) = uint8(abs(floor(b1_frontalDist(generator))));
				break;
			default:
				paramImg.at<uint8>(y, x) = 0;
				break;
			}
		}
	}
	FString pckgName = "/Game/HairAging/" + characterName + "/Materials/";
	FString b1Tex = "AgingParameters_" + characterName;
	return createTexFromImg(paramImg, pckgName, b1Tex, false); //create and save a texture for the AgingParameter image

}

Mat initDefaultCentroids(){ //initialize default centroids, where each value was empirically found by averaging small/average/large sized heads.
	Mat defaultCentroids(K, 1, CV_32FC3);
	Mat temp(K, 1, CV_32FC3); 
	temp.at<Vec3f>(TEMPORAL, 0) = Vec3f(128.5, 78.5, 185);
	temp.at<Vec3f>(FRONTAL, 0) = Vec3f(198, 30.5, 127.5);
	temp.at<Vec3f>(PARIETAL, 0) = Vec3f(234.5, 96, 131);
	temp.at<Vec3f>(VERTEX, 0) = Vec3f(178.5, 171.5, 122);
	temp.at<Vec3f>(OCCIPITAL, 0) = Vec3f(108, 155, 156.5);
	temp.at<Vec3f>(FACE, 0) = Vec3f(117, 13.5, 134.5);
	temp.at<Vec3f>(NECK, 0) = Vec3f(42.5, 59.5, 143);
	temp.at<Vec3f>(OTHER, 0) = Vec3f(127.5, 96, 96.5);
	temp.copyTo(defaultCentroids);
	return defaultCentroids;
}

float calcL2(Vec3f default_centroid, float* new_centroid)
{
	float distance = 0; //simple eucledian distance calc between a default centroid and the desired new centroid.
	for (int i = 0; i < 3; i++) {
		distance += std::pow(default_centroid[i] - new_centroid[i],2);
	}
	return std::sqrt(distance);
}

int findMostSimilarRegion(Mat defaultCentroids,float* centroid)
{
	float distance;
	float minDistance = 10000.f;
	int bestMatch = -1;
	
	for (int i = 0; i < K; i++) { //finds the closest default centroid index and returns it
		distance = calcL2(defaultCentroids.at<Vec3f>(i,0), centroid);
		if (distance < minDistance) {
			bestMatch = i;
			minDistance = distance;
		}

	}
	return bestMatch;
}

void determineHeadRegionforClusters(Mat new_centroids, int* mapcluster2region){
	float centroid[3];
	int region_num;
	Mat defaultCentroids = initDefaultCentroids();

;	for (int i = 0; i < K; i++) {
		for(int j = 0; j < 3; j++)
			centroid[j] = new_centroids.at<float>(i, j);
		region_num = findMostSimilarRegion(defaultCentroids,centroid);
		mapcluster2region[i] = region_num; //attributes the correct head region for each cluster found by the segmentation
	}
return;
}



