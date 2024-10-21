#define DIRECTINPUT_VERTION 0x0800

#pragma once

#include<Windows.h>
#include<wrl.h>
#include<dinput.h>




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


private:

	//キーボードのデバイス
	ComPtr<IDirectInputDevice8>keyboard;

};

