#include<Windows.h>
#include<stdio.h>

int main() {

	MEMORYSTATUSEX memstatusex;
	memstatusex.dwLength = sizeof(memstatusex);

	GlobalMemoryStatusEx(&memstatusex);
	printf("ȫ�������ڴ�: %f G\n", memstatusex.ullTotalPhys / 1024.0 / 1024 / 1024);
	printf("���������ڴ�: %f G\n", memstatusex.ullAvailPhys / 1024.0 / 1024 / 1024);
	printf("ȫ�������ڴ�: %f G\n", memstatusex.ullTotalVirtual / 1024.0 / 1024 / 1024);
	printf("���������ڴ�: %f G\n", memstatusex.ullAvailVirtual / 1024.0 / 1024 / 1024);
	printf("ȫ��ҳ���ļ�: %f G\n", memstatusex.ullTotalPageFile / 1024.0 / 1024 / 1024);
	printf("����ҳ���ļ�: %f G\n", memstatusex.ullAvailPageFile / 1024.0 / 1024 / 1024);



	system("pause");
	return 0;
}