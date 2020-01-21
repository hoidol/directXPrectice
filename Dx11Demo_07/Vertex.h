#pragma once
#include "stdafx.h"

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z, float u, float v)
		: pos(x, y, z), texCoord(u, v) {}
	Vertex(float x, float y, float z, float u, float v,float nx,float ny,float nz)
		: pos(x, y, z), texCoord(u, v),nor(nx,ny,nz) {}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 texCoord;
	DirectX::XMFLOAT3 nor;
};