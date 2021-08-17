#include "Framework.h"
#include "Buffer.h"

VertexBuffer::VertexBuffer(void* data, UINT count, UINT stride, UINT slot, bool bCpuWrite, bool bGpuWrite)
	: data(data), count(count), stride(stride), slot(slot)
	, bCpuWrite(bCpuWrite), bGpuWrite(bGpuWrite)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = stride * count;

	// 기본적으로 읽기만 가능하면 속도가 빠름
	// 쓰기로 하면 속도가 느림
	if(bCpuWrite == false && bGpuWrite == false)
	{
		// GPU 읽기
		desc.Usage = D3D11_USAGE_IMMUTABLE;
	} else if(bCpuWrite && bGpuWrite == false)
	{
		// CPU 쓰기, GPU 읽기만 가능
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //이거 안해주면 CPU 쓰기도 안된다.
	} else if(bCpuWrite == false && bGpuWrite == true)
	{
		// 쉐이더에서 뭔갈 처리하고, CPU에 보내주기 위해 쓴다.
		// CPU 쓰기 가능한 예외 상황 - UpdateSubResource
		// 하지만 UpdateSubResource는 cpu에 복사하기 위한 lock을 자기 스스로 걸기 때문에 시점 제어 불가능
		desc.Usage = D3D11_USAGE_DEFAULT;
	} else
	{
		// CPU, GPU 쓰기 가능
		desc.Usage = D3D11_USAGE_STAGING;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	}

	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = data;
	
	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &buffer));
}

VertexBuffer::~VertexBuffer()
{
	SafeDelete(buffer);
}

void VertexBuffer::Render()
{
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(slot, 1, &buffer, &stride, &offset);
}


IndexBuffer::IndexBuffer(void* data, UINT count)
	: data(data), count(count)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = sizeof(UINT) * count;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA subResource = {nullptr };
	subResource.pSysMem = data;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &_buffer));
}


IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Render()
{
	UINT offset;
	D3D::GetDC()->IASetIndexBuffer(_buffer, DXGI_FORMAT_R32_UINT, offset);
}


ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.ByteWidth = dataSize;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	Check(D3D::GetDevice()->CreateBuffer(&desc, NULL, &_buffer));
}

ConstantBuffer::~ConstantBuffer()
{
	SafeRelease(_buffer);
}

void ConstantBuffer::Render()
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	//Map을 하면 다른 곳에서 buffer를 접근하게 되면 터지게됨
	D3D::GetDC()->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, data, dataSize);
	}
	D3D::GetDC()->Unmap(_buffer, 0);
	//반드시 unmap 해야 함
}
