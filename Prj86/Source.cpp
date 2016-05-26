#include<Windows.h>
#include<stdio.h>
#define MEM_BLOCK_SIZE 32

BOOL ShowMemContent(LPVOID lpMen, SIZE_T dwSize) {
	BYTE lpShow[MEM_BLOCK_SIZE];
	INT i = 0;
	CopyMemory((LPVOID)lpShow, lpMen, dwSize);
	for (; i < dwSize; i++) {
		printf("%.2X ", lpShow[i]);
		if (!((i + 1) % 16)) {
			printf("\n");
		}
	}
	printf("\n");
	return TRUE;
}

int main() {
	HANDLE hHeap = GetProcessHeap();
	LPVOID lpMen1, lpMen2;
	lpMen1 = HeapAlloc(hHeap, 0, MEM_BLOCK_SIZE);
	ShowMemContent(lpMen1, MEM_BLOCK_SIZE);

	lpMen2 = HeapAlloc(hHeap, HEAP_ZERO_MEMORY/*ÇåÁã±êÖ¾*/, MEM_BLOCK_SIZE);
	ShowMemContent(lpMen2, MEM_BLOCK_SIZE);

	ZeroMemory(lpMen1, MEM_BLOCK_SIZE);
	ShowMemContent(lpMen1, MEM_BLOCK_SIZE);

	FillMemory(lpMen2, MEM_BLOCK_SIZE, 0xAA);
	ShowMemContent(lpMen2, MEM_BLOCK_SIZE);

	FillMemory(lpMen1, MEM_BLOCK_SIZE / 2, 0xBB);
	ShowMemContent(lpMen1, MEM_BLOCK_SIZE);

	MoveMemory(lpMen2, lpMen1, MEM_BLOCK_SIZE);
	ShowMemContent(lpMen1, MEM_BLOCK_SIZE);
	ShowMemContent(lpMen2, MEM_BLOCK_SIZE);

	FillMemory(lpMen1, MEM_BLOCK_SIZE, 0xDD);

	CopyMemory(lpMen2,lpMen1, MEM_BLOCK_SIZE);
	ShowMemContent(lpMen1, MEM_BLOCK_SIZE);
	ShowMemContent(lpMen2, MEM_BLOCK_SIZE);


	system("pause");
	return 0;
}