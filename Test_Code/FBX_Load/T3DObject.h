#pragma once
#include "TFbxImporter.h"
#include "TObject.h"

enum class E_MeshType
{
	MESH_DEFAULT,
	MESH_SKELETAL,
	MESH_NONE
};

struct S_T3DOBJECT_DESC
{
	TVector3	_scale;
	TQuaternion _rot;
	TVector3	_pos;
	W_STR       _texPath;
	W_STR		_shaderPath;
	E_MeshType  _meshType;
};

class T3DObject : public TObject
{
	using SubObj = std::shared_ptr<T3DObject>;
private:
	TFbxMesh					 _mesh;
	std::vector<const TTexture*> _texList;
	std::vector<SubObj>			 _subObj;
public:
	TQuaternion					 m_qRotation;
	E_MeshType					 _meshType;
public:
	TFbxMesh		    GetMesh() const { return _mesh; }
	void				SetMesh(TFbxMesh& mesh) { _mesh = mesh; }
	std::vector<SubObj> GetSubObjectList() const { return _subObj; }
public:
	void				LoadTextureList(std::vector<W_STR> fileList);
public:
	virtual bool		Create(S_T3DOBJECT_DESC desc);
	void				SetQuaternionRotation(TQuaternion& rot);
public:
	bool				PostRender() override;
	void				UpdateMatrix() override;
};

