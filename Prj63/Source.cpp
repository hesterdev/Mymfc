#include<Windows.h>
#include<stdio.h>
#include<Psapi.h>
#include<iostream>

using namespace std;

template<typename T>
void swap(T &a, T &b) {
	printf("hello");
}
int cmp(const void*a, const void *b) {
	return *(DWORD*)a - *(DWORD*)b;
}

BOOL UpdateProcessPrivilege(HANDLE hProcess, LPCTSTR lpPrivilegeName = SE_DEBUG_NAME);

int main() {

	//提升当前进程的权限
	UpdateProcessPrivilege(GetCurrentProcess());

	DWORD ProcessId[1024];
	DWORD cbNeeded;

	if (!EnumProcesses(ProcessId, sizeof(ProcessId), &cbNeeded)) {
		printf("Failed.\n");
		return -1;
	}
	DWORD processcount = cbNeeded / sizeof(DWORD);

	printf("当前一共有 %d 进程\n", processcount);

	qsort(ProcessId, processcount, sizeof(ProcessId[0]), cmp);
	for (DWORD i = 0; i < processcount; i++) {
		// 打开进程得到一个句柄
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessId[i]);
		HMODULE hMods[BUFSIZ];
		if (hProcess) {
			printf("\nProcessId: %d 打开成功\n", ProcessId[i]);
			if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
				for (int j = 0; j < (cbNeeded / sizeof(HMODULE)); j++) {
					TCHAR szModName[MAX_PATH];
					if (GetModuleFileNameEx(hProcess, hMods[j], szModName, sizeof(szModName) / sizeof(CHAR))) {
						printf("\t%d %s (0x%08x)\n", j, szModName, hMods[j]);
					}
				}
			}

		}
		else {
			printf("\nProcessId: %d 打开失败\n", ProcessId[i]);
		}
	}

	puts("Done");
	system("pause");
	return 0;
}

// 提升进程的权限的
BOOL UpdateProcessPrivilege(HANDLE hProcess, LPCTSTR lpPrivilegeName) {
	HANDLE hToken;
	int iResult;
	TOKEN_PRIVILEGES TokenPrivileges;
	if (OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken)) {
		LUID destLuid;
		if (LookupPrivilegeValue(NULL, lpPrivilegeName, &destLuid)) {
			TokenPrivileges.PrivilegeCount = 1;
			TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			TokenPrivileges.Privileges[0].Luid = destLuid;

			if (iResult = AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, NULL, NULL)) {
				return TRUE;
			}
		}
	}
	return FALSE;
}
