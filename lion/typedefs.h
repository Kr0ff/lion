#pragma once
#include <windows.h>

typedef BOOL(WINAPI* pfnVirtualProtect)(
	IN  LPVOID lpAddress,
	IN  SIZE_T dwSize,
	IN  DWORD  flNewProtect,
	OUT PDWORD lpflOldProtect
	);

typedef LPVOID(WINAPI* pfnCreateFiber)(
	IN          SIZE_T                dwStackSize,
	IN          LPFIBER_START_ROUTINE lpStartAddress,
	IN OPTIONAL	LPVOID                lpParameter
	);

typedef void (WINAPI* pfnSwitchToFiber)(
	IN OPTIONAL LPVOID lpParameter
	);

typedef LPVOID(WINAPI* pfnConvertThreadToFiber)(
	IN OPTIONAL LPVOID lpParameter
	);


typedef NTSYSAPI PVOID(NTAPI* pfnRtlCreateHeap)(
	IN ULONG Flags,
	IN PVOID HeapBase OPTIONAL,
	IN ULONG ReserveSize OPTIONAL,
	IN ULONG CommitSize OPTIONAL,
	IN PVOID Lock OPTIONAL,
	IN PRTL_HEAP_PARAMETERS Parameters OPTIONAL
);

typedef NTSYSAPI PVOID (NTAPI* pfnRtlDestroyHeap)(
	IN PVOID HeapHandle
);

//
// Heap allocation function (ala "malloc")
//
typedef PVOID (NTAPI* pfnRtlAllocateHeap)(
	HANDLE Heap,
	ULONG Flags,
	ULONG Size
);

//
// Heap free function (ala "free")
//
typedef BOOLEAN (NTAPI* pfnRtlFreeHeap)(
	HANDLE Heap,
	ULONG Flags,
	PVOID Address
);

typedef NTSYSAPI PVOID (NTAPI* pfnRtlDestroyHeap)(
	IN PVOID HeapHandle
);


typedef HANDLE(WINAPI* pfnHeapCreate)(
	IN DWORD	flOptions,
	IN SIZE_T	dwInitialSize,
	IN SIZE_T	dwMaximumSize
	);

typedef LPVOID(WINAPI* pfnHeapAlloc)(
	IN	HANDLE	hHandle,
	IN	DWORD	dwFlags,
	IN	SIZE_T	dwBytes
	);

PVOID VxMoveMemory(
	_Inout_ PVOID dest,
	_In_    const PVOID src,
	_In_    SIZE_T len
	);

typedef void(__stdcall* pfnSleep)(DWORD dwMilliseconds);

/*
typedef NTSTATUS(NTAPI* SystemFunction032)(
	struct ustring* data,
	const struct ustring* key
	);
*/
typedef HRSRC(WINAPI* t_FindResourceW)(
	_In_opt_ HMODULE hModule,
	_In_ LPCWSTR lpName,
	_In_ LPCWSTR lpType
	);

typedef HGLOBAL(WINAPI* t_LoadResource)(
	_In_opt_ HMODULE hModule,
	_In_ HRSRC hResInfo
	);

typedef LPVOID(WINAPI* t_LockResource)(
	_In_ HGLOBAL hResData
	);

typedef DWORD(WINAPI* t_SizeofResource)(
	_In_opt_ HMODULE hModule,
	_In_ HRSRC hResInfo
	);

typedef BOOL(WINAPI* t_FreeResource)(
	_In_ HGLOBAL hResData
	);