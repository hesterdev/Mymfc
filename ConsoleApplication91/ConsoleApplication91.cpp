// ConsoleApplication91.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	SIZE_T sizeVirtual = 4000; // ����������64kb
	LPVOID lpRound = (LPVOID)0x100000ff;

	//Ҫôһҳ,Ҫô��ҳ(��ҳ)

	LPVOID lpAddress = VirtualAlloc(lpRound, sizeVirtual, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	puts("Done");
	system("pause");
    return 0;
}

