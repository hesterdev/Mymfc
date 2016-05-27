#include<iostream>
#include<Windows.h>
#include<NTSecAPI.h>  //UNICODE_STRING

// 动态的找到它 然后用其指针
using namespace std;

#define	SystemProcessesAndThreadsInformation 5

typedef DWORD(WINAPI*ZWQUERYSYSTEMINFORMATION)(DWORD, PVOID, DWORD, PDWORD);
typedef struct _SYSTEM_pROCESS_INFORMATION {
	DWORD NextEntryDelta;
	DWORD ThreadCount;
	DWORD Reserved1[6];
	FILETIME ftCreateTime;
	FILETIME ftUserTime;
	FILETIME ftKernelTime;

	UNICODE_STRING ProcessName;

	DWORD BasePriority;
	DWORD ProcessID;
	DWORD InheritedFromProcessId;
	DWORD HandleCount;
	DWORD Reserved2[2];
	DWORD VmCounters;
	DWORD dCommitCharge;
	PVOID ThreadInfos[1];
}SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;
int main() {
	HMODULE hNtDll = GetModuleHandle(TEXT("ntdll.dll"));

	if (!hNtDll) {
		cout << "Error" << endl;
		return -1;
	}
	// 函数指针

	ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtDll, "ZwQuerySystemInformation");
	// 可以查询几十种各种各样的信息, 而我们现在要查询系统进程和线程的信息

	ULONG cbBuffer = 0x1000000;	//原来是太小 不够用啊
	LPVOID pBuffer = NULL;
	pBuffer = malloc(cbBuffer);
	if (!pBuffer) {
		cout << "Error: -2" << endl;
		return -2;
	}

	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, pBuffer, cbBuffer, NULL);
	// 进程信息结构 pInfo =(进程信息结构)pBuffer
	/*for (...)
	{
		对pinfo进行循环
	}*/
	int cnt = 0;
	PSYSTEM_PROCESS_INFORMATION pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuffer;
	for (;;) {
		cnt++;
		wprintf(TEXT("ProcessID: %d (%s)\n"), pInfo->ProcessID, pInfo->ProcessName.Buffer);
		//printf("ProcessID: %d\n", pInfo->ProcessID);
		if (pInfo->NextEntryDelta == 0)
			break;
		pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);//加上之后 等于第二个
	}

	free(pBuffer);
	cout << "共" << cnt << "个进程" << endl;
	cout << "Done" << endl;
	system("pause");
	return 0;
}