#include<stdio.h>
#include<Windows.h>
DWORD WINAPI EnumEnvironmentVariables() {
	PVOID pEv = GetEnvironmentStrings();
	LPTSTR szEnvs;
	for (szEnvs = (LPTSTR)pEv; *szEnvs;) {
		printf("%s\n", szEnvs);
		while (*szEnvs++);
	}
	FreeEnvironmentStrings((LPCH)pEv);
	return 0;
}
DWORD AppendEnvironmentAvariable(LPTSTR szName, LPTSTR szNewValue) {
	DWORD dwNewValSize;
	dwNewValSize = lstrlen(szNewValue) + 1;//因为要加分号;

	PVOID szVal;
	szVal = HeapAlloc(GetProcessHeap(), 0, BUFSIZ * 8);
	if (NULL == szVal) {
		puts("Memory error\n");
	}
	DWORD dwReturn = GetEnvironmentVariable(szName, (LPSTR)szVal, BUFSIZ * 8);
	if (dwReturn == 0) {
		DWORD dwErr = GetLastError();
		if (dwErr == ERROR_ENVVAR_NOT_FOUND) {
			printf("环境变量 %s 不存在\n", szName);
		}
		else {
			printf("append error: %d\n", dwErr);
		}
		HeapFree(GetProcessHeap(), 0, szVal);

		return 0;
	}
	else if (dwReturn > BUFSIZ * 8) {
		szVal = HeapReAlloc(GetProcessHeap(), 0, szVal, dwReturn + dwNewValSize);
		if (NULL == szVal) {
			puts("Memory error\n");
		}
		dwReturn = GetEnvironmentVariable(szName, (LPTSTR)szVal, dwReturn);
		if (!dwReturn) {
			printf("GetEnviromentVariable failed:%d\n", GetLastError());
			HeapFree(GetProcessHeap(), 0, szVal);

			return FALSE;
		}
	}
	lstrcat((LPTSTR)szVal, TEXT(";"));
	lstrcat((LPTSTR)szVal, szNewValue);
	if (!SetEnvironmentVariable(szName, (LPTSTR)szVal)) {
		printf("Set Value Error: %d\n", GetLastError());
		return FALSE;
	}
	HeapFree(GetProcessHeap(), 0, szVal);
	return TRUE;


}
int main(int argc, PTCHAR argv[]) {

	if (0 == lstrcmp("showall", argv[1]) && argc == 2) {
		EnumEnvironmentVariables();
	}
	else if (0 == lstrcmp("nsd", argv[1]) && argc == 2) {
		printf("准备添加新的环境变量\n");
		getchar();

		if (!SetEnvironmentVariable(TEXT("b"), TEXT("big"))) {
			printf("Add new environment variable error: %d\n", GetLastError());
			return 1;
		}
		EnumEnvironmentVariables();

		printf("添加新的环境变量成功\n");
		getchar();

		printf("修改环境变量\n");
		getchar();

		if (!SetEnvironmentVariable(TEXT("b"), TEXT("button"))) {
			printf("Edit environment variable error: %d\n", GetLastError());
			return 1;
		}
		EnumEnvironmentVariables();

		printf("修改环境变量成功\n");
		getchar();

		printf("删除环境变量\n");
		getchar();


		if (!SetEnvironmentVariable(TEXT("b"), NULL)) {
			printf("Edit environment variable error: %d\n", GetLastError());
			return 1;
		}

		printf("删除环境变量成功\n");
		getchar();

		/*这里的问题时,每次的环境变量都是该进程的环境变量*/
	}
	else if (0 == lstrcmp("get", argv[1]) && argc == 2) {
		char buf[BUFSIZ];

		if (!GetEnvironmentVariable(TEXT("username1"), buf, BUFSIZ)) {
			DWORD dwErr = GetLastError();
			if (ERROR_ENVVAR_NOT_FOUND == dwErr) {
				printf("环境变量不存在\n");
				return dwErr;
			}
		}
		printf("%s\n", buf);
	}
	else if (0 == lstrcmp("append", argv[1]) && argc == 2) {
		// 在已有的环境变量后面增加新的内容

		printf("追加之前:\n");
		EnumEnvironmentVariables();
		if (!AppendEnvironmentAvariable(TEXT("PATH"), TEXT("d:\\demo"))) {
			printf("Append environment variable failed");
			return 5;
		}
		printf("追加之后:\n");
		EnumEnvironmentVariables();
	}
	system("pause");
	return 0;
}