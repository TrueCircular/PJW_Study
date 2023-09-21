#pragma once
#include "TObject.h"
struct TMapInfo
{
	UINT  row;
	UINT  col;
	float fDistance;
	W_STR strDefaultTextureFileName;
	W_STR strShaderFileName;
};
class TMap : public TObject
{
	TMapInfo		m_MapInfo;
	UINT m_iNumVertices;
	UINT m_iNumFace;
	UINT m_iNumCellRows;
	UINT m_iNumCellCols;
	UINT m_iNumCols;
	UINT m_iNumRows;
	std::vector<float> m_heightList;
	bool _isHeightLoad = false;
public:
	float		GetHeightOfVertex(UINT iVertexIndex);
	TVector3	GetNormalOfVertex(UINT iVertexIndex);
	TVector4	GetColorOfVertex(UINT iVertexIndex);
	TVector2	GetTextureOfVertex(UINT, UINT);
	bool		CreateHeightMap(std::wstring hPath);
public:
	bool	CreateVertexData() override;
	bool	CreateHeightVertexData();
	bool	CreateIndexData()override;
	bool	 Load(TMapInfo info);
	bool	 LoadHightMap(std::wstring shaderFilename, std::wstring texFilename);

};

