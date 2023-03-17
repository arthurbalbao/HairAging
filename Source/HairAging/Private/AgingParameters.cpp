#include "AgingParameters.h"
bool createAgingMatInstances(UTexture2D* parameterTex, float agingScale, FString characterName)
{
	FString texPath = "/HairAging/Textures/AgingParameters_Facial";
	UTexture2D* facialTex = LoadObject<UTexture2D>(nullptr, *texPath);
	FString PackageName = "/Game/HairAging/" + characterName + "/Materials/";
	FString matPath = "/HairAging/Materials/M_DynamicAging";
	FString miName = "MI_HairAging_" + characterName;
	FString facialName = "MI_HairAging_" + characterName + "_Facial";

	
	UMaterialInstanceConstant* hairAgingInstance = createMatInstance(matPath, miName, PackageName);
	UMaterialInstanceConstant* hairAgingFacial = createMatInstance(matPath, facialName, PackageName);

	if (hairAgingInstance != nullptr) {
		hairAgingInstance->SetTextureParameterValueEditorOnly(FName("AgingParameters"), parameterTex);
		hairAgingFacial->SetTextureParameterValueEditorOnly(FName("AgingParameters"), facialTex);
		hairAgingFacial->SetScalarParameterValueEditorOnly(FName("Beta1"), BETA * agingScale);
		return true;
	}
	else
		return false;
}

float calcBiologicalAgingRate(float agingScale){
	if (agingScale > .5f) {
	float alpha = (agingScale - .5f) * 2;//remapping to 0-1 interval so we can lerp between AVG_SIG1 and EARLY_SIG1
	return  (AVG_SIG1 + alpha * (EARLY_SIG1 - AVG_SIG1)) / AVG_SIG1;
	}
	else {
		float alpha = agingScale * 2;
		return (LATE_SIG1 + alpha * (AVG_SIG1 - LATE_SIG1)) / AVG_SIG1; //linear interp between average and late sigma
	}
}
