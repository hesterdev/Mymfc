#include<Windows.h>
#include"resource.h"

#define SIZ (1024*8)

void f(HWND hwndList) {

	//使用栈
	//TCHAR szBuf[SIZ];

	//使用堆
	//TCHAR *pVarName;

	//使用堆
	PVOID  pVName;

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

			//pVarName = (TCHAR*)calloc(iLength + 1, sizeof(TCHAR)); //会进行初始化

			/*pVarName = (TCHAR*)malloc((iLength + 1)*sizeof(TCHAR));
			ZeroMemory(pVarName, (iLength + 1)*sizeof(TCHAR));
			CopyMemory(pVarName, pVarBeg, iLength*sizeof(TCHAR));*/


			// HeapAlloc是 windows api函数
			pVName = HeapAlloc(GetProcessHeap(), 0, (iLength + 1)*sizeof(TCHAR));
			ZeroMemory(pVName, (iLength + 1)*sizeof(TCHAR));
			CopyMemory(pVName, pVarBeg, iLength*sizeof(TCHAR));



			//ZeroMemory(szBuf, SIZ);
			//CopyMemory(szBuf, pVarBeg, iLength*sizeof(TCHAR));

			SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)pVName);
			HeapFree(GetProcessHeap(), 0, pVName);
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
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE) {
			int iIndex, iLength;
			TCHAR *pVarName, *pVarValue;

			iIndex = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCURSEL, 0, 0);
			iLength = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXTLEN, iIndex, 0) + 1;
			pVarName = (TCHAR*)calloc(iLength, sizeof(TCHAR));

			SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, iIndex, (LPARAM)pVarName);


			iLength = GetEnvironmentVariable(pVarName, NULL, 0);
			pVarValue = (TCHAR*)calloc(iLength, sizeof(TCHAR*));
			GetEnvironmentVariable(pVarName, pVarValue,iLength);

			SetWindowText(GetDlgItem(hDlg,IDC_STATIC1), pVarValue);
			free(pVarName);
			free(pVarValue);
		}
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