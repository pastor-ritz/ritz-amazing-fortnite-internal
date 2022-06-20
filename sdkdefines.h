#pragma once
#include "vector.h"
#include <xmmintrin.h>
#include <immintrin.h>
namespace ue {
	struct FVector
	{
		double X;
		double Y;
		double Z;
	};
	struct FMatrix
	{
		double M[4][4];


	};
	static FMatrix* myMatrix = new FMatrix();

	template<class T>
	struct TArray
	{
		friend struct FString;

	public:
		inline TArray()
		{
			Data = nullptr;
			Count = Max = 0;
		};

		inline int Num() const
		{
			return Count;
		};

		inline T& operator[](int i)
		{
			return Data[i];
		};

		inline const T& operator[](int i) const
		{
			return Data[i];
		};

		inline bool IsValidIndex(int i) const
		{
			return i < Num();
		}

	private:
		T* Data;
		int32_t Count;
		int32_t Max;
	};

	struct FString : private TArray<wchar_t>
	{
		inline FString()
		{
		};

		FString(const wchar_t* other)
		{
			Max = Count = *other ? wcslen(other) + 1 : 0;

			if (Count)
			{
				Data = const_cast<wchar_t*>(other);
			}
		};

		inline bool IsValid() const
		{
			return Data != nullptr;
		}

		inline const wchar_t* c_str() const
		{
			return Data;
		}
		std::string ToString() const
		{
			auto length = std::wcslen(Data);

			std::string str(length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

			return str;
		}
	};

	struct FName
	{
		uint32_t ComparisonIndex;
		uint32_t DisplayIndex;
	};

	struct FKey
	{
		FName KeyName;
		unsigned char Padding_00[0x10];
	};

	struct FLinearColor
	{
		float R;
		float G;
		float B;
		float A;

		FLinearColor()
		{
			R = G = B = A = 0;
		}

		FLinearColor(float R, float G, float B, float A)
		{
			this->R = R;
			this->G = G;
			this->B = B;
			this->A = A;
		}
	};
	struct FPawnHighlight
	{
		float                                              Priority_28_E2E1B5344846E187B9C11B863A7F0698;             // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		FLinearColor                                Inner_21_4CC2801147EA190DE16F59B34F36853E;                // 0x0004(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		FLinearColor                                Outer_22_5A1D7D0543D303E8B54B66A7F7BD2E2E;                // 0x0014(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              FresnelBrightness_23_52B0F96447FF640F47DF2895B0602E92;    // 0x0024(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              FresnelExponent_24_B427CF0C441AA37ED49833BF7579DE6D;      // 0x0028(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              UsesPulse_25_E29229F64E540F0617E4C4987AD77605;            // 0x002C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	};
	struct FRotator
	{
		double Pitch;
		double Yaw;
		double Roll;
	};

	struct FMinimalViewInfo {
		Vector3 Location;
		Vector3 Rotation;
		float FOV;
		float OrthoWidth;
		float OrthoNearClipPlane;
		float OrthoFarClipPlane;
		float AspectRatio;
	};

	class FTextData {
	public:
		char pad_0x0000[0x30];  //0x0000
		wchar_t* Name;          //0x0028 
		__int32 Length;         //0x0030 

	};

	struct FText {
		FTextData* Data;
		char UnknownData[0x10];

		wchar_t* Get() const {
			if (Data) {
				return Data->Name;
			}

			return nullptr;
		}
	};
	namespace classes
	{
		class UClass {
		public:
			BYTE _padding_0[0x40];
			UClass* SuperClass;
		};

		class UObject {
		public:
			PVOID VTableObject;
			DWORD ObjectFlags;
			DWORD InternalIndex;
			UClass* Class;
			BYTE _padding_0[0x8];
			UObject* Outer;

			inline BOOLEAN IsA(PVOID parentClass)
			{
				for (auto super = this->Class; super; super = super->SuperClass)
					if (super == parentClass)
						return true;

				return false;
			}
		};

		class UControl
		{
		public:
			Vector2 Origin;
			Vector2 Size;
			bool* BoundBool = nullptr;
			bool bIsMenuTabControl;
			bool bIsRangeSlider;
			int RangeValueMin;
			int RangeValueMax;
			int* pBoundRangeValue;
			int BoundMenuTabIndex;

			bool ContainsPoint(Vector2 pt)
			{
				auto extent = Origin + Size;
				return (pt.x > Origin.x && pt.y > Origin.y && pt.x < extent.x&& pt.y < extent.y);
			}
		};

		class FUObjectItem {
		public:
			UObject* Object;
			DWORD Flags;
			DWORD ClusterIndex;
			DWORD SerialNumber;
			DWORD SerialNumber2;
		};

		class TUObjectArray {
		public:
			FUObjectItem* Objects[9];
		};

		class GObjects {
		public:
			TUObjectArray* ObjectArray;
			BYTE _padding_0[0xC];
			DWORD ObjectCount;
		};

		inline GObjects* objects = nullptr;
	}
	namespace cached {
		inline uintptr_t Base = 0;

		namespace keys
		{
			inline ue::FKey LButton;
			inline ue::FKey Insert;
		}
		namespace offsets {
			inline uintptr_t OwningGameInstance;
			inline uintptr_t Levels;
			inline uintptr_t AcknowledgedPawn;
			inline uintptr_t PlayerCameraManager;
			inline uintptr_t PlayerState;
			inline uintptr_t bADSWhileNotOnGround;
			inline uintptr_t CurrentWeapon;
			inline uintptr_t TeamIndex;
			inline uintptr_t WeaponData;
			inline uintptr_t DisplayName;
			inline uintptr_t Mesh;
			inline uintptr_t RootComponent;
			inline uintptr_t LastFireTime;
			inline uintptr_t AmmoCount;
			inline uintptr_t LastFireTimeVerified;
			inline uintptr_t RelativeLocation;
			inline uintptr_t Tier;
		}
		namespace signatures
		{
			inline uintptr_t GWorld = 0;
			inline uintptr_t FreeFn = 0;
			
			inline uintptr_t GetNameByIndex = 0;
			inline uintptr_t LineSightOfTo = 0;
			inline uintptr_t GetBoneMatrix = 0;
			inline uintptr_t ProjectWorldToScreen = 0;
			
		}
		inline  ue::classes::UObject* FortKismetLibrary = 0;
		inline  ue::classes::UObject* KismetStringLibrary = 0;
		inline  ue::classes::UObject* KismetMathLibrary = 0;
		inline  ue::classes::UObject* Conv_StringToName = 0;
		inline  ue::classes::UObject* Cos = 0;
		inline  ue::classes::UObject* Sin = 0;


		namespace objects {
			inline ue::classes::UObject* FortProjectileBase = 0;
			inline ue::classes::UObject* AFortAthenaZipline = 0;
			inline ue::classes::UObject* K2_SetActorLocation = 0;
			inline ue::classes::UObject* K2_TeleportTo = 0;
			inline ue::classes::UObject* FortRangedWeaponStats = 0;
			inline ue::classes::UObject* K2_GetActorRotation = 0;
			

			namespace actor {
				inline  ue::classes::UObject* FortPlayerPawnAthena = 0;
				inline  ue::classes::UObject* ClientSetRotation = 0;
				inline  ue::classes::UObject* GetPlayerName = 0;
				inline  ue::classes::UObject* ApplyPawnHighlight = 0;
				inline  ue::classes::UObject* ScalePlayerUp = 0;
				inline  ue::classes::UObject* ScalePlayerDown = 0;
				inline  ue::classes::UObject* isHiddingInProp = 0;
				inline  ue::classes::UObject* Fov = 0;
				inline  ue::classes::UObject* SetMouseLocation = 0;
				inline  ue::classes::UObject* SetCharacterBodyVisibilityForPossession = 0;
				inline  ue::classes::UObject* K2_PayBuildingResourceCost = 0;
				inline  ue::classes::UObject* GetVehicle = 0;
				

				
				

				
				
				
			}
			namespace camera {
				inline ue::classes::UObject* GetCameraLocation = 0; 
				inline ue::classes::UObject* GetCameraRotation = 0;
				inline ue::classes::UObject* GetFOVAngle = 0;
			}
			

			namespace render {
				inline ue::classes::UObject* Font = 0;
				inline ue::classes::UObject* K2_DrawLine = 0;
				inline ue::classes::UObject* K2_DrawBox = 0;
				inline ue::classes::UObject* K2_DrawText = 0;
				inline ue::classes::UObject* K2_TextSize = 0;
			}

		}

	}
}
namespace math {
	inline float custom_sqrtf(float _X)
	{
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(_X)));
	}

	inline float custom_sinf(float _X)
	{
		return _mm_cvtss_f32(_mm_sin_ps(_mm_set_ss(_X)));
	}

	inline float custom_cosf(float _X)
	{
		return _mm_cvtss_f32(_mm_cos_ps(_mm_set_ss(_X)));
	}

	inline float custom_acosf(float _X)
	{
		return _mm_cvtss_f32(_mm_acos_ps(_mm_set_ss(_X)));
	}

	inline float custom_tanf(float _X)
	{
		return _mm_cvtss_f32(_mm_tan_ps(_mm_set_ss(_X)));
	}

	inline float custom_atan2f(float _X, float _Y)
	{
		return _mm_cvtss_f32(_mm_atan2_ps(_mm_set_ss(_X), _mm_set_ss(_Y)));
	}

	inline int custom_compare(const char* X, const char* Y)
	{
		while (*X && *Y) {
			if (*X != *Y) {
				return 0;
			}
			X++;
			Y++;
		}

		return (*Y == '\0');
	}

	inline int custom_wcompare(const wchar_t* X, const wchar_t* Y)
	{
		while (*X && *Y) {
			if (*X != *Y) {
				return 0;
			}
			X++;
			Y++;
		}

		return (*Y == L'\0');
	}

	inline const wchar_t* custom_wcsstr(const wchar_t* X, const wchar_t* Y)
	{
		while (*X != L'\0') {
			if ((*X == *Y) && custom_wcompare(X, Y)) {
				return X;
			}
			X++;
		}
		return NULL;
	}

	inline const char* custom_strstr(const char* X, const char* Y)
	{
		while (*X != '\0') {
			if ((*X == *Y) && custom_compare(X, Y)) {
				return X;
			}
			X++;
		}
		return NULL;
	}

	inline int custom_strlen(const char* string)
	{
		int cnt = 0;
		if (string)
		{
			for (; *string != 0; ++string) ++cnt;
		}
		return cnt;
	}

	inline int custom_wcslen(const wchar_t* string)
	{
		int cnt = 0;
		if (string)
		{
			for (; *string != 0; ++string) ++cnt;
		}
		return cnt;
	}
}

//namespace Colors
//{
//	ue::FLinearColor AliceBlue = { 0.941176534f, 0.972549081f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor AntiqueWhite = { 0.980392218f, 0.921568692f, 0.843137324f, 1.000000000f };
//	ue::FLinearColor Aqua = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor Aquamarine = { 0.498039246f, 1.000000000f, 0.831372619f, 1.000000000f };
//	ue::FLinearColor Azure = { 0.941176534f, 1.000000000f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor Beige = { 0.960784376f, 0.960784376f, 0.862745166f, 1.000000000f };
//	ue::FLinearColor Bisque = { 1.000000000f, 0.894117713f, 0.768627524f, 1.000000000f };
//	ue::FLinearColor Black = { 0.000000000f, 0.000000000f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor BlanchedAlmond = { 1.000000000f, 0.921568692f, 0.803921640f, 1.000000000f };
//	ue::FLinearColor Blue = { 0.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor BlueViolet = { 0.541176498f, 0.168627456f, 0.886274576f, 1.000000000f };
//	ue::FLinearColor Brown = { 0.647058845f, 0.164705887f, 0.164705887f, 1.000000000f };
//	ue::FLinearColor BurlyWood = { 0.870588303f, 0.721568644f, 0.529411793f, 1.000000000f };
//	ue::FLinearColor CadetBlue = { 0.372549027f, 0.619607866f, 0.627451003f, 1.000000000f };
//	ue::FLinearColor Chartreuse = { 0.498039246f, 1.000000000f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor Chocolate = { 0.823529482f, 0.411764741f, 0.117647067f, 1.000000000f };
//	ue::FLinearColor Coral = { 1.000000000f, 0.498039246f, 0.313725501f, 1.000000000f };
//	ue::FLinearColor CornflowerBlue = { 0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f };
//	ue::FLinearColor Cornsilk = { 1.000000000f, 0.972549081f, 0.862745166f, 1.000000000f };
//	ue::FLinearColor Crimson = { 0.862745166f, 0.078431375f, 0.235294133f, 1.000000000f };
//	ue::FLinearColor Cyan = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor DarkBlue = { 0.000000000f, 0.000000000f, 0.545098066f, 1.000000000f };
//	ue::FLinearColor DarkCyan = { 0.000000000f, 0.545098066f, 0.545098066f, 1.000000000f };
//	ue::FLinearColor DarkGoldenrod = { 0.721568644f, 0.525490224f, 0.043137256f, 1.000000000f };
//	ue::FLinearColor DarkGray = { 0.662745118f, 0.662745118f, 0.662745118f, 1.000000000f };
//	ue::FLinearColor DarkGreen = { 0.000000000f, 0.392156899f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor DarkKhaki = { 0.741176486f, 0.717647076f, 0.419607878f, 1.000000000f };
//	ue::FLinearColor DarkMagenta = { 0.545098066f, 0.000000000f, 0.545098066f, 1.000000000f };
//	ue::FLinearColor DarkOliveGreen = { 0.333333343f, 0.419607878f, 0.184313729f, 1.000000000f };
//	ue::FLinearColor DarkOrange = { 1.000000000f, 0.549019635f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor DarkOrchid = { 0.600000024f, 0.196078449f, 0.800000072f, 1.000000000f };
//	ue::FLinearColor DarkRed = { 0.545098066f, 0.000000000f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor DarkSalmon = { 0.913725555f, 0.588235319f, 0.478431404f, 1.000000000f };
//	ue::FLinearColor DarkSeaGreen = { 0.560784340f, 0.737254918f, 0.545098066f, 1.000000000f };
//	ue::FLinearColor DarkSlateBlue = { 0.282352954f, 0.239215702f, 0.545098066f, 1.000000000f };
//	ue::FLinearColor DarkSlateGray = { 0.120f, 0.120f, 0.120f, 1.000000000f };
//	ue::FLinearColor DarkTurquoise = { 0.000000000f, 0.807843208f, 0.819607913f, 1.000000000f };
//	ue::FLinearColor DarkViolet = { 0.580392182f, 0.000000000f, 0.827451050f, 1.000000000f };
//	ue::FLinearColor DeepPink = { 1.000000000f, 0.078431375f, 0.576470613f, 1.000000000f };
//	ue::FLinearColor DeepSkyBlue = { 0.000000000f, 0.749019623f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor DimGray = { 0.411764741f, 0.411764741f, 0.411764741f, 1.000000000f };
//	ue::FLinearColor DodgerBlue = { 0.117647067f, 0.564705908f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor Firebrick = { 0.698039234f, 0.133333340f, 0.133333340f, 1.000000000f };
//	ue::FLinearColor FloralWhite = { 1.000000000f, 0.980392218f, 0.941176534f, 1.000000000f };
//	ue::FLinearColor ForestGreen = { 0.133333340f, 0.545098066f, 0.133333340f, 1.000000000f };
//	ue::FLinearColor Fuchsia = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor Gainsboro = { 0.862745166f, 0.862745166f, 0.862745166f, 1.000000000f };
//	ue::FLinearColor GhostWhite = { 0.972549081f, 0.972549081f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor Gold = { 1.000000000f, 0.843137324f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor Goldenrod = { 0.854902029f, 0.647058845f, 0.125490203f, 1.000000000f };
//	ue::FLinearColor Gray = { 0.501960814f, 0.501960814f, 0.501960814f, 1.000000000f };
//	ue::FLinearColor Green = { 0.000000000f, 0.501960814f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor GreenYellow = { 0.678431392f, 1.000000000f, 0.184313729f, 1.000000000f };
//	ue::FLinearColor Honeydew = { 0.941176534f, 1.000000000f, 0.941176534f, 1.000000000f };
//	ue::FLinearColor HotPink = { 1.000000000f, 0.411764741f, 0.705882370f, 1.000000000f };
//	ue::FLinearColor IndianRed = { 0.803921640f, 0.360784322f, 0.360784322f, 1.000000000f };
//	ue::FLinearColor Indigo = { 0.294117659f, 0.000000000f, 0.509803951f, 1.000000000f };
//	ue::FLinearColor Ivory = { 1.000000000f, 1.000000000f, 0.941176534f, 1.000000000f };
//	ue::FLinearColor Khaki = { 0.941176534f, 0.901960850f, 0.549019635f, 1.000000000f };
//	ue::FLinearColor Lavender = { 0.901960850f, 0.901960850f, 0.980392218f, 1.000000000f };
//	ue::FLinearColor LavenderBlush = { 1.000000000f, 0.941176534f, 0.960784376f, 1.000000000f };
//	ue::FLinearColor LawnGreen = { 0.486274540f, 0.988235354f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor LemonChiffon = { 1.000000000f, 0.980392218f, 0.803921640f, 1.000000000f };
//	ue::FLinearColor LightBlue = { 0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f };
//	ue::FLinearColor LightCoral = { 0.941176534f, 0.501960814f, 0.501960814f, 1.000000000f };
//	ue::FLinearColor LightCyan = { 0.878431439f, 1.000000000f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor LightGoldenrodYellow = { 0.980392218f, 0.980392218f, 0.823529482f, 1.000000000f };
//	ue::FLinearColor LightGreen = { 0.564705908f, 0.933333397f, 0.564705908f, 1.000000000f };
//	ue::FLinearColor LightGray = { 0.827451050f, 0.827451050f, 0.827451050f, 1.000000000f };
//	ue::FLinearColor LightPink = { 1.000000000f, 0.713725507f, 0.756862819f, 1.000000000f };
//	ue::FLinearColor LightSalmon = { 1.000000000f, 0.627451003f, 0.478431404f, 1.000000000f };
//	ue::FLinearColor LightSeaGreen = { 0.125490203f, 0.698039234f, 0.666666687f, 1.000000000f };
//	ue::FLinearColor LightSkyBlue = { 0.529411793f, 0.807843208f, 0.980392218f, 1.000000000f };
//	ue::FLinearColor LightSlateGray = { 0.466666698f, 0.533333361f, 0.600000024f, 1.000000000f };
//	ue::FLinearColor LightSteelBlue = { 0.690196097f, 0.768627524f, 0.870588303f, 1.000000000f };
//	ue::FLinearColor LightYellow = { 1.000000000f, 1.000000000f, 0.878431439f, 1.000000000f };
//	ue::FLinearColor Lime = { 0.000000000f, 1.000000000f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor LimeGreen = { 0.196078449f, 0.803921640f, 0.196078449f, 1.000000000f };
//	ue::FLinearColor Linen = { 0.980392218f, 0.941176534f, 0.901960850f, 1.000000000f };
//	ue::FLinearColor Magenta = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
//	ue::FLinearColor Maroon = { 0.501960814f, 0.000000000f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor MediumAquamarine = { 0.400000036f, 0.803921640f, 0.666666687f, 1.000000000f };
//	ue::FLinearColor MediumBlue = { 0.000000000f, 0.000000000f, 0.803921640f, 1.000000000f };
//	ue::FLinearColor MediumOrchid = { 0.729411781f, 0.333333343f, 0.827451050f, 1.000000000f };
//	ue::FLinearColor MediumPurple = { 0.576470613f, 0.439215720f, 0.858823597f, 1.000000000f };
//	ue::FLinearColor MediumSeaGreen = { 0.235294133f, 0.701960802f, 0.443137288f, 1.000000000f };
//	ue::FLinearColor MediumSlateBlue = { 0.482352972f, 0.407843173f, 0.933333397f, 1.000000000f };
//	ue::FLinearColor MediumSpringGreen = { 0.000000000f, 0.980392218f, 0.603921592f, 1.000000000f };
//	ue::FLinearColor MediumTurquoise = { 0.282352954f, 0.819607913f, 0.800000072f, 1.000000000f };
//	ue::FLinearColor MediumVioletRed = { 0.780392230f, 0.082352944f, 0.521568656f, 1.000000000f };
//	ue::FLinearColor MidnightBlue = { 0.098039225f, 0.098039225f, 0.439215720f, 1.000000000f };
//	ue::FLinearColor MintCream = { 0.960784376f, 1.000000000f, 0.980392218f, 1.000000000f };
//	ue::FLinearColor MistyRose = { 1.000000000f, 0.894117713f, 0.882353008f, 1.000000000f };
//	ue::FLinearColor Moccasin = { 1.000000000f, 0.894117713f, 0.709803939f, 1.000000000f };
//	ue::FLinearColor NavajoWhite = { 1.000000000f, 0.870588303f, 0.678431392f, 1.000000000f };
//	ue::FLinearColor Navy = { 0.000000000f, 0.000000000f, 0.501960814f, 1.000000000f };
//	ue::FLinearColor OldLace = { 0.992156923f, 0.960784376f, 0.901960850f, 1.000000000f };
//	ue::FLinearColor Olive = { 0.501960814f, 0.501960814f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor OliveDrab = { 0.419607878f, 0.556862772f, 0.137254909f, 1.000000000f };
//	ue::FLinearColor Orange = { 1.000000000f, 0.647058845f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor OrangeRed = { 1.000000000f, 0.270588249f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor Orchid = { 0.854902029f, 0.439215720f, 0.839215755f, 1.000000000f };
//	ue::FLinearColor PaleGoldenrod = { 0.933333397f, 0.909803987f, 0.666666687f, 1.000000000f };
//	ue::FLinearColor PaleGreen = { 0.596078455f, 0.984313786f, 0.596078455f, 1.000000000f };
//	ue::FLinearColor PaleTurquoise = { 0.686274529f, 0.933333397f, 0.933333397f, 1.000000000f };
//	ue::FLinearColor PaleVioletRed = { 0.858823597f, 0.439215720f, 0.576470613f, 1.000000000f };
//	ue::FLinearColor PapayaWhip = { 1.000000000f, 0.937254965f, 0.835294187f, 1.000000000f };
//	ue::FLinearColor PeachPuff = { 1.000000000f, 0.854902029f, 0.725490212f, 1.000000000f };
//	ue::FLinearColor Peru = { 0.803921640f, 0.521568656f, 0.247058839f, 1.000000000f };
//	ue::FLinearColor Pink = { 1.000000000f, 0.752941251f, 0.796078503f, 1.000000000f };
//	ue::FLinearColor Plum = { 0.866666734f, 0.627451003f, 0.866666734f, 1.000000000f };
//	ue::FLinearColor PowderBlue = { 0.690196097f, 0.878431439f, 0.901960850f, 1.000000000f };
//	ue::FLinearColor Purple = { 0.501960814f, 0.000000000f, 0.501960814f, 1.000000000f };
//	ue::FLinearColor Red = { 1.f, 0.f, 0.f, 1.f };
//	ue::FLinearColor RosyBrown = { 0.737254918f, 0.560784340f, 0.560784340f, 1.000000000f };
//	ue::FLinearColor RoyalBlue = { 0.254901975f, 0.411764741f, 0.882353008f, 1.000000000f };
//	ue::FLinearColor SaddleBrown = { 0.545098066f, 0.270588249f, 0.074509807f, 1.000000000f };
//	ue::FLinearColor Salmon = { 0.980392218f, 0.501960814f, 0.447058856f, 1.000000000f };
//	ue::FLinearColor SandyBrown = { 0.956862807f, 0.643137276f, 0.376470625f, 1.000000000f };
//	ue::FLinearColor SeaGreen = { 0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f };
//	ue::FLinearColor SeaShell = { 1.000000000f, 0.960784376f, 0.933333397f, 1.000000000f };
//	ue::FLinearColor Sienna = { 0.627451003f, 0.321568638f, 0.176470593f, 1.000000000f };
//	ue::FLinearColor Silver = { 0.752941251f, 0.752941251f, 0.752941251f, 1.000000000f };
//	ue::FLinearColor SkyBlue = { 0.529411793f, 0.807843208f, 0.921568692f, 1.000000000f };
//	ue::FLinearColor SlateBlue = { 0.415686309f, 0.352941185f, 0.803921640f, 1.000000000f };
//	ue::FLinearColor SlateGray = { 0.720, 0.720, 0.720, 1.000000000f };
//	ue::FLinearColor Snow = { 1.000000000f, 0.980392218f, 0.980392218f, 1.000000000f };
//	ue::FLinearColor SpringGreen = { 0.000000000f, 1.000000000f, 0.498039246f, 1.000000000f };
//	ue::FLinearColor SteelBlue = { 0.274509817f, 0.509803951f, 0.705882370f, 1.000000000f };
//	ue::FLinearColor Tan = { 0.823529482f, 0.705882370f, 0.549019635f, 1.000000000f };
//	ue::FLinearColor Teal = { 0.000000000f, 0.501960814f, 0.501960814f, 1.000000000f };
//	ue::FLinearColor Thistle = { 0.847058892f, 0.749019623f, 0.847058892f, 1.000000000f };
//	ue::FLinearColor Tomato = { 1.000000000f, 0.388235331f, 0.278431386f, 1.000000000f };
//	ue::FLinearColor Transparent = { 0.000000000f, 0.000000000f, 0.000000000f, 0.000000000f };
//	ue::FLinearColor Turquoise = { 0.250980407f, 0.878431439f, 0.815686345f, 1.000000000f };
//	ue::FLinearColor Violet = { 0.933333397f, 0.509803951f, 0.933333397f, 1.000000000f };
//	ue::FLinearColor Wheat = { 0.960784376f, 0.870588303f, 0.701960802f, 1.000000000f };
//	ue::FLinearColor White = { 1.000000000f, 1.000000000f, 1.0f, 1.000000000f };
//	ue::FLinearColor WhiteSmoke = { 0.960784376f, 0.960784376f, 0.960784376f, 1.000000000f };
//	ue::FLinearColor Yellow = { 1.000000000f, 1.000000000f, 0.000000000f, 1.000000000f };
//	ue::FLinearColor YellowGreen = { 0.603921592f, 0.803921640f, 0.196078449f, 1.000000000f };
//};