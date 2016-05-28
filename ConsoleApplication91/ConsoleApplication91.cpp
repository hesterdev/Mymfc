// ConsoleApplication91.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	SIZE_T sizeVirtual = 4000; // ����������64kb
	LPVOID lpRound = (LPVOID)0x100000ff;
	//Ҫôһҳ,Ҫô��ҳ(��ҳ)

	LPVOID lpAddress = VirtualAlloc(lpRound, sizeVirtual, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (lpAddress == NULL) {
		printf("VirtualAlloc error: %d\n", GetLastError());
		return 1;
	}
	printf("Alloc: MEM_COMMIT|MEM_RESERVE\n");

	CopyMemory(lpAddress, "hello", strlen("hello"));

	printf("%s\n", lpAddress);

	MEMORY_BASIC_INFORMATION mbi;

	VirtualQuery(lpAddress, &mbi, sizeof(mbi));//��ѯ��ַ

	printf("BaseAddress: 0x%p\n", mbi.BaseAddress);
	printf("AllocationBase: 0x%p\n", mbi.AllocationBase);
	printf("AllocationProtect: 0x%p\n", mbi.AllocationProtect);// ��������
	printf("RegionSize: %d\n", mbi.RegionSize); 
	printf("������� %d ҳ\n", mbi.RegionSize / 4096);
	printf("State: 0x%p\n", mbi.State); //#define MEM_COMMIT                  0x1000
	printf("Protect: 0x%p\n", mbi.Protect);

	printf("Type: 0x%p\n", mbi.Type);  //MEM_PRIVATE�������˽�е�   MEM_MAPPED �ڴ�ӳ��õ���

	BOOL res=VirtualFree(lpRound, sizeVirtual, MEM_DECOMMIT);//�ͷ�
	if (res == FALSE) {
		printf("VirtualFreeʧ��: %d\n",GetLastError());
		return 2;
	}
	puts("");

	printf("Free: DECOMMIT\n");/*ȡ���ύ*/

	puts("");


	VirtualQuery(lpAddress, &mbi, sizeof(mbi));//��ѯ��ַ

	printf("BaseAddress: 0x%p\n", mbi.BaseAddress);
	printf("AllocationBase: 0x%p\n", mbi.AllocationBase);
	printf("AllocationProtect: 0x%p\n", mbi.AllocationProtect);// ��������
	printf("RegionSize: %d\n", mbi.RegionSize);
	printf("������� %d ҳ\n", mbi.RegionSize / 4096);
	printf("State: 0x%p\n", mbi.State); //#define MEM_COMMIT                  0x1000
	printf("Protect: 0x%p\n", mbi.Protect);

	printf("Type: 0x%p\n", mbi.Type);  //MEM_PRIVATE�������˽�е�   MEM_MAPPED �ڴ�ӳ��õ���

	puts("");


	if (!VirtualFree(lpAddress, 0, MEM_RELEASE)) {
		printf("VirtualFree error: %d\n", GetLastError());
		return 4;
	}



	puts("Done");
	system("pause");
    return 0;
}

