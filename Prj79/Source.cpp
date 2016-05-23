#include<Windows.h>

#include"resource.h"
#include<strsafe.h>

PTSTR BigNumToString(LONG lNum, PTSTR szBuf, DWORD chBufSize) {
	TCHAR szNum[100];
	StringCchPrintf(szNum, _countof(szNum), TEXT("%d"), lNum);
	NUMBERFMT nf;
	nf.NumDigits = 0;
	nf.LeadingZero = FALSE;//前导0 不要
	nf.Grouping = 3;
	nf.lpDecimalSep = TEXT(".");//欧洲人的小数点是一个逗号
	nf.lpThousandSep = TEXT(",");// 欧洲人用小数据点作为千分位
	nf.NegativeOrder = 0;
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szNum, &nf, szBuf, chBufSize);

	return szBuf;
}

void ShowCPUInfo(HWND hWnd, WORD wProcessorArchitecture, WORD wProcessorLevel, WORD wPorcessorRevision) {
	TCHAR szCPUArch[64] = TEXT("unknown");
	TCHAR szCPULevel[64] = TEXT("unknown");
	TCHAR szCPURev[64] = TEXT("unknown");


	switch (wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_INTEL:
		ua_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("Intel"));
		switch (wProcessorLevel)
		{
		case 3:
		case 4:
			StringCchPrintf(szCPULevel, _countof(szCPULevel), TEXT("80%c86"), wProcessorLevel + '0'/*数字转为字符*/);
			StringCchPrintf(szCPURev, _countof(szCPURev), TEXT("%c%d"), HIBYTE(wPorcessorRevision) + TEXT('A'), LOBYTE(wPorcessorRevision));
			break;
		case 5://叫做奔腾  之前是386 486
			ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Pentium"));
			StringCchPrintf(szCPURev, _countof(szCPURev), TEXT("Model %d, Stepping %d"), HIBYTE(wPorcessorRevision), LOBYTE(wPorcessorRevision));

			break;
		case 6:
			switch (wProcessorLevel)
			{
			case 1:
				ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Pentium Pro"));
				break;
			case 3:
			case 5:
				ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Pentium II"));
				break;
			case 6:
				ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Celeron"));
				break;
			case 7:
			case 8:
			case 11:
				ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Pentium III"));
				break;
			case 9:
			case 13:
				ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Pentium M"));
				break;
			case 10:
				ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Pentium Xeon"));//至强
				break;
			case 15:
				ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Core 2 Duo"));
				break;
			default:
				ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Unknown pentium"));

				break;
			}
			StringCchPrintf(szCPURev, _countof(szCPURev), TEXT("Model %d, Stepping %d"),
				HIBYTE(wPorcessorRevision), LOBYTE(wPorcessorRevision));
			break;
		case 15:// 奔腾4 截止到目前是最新的
			ua_tcscpy_s(szCPULevel, _countof(szCPULevel), TEXT("Pentium 4"));
			break;

		default:
			break;
		}
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		ua_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("IA-64"));
		break;
	case PROCESSOR_ARCHITECTURE_AMD64:
		ua_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("AMD64"));
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
	default:
		ua_tcscpy_s(szCPUArch, _countof(szCPUArch), TEXT("unknown"));
		break;
	}

	SetDlgItemText(hWnd, IDC_PROCARCH, szCPUArch);
	SetDlgItemText(hWnd, IDC_PROCLEVEL, szCPULevel);
	SetDlgItemText(hWnd, IDC_PROREV, szCPURev);
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

		StringCchPrintf(szBuf, _countof(szBuf), BigNumToString(sinf.dwAllocationGranularity, szBuf, _countof(szBuf)));
		SetDlgItemText(hDlg, IDC_ALLOCGRAN, szBuf);

		SetDlgItemInt(hDlg, IDC_NUMOFPRO, sinf.dwNumberOfProcessors, FALSE);

		StringCchPrintf(szBuf, _countof(szBuf), TEXT("0x%I64X", (__int64)sinf.dwActiveProcessorMask));
		SetDlgItemText(hDlg, IDC_ACTIVEPROCMASK, szBuf);

		ShowCPUInfo(hDlg, sinf.wProcessorArchitecture, sinf.wProcessorLevel, sinf.wProcessorRevision);
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