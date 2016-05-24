#include<Windows.h>
#include<stdio.h>

#include<WtsApi32.h>

// 需要动态链接的导入库
#pragma comment(lib,"WtsApi32.lib")

int main() {

	LPTSTR szServerName = TEXT("127.0.0.1");// pc-PC  localhost 127.0.0.1
	HANDLE hWtsServer = WTSOpenServer(szServerName);
	PWTS_PROCESS_INFO  pWtspi;
	DWORD dwCount;

	if (!WTSEnumerateProcesses(hWtsServer, 0, 1, &pWtspi, &dwCount)) {
		puts("Error!");
		return 1;
	}
	for (int i = 0; i < dwCount; i++) {
		wprintf(TEXT("ProcessID: %d (%s)\n"),pWtspi[i].ProcessId,pWtspi[i].pProcessName);
	}
	WTSCloseServer(hWtsServer);

	puts("Done");
	system("pause");
	return 0;
}