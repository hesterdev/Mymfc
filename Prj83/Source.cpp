#include<Windows.h>
#include"resource.h"

void FillListBox(HWND hwndList) {
	//สนำรีป
	TCHAR *pVarBock;
	pVarBock = GetEnvironmentStrings();
	while(*pVarBock)
}

INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	BOOL bRet = TRUE;
	switch (uMsg) {
	case WM_INITDIALOG:
		FillListBox(GetDlgItem(hDlg, IDC_LIST1));
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
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);
}