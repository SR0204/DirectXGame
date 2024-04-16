#include <Windows.h>
#include<cstdint>


//ウィンドウプロシージャ
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

		//メッセージに応じてゲーム固有の処理を行う
		switch (msg) {
			//ウィンドウが破壊された
		case WM_DESTROY:
			//OSに対してアプリの終了を伝える
			PostQuitMessage(0);
			return 0;
		}
		//標準のメッセージ処理を行う
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

//Windowsアプリでのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WNDCLASS wc{};
	//ウィンドウプロシージャ
	wc.lpfnWndProc = WindowProc;

	//ウィンドウクラス名
	wc.lpszClassName = L"CG2WindowClass";

	//インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);

	//カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウィンドウクラスを登録
	RegisterClass(&wc);

	//クライアント領域のサイズ
	const int32_t kClientWidth = 1280;

	const int32_t kClientHeight = 720;
	
	//ウィンドウサイズを表す構造体にwrcを変更してもらう
	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	//クライアント領域をもとに実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの生成
	HWND hwnd = CreateWindow(
		wc.lpszClassName,  //利用するクラス名
		L"CG2",            //タイトルバーの文字
		WS_OVERLAPPEDWINDOW,//よく見るウィンドウスタイル
		CW_USEDEFAULT,//標準X座標
		CW_USEDEFAULT,//標準Y座標
		wrc.right - wrc.left,//ウィンドウ横幅
		wrc.bottom - wrc.top,//ウィンドウ縦幅
		nullptr,//親ウィンドウハンドル
		nullptr,//メニューハンドル
		wc.hInstance,//インスタンスハンドル
		nullptr//オプション
	);

	//ウィンドウを表示する
	ShowWindow(hwnd, SW_SHOW);
	

	MSG msg{};

	//ウィンドウの×ボタンが押されるまでのループ
	while (msg.message != WM_QUIT) {
		//windowにメッセージが来てたら最優先で処理させる

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//ゲームの処理

		}
	}

	

	//出力ウィンドウへの文字出力
	//OutputDebugStringA("Hello,DirectX!\n");

	return 0;
}