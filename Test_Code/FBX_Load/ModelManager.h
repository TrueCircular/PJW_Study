#pragma once
#include "TFbxImporter.h"
#include "T3DObject.h"

struct S_MeshData
{
	std::vector<TFbxMesh> _meshData;
	std::wstring		  _srcPath;
};


class ModelManager
{
	using MeshData = std::vector<TFbxMesh>;
private:
	static ModelManager*			   _instance;
	std::shared_ptr<TFbxImporter>	   _importer;
	std::map<std::wstring, S_MeshData> _meshDictionary;
private:
	ModelManager()
	{
		Init();
	}
	void Init();
public:
	~ModelManager()
	{
		ReleaseDictionary();
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
private:
	void		 ReleaseDictionary();
	std::wstring SplitSrcPath(std::wstring path);
public:
	bool					   AddFbxMeshData(std::wstring mName, std::wstring mPath);
	S_MeshData				   GetFbxMeshData(std::wstring key);
	std::shared_ptr<T3DObject> GetFbxMeshObject(std::wstring key);
};

