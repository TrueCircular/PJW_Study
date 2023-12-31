#pragma once
#include "TObject.h"
#include <fbxsdk.h>

#pragma comment (lib, "libfbxsdk-md.lib")
#pragma comment (lib, "libxml2-md.lib")
#pragma comment (lib, "zlib-md.lib")

struct TFbxModel
{
	C_STR	   m_name;
	TMatrix	   m_worldMat;
	TFbxModel* m_parent = nullptr;
};

struct TFbxMesh : public TFbxModel
{
	using SubMaterial = std::vector<PT_Vertex>;
	UINT                     m_PolygonSize = 0;
	std::vector<SubMaterial> m_triangleList;
	std::vector<UINT>        m_offsetList;
	std::vector<W_STR>       m_texFileNameList;
	std::vector<TFbxMesh*>   m_child;
};

class TFbxImporter
{
	using Fbx_Model = std::shared_ptr<TFbxModel>;
public:
	FbxManager*			   m_pSDKManager = nullptr;
	FbxImporter*		   m_pFbxImporter = nullptr;
	FbxScene*			   m_pFbxScene = nullptr;
	FbxNode*			   m_rootNode = nullptr;
public:
	std::vector<FbxNode*>  m_pNodeList;
	std::vector<Fbx_Model> m_modelList;
public:
	std::vector<FbxNode*>  m_pMeshNodeList;
	std::vector<TFbxMesh>  m_meshList;
public:
	bool	   Load(W_STR filePath);
	void	   PreProcess(FbxNode* fbxNode, TFbxModel* parent = nullptr);
	void	   LoadMesh(FbxNode* node, TFbxMesh& mesh);
public:
	FbxVector2 ReadTextureCoord(FbxLayerElementUV* uvLayer,int idxIndex, int uvIndex);
	FbxColor   ReadColor(FbxLayerElementVertexColor* lColor, int vIndex, int iIndex);
	FbxVector4 ReadNormal(FbxLayerElementNormal* lNormal, int vIndex, int iIndex);
	C_STR      ParseMaterial(FbxSurfaceMaterial* sMtrl);
	int        GetSubMaterialIndex(UINT poly, FbxLayerElementMaterial* eMtrl);
public:
	TMatrix FbxMatConvertToDxMat(FbxMatrix& fMat);
	TMatrix FbxAMatConvertToDxMat(FbxAMatrix& faMat);
	TMatrix DxMatConvert(TMatrix& tMat);
	TMatrix ParseTransform(FbxNode* fNode);
public:
	bool	   Init();
	bool	   Release();
	bool	   Clear();
};

