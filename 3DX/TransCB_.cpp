#include "TransCB_.h"

TransCB_::TransCB_(Graphics & gfx, const DrawableBase & db) : db0(db)
{
	if (combMatrix_ == nullptr)
	{
		combMatrix_ = std::make_unique<VSConstBuff<DirectX::XMMATRIX>>(gfx);
	}
}
