// (c) FFRI Security, Inc., 2020 / Koh M. Nakagawa: FFRI Security, Inc.

#include "MiniWin32Api.h"

typedef WINUSERAPI int (WINAPI *MESSAGEBOXA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

#define GET_PROC_ADDRESS_HASH 0x83bbda31
#define LOADLIBRARYA_HASH 0x7e1d6602

__declspec(noinline)
__declspec(code_seg(".scode"))
__declspec(dllexport)
void ShellcodeEntry() {
	const uint32_t user32_dll_str[] = { 0x72657375, 0x642e3233, 0x6c6c };
	const uint32_t message_boxa_str[] = { 0x7373654d, 0x42656761, 0x41786f };
	const uint32_t hello_msg_str[] = { 0x6c6c6548, 0x6f };

	CustomGetProcAddressFunc pGetProcAddress = (CustomGetProcAddressFunc)GetApiAddressFromHash32(GET_PROC_ADDRESS_HASH);
	CustomLoadLibraryFunc pLoadLibraryA = (CustomLoadLibraryFunc)GetApiAddressFromHash32(LOADLIBRARYA_HASH);

	HMODULE user32_base_addr = pLoadLibraryA((const char*)user32_dll_str);
	MESSAGEBOXA pMessageBoxA = (MESSAGEBOXA)pGetProcAddress((const char*)user32_base_addr, (const char*)message_boxa_str);
	pMessageBoxA(NULL, (const char*)hello_msg_str, (const char*)hello_msg_str, MB_OK);
}

int main() {
	ShellcodeEntry();
}
