#include "HairAgingUtils.h"


UTexture2D* createTexFromImg(Mat img, FString pckgName, FString texName, bool bIsBGRA) {

	if (bIsBGRA) { //if image is RGB, create an alpha channel
		cv::Mat argb_img;
		cv::cvtColor(img, img, COLOR_RGB2RGBA);
		std::vector<cv::Mat> bgra;
		cv::split(img, bgra);
		bgra[3].setTo(255);
		cv::merge(bgra, img);
	}
	uint8* data = new uint8[img.total() * img.elemSize()];
	std::memcpy(data, img.data, img.total() * img.elemSize());
	
	pckgName += texName;

	bool newTex = false;
	UPackage* Package = nullptr;
	uint8* TextureData = nullptr;
	UTexture2D* res = nullptr;
	FTexturePlatformData* platformData = nullptr;
	UTexture2D* tex = LoadObject<UTexture2D>(nullptr, *pckgName);
	if (tex == nullptr) {
		newTex = true;
		Package = CreatePackage(*pckgName);
		Package->FullyLoad();
		res = NewObject<UTexture2D>(Package, *texName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
		res->AddToRoot();
		res->MipGenSettings = TMGS_NoMipmaps;
		tex = res;
	}
	FTexture2DMipMap* Mip = new FTexture2DMipMap();
	Mip->SizeX = TEXSIZE;
	Mip->SizeY = TEXSIZE;
	platformData = new FTexturePlatformData();	// Then we initialize the PlatformData
	platformData->SizeX = TEXSIZE;
	platformData->SizeY = TEXSIZE;
	platformData->Mips.Empty();
	platformData->Mips.Add(Mip);
	if (bIsBGRA)
		platformData->PixelFormat = EPixelFormat::PF_B8G8R8A8;
	else
		platformData->PixelFormat = EPixelFormat::PF_G8;
	tex->SetPlatformData(platformData);

	platformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	TextureData = static_cast<uint8*>(platformData->Mips[0].BulkData.Realloc(img.total() * img.elemSize()));
	FMemory::Memcpy(TextureData, data, img.total() * img.elemSize());
	platformData->Mips[0].BulkData.Unlock();
	tex->UpdateResource();

	if (bIsBGRA) {
		tex->SRGB = 1;
		tex->Source.Init(TEXSIZE,TEXSIZE,1, 1, ETextureSourceFormat::TSF_BGRA8, reinterpret_cast<uint8*>(data));
	}
	else {
		tex->SRGB = 0;
		tex->Source.Init(TEXSIZE,TEXSIZE,1, 1, ETextureSourceFormat::TSF_G8, reinterpret_cast<uint8*>(data));
	}

	tex->UpdateResource();
	if (newTex) {

		FAssetRegistryModule::AssetCreated(tex);
		FString PackageFileName = FPackageName::LongPackageNameToFilename(pckgName, FPackageName::GetAssetPackageExtension());
		FSavePackageArgs Args;
		Args.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
		UPackage::SavePackage(Package, tex, *PackageFileName,Args);
	}
	return tex;

}


Mat readImage(std::string filename) {

	Mat img(TEXSIZE, TEXSIZE, CV_8UC3);
	img = imread(filename, cv::IMREAD_COLOR);
	return img;
}

UMaterialInstanceConstant* createMatInstance(FString matPath, FString instanceName, FString pckgName){

	UMaterial* chosenMat = LoadObject<UMaterial>(NULL, *matPath, NULL, LOAD_None, NULL);
	if (chosenMat == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find material %s"), *matPath);
		return nullptr;
	}
	FAssetToolsModule& AssetToolsModule =
		FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");

	FString existingPath = pckgName + instanceName;
	UMaterialInstanceConstant* existingInstance = LoadObject<UMaterialInstanceConstant>(NULL, *existingPath, NULL, LOAD_None, NULL);

	if (existingInstance != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Material instance %s already exists! Only replacing textures"), *instanceName);
		return existingInstance;
	}
	UMaterialInstanceConstantFactoryNew* Factory =
		NewObject<UMaterialInstanceConstantFactoryNew>();
	Factory->InitialParent = chosenMat;
	FString Name =  instanceName;

	UMaterialInstanceConstant* matInstance = CastChecked<UMaterialInstanceConstant>(
		AssetToolsModule.Get().CreateAsset(Name,
			FPackageName::GetLongPackagePath(pckgName),
			UMaterialInstanceConstant::StaticClass(),
			Factory));

	return matInstance;
}

bool checkImgDims(std::string filename, int width, int height) {
	Mat img = imread(filename, cv::IMREAD_UNCHANGED);

	if (img.rows != TEXSIZE || img.cols != TEXSIZE)
		return false;
	else
		return true;
}


