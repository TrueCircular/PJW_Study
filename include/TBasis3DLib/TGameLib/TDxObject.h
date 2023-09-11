#pragma once
#include <d3d11.h>
#include <vector>
#include <d3dcompiler.h>//D3DCompileFromFile
#include "Matrix.h"
#include "TImageManager.h"
#pragma comment(lib, "d3dcompiler.lib")

struct TVertex
{
	FVector p; // 0 ~ 12
	FVector2 t;    // 12 ~ 20
	TVertex()
	{
		p.X = p.Y = p.Z = 0;
		t.X = 0.0f;
		t.X = 1.0f;
	}
};
struct CB_DATA
{
	FMatrix  matWorld;
	FMatrix  matView;
	FMatrix  matProj;
	FVector4 vColor;
	CB_DATA()
	{
		matWorld = FMatrix::Identity;
		matView = FMatrix::Identity;
		matProj = FMatrix::Identity;
		vColor = FVector4(1, 1, 1, 1);
	}
};
class TDxObject
{
public:
	std::wstring		  m_csName;
	ID3D11Device*		  m_pd3dDevice;
	ID3D11DeviceContext*  m_pd3dContext;
	ID3DBlob*			  m_pVSObj;
	CB_DATA				  m_cbData;
	FMatrix				  m_matWorld;
	FMatrix				  m_matView;
	FMatrix				  m_matProj;
public:
	std::vector<TVertex>  m_VertexList;
	ID3D11Buffer*         m_VertexBuffer;
	ID3D11Buffer*         m_ConstantBuffer;
	ID3D11VertexShader*   m_pVertexShader;
	ID3D11PixelShader*    m_pPixelShader;
	ID3D11InputLayout*	  m_pInputLayout;
	TImage*			      m_pImage;
	TImage*				  m_pImageMask;
	TImage*				  m_pCurrentState;
public:
	virtual bool	Create(ID3D11Device* pd3dDevice,	
		ID3D11DeviceContext*    pd3dContext,
		std::wstring objName,
		std::wstring loadfile,
		std::wstring loadMaskfile=L"");
	virtual bool	CreateVertexData() = 0;
	virtual bool	CreateVertexBuffer();
	virtual bool	CreateConstantData();
	virtual bool	CreateConstantBuffer();
	virtual bool    CreateShader();
	virtual bool    CreateVertexLayout();
	virtual bool    LoadTexture(std::wstring loadfile, std::wstring loadMaskfile);
	virtual bool	Init();
	virtual bool	Frame();
	virtual void	SetMatrix(FMatrix* world,
							  FMatrix* view, FMatrix* proj);
	virtual bool	Render();
	virtual bool	Release();
	void    Convert(TVertex& v, float sw, float sh, float tw, float th);
	void    ConvertPos(FVector& v, float sw, float sh);
	void    ConvertUV(FVector2& v, float tw, float th);
	HRESULT	Load(ID3D11Device* pDevice, const TCHAR* strFilePath);
public:
	TDxObject();
	virtual ~TDxObject();
};

