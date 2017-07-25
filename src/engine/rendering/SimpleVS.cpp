#pragma once

#include "engine/core/Engine.h"
#include "engine/rendering/SimpleVS.h"
#include "engine/rendering/RendererDX11.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>

void SimpleVS::Init()
{
	RendererDX11* renderer = Engine::GetEngine()->GetModule<RendererDX11>();
	if (!renderer)
	{
		//TODO add log messsage after logger is merged
		return;
	}
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	m_VSShader = renderer->CreateVSFromFile(m_FileName.c_str(), layout, numElements, ShaderVersion::V4_0);
}

void SimpleVS::Destroy()
{
	auto renderer = Engine::GetEngine()->GetModule<RendererDX11>();
	Engine::GetEngine()->GetModule<RendererDX11>()->DestroyVS(m_VSShader);
}

void SimpleVS::BindData(ID3D11DeviceContext* context)
{
	context->VSSetShader(static_cast<ID3D11VertexShader*>(m_VSShader.VSPtr), nullptr, 0);
	context->IASetInputLayout(static_cast<ID3D11InputLayout*>(m_VSShader.LayoutPtr));

}
