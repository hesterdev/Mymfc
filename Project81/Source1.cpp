#include<Windows.h>
#include<strsafe.h>
#include<Psapi.h>

#pragma comment(lib,"psapi.lib")

#include"resource.h"

#define IDT_UPDATE 1


INT_PTR CALLBACK MainDlgProc(HWND hDlg, WPARAM uMsg, WPARAM wParam, LPARAM lParam) {
	BOOL bRet = TRUE;
	switch (uMsg) {
	case WM_INITDIALOG:

		SetTimer(hDlg, IDT_UPDATE, 100, NULL);
		SendMessage(hDlg, WM_TIMER, IDT_UPDATE, 0);
	case WM_TIMER:
	{
		MEMORYSTATUSEX ms = { sizeof(ms) };
		GlobalMemoryStatusEx(&ms);

		TCHAR szData[512] = { 0 };
		StringCchPrintf(szData, _countof(szData),
			TEXT("%d\n%I64d\n%I64d\n%I64d\n%I64d\n%I64d\n%I64d\n"), 
			ms.dwMemoryLoad/*已经使用的内存的百分比*/,ms.ullTotalPhys,
			(__int64)ms.ullAvailPhys, (__int64)ms.ullTotalPageFile, (__int64)ms.ullAvailPageFile, (__int64)ms.ullTotalVirtual, (__int64)ms.ullAvailVirtual);

		SetDlgItemText(hDlg, IDC_STATIC1, szData);

		PROCESS_MEMORY_COUNTERS_EX pmc = { sizeof(pmc) };

		GetProcessMemoryInfo(GetCurrentProcess(), (PPROCESS_MEMORY_COUNTERS)&pmc, sizeof(pmc));
		StringCchPrintf(szData, _countof(szData), TEXT("%I64d K\n%I64d K"), (__int64)pmc.WorkingSetSize/1024, (__int64)pmc.PrivateUsage/1024);
		SetDlgItemText(hDlg, IDC_STATIC2, szData);
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