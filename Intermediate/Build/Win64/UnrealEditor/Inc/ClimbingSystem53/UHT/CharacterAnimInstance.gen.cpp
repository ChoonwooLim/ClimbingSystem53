// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ClimbingSystem53/Public/AnimInstance/CharacterAnimInstance.h"
#include "../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCharacterAnimInstance() {}
// Cross Module References
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_AClimbingSystem53Character_NoRegister();
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_UCharacterAnimInstance();
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_UCharacterAnimInstance_NoRegister();
	CLIMBINGSYSTEM53_API UClass* Z_Construct_UClass_UCustomMovementComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UAnimInstance();
	UPackage* Z_Construct_UPackage__Script_ClimbingSystem53();
// End Cross Module References
	void UCharacterAnimInstance::StaticRegisterNativesUCharacterAnimInstance()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCharacterAnimInstance);
	UClass* Z_Construct_UClass_UCharacterAnimInstance_NoRegister()
	{
		return UCharacterAnimInstance::StaticClass();
	}
	struct Z_Construct_UClass_UCharacterAnimInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClimbingSystem53Character_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ClimbingSystem53Character;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CustomMovementComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CustomMovementComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GroundSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_GroundSpeed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AirSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AirSpeed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bShouldMove_MetaData[];
#endif
		static void NewProp_bShouldMove_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldMove;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIsFalling_MetaData[];
#endif
		static void NewProp_bIsFalling_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsFalling;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCharacterAnimInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAnimInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_ClimbingSystem53,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterAnimInstance_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "AnimInstance" },
		{ "IncludePath", "AnimInstance/CharacterAnimInstance.h" },
		{ "ModuleRelativePath", "Public/AnimInstance/CharacterAnimInstance.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_ClimbingSystem53Character_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//GC(Garbage Collection) \xef\xbf\xbd\xc3\xbd\xef\xbf\xbd\xef\xbf\xbd\xdb\xbf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xde\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xda\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/AnimInstance/CharacterAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "GC(Garbage Collection) \xef\xbf\xbd\xc3\xbd\xef\xbf\xbd\xef\xbf\xbd\xdb\xbf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xde\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xda\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_ClimbingSystem53Character = { "ClimbingSystem53Character", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterAnimInstance, ClimbingSystem53Character), Z_Construct_UClass_AClimbingSystem53Character_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_ClimbingSystem53Character_MetaData), Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_ClimbingSystem53Character_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_CustomMovementComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xd6\xb4\xcf\xb8\xef\xbf\xbd\xef\xbf\xbd\xcc\xbc\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AnimInstance/CharacterAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd6\xb4\xcf\xb8\xef\xbf\xbd\xef\xbf\xbd\xcc\xbc\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb4\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_CustomMovementComponent = { "CustomMovementComponent", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterAnimInstance, CustomMovementComponent), Z_Construct_UClass_UCustomMovementComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_CustomMovementComponent_MetaData), Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_CustomMovementComponent_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_GroundSpeed_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Reference" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*VisibleAnywhere \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xbf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd, Details \xef\xbf\xbd\xd0\xb3\xce\xbf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd2\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)\n       BlueprintReadOnly \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd, \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.(BlueprintReadWrite\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)\n       Category = Reference \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xab\xef\xbf\xbd\xd7\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \"Reference\"\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd. (\xef\xbf\xbd\xef\xbf\xbd, \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \"Reference\" \xc4\xab\xef\xbf\xbd\xd7\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc6\xb7\xef\xbf\xbd \xc7\xa5\xef\xbf\xbd\xc3\xb5\xef\xbf\xbd)\n       meta = (AllowPrivateAccess = \"true\") \xef\xbf\xbd\xef\xbf\xbd C++\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd private \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd. *///GroundSpeed \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/AnimInstance/CharacterAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "VisibleAnywhere \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xbf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd, Details \xef\xbf\xbd\xd0\xb3\xce\xbf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc8\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd2\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)\n       BlueprintReadOnly \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd, \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.(BlueprintReadWrite\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)\n       Category = Reference \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xab\xef\xbf\xbd\xd7\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \"Reference\"\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd. (\xef\xbf\xbd\xef\xbf\xbd, \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \"Reference\" \xc4\xab\xef\xbf\xbd\xd7\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc6\xb7\xef\xbf\xbd \xc7\xa5\xef\xbf\xbd\xc3\xb5\xef\xbf\xbd)\n       meta = (AllowPrivateAccess = \"true\") \xef\xbf\xbd\xef\xbf\xbd C++\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd private \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd. //GroundSpeed \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_GroundSpeed = { "GroundSpeed", nullptr, (EPropertyFlags)0x0040000000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterAnimInstance, GroundSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_GroundSpeed_MetaData), Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_GroundSpeed_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_AirSpeed_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Reference" },
		{ "ModuleRelativePath", "Public/AnimInstance/CharacterAnimInstance.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_AirSpeed = { "AirSpeed", nullptr, (EPropertyFlags)0x0040000000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterAnimInstance, AirSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_AirSpeed_MetaData), Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_AirSpeed_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bShouldMove_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Reference" },
		{ "ModuleRelativePath", "Public/AnimInstance/CharacterAnimInstance.h" },
	};
#endif
	void Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bShouldMove_SetBit(void* Obj)
	{
		((UCharacterAnimInstance*)Obj)->bShouldMove = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bShouldMove = { "bShouldMove", nullptr, (EPropertyFlags)0x0040000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCharacterAnimInstance), &Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bShouldMove_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bShouldMove_MetaData), Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bShouldMove_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bIsFalling_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Reference" },
		{ "ModuleRelativePath", "Public/AnimInstance/CharacterAnimInstance.h" },
	};
#endif
	void Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bIsFalling_SetBit(void* Obj)
	{
		((UCharacterAnimInstance*)Obj)->bIsFalling = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bIsFalling = { "bIsFalling", nullptr, (EPropertyFlags)0x0040000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UCharacterAnimInstance), &Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bIsFalling_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bIsFalling_MetaData), Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bIsFalling_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCharacterAnimInstance_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_ClimbingSystem53Character,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_CustomMovementComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_GroundSpeed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_AirSpeed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bShouldMove,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterAnimInstance_Statics::NewProp_bIsFalling,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCharacterAnimInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCharacterAnimInstance>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCharacterAnimInstance_Statics::ClassParams = {
		&UCharacterAnimInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCharacterAnimInstance_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::PropPointers),
		0,
		0x009000A8u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UCharacterAnimInstance_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterAnimInstance_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UCharacterAnimInstance()
	{
		if (!Z_Registration_Info_UClass_UCharacterAnimInstance.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCharacterAnimInstance.OuterSingleton, Z_Construct_UClass_UCharacterAnimInstance_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCharacterAnimInstance.OuterSingleton;
	}
	template<> CLIMBINGSYSTEM53_API UClass* StaticClass<UCharacterAnimInstance>()
	{
		return UCharacterAnimInstance::StaticClass();
	}
	UCharacterAnimInstance::UCharacterAnimInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCharacterAnimInstance);
	UCharacterAnimInstance::~UCharacterAnimInstance() {}
	struct Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_AnimInstance_CharacterAnimInstance_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_AnimInstance_CharacterAnimInstance_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCharacterAnimInstance, UCharacterAnimInstance::StaticClass, TEXT("UCharacterAnimInstance"), &Z_Registration_Info_UClass_UCharacterAnimInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCharacterAnimInstance), 842730243U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_AnimInstance_CharacterAnimInstance_h_442508993(TEXT("/Script/ClimbingSystem53"),
		Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_AnimInstance_CharacterAnimInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_00_UnrealWork_ClimbingSystem53_Source_ClimbingSystem53_Public_AnimInstance_CharacterAnimInstance_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
