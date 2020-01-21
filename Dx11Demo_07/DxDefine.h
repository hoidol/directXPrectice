#pragma once

/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")


//////////////
// INCLUDES //
//////////////
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "DDSTextureLoader.h"	// DDS 颇老 贸府
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Vertex.h"
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
using namespace DirectX;


///////////////////////////
//  warning C4316 贸府侩  //
///////////////////////////
#include "AlignedAllocationPolicy.h"
