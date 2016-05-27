// ConsoleApplication89.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	setlocale(LC_ALL, "");

	HGLOBAL hMen;
	hMen = GlobalAlloc(GHND, 1000);

	LPVOID lpMen;
	lpMen = GlobalLock(hMen);
	lstrcpy((LPTSTR)lpMen, _T("this is a string"));
	GlobalUnlock(hMen);

	SIZE_T memSize = GlobalSize(hMen);

	_tprintf(_T("内存地址:0x%p\n"), lpMen);
	_tprintf(_T("内存大小:%d\n"), memSize);
	_tprintf(_T("内存内容:%s\n"), lpMen);


	hMen = GlobalReAlloc(hMen, 2000, GHND);

	lpMen = GlobalLock(hMen);
	lstrcpy((LPTSTR)lpMen, _T("hello this is a string again"));
	GlobalUnlock(hMen);

	memSize = GlobalSize(hMen);
	_tprintf(_T("内存地址:0x%p\n"), lpMen);
	_tprintf(_T("内存大小:%d\n"), memSize);
	_tprintf(_T("内存内容:%s\n"), lpMen);




	system("pause");
	return 0;
}

