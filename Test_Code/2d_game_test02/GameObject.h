#pragma once
#include "TStd.h"
#include "GameComponent.h"

class GameObject : public TPlaneObj, public std::enable_shared_from_this<GameObject>
{
protected:
	std::shared_ptr<GameObject>								_instance;
	std::map<std::wstring, std::shared_ptr<GameComponent>>	_components;
public:
	GameObject();
	virtual ~GameObject();
public:
	void							AddComponent(std::wstring key, std::shared_ptr<GameComponent> component);
	void							DeleteComponent(std::wstring key);
	std::shared_ptr<GameComponent>	GetComponent(std::wstring key);
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

