#pragma once
#pragma warning (disable : 4005) // Disable macro redefition warnings

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define ERR -0x1
#define SUCCESS 0x0

// Pseudo handles to current process & thread
#define NtCurrentProcess() ( (HANDLE)-1 ) // Return the pseudo handle for the current process
#define NtCurrentThread()  ( (HANDLE)-2 ) // Return the pseudo handle for the current thread

struct ustring {
	ULONG Length;
	ULONG MaximumLength;
	PUCHAR Buffer;
} _data, key;

/*
struct ustring {
	SIZE_T Length;
	SIZE_T MaximumLength;
	PUCHAR Buffer;
} _data, key;
*/

typedef struct _LSA_UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} LSA_UNICODE_STRING, * PLSA_UNICODE_STRING, UNICODE_STRING, * PUNICODE_STRING, * PUNICODE_STR;

typedef struct _PEB_LDR_DATA {
	ULONG                   Length;
	ULONG                   Initialized;
	PVOID                   SsHandle;
	LIST_ENTRY              InLoadOrderModuleList;
	LIST_ENTRY              InMemoryOrderModuleList;
	LIST_ENTRY              InInitializationOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _RTL_BITMAP
{
	ULONG SizeOfBitMap;
	ULONG* Buffer;
} RTL_BITMAP, * PRTL_BITMAP;

typedef struct _RTL_DRIVE_LETTER_CURDIR {

	USHORT                  Flags;
	USHORT                  Length;
	ULONG                   TimeStamp;
	UNICODE_STRING          DosPath;

} RTL_DRIVE_LETTER_CURDIR, * PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS {

	ULONG                   MaximumLength;
	ULONG                   Length;
	ULONG                   Flags;
	ULONG                   DebugFlags;
	PVOID                   ConsoleHandle;
	ULONG                   ConsoleFlags;
	HANDLE                  StdInputHandle;
	HANDLE                  StdOutputHandle;
	HANDLE                  StdErrorHandle;
	UNICODE_STRING          CurrentDirectoryPath;
	HANDLE                  CurrentDirectoryHandle;
	UNICODE_STRING          DllPath;
	UNICODE_STRING          ImagePathName;
	UNICODE_STRING          CommandLine;
	PVOID                   Environment;
	ULONG                   StartingPositionLeft;
	ULONG                   StartingPositionTop;
	ULONG                   Width;
	ULONG                   Height;
	ULONG                   CharWidth;
	ULONG                   CharHeight;
	ULONG                   ConsoleTextAttributes;
	ULONG                   WindowFlags;
	ULONG                   ShowWindowFlags;
	UNICODE_STRING          WindowTitle;
	UNICODE_STRING          DesktopName;
	UNICODE_STRING          ShellInfo;
	UNICODE_STRING          RuntimeData;
	RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];

} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;


typedef struct _PEB
{
	BOOLEAN                      InheritedAddressSpace;
	BOOLEAN                      ReadImageFileExecOptions;
	BOOLEAN                      BeingDebugged;
	BOOLEAN                      SpareBool;
	HANDLE                       Mutant;
	HMODULE                      ImageBaseAddress;
	PPEB_LDR_DATA                LdrData;
	RTL_USER_PROCESS_PARAMETERS* ProcessParameters;
	PVOID                        SubSystemData;
	HANDLE                       ProcessHeap;
	PRTL_CRITICAL_SECTION        FastPebLock;
	PVOID						 FastPebLockRoutine;
	PVOID						 FastPebUnlockRoutine;
	ULONG                        EnvironmentUpdateCount;
	PVOID                        KernelCallbackTable;
	PVOID                        EventLogSection;
	PVOID                        EventLog;
	PVOID						 FreeList;
	ULONG                        TlsExpansionCounter;
	PRTL_BITMAP                  TlsBitmap;
	ULONG                        TlsBitmapBits[2];
	PVOID                        ReadOnlySharedMemoryBase;
	PVOID                        ReadOnlySharedMemoryHeap;
	PVOID* ReadOnlyStaticServerData;
	PVOID                        AnsiCodePageData;
	PVOID                        OemCodePageData;
	PVOID                        UnicodeCaseTableData;
	ULONG                        NumberOfProcessors;
	ULONG                        NtGlobalFlag;
	BYTE                         Spare2[4];
	LARGE_INTEGER                CriticalSectionTimeout;
	ULONG                        HeapSegmentReserve;
	ULONG                        HeapSegmentCommit;
	ULONG                        HeapDeCommitTotalFreeThreshold;
	ULONG                        HeapDeCommitFreeBlockThreshold;
	ULONG                        NumberOfHeaps;
	ULONG                        MaximumNumberOfHeaps;
	PVOID* ProcessHeaps;
	PVOID                        GdiSharedHandleTable;
	PVOID                        ProcessStarterHelper;
	PVOID                        GdiDCAttributeList;
	PVOID                        LoaderLock;
	ULONG                        OSMajorVersion;
	ULONG                        OSMinorVersion;
	ULONG                        OSBuildNumber;
	ULONG                        OSPlatformId;
	ULONG                        ImageSubSystem;
	ULONG                        ImageSubSystemMajorVersion;
	ULONG                        ImageSubSystemMinorVersion;
	ULONG                        ImageProcessAffinityMask;
	ULONG                        GdiHandleBuffer[34];
	ULONG                        PostProcessInitRoutine;
	PRTL_BITMAP                  TlsExpansionBitmap;
	ULONG                        TlsExpansionBitmapBits[32];
	ULONG                        SessionId;

} PEB, * PPEB;

typedef PVOID PACTIVATION_CONTEXT;

typedef struct _LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	WORD LoadCount;
	WORD TlsIndex;
	union {
		LIST_ENTRY HashLinks;
		struct {
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};
	union {
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};
	PACTIVATION_CONTEXT EntryPointActivationContext;
	PVOID PatchInformation;
	LIST_ENTRY ForwarderLinks;
	LIST_ENTRY ServiceTagLinks;
	LIST_ENTRY StaticLinks;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef NTSTATUS
(*PRTL_HEAP_COMMIT_ROUTINE)(
	IN PVOID Base,
	IN OUT PVOID* CommitAddress,
	IN OUT PULONG CommitSize
	);

typedef struct _RTL_HEAP_PARAMETERS {
	ULONG Length;
	ULONG SegmentReserve;
	ULONG SegmentCommit;
	ULONG DeCommitFreeBlockThreshold;
	ULONG DeCommitTotalFreeThreshold;
	ULONG MaximumAllocationSize;
	ULONG VirtualMemoryThreshold;
	ULONG InitialCommit;
	ULONG InitialReserve;
	PRTL_HEAP_COMMIT_ROUTINE CommitRoutine;
	ULONG Reserved[2];
} RTL_HEAP_PARAMETERS, * PRTL_HEAP_PARAMETERS;
