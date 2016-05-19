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

	}
	system("pause");
	return 0;
}