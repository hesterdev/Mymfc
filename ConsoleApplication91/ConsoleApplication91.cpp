// ConsoleApplication91.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	SIZE_T sizeVirtual = 4000; // 分配粒度是64kb
	LPVOID lpRound = (LPVOID)0x100000ff;

	//要么一页,要么两页(跨页)

	LPVOID lpAddress = VirtualAlloc(lpRound, sizeVirtual, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	puts("Done");
	system("pause");
    return 0;
}

