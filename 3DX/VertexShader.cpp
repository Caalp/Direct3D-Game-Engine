#include "VertexShader.h"

VertexShader::VertexShader()
{
	m_pVertexLayout11 = NULL;
	m_pVertexShader = NULL;
	m_pcbVSMatrices = NULL;
	m_pcbVSMaterial = NULL;
	m_pcbVSLighting = NULL;
	m_enableLights = true;
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_pVertexLayout11);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pcbVSMatrices);
	SAFE_RELEASE(m_pcbVSMaterial);
	SAFE_RELEASE(m_pcbVSLighting);
}
