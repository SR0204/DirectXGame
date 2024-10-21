//#define DIRECTINPUT_VERTION 0x0800
#include "Input.h"
#include<cassert>
//#include<wrl.h>
//#include<dinput.h>


#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

//using namespace Microsoft::WRL;

void Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{

	HRESULT result;


	//DirectXの初期化

	//DirectInputの初期化
	IDirectInput8* directInput = nullptr;
	result = DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr
	);
	assert(SUCCEEDED(result));


	//キーボードデバイスの生成
	//IDirectInputDevice8* keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);
	assert(SUCCEEDED(result));

}



void Input::Update()
{

	//キーボード情報の取得開始
	keyboard->Acquire();

	//全キーの入力状態を取得する
	BYTE key[256] = {};
	keyboard->GetDeviceState(sizeof(key), key);

}
