#include<Windows.h>
#include<stdio.h>

int main() {

	MEMORYSTATUSEX memstatusex;
	memstatusex.dwLength = sizeof(memstatusex);

	GlobalMemoryStatusEx(&memstatusex);
	printf("全部物理内存: %f G\n", memstatusex.ullTotalPhys / 1024.0 / 1024 / 1024);
	printf("可用物理内存: %f G\n", memstatusex.ullAvailPhys / 1024.0 / 1024 / 1024);
	printf("全部虚拟内存: %f G\n", memstatusex.ullTotalVirtual / 1024.0 / 1024 / 1024);
	printf("可用虚拟内存: %f G\n", memstatusex.ullAvailVirtual / 1024.0 / 1024 / 1024);
	printf("全部页面文件: %f G\n", memstatusex.ullTotalPageFile / 1024.0 / 1024 / 1024);
	printf("可用页面文件: %f G\n", memstatusex.ullAvailPageFile / 1024.0 / 1024 / 1024);



	system("pause");
	return 0;
}