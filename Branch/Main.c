// (c) FFRI Security, Inc., 2020 / Koh M. Nakagawa: FFRI Security, Inc.

#include <stdio.h>
#include <windows.h>

__declspec(noinline)
void func0() {
	MessageBoxW(NULL, L"func0", L"func0", MB_OK);
}

__declspec(noinline)
void func1() {
	puts("func1");
}

__declspec(noinline)
void func2(int i) {
	printf("number is %d\n", i);
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		func0();
	}
	else if (argc == 2) {
		func2(argc);
	}
	else {
		func1();
	}
}