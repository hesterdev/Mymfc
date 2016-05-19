// 环境变量59.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<Windows.h>

int main()
{
	PVOID pEv = GetEnvironmentStrings();
	LPTSTR szEnvs;
	for (szEnvs = (LPTSTR)pEv; *szEnvs;) {
		printf("%s\n", szEnvs);
		while (szEnvs++);
	}
	FreeEnvironmentStrings((LPTCH)pEv);


	printf("%s\n", pEv);


	system("pause");
	return 0;
}

