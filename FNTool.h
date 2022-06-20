#pragma once
#include <Windows.h>

#define RELATIVE(addr, size) ((uintptr_t)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))

static const void* game_rbx_jmp;

class FNTool
{
public:
	bool Initialize(uintptr_t GObjects, uintptr_t GetNameByIndex, uintptr_t FnFree);
	uintptr_t FindSignature(const char* Signature);
	DWORD FindOffset(const char* Class, const char* var);
	VOID FindAndLogOffset(const char* Class, const char* var);
	VOID FindAndLogClass(const char* Class);
	VOID FindAndChangeOffset(const char* Class, const char* var, uintptr_t& offfset);

private:
	uintptr_t UObjectArray = NULL;
	uintptr_t GetNameByIndex = NULL;
	uintptr_t FnFree = NULL;
	DWORD ObjectsCount = 0;

	void cFixName(char* Name);
	void FreeObjName(uintptr_t Address);
	char* fGetObjectName(uintptr_t Object);
	char* fGetNameByIndex(int Index);
};