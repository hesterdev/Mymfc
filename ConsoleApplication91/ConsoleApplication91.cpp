// ConsoleApplication91.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	SIZE_T sizeVirtual = 4000; // 分配粒度是64kb
	LPVOID lpRound = (LPVOID)0x100000ff;
	//要么一页,要么两页(跨页)

	LPVOID lpAddress = VirtualAlloc(lpRound, sizeVirtual, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (lpAddress == NULL) {
		printf("VirtualAlloc error: %d\n", GetLastError());
		return 1;
	}
	printf("Alloc: MEM_COMMIT|MEM_RESERVE\n");

	CopyMemory(lpAddress, "hello", strlen("hello"));

	printf("%s\n", lpAddress);

	MEMORY_BASIC_INFORMATION mbi;

	VirtualQuery(lpAddress, &mbi, sizeof(mbi));//查询地址

	printf("BaseAddress: 0x%p\n", mbi.BaseAddress);
	printf("AllocationBase: 0x%p\n", mbi.AllocationBase);
	printf("AllocationProtect: 0x%p\n", mbi.AllocationProtect);// 保护属性
	printf("RegionSize: %d\n", mbi.RegionSize); 
	printf("结果分了 %d 页\n", mbi.RegionSize / 4096);
	printf("State: 0x%p\n", mbi.State); //#define MEM_COMMIT                  0x1000
	printf("Protect: 0x%p\n", mbi.Protect);

	printf("Type: 0x%p\n", mbi.Type);  //MEM_PRIVATE这个程序私有的   MEM_MAPPED 内存映射得到的

	BOOL res=VirtualFree(lpRound, sizeVirtual, MEM_DECOMMIT);//释放
	if (res == FALSE) {
		printf("VirtualFree失败: %d\n",GetLastError());
		return 2;
	}
	puts("");

	printf("Free: DECOMMIT\n");/*取消提交*/

	puts("");


	VirtualQuery(lpAddress, &mbi, sizeof(mbi));//查询地址

	printf("BaseAddress: 0x%p\n", mbi.BaseAddress);
	printf("AllocationBase: 0x%p\n", mbi.AllocationBase);
	printf("AllocationProtect: 0x%p\n", mbi.AllocationProtect);// 保护属性
	printf("RegionSize: %d\n", mbi.RegionSize);
	printf("结果分了 %d 页\n", mbi.RegionSize / 4096);
	printf("State: 0x%p\n", mbi.State); //#define MEM_COMMIT                  0x1000
	printf("Protect: 0x%p\n", mbi.Protect);

	printf("Type: 0x%p\n", mbi.Type);  //MEM_PRIVATE这个程序私有的   MEM_MAPPED 内存映射得到的

	puts("");


	if (!VirtualFree(lpAddress, 0, MEM_RELEASE)) {
		printf("VirtualFree error: %d\n", GetLastError());
		return 4;
	}



	puts("Done");
	system("pause");
    return 0;
}

