#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include"WinApp.h"
#include"Logger.h"
class DirectXCommon
{
public:
	//初期化
	void Initialize();
	
	void Device();
	void Command();
	void SwapChain();
	void DepthBuffer();
	void DescriptorHeap();
	void LenderTargetView();//CG2_01_00
	
	void Fence();
	
	//描画開始
	void PreDraw();
	//描画終了
	void PostDraw();

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>CreateDescriptorHeap
	(
		D3D12_DESCRIPTOR_HEAP_TYPE heapType,
		UINT numDescriptors,
		bool shaderVisible
	);
	
private:

	//WindowsAPI
	WinApp* winApp = nullptr;

	

	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリー
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	
};