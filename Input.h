#pragma once
#include"Windows.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <cstdint>


typedef uint8_t KeyCode;

class Input
{
public:
	
	Input() = default;
	~Input()
	{
		delete directInput;
		//delete keyboad;
	};
   



	//初期化
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//更新
	void Update();


	bool PushKey(KeyCode keyCode) { return key[keyCode]; }
	bool TriggerKey(KeyCode keyCode) { return key[keyCode]&&!prekey[keyCode]; }
	bool ReleaseKey(KeyCode keyCode) { return !key[keyCode]&&prekey[keyCode]; }


private:
	
	
	//DXGIファクトリーの生成
	

	//Direct Input
	IDirectInput8* directInput = nullptr;

	//keyboadDevice
	IDirectInputDevice8* keyboard = nullptr;

	//各キーの入力状態
	BYTE key[256] = {};//現在の各キー入力状態
	BYTE prekey[256] = {};
	//1frame前の各キー入力状態


};

