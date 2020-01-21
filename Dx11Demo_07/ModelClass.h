#pragma once

class TextureClass;

class ModelClass
{
private:
	struct ModelType {
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, WCHAR*, ConstantBuffer<CB_VS_vertexshader>&);
	void Shutdown();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	void Draw(const XMMATRIX & viewProjectionMatrix);

	const XMVECTOR & GetPositionVector() const;
	const XMFLOAT3 & GetPositionFloat3() const;
	const XMVECTOR & GetRotationVector() const;
	const XMFLOAT3 & GetRotationFloat3() const;

	void SetPosition(const XMVECTOR & pos);
	void SetPosition(const XMFLOAT3 & pos);
	void SetPosition(float x, float y, float z);
	void AdjustPosition(const XMVECTOR & pos);
	void AdjustPosition(const XMFLOAT3 & pos);
	void AdjustPosition(float x, float y, float z);
	void SetRotation(const XMVECTOR & rot);
	void SetRotation(const XMFLOAT3 & rot);
	void SetRotation(float x, float y, float z);
	void AdjustRotation(const XMVECTOR & rot);
	void AdjustRotation(const XMFLOAT3 & rot);
	void AdjustRotation(float x, float y, float z);
	void SetLookAtPos(XMFLOAT3 lookAtPos);
	const XMVECTOR & GetForwardVector();
	const XMVECTOR & GetRightVector();
	const XMVECTOR & GetBackwardVector();
	const XMVECTOR & GetLeftVector();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	void UpdateWorldMatrix();

	ID3D11Device * device = nullptr;
	ID3D11DeviceContext * deviceContext = nullptr;
	ConstantBuffer<CB_VS_vertexshader> * cb_vs_vertexshader = nullptr;
	ID3D11ShaderResourceView * texture = nullptr;

	VertexBuffer<Vertex> m_VertexBuffer;
	IndexBuffer m_IndexBuffer;

	int m_vertexCount = 0;
	int m_indexCount = 0;
	TextureClass* m_Texture = nullptr;
	ModelType* m_model = nullptr;


	XMMATRIX worldMatrix = XMMatrixIdentity();

	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_BACKWARD_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR vec_forward;
	XMVECTOR vec_left;
	XMVECTOR vec_right;
	XMVECTOR vec_backward;
};