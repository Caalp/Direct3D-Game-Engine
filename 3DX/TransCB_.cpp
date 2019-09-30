#include "TransCB_.h"

//TransCB_::TransCB_(Graphics & gfx)
//{
//	/*if (!viewMatrix_)
//	{
//		viewMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx);
//	}
//	if (!projMatrix_)
//	{
//		projMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx);
//	}
//	if (!worldMatrix_)
//	{
//		projMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx);
//	}*/
//}

TransCB_::TransCB_(Graphics & gfx, const DrawableBase & parent) :
	parent(parent)
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx);
	}
}

void TransCB_::Bind(Graphics & gfx)
{
	pVcbuf->Update(gfx,
		DirectX::XMMatrixTranspose(
			parent.GetTransformXM() * gfx.GetProjection()
		)
	);
	pVcbuf->Bind(gfx);
	/*worldMatrix_->Bind(gfx, 0u, 1u);
	viewMatrix_->Bind(gfx, 1u, 1u);
	projMatrix_->Bind(gfx, 2u, 1u);*/
}




void TransCB_::SetviewM_(Graphics& gfx,DirectX::XMMATRIX vm)
{
	//viewMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx, std::move(vm));
	
}

void TransCB_::SetprojM_(Graphics& gfx, DirectX::XMMATRIX pm)
{
	//projMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx, std::move(pm));
	
}

void TransCB_::SetworldM_(Graphics & gfx, DirectX::XMMATRIX wm)
{
	//worldMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx, std::move(wm));
	
}
std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> TransCB_::pVcbuf;