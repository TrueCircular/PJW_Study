#include "ModelManager.h"

ModelManager* ModelManager::_instance = nullptr;

void ModelManager::Init()
{
    _importer = std::make_shared<TFbxImporter>();
    _importer->Init();
}

bool ModelManager::AddFbxModelData(std::wstring mName, std::wstring mPath)
{
    if (!mName.empty() && !mPath.empty())
    {
        _importer->Clear();

        if (_importer->Load(mPath))
        {
            auto tList = _importer->m_meshList[0].m_triangleList;
            _modelDictionary.insert(std::make_pair(mName, tList));
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

    return false;
}

std::vector<PT_Vertex> ModelManager::GetFbxModelData(std::wstring key)
{
    std::vector<PT_Vertex> pt;

    auto findIter = _modelDictionary.find(key);

    if (findIter != _modelDictionary.end())
    {

        pt = findIter->second;
        return pt;
    }
    else
    {
        throw std::runtime_error("Component not found");
    }
}
