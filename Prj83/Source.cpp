#include<Windows.h>
#include"resource.h"

#define SIZ (1024*8)

void f(HWND hwndList) {
	//使用栈
	TCHAR szBuf[SIZ];
	TCHAR *pVarBlock;
	TCHAR *pVarBeg, *pVarEnd;

	pVarBlock = GetEnvironmentStrings();
	auto p = pVarBlock;
	while (*pVarBlock) {
		if (*pVarBlock != '=') {
			pVarBeg = pVarBlock;
			while (*pVarBlock++ != '=');
			pVarEnd = pVarBlock - 1;
			int iLength = pVarEnd - pVarBeg;

			ZeroMemory(szBuf, SIZ);
			CopyMemory(szBuf, pVarBeg, iLength*sizeof(TCHAR));

			SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)szBuf);
		}
		while (*pVarBlock++ != '\0');
	}
	FreeEnvironmentStrings(p);		//get 和 free 相对应

}

INT_PTR CALLBACK MainDlgProc(HWND hDlg, WPARAM uMsg, WPARAM wParam, LPARAM lParam) {
	BOOL bRet = TRUE;
	switch (uMsg) {
	case WM_INITDIALOG:
		f(GetDlgItem(hDlg, IDC_LIST1));
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}

int APIENTRY WinMain(HINSTANCE ins, HINSTANCE pins, LPTSTR lpCmdLine, int nCmdShow) {
	DialogBox(ins, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);
}