#pragma once
#include <Psapi.h>

#define _PRINT_DEBUG
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

namespace Utils
{

	__int64 find_pattern(const char* Assembly, const char* pattern) {
		const char* pat = pattern;
		__int64 firstMatch = NULL;
		MODULEINFO moduleInfo;
		if (!GetModuleInformation((HANDLE)-1, GetModuleHandle(Assembly), &moduleInfo, sizeof(MODULEINFO)) || !moduleInfo.lpBaseOfDll) {
			return NULL;
		}
		__int64 pCur = (__int64)moduleInfo.lpBaseOfDll;
		__int64 range_end = (__int64)moduleInfo.lpBaseOfDll + moduleInfo.SizeOfImage;
		__int64 region_end;
		MEMORY_BASIC_INFORMATION mbi{};
		while (sizeof(mbi) == VirtualQuery((LPCVOID)pCur, &mbi, sizeof(mbi))) {
			if (pCur >= range_end - strlen(pattern))
				break;
			if (!(mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE))) {
				pCur += mbi.RegionSize;
				continue;
			}
			region_end = pCur + mbi.RegionSize;
			while (pCur < region_end)
			{
				if (!*pat)
					return firstMatch;
				if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
					if (!firstMatch)
						firstMatch = pCur;
					if (!pat[1] || !pat[2])
						return firstMatch;

					if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
						pat += 3;
					else
						pat += 2;
				}
				else {
					if (firstMatch)
						pCur = firstMatch;
					pat = pattern;
					firstMatch = 0;
				}
				pCur++;
			}
		}
		return NULL;
	}

	__int64 find_ida_sig(const char* mod, const char* sig)
	{
		/// Credits: MarkHC, although slightly modified by me and also documented

		static auto pattern_to_byte = [](const char* pattern)
		{
			/// Prerequisites
			auto bytes = std::vector<int>{};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern) + strlen(pattern);

			/// Convert signature into corresponding bytes
			for (auto current = start; current < end; ++current)
			{
				/// Is current byte a wildcard? Simply ignore that that byte later
				if (*current == '?')
				{
					++current;

					/// Check if following byte is also a wildcard
					if (*current == '?')
						++current;

					/// Dummy byte
					bytes.push_back(-1);
				}
				else
				{
					/// Convert character to byte on hexadecimal base
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
		};

		const auto module_handle = GetModuleHandleA(mod);
		auto base_mode = (uintptr_t)(GetModuleHandleA(NULL));
		if (!module_handle)
			return {};

		/// Get module information to search in the given module
		MODULEINFO module_info;
		GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_handle), &module_info, sizeof(MODULEINFO));

		/// The region where we will search for the byte sequence
		const auto image_size = module_info.SizeOfImage;

		/// Check if the image is faulty
		if (!image_size)
			return {};

		/// Convert IDA-Style signature to a byte sequence
		auto pattern_bytes = pattern_to_byte(sig);

		const auto image_bytes = reinterpret_cast<byte*>(module_handle);

		const auto signature_size = pattern_bytes.size();
		const auto signature_bytes = pattern_bytes.data();

		/// Loop through all pages and check the accessable pages
		auto page_information = MEMORY_BASIC_INFORMATION{};
		for (auto current_page = reinterpret_cast<byte*>(module_handle); current_page < reinterpret_cast<byte*>(module_handle + image_size); current_page = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(page_information.BaseAddress) + page_information.RegionSize))
		{
			auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

			if (page_information.Protect != PAGE_EXECUTE_READWRITE)
				continue;

			/// Now loop through all bytes and check if the byte sequence matches
			for (auto i = reinterpret_cast<uintptr_t>(page_information.BaseAddress) - reinterpret_cast<uintptr_t>(module_handle); i < page_information.RegionSize; ++i)
			{
				auto byte_sequence_found = true;

				if (i + signature_size == page_information.RegionSize)
				{
					auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

					if (page_information.Protect != PAGE_EXECUTE_READ)
						break;
				}

				/// Go through all bytes from the signature and check if it matches
				for (auto j = 0ul; j < signature_size; ++j)
				{
					if (image_bytes[i + j] != signature_bytes[j] /// Bytes don't match
						&& signature_bytes[j] != -1) /// Byte isn't a wildcard either, WHAT THE HECK
					{
						byte_sequence_found = false;
						break;
					}
				}

				if (byte_sequence_found)


					/// All good, now return the right address
					if (byte_sequence_found)
						return uintptr_t(uintptr_t(&image_bytes[i]));
			}
		}

		/// Byte sequence wasn't found
		return {};
	}

	auto resolve_jmp = [](__int64 addr) -> __int64 {
		return *(int*)(addr + 1) + addr + 5;
	};
	auto resolve_lea = [](__int64 addr) -> __int64 {
		return *(int*)(addr + 3) + addr + 7;
	};
}