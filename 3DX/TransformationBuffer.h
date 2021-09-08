#pragma once

#include "ConstBuffs.h"
#include "Types.h"
// Apperantly not used anymore

class TransformationBuffer : public Bindable
{

public:

	TransformationBuffer(std::shared_ptr<VSConstBuff<std::vector<char>>> tbuff);


	void Bind() override;

	
private:

	std::weak_ptr<VSConstBuff<std::vector<char>>> m_TBuffer;

	
};