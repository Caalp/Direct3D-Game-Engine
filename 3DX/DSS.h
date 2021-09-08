#pragma once
#include "Bindable.h"


	class DSS : public Bindable
	{
	public:
		enum DSSType
		{
			Default,
			Mirror,
			DrawReflaction,
			NoDoubleBlend,
			NoDepthWrite,
			LessOrEqual,
			Mask,
			Write
		};
		
		DSS(Graphics& gfx, DSSType dType);
		void Bind(Graphics& gfx);
		void Bind() override;
	private:
		DSSType dss;
		Microsoft::WRL::ComPtr< ID3D11DepthStencilState> pDSS;
	};
