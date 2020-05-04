#include "GeometryGenerator.h"

#define XM_PI               3.141592654f
#define XM_2PI              6.283185307f

GeometryGenerator::GeometryGenerator():pitch(0.0f),yaw(0.0f),roll(0.0f),
										x(0.0f),y(0.0f),z(0.0f)
{
}

void GeometryGenerator::GenerateGrid(Graphics& gfx, const char* filePath, UINT numRows, UINT numCols, float dx, float dt, float damping, float texScale)
{
	
	//texLoader =filePath);
	
	//this->dt = dt;
	//numRows = numRow;
	//numCols = numCol;
	MeshData md;
	md.vertexData.resize(numRows*numCols);
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

	md.vertexData.resize(numCols*numRows);
	//Generate grid vertices
	for (UINT i = 0; i < numRows; i++)
	{
		float z = halfHeight - i * dx;
		for (UINT j = 0; j < numCols; j++)
		{
			float x = -halfWidth + j * dx;

			md.vertexData[i*numCols + j].Pos = DirectX::XMFLOAT3(x, 0.0f, z);
			//prevSolution[i*numCols + j] = DirectX::XMFLOAT3(x, 0.0f, z);
			//currSolution[i*numCols + j] = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
			//currSolution[i*numCols + j].texCoord = DirectX::XMFLOAT2(0.05f*i*dx,0.05f*j*dx);


			md.vertexData[i*numCols + j].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
			
			//vertexData[i*numCols + j].texCoord = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

			//prevSolution[i*numCols + j].texCoord = DirectX::XMFLOAT2(0.05f*i*dx, 0.05f*j*dx);

		}
	}

	
	//reserve space for indices
	md.indices.resize(3 * triangleCount);
	//Create indices
	int k = 0;
	for (UINT i = 0; i < numRows - 1; i++)
	{
		for (UINT j = 0; j < numCols - 1; j++)
		{
			md.indices[k] = i * numCols + j;
			md.indices[k + 1] = i * numCols + j + 1;
			md.indices[k + 2] = (i + 1) * numCols + j;

			md.indices[k + 3] = (i + 1) * numCols + j;
			md.indices[k + 4] = i * numCols + j + 1;
			md.indices[k + 5] = (i + 1) * numCols + j + 1;

			k += 6;
		}
	}
	for (UINT i = 0; i < vertexCount; ++i)
	{
		
		//Derive tex-coords in [0,1] from position.
		md.vertexData[i].texCoord.x = texScale*(0.5f + md.vertexData[i].Pos.x / width);
		md.vertexData[i].texCoord.y = texScale*(0.5f - md.vertexData[i].Pos.z / depth);
	}
	Bind(gfx,md);
}

void GeometryGenerator::GenerateCylinder(Graphics & gfx, const char * filePath, float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, float texScale)
{
	MeshData md;
	this->filePath = static_cast<std::string>(filePath);
	float dTheta = (2 * 3.141592653589793238) / sliceCount;

	float stackHeight = height / stackCount;

	float ringCount = stackCount + 1;

	float radiusStep = (topRadius - bottomRadius) / stackCount;

	
	for (int i = 0; i < ringCount; i++)
	{
		float y = -0.5f*height + i * stackHeight;
		float r = bottomRadius - i * radiusStep;
		//Check <= again
		for (int j = 0; j <= sliceCount; j++)
		{

			float x = cosf(dTheta*j);
			float z = sinf(dTheta*j);
			Vertex v;
			v.Pos = DirectX::XMFLOAT3(x*r, y, z*r);

			float tx = texScale*((float)j / sliceCount);
			float ty = texScale*(1.0f - (float)i / stackCount);

			v.texCoord = DirectX::XMFLOAT2(tx, ty);
			float dr = bottomRadius - topRadius;
			DirectX::XMVECTOR tangent = { -z,0.0f,x };
			DirectX::XMVECTOR biTangent = { dr*z ,-height, dr*x };

			DirectX::XMVECTOR N = DirectX::XMVector3Normalize(DirectX::XMVector3AngleBetweenNormals(tangent, biTangent));

			DirectX::XMStoreFloat3(&v.Normal, N);
			md.vertexData.push_back(v);

		}
	}
	float ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount; i++)
	{
		for (int j = 0; j < sliceCount; j++)
		{
			md.indices.push_back(i*ringVertexCount + j);
			md.indices.push_back((i + 1)*ringVertexCount + j);
			md.indices.push_back((i+1)*ringVertexCount + (j + 1));
			

			md.indices.push_back(i*ringVertexCount + j);
			md.indices.push_back((i+1)*ringVertexCount + (j+1));
			md.indices.push_back((i)*ringVertexCount + (j+1));
		}
	}
	Bind(gfx,md);
}

void GeometryGenerator::GenerateSphere(Graphics & gfx, const char * filePath, float radius, unsigned int sliceCount, unsigned int stackCount)
{
	this->filePath = static_cast<std::string>(filePath);


	
	Vertex v;
	// Each slice of Sphere and each stack step in each slice
	// phi angle is 0<= phi<= pi and theta is between 0<= theta <= 2pi
	float phiStep = XM_PI / stackCount;
	float thetaStep = XM_2PI / sliceCount;
	float r = radius;
	float phi = 0.0f;
	float theta = 0.0f;
	
	
	// Add top pole point and calculate the normal and texCoord 
	v.Pos = DirectX::XMFLOAT3(0.0f, r, 0.0f);
	v.Normal = MatHelper::normalize(v.Pos);
	v.texCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
	// Push it to the vector
	meshData.vertexData.push_back(v);

	// Skip the first stack which is between points on the second latitude lines
	// and the top pole point. For each stack(latitude lines) calculate each vertex point
	// Calculating means : completing 2pi period. After a full period increase the phi angle
	// (which is angle between y axis and rho vector) and calculate the next stacks vertices and so on.

	for (int i = 1; i <= stackCount-1; i++)
	{
		phi = i * phiStep;
		for (int j = 0; j <= sliceCount; j++)
		{
			// Angle theta for 2pi period.
			theta = j * thetaStep;

			// Calculate the x,y,z coordinates
			// y axis is up vector and r*cos(phi) will give y coordinate
			// for x,z we should first calculate their values xz plane
			// after that with theta angle we can find x and z coordinates
			v.Pos.x = r * sinf(phi)*cosf(theta);;
			v.Pos.y = r * cosf(phi);
			v.Pos.z = r * sinf(phi)*sinf(theta);

			//v.Pos = MatHelper::normalize(v.Pos);
			v.Normal = MatHelper::normalize(v.Pos);
			
			float du = theta / XM_2PI;
			float dv = phi / XM_PI;
			v.texCoord.x = du;
			v.texCoord.y = dv;
		
			meshData.vertexData.push_back(v);
		}
		
	}

	// Push the bottom pole point to the vector
	v.Pos = DirectX::XMFLOAT3(0.0f, -r, 0.0f);
	v.Normal = MatHelper::normalize(v.Pos);
	v.texCoord = DirectX::XMFLOAT2(1.0f, 0.0f);
	meshData.vertexData.push_back(v);

	// Calculate the triangles in first stack (between nort(top) pole point and first stack vertices
	// Triangles are created respect to the clockwise winding order
		for (int i = 1; i <= sliceCount; i++)
	{
		meshData.indices.push_back(0);
		meshData.indices.push_back(i+ 1);
		meshData.indices.push_back(i);
	}

	// Create index buffer vector for body of the sphere 
	// (stack-2) because we need to avoid the portion which includes top and bottom pole part
	for (int i = 0; i < stackCount-2; i++)
	{
		for (int j=1; j <= sliceCount; j++)
		{
				
			meshData.indices.push_back((sliceCount + 1)*(i + 1) + j);
			meshData.indices.push_back(((sliceCount+1)*i) + j);
			meshData.indices.push_back(((sliceCount+1)*(i + 1)) + (j+1));

			meshData.indices.push_back(((sliceCount + 1)*(i + 1)) + (j + 1));
			meshData.indices.push_back(((sliceCount + 1)*i) + j);
			meshData.indices.push_back(((sliceCount + 1)*i) + j+1);
						
		}
	}
	
	// Fill the index buffer vector for bottom stack
	// As a last vertex bottom pole point is pushed to the vector
	// We should get its index and with substracting sliceCount visit each vertex in clockwise winding direction
	int bottomPoleIndex = meshData.vertexData.size() - 1;
	for (UINT i = 0; i < sliceCount; ++i)
	{
		meshData.indices.push_back(bottomPoleIndex);
		meshData.indices.push_back((bottomPoleIndex-sliceCount) + i);
		meshData.indices.push_back((bottomPoleIndex - sliceCount) + i + 1);
	}

	Bind(gfx, meshData);

}

void GeometryGenerator::GenerateIcosahedron(Graphics & gfx, const char * filePath)
{
	MeshData md;
	this->filePath = static_cast<std::string>(filePath);
	
	md.vertexData.resize(12);
	static const float  t1 = 0.525731f;
	static const float  t2 = 0.850651f;
	
	md.vertexData[0].Pos = DirectX::XMFLOAT3(-t1, 0.0f,t2);
	md.vertexData[1].Pos = DirectX::XMFLOAT3(t1, 0.0f, t2);
	md.vertexData[2].Pos = DirectX::XMFLOAT3(-t1, 0.0f, -t2);
	md.vertexData[3].Pos = DirectX::XMFLOAT3(t1, 0.0f, -t2);
	md.vertexData[4].Pos = DirectX::XMFLOAT3(0.0f, t2, t1);
	md.vertexData[5].Pos = DirectX::XMFLOAT3(0.0f, t2, -t1);
	md.vertexData[6].Pos = DirectX::XMFLOAT3(0.0f, -t2, t1);
	md.vertexData[7].Pos = DirectX::XMFLOAT3(0.0f, -t2, -t1);
	md.vertexData[8].Pos = DirectX::XMFLOAT3(t2, t1,0.0f);
	md.vertexData[9].Pos = DirectX::XMFLOAT3(-t2, t1,0.0f);
	md.vertexData[10].Pos = DirectX::XMFLOAT3(t2, -t1,0.0f);
	md.vertexData[11].Pos = DirectX::XMFLOAT3(-t2, -t1,0.0f);

		
	md.indices =
	{
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,    
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0,
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7 
	};
	for (UINT i = 0; i < md.vertexData.size(); i++)
	{
		DirectX::XMVECTOR n = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&md.vertexData[i].Pos));
		DirectX::XMStoreFloat3(&md.vertexData[i].Normal, n);

		float theta = MatHelper::AngleFromXY(md.vertexData[i].Pos.x, md.vertexData[i].Pos.z);
		float phi = acosf(md.vertexData[i].Pos.y / t2);
		md.vertexData[i].texCoord.x = theta / XM_2PI;
		md.vertexData[i].texCoord.y = phi / XM_PI;
	}
	SubDivide(1u,md);
	Bind(gfx,md);
}



void GeometryGenerator::Update(float ft)
{
}

DirectX::XMMATRIX GeometryGenerator::GetTransformation() const
{
	if (!isReflaction)
	{
		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)*DirectX::XMMatrixTranslation(x, y, z);
	}
	else
	{
		DirectX::XMVECTOR mirrorPlane = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		DirectX::XMMATRIX R = DirectX::XMMatrixReflect(mirrorPlane);

		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * DirectX::XMMatrixTranslation(x, y, z)*R;
	}
}

DirectX::XMMATRIX GeometryGenerator::GetTransformation(Graphics & gfx) const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)*DirectX::XMMatrixTranslation(x, y, z);
}

DirectX::XMMATRIX GeometryGenerator::GetTexTransformXM() const
{
	return DirectX::XMMatrixScaling(3.0f, 1.5f, 1.0f)*DirectX::XMMatrixTranslation(0.0076f * 0.02f, 0.0f, 0.0f);
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

void GeometryGenerator::Bind(Graphics & gfx, const MeshData& meshData)
{
	
	
	if (!isStaticallyBinded())
	{
		//SetBlendState(true);
		//AddStaticBind(std::make_unique<BlendState>(gfx));
		AddBind(std::make_unique<VertexBuffer>(gfx, meshData.vertexData));
		//AddStaticBind(std::make_unique<PixelShader>(gfx, L"ConstantColorPS.cso"));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
		//AddStaticBind(std::make_unique<GeometryShader>(gfx, L"GS_Subdivide.cso"));
		auto vs = std::make_unique<VertexShader>(gfx, L"TexPhongVS.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		AddStaticBind(std::make_unique<IndexBuff>(gfx, const_cast<std::vector<WORD>&>(meshData.indices)));
		
		
		struct MaterialConstantPS
		{

			DirectX::XMFLOAT4 amb;
			DirectX::XMFLOAT4 diff;
			DirectX::XMFLOAT4 spec;
			DirectX::XMFLOAT4 reflection;

		}matConst;

		struct EffectStatus
		{
			BOOL fogEnabled;
			BOOL reflactionEnabled;
			BOOL alphaClipEnabled;
			BOOL textureUsed;
		}effectStatus;
		matConst.amb = DirectX::XMFLOAT4(0.2f, 0.3f, 0.4f, 1.0f);
		matConst.diff = DirectX::XMFLOAT4(0.2f, 0.3f, 0.4f, 1.0f);
		matConst.spec = DirectX::XMFLOAT4(0.9f, 0.9f, 0.9f, 16.0f);
		matConst.reflection = DirectX::XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
		
		effectStatus.fogEnabled = fogEnabled;
		effectStatus.reflactionEnabled = reflectionEnabled;
		effectStatus.alphaClipEnabled = alphaClipEnabled;
		effectStatus.textureUsed = textureUsed;

		if (reflectionEnabled)
		{
			AddStaticBind(std::make_unique<Texture>(gfx, gfx.GetCubeMapSRV(), 1u));
		}
		AddStaticBind(std::make_unique<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));
		AddStaticBind(std::make_unique<PSConstBuff<EffectStatus>>(gfx, effectStatus, 4u));
		

		
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
	AddStaticBind(std::make_unique<Texture>(gfx, TextureLoader(filePath.c_str()),index));
	AddBind(std::make_unique<TransformationBuffer>(gfx, *this, true));
}

void GeometryGenerator::ReflactionOn(bool reflactionStatus)
{
	isReflaction = reflactionStatus;
}

void GeometryGenerator::UpdateTex(float dt)
{
	static float t = 0.0f;
	t += 0.01130006f;

	if (t >= 0.033333f)
	{
		index++;
		t = 0.0f;

		if (index == 5)
			index = 0;
	}
	if (std::filesystem::is_directory(filePath))
	{
		//tx.GetImageByIndex(index);
	}
}

void GeometryGenerator::SubDivide(unsigned int numTimesDivide, MeshData& md)
{
	for (int i = 0; i < numTimesDivide; i++)
	{
		MeshData mdTemp = md;
		int triangleCount = mdTemp.indices.size() / 3;
		Vertex v[6];

		// Clear md data and store new vertices and indices inside it
		md.indices.clear();
		md.vertexData.clear();

		for (int i = 0; i < triangleCount; i++)
		{
			// Normalize the Pos XMFLOAT3 types in order to avoid distortions 
			// v[0] , v[3], v[5] is main triangle vertices and has the order of 1st, 2nd, 3rd
			// respect to the clockwise winding. Calculate mid points v[1], v[2] and v[4]

			v[0] = mdTemp.vertexData[mdTemp.indices[3 * i]];
			v[0].Pos = MatHelper::normalize(v[0].Pos);

			v[1].Pos = MatHelper::normalize(0.5f*(mdTemp.vertexData[mdTemp.indices[3 * i]].Pos + mdTemp.vertexData[mdTemp.indices[3 * i + 1]].Pos));
			v[1].texCoord = 0.5f*(mdTemp.vertexData[mdTemp.indices[3 * i]].texCoord + mdTemp.vertexData[mdTemp.indices[3 * i + 1]].texCoord);
			v[1].Normal = MatHelper::normalize(v[1].Pos);

			v[2].Pos = MatHelper::normalize(0.5f* (mdTemp.vertexData[mdTemp.indices[3 * i]].Pos + mdTemp.vertexData[mdTemp.indices[3 * i + 2]].Pos));
			v[2].texCoord = 0.5 * (mdTemp.vertexData[mdTemp.indices[3 * i]].texCoord + mdTemp.vertexData[mdTemp.indices[3 * i + 2]].texCoord);
			v[2].Normal = MatHelper::normalize(v[2].Pos);

			v[3] = mdTemp.vertexData[mdTemp.indices[3 * i + 2]];
			v[3].Pos = MatHelper::normalize(v[3].Pos);

			v[4].Pos = MatHelper::normalize(0.5f* (mdTemp.vertexData[mdTemp.indices[3 * i + 1]].Pos + mdTemp.vertexData[mdTemp.indices[3 * i + 2]].Pos));
			v[4].texCoord = 0.5 * (mdTemp.vertexData[mdTemp.indices[3 * i + 1]].texCoord + mdTemp.vertexData[mdTemp.indices[3 * i + 2]].texCoord);
			v[4].Normal = MatHelper::normalize(v[3].Pos);

			v[5] = mdTemp.vertexData[mdTemp.indices[3 * i + 1]];
			v[5].Pos = MatHelper::normalize(v[5].Pos);

			//-------- triangle vertices------//
			// push vertices into vertexData inside the MeshData struct

			md.vertexData.push_back(v[0]);
			md.vertexData.push_back(v[1]);
			md.vertexData.push_back(v[2]);
			md.vertexData.push_back(v[3]);
			md.vertexData.push_back(v[4]);
			md.vertexData.push_back(v[5]);

			// according to position of the vertices inside the vector create triangles
			// respect to the clockwise winding order (front-face)
			//-------- 1st triangle indices------//
			md.indices.push_back(6 * i);
			md.indices.push_back(6 * i + 1);
			md.indices.push_back(6 * i + 2);
			//-------- 2nd triangle indices------//
			md.indices.push_back(6 * i + 1);
			md.indices.push_back(6 * i + 4);
			md.indices.push_back(6 * i + 2);
			//-------- 3rd triangle indices------//
			md.indices.push_back(6 * i + 2);
			md.indices.push_back(6 * i + 4);
			md.indices.push_back(6 * i + 3);
			//-------- 4th triangle indices------//
			md.indices.push_back(6 * i + 1);
			md.indices.push_back(6 * i + 5);
			md.indices.push_back(6 * i + 4);


		}
	}
}

GeometryGenerator::MeshData* GeometryGenerator::GetMeshData() 
{
	return &meshData;
}

void GeometryGenerator::EnableReflaction(bool status)
{
	reflectionEnabled = status;
}

void GeometryGenerator::EnableFog(bool status)
{
	fogEnabled = status;
}

void GeometryGenerator::EnableTexture(bool status)
{
	textureUsed = status;
}

void GeometryGenerator::EnableAlphaClip(bool status)
{
	alphaClipEnabled = status;
}



