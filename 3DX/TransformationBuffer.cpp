#include "TransformationBuffer.h"


TransformationBuffer::TransformationBuffer(std::shared_ptr<VSConstBuff<std::vector<char>>> tbuff)
{
	m_TBuffer = tbuff;
}

void TransformationBuffer::Bind()
{


	if (auto pref = m_TBuffer.lock())
	{
		
		pref->Bind(0u, 1u);
	}

}


