#include<Windows.h>

#include"resource.h"
#include<strsafe.h>

PTSTR BigNumToString(LONG lNum, PTSTR szBuf, DWORD chBufSize) {
	TCHAR szNum[100];
	StringCchPrintf(szNum, _countof(szNum), TEXT("%d"), lNum);
	NUMBERFMT nf;
	nf.NumDigits = 0;
	nf.LeadingZero = FALSE;//ǰ��0 ��Ҫ
	nf.Grouping = 3;
	nf.lpDecimalSep = TEXT(".");//ŷ���˵�С������һ������
	nf.lpThousandSep = TEXT(",");// ŷ������С���ݵ���Ϊǧ��λ
	nf.NegativeOrder = 0;
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szNum, &nf, szBuf, chBufSize);

	return szBuf;
}


INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BOOL bRet = TRUE;
	switch (uMsg) {
	case WM_INITDIALOG:

		SYSTEM_INFO sinf;
		GetSystemInfo(&sinf);

		TCHAR szBuf[50];
		SetDlgItemText(hDlg, IDC_PAGESIZE, BigNumToString(sinf.dwPageSize, szBuf, _countof(szBuf)));

		StringCchPrintf(szBuf, _countof(szBuf), TEXT("%p"), sinf.lpMinimumApplicationAddress);
		SetDlgItemText(hDlg, IDC_MINADDR, szBuf);

		StringCchPrintf(szBuf, _countof(szBuf), TEXT("%p"), sinf.lpMaximumApplicationAddress);
		SetDlgItemText(hDlg, IDC_MAXADDR, szBuf);

		StringCchPrintf(szBuf, _countof(szBuf),BigNumToString(sinf.dwAllocationGranularity,szBuf,_countof(szBuf)));
		SetDlgItemText(hDlg,IDC_ALLOCGRAN, szBuf);



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
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);
}