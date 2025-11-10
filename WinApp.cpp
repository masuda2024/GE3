#include "WinApp.h"

#include"externals/imgui/imgui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler
(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


void WinApp::Initialize()
{
	
	CoInitializeEx(0, COINIT_MULTITHREADED);
	
	
	//WNDCLASS wc{};
	
	
	//ウィンドウブロシージャ
	wc.lpfnWndProc = WindowProc;

	//ウィンドウクラス(なんでも良い)
	wc.lpszClassName = L"CG2WindowClass";
	//インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);//スペル間違いを
	//カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウィンドウクラスを登録する
	RegisterClass(&wc);

	

	//ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	//クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	
	//ウィンドウの生成
	//HWND hwnd = CreateWindow
	//(
	//	wc.lpszClassName,        //利用するクラス名
	//	L"CG2",                  //タイトルバーの文字(なんでも良い)
	//	WS_OVERLAPPEDWINDOW,	 //よく見るウィンドウスタイル
	//	CW_USEDEFAULT,			 //表示X座標(Windowsに任せる)
	//	CW_USEDEFAULT,			 //表示Y座標(WindowsOSに任せる)
	//	wrc.right - wrc.left,	 //ウィンドウ横幅
	//	wrc.bottom - wrc.top,	 //ウィンドウ縦幅
	//	nullptr,				 //親ウィンドウハンドル
	//	nullptr,				 //メニューハンドル
	//	wc.hInstance,			 //インスタンスハンドル
	//	nullptr
	//);				 //オプション
    


	//ウィンドウを表示する
	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::Update()
{

}

void WinApp::Finalize()
{
	CloseWindow(hwnd);
	CoUninitialize();
}


bool WinApp::ProceccMassage()
{
	MSG msg{};

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT)
	{
		return true;
	}


	return false;
}
