#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>

#include"WinApp.h"
#include"Logger.h"
#include"StringUtility.h"

//入力デバイス
#define DIRECTINPUT_VERSION 0x0800// DirectInput8のバージョン指定
#include <dinput.h>

using namespace Microsoft::WRL;



class DirectX;

class DirectXCommon
{
public:

	HRESULT hr;
	 


//初期化
	void Initialize(WinApp* winApp);



	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	




public:



	//ID3D12Device* GetDxDevice()const { return device; }

	//IDXGISwapChain4* GetSwapChain()const { return swapChain; }







	//RTV
	//RTVの指定番号のCPUディスクリプタハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUDescriptorHandle(uint32_t index);
	//RTVの指定番号のGPUディスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetRTVGPUDescriptorHandle(uint32_t index);


	//SRV
	//SRVの指定番号のCPUディスクリプタハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);
	//SRVの指定番号のGPUディスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);


	//DSV
	//DSVの指定番号のCPUディスクリプタハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCPUDescriptorHandle(uint32_t index);
	//DSVの指定番号のGPUディスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetDSVGPUDescriptorHandle(uint32_t index);





	//指定番号のCPUディスクリプタハンドルを取得する
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	//指定番号のGPUディスクリプタハンドルを取得する
	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);



	




	/*
	void SetClearColor(float r, float g, float b, float a)
	{
		clearcolor[0] = r;
		clearcolor[1] = g;
		clearcolor[2] = b;
		clearcolor[3] = a;
	}*/




private:


	void CreateDescriptorHeap();
	void RenderTargetView();//CG2_01_00
	void CreateDepthStencilView(ID3D12Device* device, int32_t width, int32_t height);
	void ViewPort();
	void ScissorRect();

	void CreateDXC();



private:

	//デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device = nullptr;
	//コマンド
	//スワップチェーン
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = nullptr;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	//フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence = nullptr;
	//rtv
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};



	//ディスクリプタヒープ
	//RTV Heap
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap = nullptr;
	//SRV Heap
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap = nullptr;
	//DSV Heap
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap = nullptr;


	uint32_t DescriptorSizeRTV = 0;
	uint32_t DescriptorSizeSRV = 0;
	uint32_t DescriptorSizeDSV = 0;



	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//RTVを2つ作成するためディスクリプタも2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2]{};


	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilResource = nullptr;
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle{};

	D3D12_VIEWPORT viewport{};
	//scissor
	D3D12_RECT scissorRect{};


public:


	
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);


	void RenderTargetView();


	










	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2>swapChainResources;



























	
	






	void CreateDevice();
	void Command();
	void SwapChain();
	




	void Descriptor();


	

	void CreateDepthStencilView();

	void Fence();
	

	

	


	void DXC();

	void ImGui(ID3D12Device* device);



	//描画開始
	void PreDraw();
	//描画終了
	void PostDraw();



	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);

	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	
private:

	//WindowsAPI
	WinApp* winApp = nullptr;

	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリー
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>CreateDescriptorHeap
	(
		D3D12_DESCRIPTOR_HEAP_TYPE heapType,
		UINT numDescriptors,
		bool shaderVisible
	);

	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);

	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);

	//std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;





private:

	

private:


	/*
	std::unique_ptr<DxDevice> device = nullptr;
	std::unique_ptr<DxCommand> command = nullptr;
	std::unique_ptr<DxSwapChain>swapChain = nullptr;
	std::unique_ptr<DxFence>fence = nullptr;


	UINT backBufferIndex = 0;


	//ディスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap>rtvDescriptorHeap = nullptr;
	ComPtr<ID3D12DescriptorHeap>srvDescriptorHeap = nullptr;
	ComPtr<ID3D12DescriptorHeap>dsvDescriptorHeap = nullptr;

	uint32_t rtvDescriptorSize = 0;
	uint32_t srvDescriptorSize = 0;
	uint32_t dsvDescriptorSize = 0;

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2]{};

	ComPtr<ID3D12Resource> depthStencilResource = nullptr;
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle{};





	D3D12_VIEWPORT viewport{};

	D3D12_RECT scissorRect{};






*/
















};