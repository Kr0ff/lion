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

typedef NTSTATUS(NTAPI* SystemFunction032)(
	struct ustring* data,
	const struct ustring* key
	);