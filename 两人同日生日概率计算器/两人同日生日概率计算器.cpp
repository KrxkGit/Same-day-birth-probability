// 两人同日生日概率计算器.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "两人同日生日概率计算器.h"



// 此代码模块中包含的函数的前向声明:
HINSTANCE hInst;


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	hInst=hInstance;
	DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1),NULL,MainDlgFunc);
	return GetLastError();
}




// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

VOID OnCommand(HWND hWnd,WPARAM wParam)
{
	if(LOWORD(wParam)==IDOK) {
		const unsigned int Days=SendDlgItemMessage(hWnd,IDC_CHECK1,BM_GETCHECK,0,0)? 366:365;
		unsigned int n = GetDlgItemInt(hWnd,IDC_EDIT1,NULL,FALSE);
		if(n<2) {
			SetDlgItemText(hWnd,IDC_EDIT2,_T("不可能事件"));
			return;
		}
		if(n>151/*最大数值*/) {
			if(n>Days) {
				SetDlgItemText(hWnd,IDC_EDIT2,_T("100%"));
				return;
			}
			SetDlgItemText(hWnd,IDC_EDIT2,_T("超出计算范围"));
			return;
		}
		long double S=1;
		for(n-=1;n;n--) {
			S=S*(Days-n)/Days;
		}
		S=100*(1-S);
		TCHAR sz[40];
		_stprintf_s(sz,_countof(sz),_T("%.15lf%%"),S);
		SetDlgItemText(hWnd,IDC_EDIT2,sz);
	}
	switch (LOWORD(wParam))
	{
	case IDM_ABOUT:
		DialogBox(hInst,MAKEINTRESOURCE(IDD_ABOUTBOX),hWnd,About);
		break;
	case IDM_AUTHORPAGE:
		ShellExecute(NULL,_T("open"),_T("https://github.com/KrxkGit/"),NULL,NULL,SW_SHOWNORMAL);
		break;
	}
}

INT_PTR CALLBACK MainDlgFunc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(hDlg,WM_SETICON,0,(LPARAM)LoadIcon(hInst,MAKEINTRESOURCE(IDI_MY)));
		return TRUE;
	case WM_COMMAND:
		OnCommand(hDlg,wParam);
		if(LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
