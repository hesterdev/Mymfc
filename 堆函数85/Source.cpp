#include<Windows.h>
#include<stdio.h>

int main() {
	//内存是一页一页的, 先获取页面大小
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	HANDLE hHeap1,hHeap2;
	hHeap1 = HeapCreate(HEAP_NO_SERIALIZE/*不要序列化有时会提升性能*/,/*初始大小, 随便写一个,也会让其向上是页的整数倍*/si.dwPageSize * 2, si.dwPageSize * 10);
	if (hHeap1 == NULL) {
		printf("创建堆失败: %d\n", GetLastError());
		return 1;
	}

	printf("创建成功, 初始大小为2页, 最大为10页\n");

	hHeap2 = HeapCreate(HEAP_NO_SERIALIZE, 0/*会向上取一页的*/, 0); //最大没有限制, 可以增长
	if (hHeap2 == NULL) {
		printf("创建堆失败: %d\n", GetLastError());
		return 2;
	}

	printf("创建成功, 初始大小为1页, 没有最大限制, 可以增长\n");

	// 查看当前进程一共有多少堆
	DWORD dwHeapNum = GetProcessHeaps(0, NULL);// 参数若是数组和数组大小,则可以获得所有堆的句柄

	if (dwHeapNum == 0) {//至少也会有一个进程默认的堆
		printf("GetProcessHeaps error: %d\n", GetLastError());
		return 3;
	}

	printf("当前进程一共有 %d 堆\n", dwHeapNum);

	PVOID lpMen1, lpMen2;
	lpMen1 = HeapAlloc(hHeap1, HEAP_ZERO_MEMORY, si.dwPageSize * 3);
	if (lpMen1 == NULL) {
		printf("HeapAlloc error: %d\n", GetLastError());
		return 4;
	}

	printf("在第一个堆上分配内存成功, 起始地址为: 0x%p\n", lpMen1);


	PVOID  lpReAlloc1, lpReAlloc2;

	lpReAlloc1 = HeapReAlloc(hHeap1, HEAP_ZERO_MEMORY, lpMen1, si.dwPageSize * 11);
	if (lpReAlloc1 == NULL) {
		printf("HeapRealloc error: %d\n", GetLastError());
	}




	lpMen2 = HeapAlloc(hHeap2, HEAP_ZERO_MEMORY, si.dwPageSize * 3);
	if (lpMen2 == NULL) {
		printf("HeapAlloc error: %d\n", GetLastError());
		return 4;
	}

	printf("在第一个堆上分配内存成功, 起始地址为: 0x%p\n", lpMen2);



	lpReAlloc2 = HeapReAlloc(hHeap2, HEAP_ZERO_MEMORY, lpMen2, si.dwPageSize * 11);
	if (lpReAlloc2 == NULL) {
		printf("HeapRealloc error: %d\n", GetLastError());
		return 6;
	}

	printf("在堆上再分配内存, 地址: 0x%x, 原地址: 0x%x\n", lpReAlloc2, lpMen2);
	SIZE_T dwHeapBlockAsize;
	dwHeapBlockAsize = HeapSize(hHeap2, HEAP_NO_SERIALIZE, lpReAlloc2);

	if (dwHeapBlockAsize == -1) {
		printf("")
	}

	system("pause");
	return 0;
}