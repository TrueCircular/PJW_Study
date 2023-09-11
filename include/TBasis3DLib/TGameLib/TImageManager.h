#pragma once
#include "TManager.h"
#include <d3d11.h>
#include "dxtk/WICTextureLoader.h"
#include "dxtk/DDSTextureLoader.h"
class TImage
{
protected:
	std::wstring			m_csName;
	ID3D11Device*			m_pd3dDevice; //积己
	ID3D11DeviceContext*    m_pd3dContext;//包府
public:
	ID3D11ShaderResourceView*  m_pTextureSRV;
	ID3D11Resource*			   m_Texture;
	D3D11_TEXTURE2D_DESC       m_TextureDesc;
public:	
	bool    Init(ID3D11Device* pd3dDevice,
				 ID3D11DeviceContext* pd3dContext);
	bool	Load(std::wstring path, std::wstring key);
	bool	Release();
	TImage()
	{
		m_pTextureSRV = nullptr;
		m_Texture = nullptr;
	}
	TImage(std::wstring name)
	{
		m_csName = name;
	}
	virtual ~TImage();
};

class TImageManager : public TManager<TImage>
{
	// 窜老按眉 积己(教臂沛)
	static TImageManager g_ImageManager;
public:
	static TImageManager* Get()
	{
		return &g_ImageManager;
	}
	TImage*			m_pWhiteImage;
	TImage*			m_pBlackImage;
public:
	bool    Init(ID3D11Device* pd3dDevice,
				 ID3D11DeviceContext* pd3dContext) override;
	TImage* Load(std::wstring key);
	bool	Release()override;
private:
	TImageManager();
public:
	virtual ~TImageManager();
};
