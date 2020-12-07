// (c) FFRI Security, Inc., 2020 / Koh M. Nakagawa: FFRI Security, Inc.

#pragma once

#include <windows.h>

void* __cdecl MyMemSet(
    void* dst, int val, size_t size
);

void* __cdecl MyMemCpy(
    void* dst, void const* src, size_t size
);
