#pragma once
// directx sdk  win10에 설치 되어 있다.
#include <d3d11.h> // 2d, 3d 그래픽
#pragma comment (lib,"d3d11.lib") // D3D11.DLL
class TGraphics
{
public:
	ID3D11Device*			m_pd3dDevice; //생성
	ID3D11DeviceContext*    m_pd3dContext;//관리
	IDXGISwapChain*			m_pSwapChain; //백버퍼
	ID3D11RenderTargetView* m_pRTV;       //백버퍼타켓
	D3D11_VIEWPORT			m_ViewPort;   //화면 어느곳에 랜더링
	
	ID3D11SamplerState*		m_pSamplerState;
	// blend state
	ID3D11BlendState*		m_pAlphaBlend;
	bool					CreateBlendState();
	// depth-stencil state	
	ID3D11DepthStencilView*	 m_pDepthStencilView;
	ID3D11DepthStencilState* m_pDSSDepthEnable;
	ID3D11DepthStencilState* m_pDSSDepthDisable;
	HRESULT UpdateDepthStencilView(ID3D11Device* pDevice, UINT Width, UINT Height);
public:
	bool	Init(HWND hWnd,LONG w, LONG h);
	bool    PreRender();
	bool    PostRender(); 
	bool    Release();
public:
	TGraphics();
	virtual ~TGraphics();
};

