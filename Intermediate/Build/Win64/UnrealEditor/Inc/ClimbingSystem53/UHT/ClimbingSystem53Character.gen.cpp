// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ClimbingSystem53/ClimbingSystem53Character.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeClimbingSystem53Character() {}
// Cross Module References
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_AClimbingSystem53Character();
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_AClimbingSystem53Character_NoRegister();
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_UCustomMovementComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ClimbingSystem53();
// End Cross Module References
	void AClimbingSystem53Character::StaticRegisterNativesAClimbingSystem53Character()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AClimbingSystem53Character);
	UClass* Z_Construct_UClass_AClimbingSystem53Character_NoRegister()
	{
		return AClimbingSystem53Character::StaticClass();
	}
	struct Z_Construct_UClass_AClimbingSystem53Character_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CustomMovementComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CustomMovementComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClimbAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ClimbAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SwimAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SwimAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FlyAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FlyAction;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AClimbingSystem53Character_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_ClimbingSystem53,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "ClimbingSystem53Character.h" },
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CameraBoom_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CameraBoom_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Follow camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Follow camera" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FollowCamera_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FollowCamera_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CustomMovementComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Movement" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CustomMovementComponent = { "CustomMovementComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, CustomMovementComponent), Z_Construct_UClass_UCustomMovementComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CustomMovementComponent_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CustomMovementComponent_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** MappingContext */" },
#endif
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "MappingContext" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_DefaultMappingContext_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_DefaultMappingContext_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_JumpAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_JumpAction_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_JumpAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_MoveAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_MoveAction_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_MoveAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_LookAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_LookAction_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_LookAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_ClimbAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Climb Input Action */" },
#endif
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Climb Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_ClimbAction = { "ClimbAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, ClimbAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_ClimbAction_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_ClimbAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_SwimAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Swim Input Action */" },
#endif
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Swim Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_SwimAction = { "SwimAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, SwimAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_SwimAction_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_SwimAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FlyAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fly Input Action */" },
#endif
		{ "ModuleRelativePath", "ClimbingSystem53Character.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fly Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FlyAction = { "FlyAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AClimbingSystem53Character, FlyAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FlyAction_MetaData), Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FlyAction_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AClimbingSystem53Character_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CameraBoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FollowCamera,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_CustomMovementComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_DefaultMappingContext,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_JumpAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_MoveAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_LookAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_ClimbAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_SwimAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AClimbingSystem53Character_Statics::NewProp_FlyAction,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AClimbingSystem53Character_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AClimbingSystem53Character>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AClimbingSystem53Character_Statics::ClassParams = {
		&AClimbingSystem53Character::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AClimbingSystem53Character_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::Class_MetaDataParams), Z_Construct_UClass_AClimbingSystem53Character_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AClimbingSystem53Character_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AClimbingSystem53Character()
	{
		if (!Z_Registration_Info_UClass_AClimbingSystem53Character.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AClimbingSystem53Character.OuterSingleton, Z_Construct_UClass_AClimbingSystem53Character_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AClimbingSystem53Character.OuterSingleton;
	}
	template<> CLIMBINGSYSTEM53_API UClass* StaticClass<AClimbingSystem53Character>()
	{
		return AClimbingSystem53Character::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AClimbingSystem53Character);
	AClimbingSystem53Character::~AClimbingSystem53Character() {}
	struct Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53Character_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53Character_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AClimbingSystem53Character, AClimbingSystem53Character::StaticClass, TEXT("AClimbingSystem53Character"), &Z_Registration_Info_UClass_AClimbingSystem53Character, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AClimbingSystem53Character), 3725087090U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53Character_h_1215537272(TEXT("/Script/ClimbingSystem53"),
		Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53Character_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_ClimbingSystem53Character_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
