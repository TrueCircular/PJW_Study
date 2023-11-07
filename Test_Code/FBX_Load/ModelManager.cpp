#include "ModelManager.h"
#include "ICoreStd.h" 

ModelManager* ModelManager::_instance = nullptr;

using std::shared_ptr;
using std::make_shared;
using MeshData = std::vector<TFbxMesh>;

void ModelManager::Init()
{
    _importer = make_shared<TFbxImporter>();
    _importer->Init();
}

void ModelManager::ReleaseDictionary()
{
    for (auto a : _meshDictionary)
    {
        auto data = a.second._meshData;
        
        for (int i = 0; i < data.size(); i++)
        {  
            for (int j = 0; j < data[i].m_child.size(); j++)
            {
                if (data[i].m_child[j] != nullptr)
                {
                    delete data[i].m_child[j];
                    data[i].m_child[j] = nullptr;
                }
            }
            data[i].m_child.clear();
        }
    }

    _meshDictionary.clear();
}

std::wstring ModelManager::SplitSrcPath(std::wstring path)
{
    std::size_t size = path.find_last_of(L"/");
    std::wstring rPath = path.substr(0, size + 1);

    return rPath;
}

bool ModelManager::AddFbxMeshData(std::wstring mName, std::wstring mPath)
{
    if (!mName.empty() && !mPath.empty())
    {
        _importer->Clear();

        if (_importer->Load(mPath))
        {
            S_MeshData temp;
            temp._meshData = _importer->m_meshList;
            temp._srcPath = SplitSrcPath(mPath);
            _meshDictionary.insert(std::make_pair(mName, temp));
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

S_MeshData ModelManager::GetFbxMeshData(std::wstring key)
{
    S_MeshData pt;

    auto findIter = _meshDictionary.find(key);

    if (findIter != _meshDictionary.end())
    {
        pt = findIter->second;
        return pt;
    }
    else
    {
        throw std::runtime_error("Mesh Data not found");
    }
}

std::shared_ptr<T3DObject> ModelManager::GetFbxMeshObject(std::wstring key)
{
    shared_ptr<T3DObject> rObj = make_shared<T3DObject>();
    auto meshData = GetFbxMeshData(key);

    rObj->Set(ICore::g_pDevice, ICore::g_pContext);

    for (int sub = 0; sub < meshData._meshData.size(); sub++)
    {
        TFbxMesh subMesh = meshData._meshData[sub];

        shared_ptr<T3DObject> obj = make_shared<T3DObject>();
        obj->Set(ICore::g_pDevice, ICore::g_pContext);

        UINT tSize = subMesh.m_PolygonSize * 3;
        obj->m_VertexList.resize(tSize);
        obj->SetMesh(subMesh);

        UINT subMtrlNum = subMesh.m_triangleList.size();
        UINT subVIndex = 0;

        for (int i = 0; i < subMtrlNum; i++)
        {
            subMesh.m_offsetList.push_back(subVIndex);

            for (int j = 0; j < subMesh.m_triangleList[i].size(); j++)
            {
                UINT tVIndex = subVIndex + j;
                obj->m_VertexList[tVIndex] = subMesh.m_triangleList[i][j];
            }

            subVIndex += subMesh.m_triangleList[i].size();
        }

        W_STR fName;
        W_STR fPath = meshData._srcPath;

        S_T3DOBJECT_DESC objDesc;
        objDesc._pos = { 0,0,0 };
        objDesc._rot = { 1,1,1,1 };
        objDesc._scale = { 1,1,1 };
        objDesc._shaderPath = L"../../resource/shader/Plane.hlsl";

        if (subMesh.m_texFileNameList.size() > 1)
        {
            fName = subMesh.m_texFileNameList[0];
            fPath += fName;
            objDesc._texPath = fPath;
            obj->Create(objDesc);
        }
        else
        {
            objDesc._texPath = L"";
            obj->Create(objDesc);
        }

        std::vector<W_STR> texPath;
        for (int isubMtrl = 0; isubMtrl < subMesh.m_texFileNameList.size(); isubMtrl++)
        {
            fName = subMesh.m_texFileNameList[isubMtrl];
            fPath += fName;
            texPath.push_back(fPath);
        }
        obj->LoadTextureList(texPath);
        rObj->GetSubObjectList().push_back(obj);
    }

    return rObj;
}
