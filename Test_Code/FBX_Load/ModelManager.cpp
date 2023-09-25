#include "ModelManager.h"
#include "ICoreStd.h" 

ModelManager* ModelManager::_instance = nullptr;

using std::shared_ptr;

void ModelManager::Init()
{
    _importer = std::make_shared<TFbxImporter>();
    _importer->Init();
}

bool ModelManager::AddFbxMeshData(std::wstring mName, std::wstring mPath)
{
    if (!mName.empty() && !mPath.empty())
    {
        _importer->Clear();

        if (_importer->Load(mPath))
        {
            auto tList = _importer->m_meshList;
            _meshDictionary.insert(std::make_pair(mName, tList));
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

std::vector<TFbxMesh> ModelManager::GetFbxMeshData(std::wstring key)
{
    std::vector<TFbxMesh> pt;

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

std::shared_ptr<T3DObject> ModelManager::GetFbxMeshObject(std::shared_ptr<T3DObject> src, std::wstring key)
{
    shared_ptr<T3DObject> rObj = src;
    auto meshData = GetFbxMeshData(key);

    rObj->Set(ICore::g_pDevice, ICore::g_pContext);

    for (int sub = 0; sub < meshData.size(); sub++)
    {
        TFbxMesh subMesh = meshData[sub];
        shared_ptr<T3DObject> obj = std::make_shared<T3DObject>();
        obj->Set(ICore::g_pDevice, ICore::g_pContext);
        obj->m_VertexList.resize(subMesh.m_PolygonSize * 3);
    }


    return rObj;
}
