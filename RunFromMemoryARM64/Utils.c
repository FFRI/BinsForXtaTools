// (c) FFRI Security, Inc., 2020 / Koh M. Nakagawa: FFRI Security, Inc.

#include <windows.h>

#pragma code_seg(".scode")

#pragma optimize("", off)

void* __cdecl MyMemSet(
	void* dst,
	int    val,
	size_t size
) {
	char* pDst = (char*)dst;
	for (size_t i = 0; i < size; i++) {
		pDst[i] = (char)val;
	}
	return dst;
}

void* __cdecl MyMemCpy(
	void* dst,
	void const* src,
	size_t      size
) {
	char* pDst = (char*)dst;
	const char* pSrc = (const char*)src;
	for (size_t i = 0; i < size; i++) {
		pDst[i] = pSrc[i];
	}
	return dst;
}

#pragma optimize("", on)
