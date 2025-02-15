// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ClimbingSystem53/Public/Components/CustomMovementComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomMovementComponent() {}
// Cross Module References
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_UCustomMovementComponent();
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_UCustomMovementComponent_NoRegister();
	CLIMBINGSYSTEM53_API UEnum* Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode();
	ENGINE_API UClass* Z_Construct_UClass_UCharacterMovementComponent();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_EObjectTypeQuery();
	UPackage* Z_Construct_UPackage__Script_ClimbingSystem53();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECustomMovementMode;
	static UEnum* ECustomMovementMode_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ECustomMovementMode.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ECustomMovementMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode, (UObject*)Z_Construct_UPackage__Script_ClimbingSystem53(), TEXT("ECustomMovementMode"));
		}
		return Z_Registration_Info_UEnum_ECustomMovementMode.OuterSingleton;
	}
	template<> CLIMBINGSYSTEM53_API UEnum* StaticEnum<ECustomMovementMode::Type>()
	{
		return ECustomMovementMode_StaticEnum();
	}
	struct Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode_Statics::Enumerators[] = {
		{ "ECustomMovementMode::MOVE_Climb", (int64)ECustomMovementMode::MOVE_Climb },
		{ "ECustomMovementMode::MOVE_Fly", (int64)ECustomMovementMode::MOVE_Fly },
		{ "ECustomMovementMode::MOVE_Swim", (int64)ECustomMovementMode::MOVE_Swim },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
		{ "MOVE_Climb.DisplayName", "Climb Mode" },
		{ "MOVE_Climb.Name", "ECustomMovementMode::MOVE_Climb" },
		{ "MOVE_Fly.DisplayName", "Fly Mode" },
		{ "MOVE_Fly.Name", "ECustomMovementMode::MOVE_Fly" },
		{ "MOVE_Swim.DisplayName", "Swim Mode" },
		{ "MOVE_Swim.Name", "ECustomMovementMode::MOVE_Swim" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_ClimbingSystem53,
		nullptr,
		"ECustomMovementMode",
		"ECustomMovementMode::Type",
		Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode_Statics::Enumerators,
		RF_Public|RF_Transient|RF_MarkAsNative,
		UE_ARRAY_COUNT(Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode_Statics::Enumerators),
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::Namespaced,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode_Statics::Enum_MetaDataParams)
	};
	UEnum* Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode()
	{
		if (!Z_Registration_Info_UEnum_ECustomMovementMode.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECustomMovementMode.InnerSingleton, Z_Construct_UEnum_ClimbingSystem53_ECustomMovementMode_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ECustomMovementMode.InnerSingleton;
	}
	void UCustomMovementComponent::StaticRegisterNativesUCustomMovementComponent()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCustomMovementComponent);
	UClass* Z_Construct_UClass_UCustomMovementComponent_NoRegister()
	{
		return UCustomMovementComponent::StaticClass();
	}
	struct Z_Construct_UClass_UCustomMovementComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_ClimableSurfaceTraceTypes_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClimableSurfaceTraceTypes_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ClimableSurfaceTraceTypes;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClimbCapsuleTraceRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ClimbCapsuleTraceRadius;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClimbCapsuleTraceHalfHeight_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ClimbCapsuleTraceHalfHeight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCustomMovementComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCharacterMovementComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_ClimbingSystem53,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Components/CustomMovementComponent.h" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimableSurfaceTraceTypes_Inner = { "ClimableSurfaceTraceTypes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_Engine_EObjectTypeQuery, METADATA_PARAMS(0, nullptr) }; // 3930035403
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimableSurfaceTraceTypes_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement : Climbing" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimableSurfaceTraceTypes = { "ClimableSurfaceTraceTypes", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, ClimableSurfaceTraceTypes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimableSurfaceTraceTypes_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimableSurfaceTraceTypes_MetaData) }; // 3930035403
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement : Climbing" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius = { "ClimbCapsuleTraceRadius", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, ClimbCapsuleTraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Character Movement : Climbing" },
		{ "ModuleRelativePath", "Public/Components/CustomMovementComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight = { "ClimbCapsuleTraceHalfHeight", nullptr, (EPropertyFlags)0x0040000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCustomMovementComponent, ClimbCapsuleTraceHalfHeight), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight_MetaData), Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCustomMovementComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimableSurfaceTraceTypes_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimableSurfaceTraceTypes,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceRadius,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCustomMovementComponent_Statics::NewProp_ClimbCapsuleTraceHalfHeight,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCustomMovementComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCustomMovementComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCustomMovementComponent_Statics::ClassParams = {
		&UCustomMovementComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCustomMovementComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UCustomMovementComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCustomMovementComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UCustomMovementComponent()
	{
		if (!Z_Registration_Info_UClass_UCustomMovementComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCustomMovementComponent.OuterSingleton, Z_Construct_UClass_UCustomMovementComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCustomMovementComponent.OuterSingleton;
	}
	template<> CLIMBINGSYSTEM53_API UClass* StaticClass<UCustomMovementComponent>()
	{
		return UCustomMovementComponent::StaticClass();
	}
	UCustomMovementComponent::UCustomMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCustomMovementComponent);
	UCustomMovementComponent::~UCustomMovementComponent() {}
	struct Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_Components_CustomMovementComponent_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_Components_CustomMovementComponent_h_Statics::EnumInfo[] = {
		{ ECustomMovementMode_StaticEnum, TEXT("ECustomMovementMode"), &Z_Registration_Info_UEnum_ECustomMovementMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2720674388U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_Components_CustomMovementComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCustomMovementComponent, UCustomMovementComponent::StaticClass, TEXT("UCustomMovementComponent"), &Z_Registration_Info_UClass_UCustomMovementComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCustomMovementComponent), 1487209201U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_Components_CustomMovementComponent_h_4177411987(TEXT("/Script/ClimbingSystem53"),
		Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_Components_CustomMovementComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_Components_CustomMovementComponent_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_Components_CustomMovementComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_Components_CustomMovementComponent_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
