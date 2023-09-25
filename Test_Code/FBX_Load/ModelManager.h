#pragma once
#include "TFbxImporter.h"
#include "T3DObject.h"

class ModelManager
{
private:
	static ModelManager*						     _instance;
	std::shared_ptr<TFbxImporter>					 _importer;
	std::map<std::wstring, std::vector<TFbxMesh>>	 _meshDictionary;
private:
	ModelManager()
	{
		Init();
	}
	void Init();
public:
	~ModelManager()
	{
		_importer->Release();

		delete _instance;
		_instance = nullptr;
	}
public:
	static ModelManager* GetInstance()
	{	
		if (_instance == nullptr) _instance = new ModelManager();

		return _instance;
	}
public:
	bool					   AddFbxMeshData(std::wstring mName, std::wstring mPath);
	std::vector<TFbxMesh>	   GetFbxMeshData(std::wstring key);
	std::shared_ptr<T3DObject> GetFbxMeshObject(std::shared_ptr<T3DObject> src, std::wstring key);
};

