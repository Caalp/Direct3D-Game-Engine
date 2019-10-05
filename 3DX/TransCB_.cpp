#include "TransCB_.h"



TransCB_::TransCB_(Graphics & gfx, const DrawableBase & parent) :
	parent(parent)
	
{
	if (!worldMatrix_)
	{
		worldMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx);
	}
	if (!viewMatrix_)
	{
		viewMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx);
	}
	if (!projMatrix_)
	{
		projMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx);
	}
}


void TransCB_::Bind(Graphics & gfx)
{
	worldMatrix_->Update(gfx, DirectX::XMMatrixTranspose(parent.GetWorldXM()));
	projMatrix_->Update(gfx, DirectX::XMMatrixTranspose(parent.GetProjXM()));
	viewMatrix_->Update(gfx, DirectX::XMMatrixTranspose(parent.GetViewXM()));
	worldMatrix_->Bind(gfx,0u,1u);
	projMatrix_->Bind(gfx, 2u, 1u);
	viewMatrix_->Bind(gfx, 1u, 1u);
}




std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> TransCB_::worldMatrix_;
std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> TransCB_::viewMatrix_;
std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> TransCB_::projMatrix_;
