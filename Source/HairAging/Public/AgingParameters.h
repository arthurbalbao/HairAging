#pragma once

//[Rosenberg et al. 2021]
#define AVG_SIG1 13 //default standard deviation for b1, used for an average greyer 
#define LATE_SIG1 8 // SD for a late greyer
#define EARLY_SIG1 25 // SD for an early greyer 
#define BETA 16 //default value for Beta1 

bool createAgingMatInstances(UTexture2D* parameterTex, float agingScale, FString characterName);
float calcBiologicalAgingRate(float agingScale);