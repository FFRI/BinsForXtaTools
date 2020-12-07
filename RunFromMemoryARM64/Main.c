// (c) FFRI Security, Inc., 2020 / Koh M. Nakagawa: FFRI Security, Inc.

#include <stdio.h>

#include "MemoryModule.h"

char* LoadFile(const char* fname, size_t* size) {
	HANDLE hFile = CreateFileA(fname, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Failed to open %s\n", fname);
		return NULL;
	}

	DWORD dwLength = GetFileSize(hFile, NULL);
	if (dwLength == INVALID_FILE_SIZE || dwLength == 0) {
		fprintf(stderr, "Failed to call GetFileSize\n");
		return NULL;
	}

	*size = dwLength;
	char* lpBuffer = (char*)malloc(dwLength);
	if (!lpBuffer) {
		fprintf(stderr, "Failed to get the DLL file size\n");
		return NULL;
	}

	DWORD dwBytesRead = 0;
	if (ReadFile(hFile, lpBuffer, dwLength, &dwBytesRead, NULL) == FALSE) {
		fprintf(stderr, "Failed to alloc a buffer!\n");
		return NULL;
	}

	return lpBuffer;
}

typedef int(*entry)(void);

int main() {
	size_t size = 0;
	// char* buffer = LoadFile("C:\\Windows\\write.exe", &size);
	char* buffer = LoadFile("C:\\Windows\\System32\\calc.exe", &size);
	RunFromMemoryARM64(buffer, size);
	free(buffer);
}