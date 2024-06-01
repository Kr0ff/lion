#pragma once
#include <windows.h>
#include "struct.h"

#define CRC32BSEED 0xEDB88320

#define CRC32B(str) crc32b(str)

DWORD64 crc32b(PBYTE str);

DWORD64 crc32b(PBYTE str) {
    // Source: https://stackoverflow.com/a/21001712
    DWORD64 byte, crc, mask;
    int i = 0, j;
    crc = 0xFFFFFFFF;
    while (str[i] != 0) {
        byte = str[i];
        crc = crc ^ byte;
        for (j = 7; j >= 0; j--) {
            mask = -((int)crc & 1);
            crc = (crc >> 1) ^ (CRC32BSEED & mask);
        }
        i = i + 1;
    }
    return ~crc;
}
