#include "GeometryGenerator.h"

GeometryGenerator::GeometryGenerator():pitch(0.0f),yaw(0.0f),roll(0.0f),
										x(0.0f),y(0.0f),z(0.0f)
{
}

void GeometryGenerator::GenerateGrid(Graphics& gfx, const char* filePath, UINT numRows, UINT numCols, float dx, float dt, float damping, float texScale)
{
	//this->dt = dt;
	//numRows = numRow;
	//numCols = numCol;
	vertexData.resize(numRows*numCols);
	int vertexCount = numRows * numCols;
	int triangleCount = (numRows - 1)*(numCols - 1) * 2;
	this->filePath = static_cast<std::string>(filePath);
	//timeStep = dt;
	float spatialStep = dx;

	float width = numCols * spatialStep;
	float depth = numRows * spatialStep;


	/*delete[] prevSolution;
	delete[] currSolution;
	delete[] Normals;
	delete[] TangentX;*/

	//prevSolution = new dx::XMFLOAT3[numRows*numCols];
	//currSolution = new dx::XMFLOAT3[numRows*numCols];
	//Normals = new dx::XMFLOAT3[numRows*numCols];
	//TangentX = new dx::XMFLOAT3[numRows*numCols];

	float halfWidth = 0.5f *dx*(numCols - 1);
	float halfHeight = 0.5f *dx*(numRows - 1);

	vertexData.resize(numCols*numRows);
	//Generate grid vertices
	for (UINT i = 0; i < numRows; i++)
	{
		float z = halfHeight - i * dx;
		for (UINT j = 0; j < numCols; j++)
		{
			float x = -halfWidth + j * dx;

			vertexData[i*numCols + j].Pos = DirectX::XMFLOAT3(x, 0.0f, z);
			//prevSolution[i*numCols + j] = DirectX::XMFLOAT3(x, 0.0f, z);
			//currSolution[i*numCols + j] = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
			//currSolution[i*numCols + j].texCoord = DirectX::XMFLOAT2(0.05f*i*dx,0.05f*j*dx);




			vertexData[i*numCols + j].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
			
			//vertexData[i*numCols + j].texCoord = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

			//prevSolution[i*numCols + j].texCoord = DirectX::XMFLOAT2(0.05f*i*dx, 0.05f*j*dx);

		}
	}

	
	//reserve space for indices
	indices.resize(3 * triangleCount);
	//Create indices
	int k = 0;
	for (UINT i = 0; i < numRows - 1; i++)
	{
		for (UINT j = 0; j < numCols - 1; j++)
		{
			indices[k] = i * numCols + j;
			indices[k + 1] = i * numCols + j + 1;
			indices[k + 2] = (i + 1) * numCols + j;

			indices[k + 3] = (i + 1) * numCols + j;
			indices[k + 4] = i * numCols + j + 1;
			indices[k + 5] = (i + 1) * numCols + j + 1;

			k += 6;
		}
	}
	for (UINT i = 0; i < vertexCount; ++i)
	{
		
		//Derive tex-coords in [0,1] from position.
		vertexData[i].texCoord.x = texScale*(0.5f + vertexData[i].Pos.x / width);
		vertexData[i].texCoord.y = texScale*(0.5f - vertexData[i].Pos.z / depth);
	}
	Bind(gfx);
}

void GeometryGenerator::Update(float ft)
{
}

DirectX::XMMATRIX GeometryGenerator::GetTransformation() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)*DirectX::XMMatrixTranslation(x,y,z);
}

void GeometryGenerator::RotateGeometry(float pitch, float yaw, float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}

void GeometryGenerator::TranslateGeometry(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void GeometryGenerator::Bind(Graphics & gfx)
{
	if (!isStaticallyBinded())
	{
		//SetBlendState(true);
		//AddStaticBind(std::make_unique<BlendState>(gfx));
		AddBind(std::make_unique<VertexBuffer>(gfx, vertexData));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
		auto vs = std::make_unique<VertexShader>(gfx, L"TexPhongVS.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		AddStaticBind(std::make_unique<IndexBuff>(gfx, indices));
		TextureLoader texLoader(filePath.c_str());
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

		//AddStaticBind(std::make_unique<RasterizerState>(gfx));
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexBufferFromStatic();
	}

	AddBind(std::make_unique<TransformationBuffer>(gfx, *this, true));
}
