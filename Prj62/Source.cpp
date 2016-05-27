#include<Windows.h>
#include<TlHelp32.h>  //tool help
#include<stdio.h>

int main() {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		return -1;
	}

	PROCESSENTRY32 processEntry = { 0 };
	processEntry.dwSize = sizeof(processEntry);
	int cnt = 0;
	BOOL bRet = Process32First(hProcessSnap, &processEntry);
	while (bRet) {
		cnt++;
		printf("%d (%s)\n", processEntry.th32ProcessID,processEntry.szExeFile);

		bRet = Process32Next(hProcessSnap, &processEntry);
	}
	printf("共 %d 个进程\n", cnt);

	CloseHandle(hProcessSnap);

	puts("done");

	system("pause");
	return 0;
}