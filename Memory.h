#pragma once
#include <Psapi.h>
#include "safecall.h"

namespace MemoryHelper
{
	namespace Pattern
	{
		uintptr_t PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex = 0);
		uintptr_t PatternScan(const char* sSignature, size_t nSelectResultIndex = 0);
	}

    void Log(const char* sFilePath, char const* const sFormat, ...);
}

uintptr_t MemoryHelper::Pattern::PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex)
{
    static auto patternToByte = [](const char* pattern)
    {
        auto       bytes = std::vector<int>{};
        const auto start = const_cast<char*>(pattern);
        const auto end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    const auto dosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
    const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + dosHeader->e_lfanew);

    const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto       patternBytes = patternToByte(sSignature);
    const auto scanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);

    const auto s = patternBytes.size();
    const auto d = patternBytes.data();

    size_t nFoundResults = 0;

    for (auto i = 0ul; i < sizeOfImage - s; ++i)
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            if (nSelectResultIndex != 0)
            {
                if (nFoundResults < nSelectResultIndex)
                {
                    nFoundResults++;                                   // Skip Result To Get nSelectResultIndex.
                    found = false;                                     // Make sure we can loop again.
                }
                else
                {
                    return reinterpret_cast<uintptr_t>(&scanBytes[i]);  // Result By Index.
                }
            }
            else
            {
                return reinterpret_cast<uintptr_t>(&scanBytes[i]);      // Default/First Result.
            }
        }
    }

    return NULL;
}




uintptr_t MemoryHelper::Pattern::PatternScan(const char* sSignature, size_t nSelectResultIndex)
{
    static bool bIsSetted = false;

    static MODULEINFO info = { 0 };

    if (!bIsSetted)
    {
        GetModuleInformation(safe_call(GetCurrentProcess)(), GetModuleHandle(0), &info, sizeof(info));
        bIsSetted = true;
    }

    return PatternScan((uintptr_t)info.lpBaseOfDll, sSignature, nSelectResultIndex);
}

void MemoryHelper::Log(const char* sFilePath, char const* const sFormat, ...)
{
    char sLog[1024];

    va_list _ArgList;
    __crt_va_start(_ArgList, sFormat);
#pragma warning(push)
#pragma warning(disable: 4996) // Deprecation
    _vsprintf_l(sLog, sFormat, NULL, _ArgList);
#pragma warning(pop)
    __crt_va_end(_ArgList);

    std::ofstream ofs;
    ofs.open(sFilePath, std::ofstream::out | std::ofstream::app);
    ofs << sLog << std::endl;
    ofs.close();
}