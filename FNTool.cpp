#include "FNTool.h"
#include "spoof_call.h"
#include "Memory.h"
#include "safecall.h"
#include "xor.h"



bool FNTool::Initialize(uintptr_t GObjects, uintptr_t GetNameByIndex, uintptr_t FnFree)
{

	

	this->ObjectsCount = *(DWORD*)(GObjects + 0x14);
	if (this->ObjectsCount > 0x9000) this->ObjectsCount = 0x9000;

	uintptr_t GObjects_deref = *(uintptr_t*)GObjects;
	if (spoof_call(safe_call(IsBadWritePtr), (const LPVOID)GObjects_deref, (UINT_PTR)8)) { safe_call(MessageBoxA)(0, xorstr("Failed To Initialize"), xorstr("Error"), MB_ICONERROR); return FALSE; }

	uintptr_t GObjects_deref2 = *(uintptr_t*)GObjects_deref;
	if (spoof_call(safe_call(IsBadWritePtr), (const LPVOID)GObjects_deref2, (UINT_PTR)8)) { safe_call(MessageBoxA)(0, xorstr("Failed To Initialize"), xorstr("Error"), MB_ICONERROR); return FALSE; }

	this->UObjectArray = GObjects_deref2;
	this->GetNameByIndex = GetNameByIndex;
	this->FnFree = FnFree;

	return true;
}

BOOLEAN MaskCompare(PVOID buffer, LPCSTR pattern, LPCSTR mask) {
	for (auto b = reinterpret_cast<PBYTE>(buffer); *mask; ++pattern, ++mask, ++b) {
		if (*mask == 'x' && *reinterpret_cast<LPCBYTE>(pattern) != *b) {
			return FALSE;
		}
	}

	return TRUE;
}

PBYTE FindPattern2(LPCSTR pattern, LPCSTR mask) {
	MODULEINFO info = { 0 };
	GetModuleInformation(safe_call(GetCurrentProcess)(), GetModuleHandle(0), &info, sizeof(info));

	info.SizeOfImage -= static_cast<DWORD>(strlen(mask));

	for (auto i = 0UL; i < info.SizeOfImage; ++i) {
		auto addr = reinterpret_cast<PBYTE>(info.lpBaseOfDll) + i;
		if (MaskCompare(addr, pattern, mask)) {
			return addr;
		}
	}
}

uintptr_t FNTool::FindSignature(const char* Signature) {
	uintptr_t SigResult = MemoryHelper::Pattern::PatternScan(Signature);
	return SigResult;
}

VOID FNTool::FindAndLogOffset(const char* Class, const char* OffsetName)
{
	int strlenght = strlen((std::string(xorstr("")) + Class + xorstr(".") + OffsetName).c_str());

	int calculation = 52 - strlenght;

	std::string strspace = "";

	for (int i = 0; i < calculation; i++) {
		strspace = strspace + " ";
	}

	std::cout << "  " << Class << "." << OffsetName << strspace << xorstr(" ->   0x") << std::hex << std::uppercase << this->FindOffset(Class, OffsetName) << std::endl;

}
DWORD FNTool::FindOffset(const char* Class, const char* varName)
{
	for (DWORD i = 0x0; i < this->ObjectsCount; i++)
	{
		auto CurrentObject = *(uintptr_t*)(this->UObjectArray + (i * 0x18));

		if (!CurrentObject) {safe_call(MessageBoxA)(0, xorstr("curobjnull"), 0, 0); return NULL; }
		if (!(*(uintptr_t*)(CurrentObject + 0x50)) || *(DWORD*)(CurrentObject + 0x54) == 0xFFFFFFFF) continue;


		char* CurObjectName = this->fGetObjectName(CurrentObject);

		if (!strcmp(CurObjectName, Class)) //Same class
		{
			for (auto Property = *(uint64_t*)(CurrentObject + 0x50); !spoof_call(safe_call(IsBadWritePtr), (LPVOID)Property, (UINT_PTR)8); Property = *(uint64_t*)(Property + 0x20))
			{
				auto Type = *(uint64_t*)(Property + 0x8);

				if (!spoof_call(safe_call(IsBadWritePtr), (LPVOID)Type, (UINT_PTR)8) && Type)
				{
					auto Property_FName = *(ue::FName*)(Property + 0x28);
					auto Offset = *(DWORD*)(Property + 0x44);

					if (Offset != 0)
					{
						auto Property_idx = Property_FName.ComparisonIndex;

						if (Property_idx)
						{
							char* PropertyName = this->fGetNameByIndex(Property_idx);

							if (!strcmp(PropertyName, varName))
							{
								return Offset;
							}
						}
					}
				}

			}

			return NULL; //Return NULL if checked all properties of the class.
		}
	}
}

VOID FNTool::FindAndLogClass(const char* Class)
{
	std::cout << xorstr("\n");
	for (DWORD i = 0x0; i < this->ObjectsCount; i++)
	{
		auto CurrentObject = *(uintptr_t*)(this->UObjectArray + (i * 0x18));

		if (!CurrentObject) return;
		if (!(*(uintptr_t*)(CurrentObject + 0x50)) || *(DWORD*)(CurrentObject + 0x54) == 0xFFFFFFFF) continue;


		char* CurObjectName = this->fGetObjectName(CurrentObject);

		if (!strcmp(CurObjectName, Class)) //Same class
		{
			for (auto Property = *(uint64_t*)(CurrentObject + 0x50); !safe_call(IsBadWritePtr)((LPVOID)Property, 8); Property = *(uint64_t*)(Property + 0x20))
			{
				auto Type = *(uint64_t*)(Property + 0x8);

				if (!safe_call(IsBadWritePtr)((LPVOID)Type, 8) && Type)
				{
					auto Property_FName = *(ue::FName*)(Property + 0x28);
					auto Offset = *(DWORD*)(Property + 0x44);

					if (Offset != 0)
					{
						auto Property_idx = Property_FName.ComparisonIndex;

						if (Property_idx)
						{
							char* PropertyName = this->fGetNameByIndex(Property_idx);

							int strlenght = strlen((std::string(xorstr("")) + PropertyName).c_str());

							int calculation = 52 - strlenght;

							std::string strspace = "";

							for (int iii = 0; iii < calculation; iii++) {
								strspace = strspace + xorstr(" ");
							}
							int jjjj = 0;

							for (int iiiii = 0; iiiii < strlenght; iiiii++)
								if (PropertyName[iiiii] >= 0 && PropertyName[iiiii] <= 127)
									PropertyName[jjjj++] = PropertyName[iiiii];

							std::cout << xorstr("  ") << PropertyName << strspace << xorstr(" ->   0x") << std::hex << std::uppercase << Offset << std::endl;

						}
					}
				}

			}

			return;
		}

	}
	std::cout << xorstr("  [!] Class doesn't exists\n");
}

void FNTool::cFixName(char* Name)
{
	for (int i = 0; Name[i] != '\0'; i++)
	{
		if (Name[i] == '_')
		{
			if (Name[i + 1] == '0' ||
				Name[i + 1] == '1' ||
				Name[i + 1] == '2' ||
				Name[i + 1] == '3' ||
				Name[i + 1] == '4' ||
				Name[i + 1] == '5' ||
				Name[i + 1] == '6' ||
				Name[i + 1] == '7' ||
				Name[i + 1] == '8' ||
				Name[i + 1] == '9')
				Name[i] = '\0';
		}
	}

	return;
}

void FNTool::FreeObjName(uintptr_t Address)
{
	if (Address == NULL) return;

	auto func = reinterpret_cast<__int64(__fastcall*)(__int64)>(this->FnFree);

	spoof_call( func, (__int64)Address);
}

char* FNTool::fGetObjectName(uintptr_t Object)
{
	if (Object == 0) return (char*)("");

	char* return_string = FNTool::fGetNameByIndex(*(int*)(Object + 0x18));

	if (return_string == NULL) return (char*)"";

	return return_string;
}

char* FNTool::fGetNameByIndex(int Index)
{
	if (Index == 0) return (char*)"";

	auto fGetNameByIdx = reinterpret_cast<ue::FString * (__fastcall*)(int*, ue::FString*)>(this->GetNameByIndex);

	ue::FString result;
	spoof_call( fGetNameByIdx, &Index, &result);

	if (result.c_str() == NULL) return (char*)"";

	auto tmp = result.ToString();

	char return_string[1024];
	spoof_call( memcpy, (void*)return_string, (const void*)std::string(tmp.begin(), tmp.end()).c_str(), (size_t)1024);

	FreeObjName((uintptr_t)result.c_str());

	cFixName(return_string);

	return return_string;
}
