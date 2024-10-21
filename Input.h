#define DIRECTINPUT_VERTION 0x0800

#pragma once

#include<Windows.h>
#include<wrl.h>
#include<dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")


//入力
class Input
{
public:
	//初期化
	void Initialize(HINSTANCE hInstance, HWND hwnd);

	//更新
	void Update();

	//namespace省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;


	bool PushKey(BYTE keyNumber);




private:

	//キーボードのデバイス
	ComPtr<IDirectInputDevice8>keyboard;

	//全キーの状態
	BYTE key[256] = {};

};

