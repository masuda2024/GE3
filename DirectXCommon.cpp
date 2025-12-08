#include "DirectXCommon.h"
#include"Logger.h"
#include"StringUtility.h"


#include <cstdint>
#include<filesystem>//ファイルやディレクトリに関するライブラリ
#include <fstream>//ファイルに書き込み、読み込み
#include <chrono>//時間を扱う

#include<string>
#include<format>





/////****************************************/////

/*
//ログ出力
namespace Logger
{
	void Log(const std::string& massage);
};
*/



#include<cassert>

//libのリンク
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")






using namespace Microsoft::WRL;
using namespace Logger;
using namespace StringUtility;






#include<d3d12.h>
#include<dxgi1_6.h>




#pragma region String
/*
void Log(const std::string& message)
{
	OutputDebugStringA(message.c_str());
}

std::wstring ConvertString(const std::string& str)
{
	if (str.empty())
	{
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar
	(
		CP_UTF8, 0,
		reinterpret_cast<const char*>(&str[0]),
		static_cast<int>(str.size()),
		NULL, 0
	);

	if (sizeNeeded == 0)
	{
		return std::wstring();
	}

	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar
	(
		CP_UTF8, 0,
		reinterpret_cast<const char*>(&str[0]),
		static_cast<int>(str.size()),
		&result[0], sizeNeeded
	);

}


std::string ConvertString(const std::wstring& str)
{
	if (str.empty())
	{
		return std::string();
	}

	auto sizeNeeded = WideCharToMultiByte
	(
		CP_UTF8, 0,
		str.data(),
		static_cast<int>(str.size()),
		NULL, 0, NULL, NULL
	);

	if (sizeNeeded == 0)
	{
		return std::string();
	}

	std::string result(sizeNeeded, 0);
	WideCharToMultiByte
	(
		CP_UTF8, 0, str.data(),
		static_cast<int>(str.size()),
		result.data(), sizeNeeded, NULL, NULL
	);


	return result;

}
//string->wstring
std::wstring ConvertString(const std::string& str);

//wstring->string
std::string ConvertString(const std::wstring& str);
*/
#pragma endregion




















/////****************************************/////
#pragma region
#pragma endregion



//DepthStencilTexureを作る
ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height)
{
	//生成するResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = width;
	resourceDesc.Height = height;
	resourceDesc.MipLevels = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	//利用するHeapの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;


	//深度値のクリア設定
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;


	//Resourceの生成
	ID3D12Resource* resource = nullptr;
	HRESULT hr = device->CreateCommittedResource
	(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(&resource)
	);



	assert(SUCCEEDED(hr));
	return resource;
}


ID3D12DescriptorHeap* CreateDescriptorHeap(
	ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType,
	UINT numDescriptors, bool shaderVisible)
{
	//ディスククリプタヒープの生成
	ID3D12DescriptorHeap* descriptorHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
	descriptorHeapDesc.Type = heapType;//レンダーターゲットビュー用
	descriptorHeapDesc.NumDescriptors = numDescriptors;//ダブルバッファように2つ。多くても構わない
	descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	HRESULT hr = device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
	//ディスクリプタヒープが作られなかったので起動できない
	assert(SUCCEEDED(hr));
	return descriptorHeap;
}


//デバイスの初期化
void DirectXCommon::Device()
{
	HRESULT hr;

	//デバッグレイヤーをオンに

	//DXGIファクトリーの生成

	//アダプターの列挙

	//デバイス生成

	//エラー時にブレークを発生させる設定



}



//コマンド関連の初期化
void DirectXCommon::Command()
{
	HRESULT hr;
	
	//コマンドアロケーター生成
	ID3D12CommandAllocator* commmandAllocator = nullptr;
	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,IID_PPV_ARGS(&commmandAllocator));
	//コマンドアロケーターの生成がうまくいなかったので起動できない
	assert(SUCCEEDED(hr));
	
	//コマンドリスト生成
	ID3D12GraphicsCommandList* commandList = nullptr;
	hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commmandAllocator, nullptr, IID_PPV_ARGS(&commandList));
	//コマンドリストの生成がうまくいなかったので起動できない
	assert(SUCCEEDED(hr));

	//コマンドキュー生成
	ID3D12CommandQueue* commandQueue = nullptr;
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	hr = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	//コマンドキューの生成がうまくいなかったので起動できない
	assert(SUCCEEDED(hr));
}

//スワップチェーンの生成
void DirectXCommon::SwapChain()
{
	//スワップチェーン生成の設定

	//スワップチェーン生成
}

//深度バッファの生成
void DirectXCommon::DepthBuffer()
{
	//深度バッファリソース設定

	//利用するヒープの設定

	//深度値のクリア設定

	//深度バッファ生成

	//リソースの生成

}

//レンダーターゲットビューの初期化
void DirectXCommon::SwapChain()
{
	//スワップチェーンからリソースを引っ張ってくる

	//RTV用の設定

	//RTVハンドルの要素数を2個に変更する
	
	/*
	//要素2つ分
	for(uint32_t i = 0; i < RTVハンドルの要素数; i++)
	{
		//RTVハンドルを取得
		//レンダーターゲットビューの生成
	}
	*/
}












void DirectXCommon::Initialize()
{
	//デバイスの生成
	//デバッグレイヤーの有効化
	//コマンド周りの生成
	//スワップチェーンの生成
	//深度バッファの生成
	//深度バッファのテクスチャ生成
	//ディスクリプタヒープの生成

	//NULL検出
	assert(winApp);
	//メンバ変数に記録
	this->winApp = winApp;

	

	HRESULT hr;
	

#pragma region アダプターの選別---CG2_00_05
	//使用するアダブタ用の変数。最初にnullptrを入れておく
	IDXGIAdapter4* useAdapter = nullptr;
	//よい順にアダブタを頼む
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i,
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) !=
		DXGI_ERROR_NOT_FOUND; i++)
	{
		//アダブターの情報を取得する
		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = useAdapter->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr));//取得できないのは一大事
		//ソフトウェアアダブタでなければ採用!
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			Log(ConvertString(std::format(L"Use Adapater:{}\n", adapterDesc.Description)));//ここのエラーは、0-5の補足教材にある
			break;
		}
		useAdapter = nullptr;
	}
	//適切なアダブタが見つからなかったので起動できない
	assert(useAdapter != nullptr);

	ID3D12Device* device = nullptr;
	//機能レベルとログ出力用の文字列
	D3D_FEATURE_LEVEL featrueLevels[] =
	{
		D3D_FEATURE_LEVEL_12_2,D3D_FEATURE_LEVEL_12_1,D3D_FEATURE_LEVEL_12_0
	};
	const char* featureLevelStrings[] = { "12.2","12.1","12.0" };
	//高い順に生成できるか試していく
	for (size_t i = 0; i < _countof(featrueLevels); i++)
	{
		hr = D3D12CreateDevice(useAdapter, featrueLevels[i], IID_PPV_ARGS(&device));
		//指定した機能レベルでデバイスが生成できたかを確認
		if (SUCCEEDED(hr))
		{
			//生成できたのでログ出力を行ってループを抜ける
			Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
			break;
		}
	}
#pragma endregion アダプターの選別

#pragma region デバイスの生成---CG2_00_05

	ID3D12Device* device = nullptr;
	//機能レベルとログ出力用の文字列
	D3D_FEATURE_LEVEL featrueLevels[] =
	{
		D3D_FEATURE_LEVEL_12_2,D3D_FEATURE_LEVEL_12_1,D3D_FEATURE_LEVEL_12_0
	};
	const char* featureLevelStrings[] = { "12.2","12.1","12.0" };
	//高い順に生成できるか試していく
	for (size_t i = 0; i < _countof(featrueLevels); i++)
	{
		//採用したアダプターでデバイスを生成
		hr = D3D12CreateDevice(useAdapter, featrueLevels[i], IID_PPV_ARGS(&device));
		//指定した機能レベルでデバイスが生成できたかを確認
		if (SUCCEEDED(hr))
		{
			//生成できたのでログ出力を行ってループを抜ける
			Log(std::format("FeatureLevel : {}\n", featureLevelStrings[i]));
			break;
		}
	}
	//デバイスの生成がうまくいかなかったので起動できない
	assert(device != nullptr);
	Log("Complete create D3D12Drivice!!!\n");//初期化完了のログをだす

#pragma endregion デバイスの生成

#pragma region コマンド周りの生成---CG2_01_00
	//コマンドキューを生成する
	ID3D12CommandQueue* commandQueue = nullptr;
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	hr = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	//コマンドキューの生成がうまくいかなかったので起動できない
	assert(SUCCEEDED(hr));

	//コマンドアロケータを生成する
	ID3D12CommandAllocator* commandAllocator = nullptr;
	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
	assert(SUCCEEDED(hr));

	//コマンドリストを生成する
	ID3D12GraphicsCommandList* commandList = nullptr;
	hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr,
		IID_PPV_ARGS(&commandList));
	assert(SUCCEEDED(hr));

	


#pragma endregion コマンド周りの生成

#pragma region スワップチェーンの生成---CG2_01_00

	//スワップチェーンを生成する
	IDXGISwapChain4* swapChain = nullptr;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = WinApp::kClientWidth;//画面の幅。ウインドウのクライアント領域を同じものにしておく
	swapChainDesc.Height = WinApp::kClientHeight;//画面の高さ。ウインドウもクライアント領域を同じものにしておく
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//色の形式
	swapChainDesc.SampleDesc.Count = 1;//マルチサンプルしない
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//描画のターゲットとして利用する
	swapChainDesc.BufferCount = 2;//ダブルバッファ
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//モニターに映したら、中身を破棄
	//コマンドキュー、ウィンドウハンドル、設定を渡して生成する
	hr = dxgiFactory->CreateSwapChainForHwnd(commandQueue, winApp->GetHwnd(), &swapChainDesc, nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(&swapChain));
	assert(SUCCEEDED(hr));

#pragma endregion スワップチェーンの生成



	
#pragma region 深度バッファ(Zバッファ)の生成---CG2_03_01






#pragma endregion 深度バッファ(Zバッファ)の生成




	







#pragma region ファクトリーの生成
	//DXGIファクトリーの生成
	IDXGIFactory7* dxgiFactory = nullptr;
	//関数が成功したかどうかをSUCCEEDEDマクロで判定できる
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	//初期化の根本的な部分でエラーが出た場合はプログラムが間違っているか、
	//どうにもできない場合が多いのでassertにしておく
	assert(SUCCEEDED(hr));
#pragma endregion ファクトリーの生成

#pragma region デバッグレイヤーの有効化
	//Debug();




#ifdef _DEBUG//DEBUGはCreateWindowの直後

	ID3D12Debug1* debugController = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		//デバックレイヤーを有効化する
		debugController->EnableDebugLayer();
		//さらにGPU側でもチェックを行うようにする
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif // _DEBUG
#pragma endregion デバッグレイヤーの有効化
	
	
	
	
	
	//アダプターの選別

	
	
	
	
	
	
	
	
	
	
	
#pragma region エラーの設定


#ifdef _DEBUG
	ID3D12InfoQueue* infoQueue = nullptr;
	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		//ヤバいエラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		//エラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		//警告時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
		//抑制するメッセージのID
		D3D12_MESSAGE_ID denyIds[] =
		{
			//Windows11でのDXGIデバックレイヤーとDX12デバックレイヤーの相互作用バグによるエラーメッセージ
			//https://stackoberflow.com/questions/69805245/directx-12-application-is-crashing-in-windows-11
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};
		//抑制するレベル
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		//指定したメッセージの表示を抑制する
		infoQueue->PushStorageFilter(&filter);

		//解放
		infoQueue->Release();
	}
#endif // DEBUG
#pragma endregion エラーの設定	
	
	
	
	
	// スワップチェーン用リソースの
#pragma region スワップチェーン用リソースの生成
	//SwapChainからResourceを引っ張ってくる
	ID3D12Resource* swapChainResources[2] = { nullptr };
	hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&swapChainResources[0]));

	//うまく取得できなけらば起動できない
	assert(SUCCEEDED(hr));
	hr = swapChain->GetBuffer(1, IID_PPV_ARGS(&swapChainResources[1]));
	assert(SUCCEEDED(hr));
#pragma endregion スワップチェーン用リソースの生成











	



	
#pragma region ディスクリプタヒープの生成---CG2_02_03
	


	//ディスクリプタヒープの生成
	ID3D12DescriptorHeap* trvDescriptorHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc{};
	rtvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビュー用
	rtvDescriptorHeapDesc.NumDescriptors = 2;//ダブルバッファ用に2つ多くても別に構わない
	hr = device->CreateDescriptorHeap(&rtvDescriptorHeapDesc, IID_PPV_ARGS(&rtvDescriptorHeapDesc));
	//ディスクリプタヒープが作れなかったので起動できない
	assert(SUCCEEDED(hr));








	//mtaDataを基に...
	
	//SRVを作成するDescriptorHeapの場所を決める
	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU = srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU = srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();


#pragma endregion ディスクリプタヒープの生成







	



	//Fenceの生成
	//ビューポート矩形の初期化
	//シザリング矩形の生成
	//DCXコンパイラの生成
	//ImGuiの初期化



	
	
	
	
	
	
	
	//深度バッファのテクスチャ生成
#pragma region 深度バッファのテクスチャ生成





#pragma endregion 深度バッファのテクスチャ生成
	
	
	
	//DSVの生成
#pragma region DSVの生成

	//DepthStencilTextureをウインドウサイズで作成
	ID3D12Resource* depthStencilResource = CreateDepthStencilTextureResource(device, WinApp::kClientWidth, WinApp::kClientHeight);
	//DSV用のヒープでディスクリプタの数は1。DSVはShader内で触るものではないので、ShaderVisibleはfalse
	ID3D12DescriptorHeap* dsvDescriptorHeap = CreateDescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1, false);
	//DSVの設定
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	//DSVHeapの先頭にDSVを作る
	device->CreateDepthStencilView(depthStencilResource, &dsvDesc, dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());


#pragma endregion DSVの生成


	//RTVの生成
#pragma region RTVの生成
	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	//RTV用のヒープでディスクリプタの数は2。RTVはShader内で触るものではないので、ShaderVisbleはfalse
	ID3D12DescriptorHeap* rtvDescriptorHeap = CreateDescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 2, false);
	//SRV用のヒープでディスクリプタの数は128。SRVはShader内で触るものではないので、ShaderVisbleはtrue
	ID3D12DescriptorHeap* srvDescriptorHeap = CreateDescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 128, true);
	//ディスクリプタの先頭を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	//RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	//まず1つ目を作る。1つ目は最初のところに作る。作る場所をこちらで指定して上げる必要がある
	rtvHandles[0] = rtvStartHandle;
	device->CreateRenderTargetView(swapChainResources[0], &rtvDesc, rtvHandles[0]);
	//2つ目のディスクリプタハンドルを得る
	rtvHandles[1].ptr = rtvHandles[0].ptr + device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//2つ目を作る
	device->CreateRenderTargetView(swapChainResources[1], &rtvDesc, rtvHandles[1]);

#pragma endregion RTVの生成








	
#pragma region Febceの生成---CG2_01_02
	//初期値0でFenceを作る
	ID3D12Fence* fence = nullptr;
	uint64_t fenceValue = 0;
	hr = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	assert(SUCCEEDED(hr));

	//FenceのSignalを持つためのイベントを作成する
	HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(fenceEvent != nullptr);
#pragma endregion Febceの生成
	
	
	
	
	
	
	
	
	//ビューポート矩形の初期化
#pragma region ビューポート矩形の初期化---CG2_02_00
	//ビューボート
	D3D12_VIEWPORT viewport{};
	//クライアント領域のサイズと一緒にして画面全体に表示
	viewport.Width = WinApp::kClientWidth;
	viewport.Height = WinApp::kClientHeight;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
#pragma endregion ビューポート矩形の初期化
	
	
	
	
	//シザリング矩形の生成
#pragma region シザリング矩形の生成---CG2_02_00
	//ｼｻﾞｰ短形
	D3D12_RECT scissorRect{};
	//基本的にビューボートと同じ短形が構成されるようにする
	scissorRect.left = 0;
	scissorRect.right = WinApp::kClientWidth;
	scissorRect.top = 0;
	scissorRect.bottom = WinApp::kClientHeight;
#pragma endregion シザリング矩形の生成
	
	
	
	
	
	//DCXコンパイラの生成
#pragma region DCXコンパイラの生成
	//dxcCompilerを初期化
	IDxcUtils* dxcUtlis = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtlis));
	assert(SUCCEEDED(hr));
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
	assert(SUCCEEDED(hr));

	//現時点でincludeはしないが、includeに対応するための設定を行っておく
	IDxcIncludeHandler* includeHandler = nullptr;
	hr = dxcUtlis->CreateDefaultIncludeHandler(&includeHandler);
	assert(SUCCEEDED(hr));
#pragma endregion DCXコンパイラの生成
	//ImGuiの初期化
#pragma region ImGuiの初期化
	//ImGuiの初期化。詳細はさして重要ではないので解説は省略する。
	//こういうもんである
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp->GetHwnd());
	ImGui_ImplDX12_Init(device,
		swapChainDesc.BufferCount,
		rtvDesc.Format,
		srvDescriptorHeap,
		srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
		srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());

#pragma endregion ImGuiの初期化


}







void DirectXCommon::PreDraw()
{
	//バックバッファの番号取得
	//リソースバリアで書き込み可能に変更
	//描画先RTVとDSVを指定する
	//画面全体の色をクリア
	//画面全体の深度をクリア
	//SRV用のディスクリプタヒープを指定する
	//ビューポート領域の設定
	//シザリング矩形の設定







			//これから書き込むバックバッファのインデックスを取得
	UINT backBuffetIndex = swapChain->GetCurrentBackBufferIndex();
	//TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier{};
	//今回のバリアはTransition
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	//Noneにしておく
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	//バリアを張る対象のリソース。現在のバックバッファに対して行う
	barrier.Transition.pResource = swapChainResources[backBuffetIndex];
	//遷移前(現在)のResourceState
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	//遷移後のResourceState
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;


	//TransitionBarrierを張る
	commandList->ResourceBarrier(1, &barrier);		//TransitionBarrierを張る
	//commandList->ResourceBarrier(1, &barrier);
	//描画先のRTVを設定する
	commandList->OMSetRenderTargets(1, &rtvHandles[backBuffetIndex], false, nullptr);
	//指定した色で画面全体をクリアする
	float clearColor[] = { 0.1f,0.25f,0.5f,1.0f };
	commandList->ClearRenderTargetView(rtvHandles[backBuffetIndex], clearColor, 0, nullptr);





	//描画先のRTVとDSVを設定する
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	commandList->OMSetRenderTargets(1, &rtvHandles[backBuffetIndex], false, &dsvHandle);
	//指定した深度で画面全体をクリアする
	commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);


	//描画用のDescriptorHeapの設定
	ID3D12DescriptorHeap* descriptorHeaps[] = { srvDescriptorHeap };
	commandList->SetDescriptorHeaps(1, descriptorHeaps);

	commandList->RSSetViewports(1, &viewport);//Viewportを設定
	commandList->RSSetScissorRects(1, &scissorRect);//Scirssorを設定
	//RootSignatrueを設定。PSPに設定しているけど別途設定が必要
	commandList->SetGraphicsRootSignature(roolSignatrue);
	commandList->SetPipelineState(graphicsPipelineState);//PSOを設定
	commandList->IASetVertexBuffers(0, 1, &vertexBufferView);//VBVを設定
	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);











}

void DirectXCommon::PostDraw()
{
	//画面に描く処理はすべて終わり、画面に映すので、状態を遷移
			//今回はRenderTargetからPresentにする
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	//TransitionBarrierを振る
	commandList->ResourceBarrier(1, &barrier);

	//コマンドリストの内容を確定させる。すべてのコマンドをつんでからCloseすること
	hr = commandList->Close();
	assert(SUCCEEDED(hr));
	//GPUにコマンドリストの実行を行わせる
	ID3D12CommandList* commandLists[] = { commandList };
	commandQueue->ExecuteCommandLists(1, commandLists);
	//GPUとOSに画面の交換を行うよう通知する
	swapChain->Present(1, 0);
	//Fenceの値を更新
	fenceValue++;
	//GPUがここまでたどり着いたときに、Fenceの値を指定した値を指定した値に代入するようにSignalを送る
	commandQueue->Signal(fence, fenceValue);

	//Fenceの値を指定したSignal値にたどり着いているか確認する
	//GetCompletedValueの初期値はFence作成時に渡した初期値
	if (fence->GetCompletedValue() < fenceValue)
	{
		//指定したSignalにたどりついていないので、たどり着くまで待つようにイベントを設定する
		fence->SetEventOnCompletion(fenceValue, fenceEvent);
		//イベント待つ
		WaitForSingleObject(fenceEvent, INFINITE);
	}

	//次のフレーム用のコマンドリストを準備
	hr = commandAllocator->Reset();
	assert(SUCCEEDED(hr));
	hr = commandList->Reset(commandAllocator, nullptr);
	assert(SUCCEEDED(hr));
}
