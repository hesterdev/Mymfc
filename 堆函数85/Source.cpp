#include<Windows.h>
#include<stdio.h>

int main() {
	//�ڴ���һҳһҳ��, �Ȼ�ȡҳ���С
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	HANDLE hHeap1,hHeap2;
	hHeap1 = HeapCreate(HEAP_NO_SERIALIZE/*��Ҫ���л���ʱ����������*/,/*��ʼ��С, ���дһ��,Ҳ������������ҳ��������*/si.dwPageSize * 2, si.dwPageSize * 10);
	if (hHeap1 == NULL) {
		printf("������ʧ��: %d\n", GetLastError());
		return 1;
	}

	printf("�����ɹ�, ��ʼ��СΪ2ҳ, ���Ϊ10ҳ\n");

	hHeap2 = HeapCreate(HEAP_NO_SERIALIZE, 0/*������ȡһҳ��*/, 0); //���û������, ��������
	if (hHeap2 == NULL) {
		printf("������ʧ��: %d\n", GetLastError());
		return 2;
	}

	printf("�����ɹ�, ��ʼ��СΪ1ҳ, û���������, ��������\n");

	// �鿴��ǰ����һ���ж��ٶ�
	DWORD dwHeapNum = GetProcessHeaps(0, NULL);// ������������������С,����Ի�����жѵľ��

	if (dwHeapNum == 0) {//����Ҳ����һ������Ĭ�ϵĶ�
		printf("GetProcessHeaps error: %d\n", GetLastError());
		return 3;
	}

	printf("��ǰ����һ���� %d ��\n", dwHeapNum);

	PVOID lpMen1, lpMen2;
	lpMen1 = HeapAlloc(hHeap1, HEAP_ZERO_MEMORY, si.dwPageSize * 3);
	if (lpMen1 == NULL) {
		printf("HeapAlloc error: %d\n", GetLastError());
		return 4;
	}

	printf("�ڵ�һ�����Ϸ����ڴ�ɹ�, ��ʼ��ַΪ: 0x%p\n", lpMen1);


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

	printf("�ڵ�һ�����Ϸ����ڴ�ɹ�, ��ʼ��ַΪ: 0x%p\n", lpMen2);



	lpReAlloc2 = HeapReAlloc(hHeap2, HEAP_ZERO_MEMORY, lpMen2, si.dwPageSize * 11);
	if (lpReAlloc2 == NULL) {
		printf("HeapRealloc error: %d\n", GetLastError());
		return 6;
	}

	printf("�ڶ����ٷ����ڴ�, ��ַ: 0x%x, ԭ��ַ: 0x%x\n", lpReAlloc2, lpMen2);
	SIZE_T dwHeapBlockAsize;
	dwHeapBlockAsize = HeapSize(hHeap2, HEAP_NO_SERIALIZE, lpReAlloc2);

	if (dwHeapBlockAsize == -1) {
		printf("")
	}

	system("pause");
	return 0;
}