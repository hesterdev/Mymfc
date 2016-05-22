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
	dwNewValSize = lstrlen(szNewValue) + 1;//��ΪҪ�ӷֺ�;

	PVOID szVal;
	szVal = HeapAlloc(GetProcessHeap(), 0, BUFSIZ * 8);
	if (NULL == szVal) {
		puts("Memory error\n");
	}
	DWORD dwReturn = GetEnvironmentVariable(szName, (LPSTR)szVal, BUFSIZ * 8);
	if (dwReturn == 0) {
		DWORD dwErr = GetLastError();
		if (dwErr == ERROR_ENVVAR_NOT_FOUND) {
			printf("�������� %s ������\n", szName);
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
		printf("׼������µĻ�������\n");
		getchar();

		if (!SetEnvironmentVariable(TEXT("b"), TEXT("big"))) {
			printf("Add new environment variable error: %d\n", GetLastError());
			return 1;
		}
		EnumEnvironmentVariables();

		printf("����µĻ��������ɹ�\n");
		getchar();

		printf("�޸Ļ�������\n");
		getchar();

		if (!SetEnvironmentVariable(TEXT("b"), TEXT("button"))) {
			printf("Edit environment variable error: %d\n", GetLastError());
			return 1;
		}
		EnumEnvironmentVariables();

		printf("�޸Ļ��������ɹ�\n");
		getchar();

		printf("ɾ����������\n");
		getchar();


		if (!SetEnvironmentVariable(TEXT("b"), NULL)) {
			printf("Edit environment variable error: %d\n", GetLastError());
			return 1;
		}

		printf("ɾ�����������ɹ�\n");
		getchar();

		/*���������ʱ,ÿ�εĻ����������Ǹý��̵Ļ�������*/
	}
	else if (0 == lstrcmp("get", argv[1]) && argc == 2) {
		char buf[BUFSIZ];

		if (!GetEnvironmentVariable(TEXT("username1"), buf, BUFSIZ)) {
			DWORD dwErr = GetLastError();
			if (ERROR_ENVVAR_NOT_FOUND == dwErr) {
				printf("��������������\n");
				return dwErr;
			}
		}
		printf("%s\n", buf);
	}
	else if (0 == lstrcmp("append", argv[1]) && argc == 2) {
		// �����еĻ����������������µ�����

		printf("׷��֮ǰ:\n");
		EnumEnvironmentVariables();
		if (!AppendEnvironmentAvariable(TEXT("PATH"), TEXT("d:\\demo"))) {
			printf("Append environment variable failed");
			return 5;
		}
		printf("׷��֮��:\n");
		EnumEnvironmentVariables();
	}
	system("pause");
	return 0;
}