// (c) FFRI Security, Inc., 2020 / Koh M. Nakagawa: FFRI Security, Inc.

#include <stdio.h>
#include "MiniWin32Api.h"

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

	DWORD old = 0;
	VirtualProtect(lpBuffer, dwLength, PAGE_EXECUTE_READWRITE, &old);

	DWORD dwBytesRead = 0;
	if (ReadFile(hFile, lpBuffer, dwLength, &dwBytesRead, NULL) == FALSE) {
		fprintf(stderr, "Failed to alloc a buffer!\n");
		return NULL;
	}

	return lpBuffer;
}

__declspec(code_seg(".scode"))
__declspec(noinline)
__declspec(dllexport)
void RunFromMemoryX86(LPVOID shellCode) {
	NTDLL_FUNCS ntdllFuncs = GetNtDllFuncs64();
	KERNELBASE_APIS kernelBaseApis = GetKernelBaseApis(&ntdllFuncs, FALSE);
	DWORD dwThreadId = 0;
	HANDLE hThread = kernelBaseApis.createThread(NULL, 0, (LPTHREAD_START_ROUTINE)shellCode, NULL, 0, &dwThreadId);
	kernelBaseApis.waitForSingleObject(hThread, INFINITE);
}

const char* shellCode = "\xFC\xEB\x67\x60\x33\xC0\x64\x8B\x40\x30\x8B\x40\x0C\x8B\x70\x14\xAD\x89\x44\x24\x1C\x8B\x68\x10\x8B\x45\x3C\x8B\x54\x28\x78\x03\xD5\x8B\x4A\x18\x8B\x5A\x20\x03\xDD\xE3\x39\x49\x8B\x34\x8B\x03\xF5\x33\xFF\x33\xC0\xAC\x84\xC0\x74\x07\xC1\xCF\x0D\x03\xF8\xEB\xF4\x3B\x7C\x24\x24\x75\xE2\x8B\x5A\x24\x03\xDD\x66\x8B\x0C\x4B\x8B\x5A\x1C\x03\xDD\x8B\x04\x8B\x03\xC5\x89\x44\x24\x1C\x61\x59\x5A\x51\xFF\xE0\x8B\x74\x24\x1C\xEB\xA6\x33\xDB\x53\x68\x63\x61\x6C\x63\x8B\xC4\x6A\x01\x50\x68\x98\xFE\x8A\x0E\xE8\x82\xFF\xFF\xFF\x53\x68\x7E\xD8\xE2\x73\xE8\x77\xFF\xFF\xFF";

int main(int argc, char* argv[]) {
	char* buffer = NULL;
	size_t bufferSize = 0;
	if (argc != 2) {
		buffer = shellCode;
		DWORD protOld = 0;
		VirtualProtect(shellCode, strlen(shellCode), PAGE_EXECUTE_READWRITE, &protOld);
	}
	else {
		buffer = LoadFile(argv[1], &bufferSize);
	}

	RunFromMemoryX86(buffer);
	if (argc == 2) {
		free(buffer);
	}
	return EXIT_SUCCESS;
}