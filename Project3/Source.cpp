#include<Windows.h>
#include<stdio.h>

int main() {
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	HANDLE hHeap3;
	hHeap3 = GetProcessHeap();

	PVOID lpMen3;
	lpMen3= HeapAlloc(hHeap3, HEAP_NO_SERIALIZE, si.dwPageSize * 3);
	if (lpMen3 == NULL) {
		printf("HeapAlloc error: %d\n", GetLastError());
		return 10;
	}
	printf("�ڽ���Ĭ�϶��Ϸ����ڴ�ɹ�\n");

	if (!HeapFree(hHeap3,HEAP_NO_SERIALIZE,lpMen3)) {
		printf("HeapFree error: %d\n", GetLastError());
		return 11;
	}
	printf("�ڽ���Ĭ�϶����ͷ��ڴ�ɹ�\n");
	system("pause");
	return 0;
}