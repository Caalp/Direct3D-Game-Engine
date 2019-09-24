#include "PrimitiveTopology.h"

PrimitiveTopology::PrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY P_topology) : Pt(P_topology)
{
}

void PrimitiveTopology::Bind(Graphics & gfx)
{
	GetContext(gfx)->IASetPrimitiveTopology(Pt);
}
