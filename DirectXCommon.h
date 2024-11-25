#pragma once

#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include "WinApp.h"

//DirectX基盤
class DirectXCommon
{

public:
	void Initialize(WinApp* winApp);

	void DeviceInitialize();

	void CommandInitialize();

	void SwapChainInitialize();

	void zBufferInitialize();

	void DescriptorHeapInitialize();

	
	void RenderTargetViewInitialize();


private:

	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device>device;

	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory;

	//WindowAPI
	WinApp* winApp = nullptr;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);


	//コマンドキューを生成する
	ID3D12CommandQueue* commandQueue = nullptr;

	//コマンドアロケータを生成する
	ID3D12CommandAllocator* commandAllocator = nullptr;

	//コマンドリストを生成する
	ID3D12GraphicsCommandList* commandList = nullptr;

	ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr;
	ID3D12DescriptorHeap* srvDescriptorHeap = nullptr;

	IDXGISwapChain4* swapChain = nullptr;

};

