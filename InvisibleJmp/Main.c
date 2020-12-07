// (c) FFRI Security, Inc., 2020 / Koh M. Nakagawa: FFRI Security, Inc.

#include <intrin.h>
#include <stdio.h>

void func();

int main(int argc, char* argv[]) {
    // jmp    0xfffffefd
    // NOTE: stop execution after this instruction because invalid instruction is fetched
    __asm {
        _emit 0xe9
        _emit 0xf8
        _emit 0xfe
        _emit 0xff
        _emit 0xff
    }

    // dummy function call to import msvcrt
    func();
}

#pragma optimize("", off)

// dummy function
__declspec(noinline)
void func() {
    puts("Hello World!");
}

#pragma optimize("", on)
