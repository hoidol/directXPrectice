#include "stdafx.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightclass.h"
#include "lightshaderclass.h"
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	// Direct3D ��ü ����
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Direct3D ��ü �ʱ�ȭ
	if(!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_NEAR, SCREEN_DEPTH))
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// m_Camera ��ü ����
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);
	m_Camera->SetProjectionValues(90.0f, screenWidth / screenHeight, SCREEN_NEAR, SCREEN_DEPTH);

	this->cb_vs_vertexshader.Initialize(this->m_Direct3D->m_device, this->m_Direct3D->m_deviceContext);

	// m_Model ��ü ����
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// m_Model ��ü �ʱ�ȭ
	if (!m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../Dx11Demo_07/data/cube.txt", L"../Dx11Demo_07/data/seafloor.dds",
		cb_vs_vertexshader))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}



	// m_LightShader ��ü ����
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// m_LightShader ��ü �ʱ�ȭ
	if (!m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// m_Light ��ü ����
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}


	// m_Light ��ü �ʱ�ȭ
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
	// m_Light ��ü ��ȯ
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// m_LightShader ��ü ��ȯ
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// m_Model ��ü ��ȯ
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// m_Camera ��ü ��ȯ
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Direct3D ��ü ��ȯ
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}


bool GraphicsClass::Frame()
{
	static float rotation = 0.0f;

	// �� �������� rotation ������ ������Ʈ�մϴ�.
	rotation += (float)XM_PI * 0.01f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	
	// �׷��� ������ ó��
	return Render(rotation);
}


bool GraphicsClass::Render(float rotation)
{
	// ���� �׸��� ���� ���۸� ����ϴ�
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// ī�޶��� ��ġ�� ���� �� ����� �����մϴ�
	m_Camera->Render();

	// ī�޶� �� d3d ��ü���� ����, �� �� ���� ����� �����ɴϴ�
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	m_Direct3D->GetWorldMatrix(worldMatrix);
	viewMatrix = m_Camera->GetViewMatrix();
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// �ﰢ���� ȸ�� �� �� �ֵ��� ȸ�� ������ ���� ����� ȸ���մϴ�.

	// �� ���ؽ��� �ε��� ���۸� �׷��� ������ ���ο� ��ġ�Ͽ� ������� �غ��մϴ�.
	{//this->model.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
		m_Model->Draw(viewMatrix*projectionMatrix);
	}
	// Light ���̴��� ����Ͽ� ���� �������մϴ�.
	if (!m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
								   m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor()))
	{
		return false;
	}

	// ������ ������ ȭ�鿡 ����մϴ�
	m_Direct3D->EndScene();

	return true;
}


