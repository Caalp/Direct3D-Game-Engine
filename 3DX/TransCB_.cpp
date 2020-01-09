#include "TransCB_.h"



TransCB_::TransCB_(Graphics & gfx, const DrawableBase & parent) :
	parent(parent)
	
	
{
	if (!TransMatrix_)
	{
		TransMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx);
	}
	
}


void TransCB_::Bind(Graphics & gfx)
{
	const auto t = DirectX::XMMatrixTranspose(parent.GetTransformation()*gfx.GetCamera());
	TransMatrix_->Update(gfx,t);
	
	TransMatrix_->Bind(gfx,0u,1u);
	
}






std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> TransCB_::TransMatrix_;