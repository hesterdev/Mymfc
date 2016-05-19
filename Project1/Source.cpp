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

	}
	system("pause");
	return 0;
}