#include "HeadSegmentation.h"
using namespace cv;

Mat modifyNormalMap(Mat img) {
	img.convertTo(img, CV_32FC3);
	
	for (int i = 0; i < TEXSIZE; i++) {
		for (int j = 0; j < TEXSIZE; j++) {
			if (img.at<Vec3f>(i, j)[2] < 128)//mirror y axis
				img.at<Vec3f>(i, j)[2] = 255 - img.at<Vec3f>(i, j)[2];

			img.at<Vec3f>(i, j)[1] = int(double(img.at<Vec3f>(i, j)[1]) * normalWeight); //scales the normal value in this axis, allowing K-Means to be more precise
			img.at<Vec3f>(i, j)[2] = int(double(img.at<Vec3f>(i, j)[2]) * normalWeight);
		}
	}
	img.convertTo(img, CV_8UC3);
	return img;
}

Mat applyClustering(Mat img, Mat* centroids, FString subjectName) {
	Mat  clusterLabels, result, centers;

	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 10, 1.0);
	img.convertTo(img, CV_32FC3);

	Mat segmentationImg(img.size(), img.type());
	Mat points(img.rows * img.cols, img.channels(), CV_32F);


	for (auto y = 0; y < TEXSIZE; y++) {
		for (auto x = 0; x < TEXSIZE; x++) {
			for (auto c = 0; c < img.channels(); c++) {
				points.at<float>(y + x * img.rows, c) = img.at<Vec3f>(y, x)[c]; //convert Mat img to format accepted by K-Means
			}
		}
	}

	 kmeans(points, K, clusterLabels, criteria, 10, KMEANS_PP_CENTERS, centers); //K-Means
	
	for (auto y = 0; y < TEXSIZE; y++) {
		for (auto x = 0; x < TEXSIZE; x++) {
			int cluster_idx = clusterLabels.at<int>(y + x * img.rows, 0);
			for (auto c = 0; c < img.channels(); c++) {
				segmentationImg.at<Vec3f>(y, x)[c] = centers.at<float>(cluster_idx, c); //convert the segmentation result to Mat
			}
		}
	}
	
	*centroids = centers.clone(); //save the new centroid values, which will be used to order the segmented regions
	segmentationImg.convertTo(segmentationImg, CV_8UC3);
	FString pckgName = "/Game/HairAging/" + subjectName + "/Segmentation/";
	FString texName = "Segmentation_" + subjectName;
	createTexFromImg(segmentationImg, pckgName, texName, true); //creates a texture for the segmentation
	return clusterLabels;
	
}

Mat Segmentation(std::string path, Mat* centroids, FString subjectName) {
	Mat img = readImage(path);
	img = modifyNormalMap(img);
	Mat labels = applyClustering(img,centroids, subjectName);


	return labels; //returns cluster labels 
}