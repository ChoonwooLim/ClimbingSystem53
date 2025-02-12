// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ClimbingSystem53/ClimbingSystem53GameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeClimbingSystem53GameMode() {}
// Cross Module References
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_AClimbingSystem53GameMode();
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_AClimbingSystem53GameMode_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_ClimbingSystem53();
// End Cross Module References
	void AClimbingSystem53GameMode::StaticRegisterNativesAClimbingSystem53GameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AClimbingSystem53GameMode);
	UClass* Z_Construct_UClass_AClimbingSystem53GameMode_NoRegister()
	{
		return AClimbingSystem53GameMode::StaticClass();
	}
	struct Z_Construct_UClass_AClimbingSystem53GameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AClimbingSystem53GameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ClimbingSystem53,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53GameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53GameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ClimbingSystem53GameMode.h" },
		{ "ModuleRelativePath", "ClimbingSystem53GameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AClimbingSystem53GameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AClimbingSystem53GameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AClimbingSystem53GameMode_Statics::ClassParams = {
		&AClimbingSystem53GameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53GameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AClimbingSystem53GameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AClimbingSystem53GameMode()
	{
		if (!Z_Registration_Info_UClass_AClimbingSystem53GameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AClimbingSystem53GameMode.OuterSingleton, Z_Construct_UClass_AClimbingSystem53GameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AClimbingSystem53GameMode.OuterSingleton;
	}
	template<> CLIMBINGSYSTEM53_API UClass* StaticClass<AClimbingSystem53GameMode>()
	{
		return AClimbingSystem53GameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AClimbingSystem53GameMode);
	AClimbingSystem53GameMode::~AClimbingSystem53GameMode() {}
	struct Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53GameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53GameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AClimbingSystem53GameMode, AClimbingSystem53GameMode::StaticClass, TEXT("AClimbingSystem53GameMode"), &Z_Registration_Info_UClass_AClimbingSystem53GameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AClimbingSystem53GameMode), 465243741U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53GameMode_h_2073562304(TEXT("/Script/ClimbingSystem53"),
		Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53GameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53GameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
