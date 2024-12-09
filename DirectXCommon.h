#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<array>
#include<dxcapi.h>
#include"externals/DirectXTex/DirectXTex.h"
#include"externals/DirectXTex/d3dx12.h"

class WinApp;

class DirectXCommon
{

public:

	Microsoft::WRL::ComPtr<ID3D12Resource>CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);

	IDxcBlob* CompileShader(
		//CompilerするShaderファイルへのパス
		const std::wstring& filePath,
		//Compilerに使用するProfile
		const wchar_t* profile
		//初期化で生成したものを３つ
	);

	//DescriptorHeapの作成関数
	ID3D12DescriptorHeap* CreateDescriptorHeap(
		D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);


public:
	//初期化
	void Initialize();

	//描画前処理
	void PreDraw();

	//描画後処理
	void PostDraw();
private:
	//デバイスの初期化
	void DeviceInitialize();

	//コマンド関連の生成
	void CreateCommand();

	//スワップチェーンの生成
	void CreateSwapChain();

	//深度バッファの生成
	void DepthCreateBufferView();

	//各種デスクリプターヒープの初期化
	void CreateAllDescriptorHeap();

	//レンダーターゲットビューの初期化
	void RTVInitialize();

	//深度ステンシルビューの初期化
	void StencilInitialize();

	//フェンスの初期化
	void CreateFence();

	//ビューポート矩形の初期化
	void ViewPortInitialize();

	//シザリングの初期化
	void CreateSizaling();

	//DCXコンパイラの初期化
	void CreateDXC();

	//ImGuiの初期化
	void ImGuiInitialize();


public:
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);//SRV用
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUDescriptorHandle(uint32_t index);//RTV用
	D3D12_GPU_DESCRIPTOR_HANDLE GetRTVGPUDescriptorHandle(uint32_t index);

	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCPUDescriptorHandle(uint32_t index);//DSV用
	D3D12_GPU_DESCRIPTOR_HANDLE GetDSVGPUDescriptorHandle(uint32_t index);

	//getter
	ID3D12Device* GetDevice()const { return device.Get(); }
	Microsoft::WRL::ComPtr < ID3D12GraphicsCommandList> GetCommandList()const { return commandList.Get(); }

private:
	HRESULT hr;

	//名前関連
	Microsoft::WRL::ComPtr<ID3D12Device>device;

	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	//コマンドの初期化


	//DSV用のヒープでディスクリプタの数１。DSVはshader内で触るものではないので、ShaderVisibleはfalse


	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils = nullptr;
	Microsoft::WRL::ComPtr<IDxcCompiler3> dxCompiler = nullptr;
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHander = nullptr;

	//スワップチェーンを生成する
	IDXGISwapChain4* swapChain = nullptr;

	//SwapChainからresourceを引っ張ってくる


	//RTV2つ作るのでディスクリプタを２つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];

	ID3D12DescriptorHeap* rtvDescriptorHeap;
	ID3D12DescriptorHeap* srvDescriptorHeap;
	ID3D12DescriptorHeap* dsvDescriptorHeap;

	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;

	//スワップチェーンリソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2>swapChainResources{};

	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorhandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);

	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorhandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);

	//初期値０でFenceを作る
	ID3D12Fence* fence = nullptr;

	//ビューポート
	D3D12_VIEWPORT viewport{};

	//シザー四角形
	D3D12_RECT scissorRect{};

	//WindowsAPI
	WinApp* winApp = nullptr;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	//コマンドキューを生成する
	Microsoft::WRL::ComPtr < ID3D12CommandQueue> commandQueue = nullptr;

	//コマンドアロケータを生成する
	Microsoft::WRL::ComPtr < ID3D12CommandAllocator> commandAllocator = nullptr;

	//コマンドリストを生成する
	Microsoft::WRL::ComPtr < ID3D12GraphicsCommandList> commandList = nullptr;

	UINT64 fenceValue = 0;

	HANDLE fenceEvent;


};


