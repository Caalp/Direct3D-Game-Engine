#include "Water.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "BlendState.h"

Water::Water(): numCols(0), numRows(0), vertexCount(0), triangleCount(0),
x(0), y(0), z(0)
{
}

Water::Water(Graphics & gfx): numCols(0), numRows(0), vertexCount(0), triangleCount(0),
x(0),y(0),z(0)
{

}

void Water::Init(Graphics& gfx, UINT numRow, UINT numCol, float dx, float dt, float speed, float damping)
{
	
		this->dt = dt;
		numRows = numRow;
		numCols = numCol;
		vertexData.resize(numRows*numCols);
		vertexCount = numRows * numCols;
		triangleCount = (numRows - 1)*(numCols - 1) * 2;

		timeStep = dt;
		spatialStep = dx;

		width = numCols * spatialStep;
		depth = numRows * spatialStep;
		

		/*delete[] prevSolution;
		delete[] currSolution;
		delete[] Normals;
		delete[] TangentX;*/

		prevSolution = new dx::XMFLOAT3[numRows*numCols];
		currSolution = new dx::XMFLOAT3[numRows*numCols];
		Normals = new dx::XMFLOAT3[numRows*numCols];
		TangentX = new dx::XMFLOAT3[numRows*numCols];

		float halfWidth = 0.5f *dx*(numCols - 1);
		float halfHeight = 0.5f *dx*(numRows - 1);

		float d = damping * dt + 2.0f;
		float e = (speed*speed)*(dt*dt) / (dx*dx);

		mK1 = (damping*dt - 2.0f) / d;
		mK2 = (4.0f - 8.0f*e) / d;
		mK3 = (2.0f*e) / d;



		//Generate grid vertices
		for (UINT i = 0; i < numRows; i++)
		{
			float z = halfHeight - i * dx;
			for (UINT j = 0; j < numCols; j++)
			{
				float x = -halfWidth + j * dx;

				currSolution[i*numCols + j] = DirectX::XMFLOAT3(x, 0.0f, z);
				prevSolution[i*numCols + j] = DirectX::XMFLOAT3(x, 0.0f, z);
				//currSolution[i*numCols + j] = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
				//currSolution[i*numCols + j].texCoord = DirectX::XMFLOAT2(0.05f*i*dx,0.05f*j*dx);




				Normals[i*numCols + j] = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
				TangentX[i*numCols + j] = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

				//prevSolution[i*numCols + j].texCoord = DirectX::XMFLOAT2(0.05f*i*dx, 0.05f*j*dx);

			}
		}


		//reserve space for indices
		waterIndices.resize(3 * triangleCount);
		//Create indices
		int k = 0;
		for (UINT i = 0; i < numRows - 1; i++)
		{
			for (UINT j = 0; j < numCols - 1; j++)
			{
				waterIndices[k] = i * numCols + j;
				waterIndices[k + 1] = i * numCols + j + 1;
				waterIndices[k + 2] = (i + 1) * numCols + j;

				waterIndices[k + 3] = (i + 1) * numCols + j;
				waterIndices[k + 4] = i * numCols + j + 1;
				waterIndices[k + 5] = (i + 1) * numCols + j + 1;

				k += 6;
			}
		}
		for (UINT i = 0; i < vertexCount; ++i)
		{
			vertexData[i].Pos = currSolution[i];
			vertexData[i].Normal = Normal(i);

			//Derive tex-coords in [0,1] from position.
			vertexData[i].Tex.x = 0.5f + currSolution[i].x / width;
			vertexData[i].Tex.y = 0.5f - currSolution[i].z / depth;
		}
		Bind(gfx);
}

void Water::Update(Graphics& gfx, float ft)
{
	static float t = 0;
	t += ft;

	if (t >= timeStep)
	{
		for (UINT i = 1; i < numRows-1; i++)
		{
			for (UINT j = 1; j < numCols - 1; j++)
			{
				prevSolution[i*numCols+j].y = mK1*prevSolution[i*numCols+j].y +
												  mK2*currSolution[i*numCols+j].y +
												  mK3*(currSolution[(i + 1)*numCols+j].y +
												  currSolution[(i - 1)*numCols+j].y +
						                          currSolution[i*numCols+j+1].y +
						                          currSolution[i*numCols+j-1].y);
			}
		}
	}
	std::swap(prevSolution, currSolution);

	t = 0.0f;

	for (UINT i = 1; i < numRows-1; i++)
	{
		for (UINT j = 1; j < numCols - 1; j++)
		{
			float l = currSolution[i*numRows+j-1].y;
			float r = currSolution[i*numRows+j+1].y;
			float t = currSolution[(i-1)*numRows+j].y;
			float b = currSolution[(i+1)*numRows+j].y;

			Normals[i*numCols+j].x = -r+1;
			Normals[i*numCols + j].y = 2.0f*spatialStep;
			Normals[i*numCols + j].z = b - t;

			dx::XMVECTOR n = dx::XMVector3Normalize(dx::XMLoadFloat3(&Normals[i*numCols + j]));
			dx::XMStoreFloat3(&Normals[i*numCols + j], n);

			TangentX[i*numCols + j] = dx::XMFLOAT3(2.0f*spatialStep, r - l, 0.0f);
			dx::XMVECTOR T = dx::XMVector3Normalize(dx::XMLoadFloat3(&TangentX[i*numCols + j]));
			dx::XMStoreFloat3(&TangentX[i*numCols + j], T);
		}
	}
	
	//UpdateVBuff(gfx);
}

void Water::Disturb(UINT i, UINT j, float magnitude)
{
	assert(i > 1 && i < numRows - 2);
	assert(j > 1 && j < numCols - 2);

	float halfMag = 0.5f*magnitude;

	// Disturb the ijth vertex height and its neighbors.
	currSolution[i*numCols + j].y += magnitude;
	currSolution[i* numCols + j + 1].y += halfMag;
	currSolution[i*numCols + j - 1].y += halfMag;
	currSolution[(i + 1)*numCols + j].y += halfMag;
	currSolution[(i - 1)*numCols + j].y += halfMag;
}

void Water::UpdateVBuff(Graphics& gfx)
{
	//D3D11_MAPPED_SUBRESOURCE MappedSource;
	//Bindable::GetContext(gfx)->Map(, 0u,D3D11_MAP_WRITE_DISCARD, 0u,&MappedSource);
	////memcpy(MappedSource.pData, &cb, sizeof(cb));
	//

	//for (UINT i = 0; i < vertexCount; ++i)
	//{
	//	vertexData[i].Pos = currSolution[i];
	//	vertexData[i].Normal = Normal(i);

	//	// Derive tex-coords in [0,1] from position.
	//	vertexData[i].Tex.x = 0.5f + currSolution[i].x / width;
	//	vertexData[i].Tex.y = 0.5f - currSolution[i].z / depth;
	//}
	//Bindable::GetContext(gfx)->Unmap(vertexData, 0u);
	////UpdateVertexBuffer(gfx, vertexData);
}

dx::XMMATRIX Water::GetTexTransformXM() const
{
	static dx::XMFLOAT2 waterTexOffset(0.0f, 0.0f);
	dx::XMMATRIX waveScale = dx::XMMatrixScaling(5.0f, 5.0f, 0.0f);

	waterTexOffset.y += 0.05*dt;
	waterTexOffset.x += 0.1f*dt;

	dx::XMMATRIX wavesOffset = dx::XMMatrixTranslation(waterTexOffset.x, waterTexOffset.y, 0.0f);

	return waveScale * wavesOffset;
}

void Water::Bind(Graphics & gfx)
{
	if (!isStaticallyBinded())
	{
	SetBlendState(true);
	AddStaticBind(std::make_unique<BlendState>(gfx,true, BlendState::BlendType::Transparent));
	AddBind(std::make_unique<VertexBuffer>(gfx,vertexData));
	AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
	auto vs = std::make_unique<VertexShader>(gfx, L"TexPhongVS.cso");
	auto vsBlob = vs->GetVBlob();
	AddStaticBind(std::move(vs));
	AddStaticBind(std::make_unique<IndexBuff>(gfx, waterIndices));
	TextureLoader texLoader("Textures\\water2.dds");
	struct MaterialConstantPS
	{

		DirectX::XMFLOAT4 amb;
		DirectX::XMFLOAT4 diff;
		DirectX::XMFLOAT4 spec;

	}matConst;

	matConst.amb = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	matConst.diff = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	matConst.spec = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 32.0f);

	AddStaticBind(std::make_unique<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));

	AddStaticBind(std::make_unique<Texture>(gfx, texLoader));

	AddStaticBind(std::make_unique<SamplerState>(gfx));

	
	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0},

	};

	AddStaticBind(std::make_unique<RasterizerState>(gfx));
	AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
	AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexBufferFromStatic();
	}

	AddBind(std::make_unique<TransformationBuffer>(gfx, *this,true));
}

UINT Water::GetRowCount() const
{
	return numRows;
}

UINT Water::GetColumnCount() const
{
	return numCols;
}

void Water::updatePosX(float x)
{
	this->x += x;
}

void Water::updatePosY(float y)
{
	this->y += y;
}

void Water::updatePosZ(float z)
{
	this->z += z;
}

DirectX::XMMATRIX Water::GetTransformation() const
{
	return DirectX::XMMatrixIdentity()*DirectX::XMMatrixTranslation(x,y,z);
}

