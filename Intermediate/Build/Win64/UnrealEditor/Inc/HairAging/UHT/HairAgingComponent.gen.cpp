// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HairAging/Public/HairAgingComponent.h"
#include "HairStrandsCore/Public/GroomAssetRendering.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHairAgingComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	HAIRAGING_API UClass* Z_Construct_UClass_UHairAgingComponent();
	HAIRAGING_API UClass* Z_Construct_UClass_UHairAgingComponent_NoRegister();
	HAIRSTRANDSCORE_API UScriptStruct* Z_Construct_UScriptStruct_FHairGeometrySettings();
	HAIRSTRANDSCORE_API UScriptStruct* Z_Construct_UScriptStruct_FHairGroupsRendering();
	UPackage* Z_Construct_UPackage__Script_HairAging();
// End Cross Module References
	DEFINE_FUNCTION(UHairAgingComponent::execsetHairGeometrySettings)
	{
		P_GET_STRUCT_REF(FHairGroupsRendering,Z_Param_Out_hairGroups);
		P_GET_STRUCT(FHairGeometrySettings,Z_Param_geometrySettings);
		P_FINISH;
		P_NATIVE_BEGIN;
		UHairAgingComponent::setHairGeometrySettings(Z_Param_Out_hairGroups,Z_Param_geometrySettings);
		P_NATIVE_END;
	}
	void UHairAgingComponent::StaticRegisterNativesUHairAgingComponent()
	{
		UClass* Class = UHairAgingComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "setHairGeometrySettings", &UHairAgingComponent::execsetHairGeometrySettings },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics
	{
		struct HairAgingComponent_eventsetHairGeometrySettings_Parms
		{
			FHairGroupsRendering hairGroups;
			FHairGeometrySettings geometrySettings;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_hairGroups;
		static const UECodeGen_Private::FStructPropertyParams NewProp_geometrySettings;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::NewProp_hairGroups = { "hairGroups", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(HairAgingComponent_eventsetHairGeometrySettings_Parms, hairGroups), Z_Construct_UScriptStruct_FHairGroupsRendering, METADATA_PARAMS(nullptr, 0) }; // 1320480435
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::NewProp_geometrySettings = { "geometrySettings", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(HairAgingComponent_eventsetHairGeometrySettings_Parms, geometrySettings), Z_Construct_UScriptStruct_FHairGeometrySettings, METADATA_PARAMS(nullptr, 0) }; // 2103870983
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::NewProp_hairGroups,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::NewProp_geometrySettings,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::Function_MetaDataParams[] = {
		{ "Category", "HairAgingPlugin" },
		{ "Keywords", "set, hairgroups, geometrysettings" },
		{ "ModuleRelativePath", "Public/HairAgingComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHairAgingComponent, nullptr, "setHairGeometrySettings", nullptr, nullptr, sizeof(Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::HairAgingComponent_eventsetHairGeometrySettings_Parms), Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UHairAgingComponent);
	UClass* Z_Construct_UClass_UHairAgingComponent_NoRegister()
	{
		return UHairAgingComponent::StaticClass();
	}
	struct Z_Construct_UClass_UHairAgingComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHairAgingComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_HairAging,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UHairAgingComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UHairAgingComponent_setHairGeometrySettings, "setHairGeometrySettings" }, // 532313938
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHairAgingComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "HairAgingComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/HairAgingComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHairAgingComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHairAgingComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UHairAgingComponent_Statics::ClassParams = {
		&UHairAgingComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UHairAgingComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHairAgingComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHairAgingComponent()
	{
		if (!Z_Registration_Info_UClass_UHairAgingComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHairAgingComponent.OuterSingleton, Z_Construct_UClass_UHairAgingComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UHairAgingComponent.OuterSingleton;
	}
	template<> HAIRAGING_API UClass* StaticClass<UHairAgingComponent>()
	{
		return UHairAgingComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHairAgingComponent);
	UHairAgingComponent::~UHairAgingComponent() {}
	struct Z_CompiledInDeferFile_FID_Users_arthu_OneDrive_Documents_HairAging32_HostProject_Plugins_HairAging_Source_HairAging_Public_HairAgingComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_arthu_OneDrive_Documents_HairAging32_HostProject_Plugins_HairAging_Source_HairAging_Public_HairAgingComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UHairAgingComponent, UHairAgingComponent::StaticClass, TEXT("UHairAgingComponent"), &Z_Registration_Info_UClass_UHairAgingComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHairAgingComponent), 49793819U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_arthu_OneDrive_Documents_HairAging32_HostProject_Plugins_HairAging_Source_HairAging_Public_HairAgingComponent_h_3835544194(TEXT("/Script/HairAging"),
		Z_CompiledInDeferFile_FID_Users_arthu_OneDrive_Documents_HairAging32_HostProject_Plugins_HairAging_Source_HairAging_Public_HairAgingComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_arthu_OneDrive_Documents_HairAging32_HostProject_Plugins_HairAging_Source_HairAging_Public_HairAgingComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
