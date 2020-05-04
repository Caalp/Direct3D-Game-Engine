//#pragma once
//#include "Bindable.h"
//// Class for binding Render Target View...
//class RTV : public Bindable
//{
//	
//public:
//	template<typename T>
//	RTV(Graphics& gfx, const T& packet, int firstArraySlice)
//	{
//		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
//		rtvDesc.Format = packet.Format;
//		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
//		rtvDesc.Texture2DArray.ArraySize = 1;
//		rtvDesc.Texture2DArray.MipSlice = 0;
//		rtvDesc.Texture2DArray.FirstArraySlice = firstArraySlice;
//
//		GetDevice(gfx)->CreateRenderTargetView()
//	}
//	void Bind(Graphics& gfx) override
//	{
//		//GetContext(gfx)->OMSetRenderTargets(1u, rtv, 0);
//	}
//private:
//	ID3D11RenderTargetView* rtv;
//
//};
