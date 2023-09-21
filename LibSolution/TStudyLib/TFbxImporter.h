#pragma once
#include "TObject.h"
#include <fbxsdk.h>

#pragma comment (lib, "libfbxsdk-md.lib")
#pragma comment (lib, "libxml2-md.lib")
#pragma comment (lib, "zlib-md.lib")

struct TFbxMesh
{
	std::vector<PT_Vertex> m_triangleList;
};

class TFbxImporter
{
public:
	FbxManager*			  m_pSDKManager = nullptr;
	FbxImporter*		  m_pFbxImporter = nullptr;
	FbxScene*			  m_pFbxScene = nullptr;
public:
	std::vector<FbxNode*> m_pMeshNodeList;
	std::vector<TFbxMesh> m_meshList;
public:
	bool	   Load(W_STR filePath);
	void	   PreProcess(FbxNode* fbxNode);
	void	   LoadMesh(FbxNode* node, TFbxMesh& mesh);
	FbxVector2 ReadTextureCoord(FbxLayerElementUV* uvLayer, int uvIndex);
public:
	bool	   Init();
	bool	   Release();
	bool	   Clear();
};

