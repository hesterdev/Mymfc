#include<iostream>
#include<Windows.h>
#include<NTSecAPI.h>  //UNICODE_STRING

// ��̬���ҵ��� Ȼ������ָ��
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
	// ����ָ��

	ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtDll, "ZwQuerySystemInformation");
	// ���Բ�ѯ��ʮ�ָ��ָ�������Ϣ, ����������Ҫ��ѯϵͳ���̺��̵߳���Ϣ

	ULONG cbBuffer = 0x1000000;	//ԭ����̫С �����ð�
	LPVOID pBuffer = NULL;
	pBuffer = malloc(cbBuffer);
	if (!pBuffer) {
		cout << "Error: -2" << endl;
		return -2;
	}

	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation, pBuffer, cbBuffer, NULL);
	// ������Ϣ�ṹ pInfo =(������Ϣ�ṹ)pBuffer
	/*for (...)
	{
		��pinfo����ѭ��
	}*/
	int cnt = 0;
	PSYSTEM_PROCESS_INFORMATION pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuffer;
	for (;;) {
		cnt++;
		wprintf(TEXT("ProcessID: %d (%s)\n"), pInfo->ProcessID, pInfo->ProcessName.Buffer);
		//printf("ProcessID: %d\n", pInfo->ProcessID);
		if (pInfo->NextEntryDelta == 0)
			break;
		pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);//����֮�� ���ڵڶ���
	}

	free(pBuffer);
	cout << "��" << cnt << "������" << endl;
	cout << "Done" << endl;
	system("pause");
	return 0;
}