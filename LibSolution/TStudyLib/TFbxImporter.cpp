#include "TFbxImporter.h"

bool TFbxImporter::Load(W_STR filePath)
{
	C_STR _filePath = wtm(filePath);

	m_pFbxImporter->Initialize(_filePath.c_str());
	m_pFbxImporter->Import(m_pFbxScene);
	FbxNode* _root = m_pFbxScene->GetRootNode();

	if (_root != nullptr)
	{
		PreProcess(_root);
	}
	for (int i = 0; i < m_pMeshNodeList.size(); i++)
	{
		TFbxMesh temp;
		LoadMesh(m_pMeshNodeList[i], temp);
		m_meshList.push_back(temp);
	}

	return true;
}

void TFbxImporter::PreProcess(FbxNode* fbxNode)
{
	if (fbxNode == nullptr) return;

	C_STR name = fbxNode->GetName();

	FbxMesh* mesh = fbxNode->GetMesh();

	if (mesh != nullptr)
	{
		m_pMeshNodeList.push_back(fbxNode);
	}

	UINT childNum = fbxNode->GetChildCount();

	for (int i = 0; i < childNum; i++)
	{
		FbxNode* child = fbxNode->GetChild(i);
		PreProcess(child);
	}
}

void TFbxImporter::LoadMesh(FbxNode* node, TFbxMesh& mesh)
{
	FbxMesh* _mesh = node->GetMesh();
	UINT _polygonCount = _mesh->GetPolygonCount();
	FbxVector4* _vertexPos = _mesh->GetControlPoints();

	UINT _layerCount = _mesh->GetLayerCount();
	std::vector<FbxLayerElementUV*> _vertexUVList;

	for (int i = 0; i < _layerCount; i++)
	{
		FbxLayer* _layer = _mesh->GetLayer(i);

		if (_layer->GetUVs() != nullptr)
		{
			_vertexUVList.push_back(_layer->GetUVs());
		}

	}

	for (int i = 0; i < _polygonCount; i++)
	{
		UINT _polygonSize = _mesh->GetPolygonSize(i);
		UINT _triangleCount = _polygonSize - 2;

		UINT _cornerIndices[3];

		for (int j = 0; j < _triangleCount; j++)
		{
			_cornerIndices[0] = _mesh->GetPolygonVertex(i, 0);
			_cornerIndices[1] = _mesh->GetPolygonVertex(i, j + 2);
			_cornerIndices[2] = _mesh->GetPolygonVertex(i, j + 1);

			int _vUv[3];
			_vUv[0] = _mesh->GetTextureUVIndex(i, 0);
			_vUv[1] = _mesh->GetTextureUVIndex(i, j + 2);
			_vUv[2] = _mesh->GetTextureUVIndex(i, j + 1);

			for (int k = 0; k < 3; k++)
			{
				UINT _idcIndex = _cornerIndices[k];
				PT_Vertex _pnct;

				FbxVector4 vx = _vertexPos[_idcIndex];
				_pnct.p.x = vx.mData[0];
				_pnct.p.y = vx.mData[2];
				_pnct.p.z = vx.mData[1];
				_pnct.n = { 0,0,0 };
				_pnct.c = { 1,1,1,1 };

				if (_vertexUVList.size() > 0)
				{
					FbxLayerElementUV* _uvLayer = _vertexUVList[0];
					FbxVector2 uv(0, 0);
					uv = ReadTextureCoord(_uvLayer, _vUv[k]);
					_pnct.t.x = (float)uv.mData[0];
					_pnct.t.y = 1.0f - (float)uv.mData[1];
				}

				mesh.m_triangleList.push_back(_pnct);
			}

		}

	}

}

FbxVector2 TFbxImporter::ReadTextureCoord(FbxLayerElementUV* uvLayer, int uvIndex)
{
	FbxVector2 _uv;

	switch (uvLayer->GetMappingMode())
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (uvLayer->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{

		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{

		}break;
		}
	}break;
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (uvLayer->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		case FbxLayerElementUV::eIndexToDirect:
		{
			_uv = uvLayer->GetDirectArray().GetAt(uvIndex);
		}break;
		}
	}break;
	}

	return _uv;
}

bool TFbxImporter::Init()
{
	m_pSDKManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pSDKManager, IOSROOT);
	m_pFbxScene = FbxScene::Create(m_pSDKManager, "");
	return true;
}

bool TFbxImporter::Release()
{
	if (m_pFbxScene)	m_pFbxScene->Destroy();
	if (m_pFbxImporter) m_pFbxImporter->Destroy();
	if (m_pSDKManager)	m_pSDKManager->Destroy();

	m_pFbxScene = nullptr;
	m_pFbxImporter = nullptr;
	m_pSDKManager = nullptr;

	return false;
}

bool TFbxImporter::Clear()
{
	if (m_pMeshNodeList.size() > 0)
	{
		for (int i = 0; i < m_pMeshNodeList.size(); i++)
		{
			m_pMeshNodeList[i]->Destroy();
			m_pMeshNodeList[i] = nullptr;
		}

		m_pMeshNodeList.clear();

	}

	if (m_pFbxScene) m_pFbxScene->Clear();

	if (m_meshList.size() > 0)
	{
		m_meshList.clear();
	}

	return true;
}
