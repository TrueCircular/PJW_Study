#pragma once
#include "TFbxImporter.h"

class ModelManager
{
	using SubMaterial = std::vector<PT_Vertex>;
private:
	static ModelManager*						   _instance;
	std::shared_ptr<TFbxImporter>				   _importer;
	std::map<std::wstring, std::vector<SubMaterial>> _modelDictionary;
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
	bool					              AddFbxModelData(std::wstring mName, std::wstring mPath);
	std::vector<std::vector<PT_Vertex>>   GetFbxModelData(std::wstring key);
};

