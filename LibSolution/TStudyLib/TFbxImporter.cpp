#include "TFbxImporter.h"

bool TFbxImporter::Load(W_STR filePath)
{
	C_STR _filePath = wtm(filePath);

	m_pFbxImporter->Initialize(_filePath.c_str());
	m_pFbxImporter->Import(m_pFbxScene);
	m_rootNode = m_pFbxScene->GetRootNode();

	if (m_rootNode != nullptr)
	{
		PreProcess(m_rootNode);
	}

	m_meshList.resize(m_pMeshNodeList.size());

	for (int i = 0; i < m_pMeshNodeList.size(); i++)
	{
		TFbxMesh& temp = m_meshList[i];
		LoadMesh(m_pMeshNodeList[i], temp);
		temp.m_name = m_pMeshNodeList[i]->GetName();
		temp.m_worldMat = ParseTransform(m_pMeshNodeList[i]);
	}

	return true;
}

void TFbxImporter::PreProcess(FbxNode* fbxNode, TFbxModel* parent)
{
	if (fbxNode == nullptr) return;
	if (fbxNode->GetCamera() ||
		fbxNode->GetLight()) return;

	Fbx_Model model = std::make_shared<TFbxModel>();
	model->m_name = fbxNode->GetName();
	model->m_parent = parent;
	model->m_worldMat = ParseTransform(fbxNode);
	m_pNodeList.push_back(fbxNode);
	m_modelList.push_back(model);

	FbxMesh* mesh = fbxNode->GetMesh();

	if (mesh != nullptr)
	{
		m_pMeshNodeList.push_back(fbxNode);
	}

	UINT childNum = fbxNode->GetChildCount();

	for (int i = 0; i < childNum; i++)
	{
		FbxNode* child = fbxNode->GetChild(i);
		PreProcess(child, model.get());
	}
}

void TFbxImporter::LoadMesh(FbxNode* node, TFbxMesh& mesh)
{
	FbxMesh* _mesh = node->GetMesh();
	UINT _polygonCount = _mesh->GetPolygonCount();
	FbxVector4* _vertexPos = _mesh->GetControlPoints();

	UINT _layerCount = _mesh->GetLayerCount();

	std::vector<FbxLayerElementVertexColor*> _vertexColorList;
	std::vector<FbxLayerElementNormal*>      _vertexNormalList;
	std::vector<FbxLayerElementUV*>			 _vertexUVList;
	std::vector<FbxLayerElementMaterial*>    _materialList;

	for (int i = 0; i < _layerCount; i++)
	{
		FbxLayer* _layer = _mesh->GetLayer(i);

		if (_layer->GetUVs() != nullptr)
		{
			_vertexUVList.push_back(_layer->GetUVs());
		}
		if (_layer->GetVertexColors() != nullptr)
		{
			_vertexColorList.push_back(_layer->GetVertexColors());
		}
		if (_layer->GetNormals() != nullptr)
		{
			_vertexNormalList.push_back(_layer->GetNormals());
		}
		if (_layer->GetMaterials() != nullptr)
		{
			_materialList.push_back(_layer->GetMaterials());
		}

	}

	int mtrlNum = node->GetMaterialCount();

	if (mtrlNum > 1)
	{
		mesh.m_triangleList.resize(mtrlNum);
	}
	else
	{
		mesh.m_triangleList.resize(1);
	}

	for (int i = 0; i < mtrlNum; i++)
	{
		FbxSurfaceMaterial* mSurface = node->GetMaterial(i);

		if (mSurface)
		{
			std::string texName = ParseMaterial(mSurface);
			CHAR drive[MAX_PATH];
			CHAR dir[MAX_PATH];
			CHAR fName[MAX_PATH];
			CHAR ext[MAX_PATH];
			_splitpath_s(texName.c_str(), drive, MAX_PATH, dir, MAX_PATH, fName, MAX_PATH, ext, MAX_PATH);

			std::string tName = fName;
			tName += ext;
			mesh.m_texFileNameList.push_back(mtw(tName));
		}
	}

	FbxAMatrix geoMat;
	FbxAMatrix normalMat;
	{
		FbxVector4 s = node->GetGeometricScaling(FbxNode::eSourcePivot);
		FbxVector4 r = node->GetGeometricRotation(FbxNode::eSourcePivot);
		FbxVector4 t = node->GetGeometricTranslation(FbxNode::eSourcePivot);

		geoMat.SetS(s);
		geoMat.SetR(r);
		geoMat.SetT(t);

		normalMat = geoMat;
		normalMat = normalMat.Inverse();
		normalMat = normalMat.Transpose();
	}

	UINT basePolyIndex = 0;

	for (int i = 0; i < _polygonCount; i++)
	{
		int subMtrl = 0;
		if (mtrlNum >= 1)
		{
			subMtrl = GetSubMaterialIndex(i, _materialList[0]);
		}

		UINT _polygonSize = _mesh->GetPolygonSize(i);
		UINT _triangleCount = _polygonSize - 2;

		UINT _cornerIndices[3];

		mesh.m_PolygonSize += _triangleCount;

		for (int j = 0; j < _triangleCount; j++)
		{
			_cornerIndices[0] = _mesh->GetPolygonVertex(i, 0);
			_cornerIndices[1] = _mesh->GetPolygonVertex(i, j + 2);
			_cornerIndices[2] = _mesh->GetPolygonVertex(i, j + 1);

			int _vUv[3];
			_vUv[0] = _mesh->GetTextureUVIndex(i, 0);
			_vUv[1] = _mesh->GetTextureUVIndex(i, j + 2);
			_vUv[2] = _mesh->GetTextureUVIndex(i, j + 1);

			UINT _vColor[3];
			_vColor[0] = 0;
			_vColor[1] = j + 2;
			_vColor[2] = j + 1;

			for (int k = 0; k < 3; k++)
			{
				UINT _idcIndex = _cornerIndices[k];
				PT_Vertex _pnct;

				//vertex
				FbxVector4 vx = _vertexPos[_idcIndex];
				_pnct.p.x = vx.mData[0];
				_pnct.p.y = vx.mData[2];
				_pnct.p.z = vx.mData[1];

				//normal
				_pnct.n = { 0,0,0 };
				if (_vertexNormalList.size() > 0)
				{
					FbxVector4 tNormal = ReadNormal(_vertexNormalList[0], _idcIndex, basePolyIndex + _vColor[k]);

					auto latNormal = normalMat.MultT(tNormal);
					latNormal.Normalize();
					_pnct.n.x = latNormal.mData[0];
					_pnct.n.y = latNormal.mData[1];
					_pnct.n.z = latNormal.mData[2];
				}
				//color
				_pnct.c = { 1,1,1,1 };
				if (_vertexColorList.size() > 0)
				{
					FbxColor tColor = ReadColor(_vertexColorList[0], _idcIndex, basePolyIndex + _vColor[k]);
					_pnct.c.x = tColor.mRed;
					_pnct.c.y = tColor.mGreen;
					_pnct.c.z = tColor.mBlue;
					_pnct.c.w = tColor.mAlpha;
				}
				//texUV
				if (_vertexUVList.size() > 0)
				{
					FbxLayerElementUV* _uvLayer = _vertexUVList[0];
					FbxVector2 uv(0, 0);
					uv = ReadTextureCoord(_uvLayer, _idcIndex, _vUv[k]);
					_pnct.t.x = (float)uv.mData[0];
					_pnct.t.y = 1.0f - (float)uv.mData[1];
				}

				mesh.m_triangleList[subMtrl].push_back(_pnct);
			}
		}
		basePolyIndex += _polygonSize;
	}
}

FbxVector2 TFbxImporter::ReadTextureCoord(FbxLayerElementUV* uvLayer, int idxIndex, int uvIndex)
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
			_uv = uvLayer->GetDirectArray().GetAt(idxIndex);
		}break;
		case FbxLayerElementUV::eIndexToDirect:
		{
			int id = uvLayer->GetIndexArray().GetAt(idxIndex);
			_uv = uvLayer->GetDirectArray().GetAt(id);
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

FbxColor TFbxImporter::ReadColor(FbxLayerElementVertexColor* lColor, int vIndex, int iIndex)
{
	FbxColor _color(1, 1, 1, 1);

	switch (lColor->GetMappingMode())
	{
	case FbxLayerElementVertexColor::eByControlPoint:
	{
		switch (lColor->GetReferenceMode())
		{
		case FbxLayerElementVertexColor::eDirect:
		{
			_color = lColor->GetDirectArray().GetAt(vIndex);
		}break;
		case FbxLayerElementVertexColor::eIndexToDirect:
		{
			int id = lColor->GetIndexArray().GetAt(vIndex);
			_color = lColor->GetDirectArray().GetAt(id);
		}break;
		}
	}break;

	case FbxLayerElementVertexColor::eByPolygonVertex:
	{
		switch (lColor->GetReferenceMode())
		{
		case FbxLayerElementVertexColor::eDirect:
		{
			_color = lColor->GetDirectArray().GetAt(iIndex);
		}break;
		case FbxLayerElementVertexColor::eIndexToDirect:
		{
			int id = lColor->GetIndexArray().GetAt(iIndex);
			_color = lColor->GetDirectArray().GetAt(id);
		}break;
		}
	}break;
	}

	return _color;
}

FbxVector4 TFbxImporter::ReadNormal(FbxLayerElementNormal* lNormal, int vIndex, int iIndex)
{
	FbxVector4 _normal;

	switch (lNormal->GetMappingMode())
	{
	case FbxLayerElementNormal::eByControlPoint:
	{
		switch (lNormal->GetReferenceMode())
		{
		case FbxLayerElementNormal::eDirect:
		{
			_normal = lNormal->GetDirectArray().GetAt(vIndex);
		}break;
		case FbxLayerElementNormal::eIndexToDirect:
		{
			int id = lNormal->GetIndexArray().GetAt(vIndex);
			_normal = lNormal->GetDirectArray().GetAt(id);
		}break;
		}
	}break;

	case FbxLayerElementNormal::eByPolygonVertex:
	{
		switch (lNormal->GetReferenceMode())
		{
		case FbxLayerElementNormal::eDirect:
		{
			_normal = lNormal->GetDirectArray().GetAt(iIndex);
		}break;
		case FbxLayerElementNormal::eIndexToDirect:
		{
			int id = lNormal->GetIndexArray().GetAt(iIndex);
			_normal = lNormal->GetDirectArray().GetAt(id);
		}break;
		}
	}break;
	}

	return _normal;
}

C_STR TFbxImporter::ParseMaterial(FbxSurfaceMaterial* sMtrl)
{
	C_STR texName = "";

	auto Property = sMtrl->FindProperty(FbxSurfaceMaterial::sDiffuse);

	if (Property.IsValid())
	{
		FbxFileTexture* _tex = Property.GetSrcObject<FbxFileTexture>(0);

		if (_tex != nullptr)
		{
			C_STR fName = _tex->GetFileName();
			return fName;
		}
	}

	return texName;
}

int TFbxImporter::GetSubMaterialIndex(UINT poly, FbxLayerElementMaterial* eMtrl)
{
	int _subMtrlIndex = 0;

	switch (eMtrl->GetMappingMode())
	{
	case FbxLayerElementUV::eByPolygon:
	{
		switch (eMtrl->GetReferenceMode())
		{
		case FbxLayerElementUV::eIndex:
		{
			_subMtrlIndex = poly;
		}break;

		case FbxLayerElementUV::eIndexToDirect:
		{
			_subMtrlIndex = eMtrl->GetIndexArray().GetAt(poly);
		}break;
		}
	}break;
	}

	return _subMtrlIndex;
}

TMatrix TFbxImporter::FbxMatConvertToDxMat(FbxMatrix& fMat)
{
	TMatrix rMat;
	float* matArray = reinterpret_cast<float*>(&rMat);
	double* srcArray = reinterpret_cast<double*>(&fMat);

	for (int i = 0; i < 16; i++)
	{
		matArray[i] = srcArray[i];
	}

	return rMat;
}

TMatrix TFbxImporter::FbxAMatConvertToDxMat(FbxAMatrix& faMat)
{
	TMatrix rMat;
	float* matArray = reinterpret_cast<float*>(&rMat);
	double* srcArray = reinterpret_cast<double*>(&faMat);

	for (int i = 0; i < 16; i++)
	{
		matArray[i] = srcArray[i];
	}

	return rMat;
}

TMatrix TFbxImporter::DxMatConvert(TMatrix& tMat)
{
	TMatrix rMat;
	rMat._11 = tMat._11; rMat._12 = tMat._13; rMat._13 = tMat._12;
	rMat._21 = tMat._31; rMat._22 = tMat._33; rMat._23 = tMat._32;
	rMat._31 = tMat._21; rMat._32 = tMat._23; rMat._33 = tMat._22;
	rMat._41 = tMat._41; rMat._42 = tMat._43; rMat._43 = tMat._42;
	
	rMat._14 = rMat._24 = rMat._34 = 0.0f;
	rMat._44 = 1.0f;

	return rMat;
}

TMatrix TFbxImporter::ParseTransform(FbxNode* fNode)
{
	TMatrix rMat;

	auto timeMode = FbxTime::GetGlobalTimeMode();
	FbxTime time;
	time.SetFrame(0.0f, timeMode);
	
	FbxAMatrix fbxMat = fNode->EvaluateGlobalTransform(time);
	rMat = FbxAMatConvertToDxMat(fbxMat);
	rMat = DxMatConvert(rMat);

	return rMat;
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

	return true;
}

bool TFbxImporter::Clear()
{
	m_pNodeList.clear();
	m_modelList.clear();
	m_pMeshNodeList.clear();
	m_meshList.clear();

	m_rootNode->Destroy();
	if (m_pFbxScene) m_pFbxScene->Clear();

	return true;
}
