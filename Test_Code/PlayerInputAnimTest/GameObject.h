#pragma once
#include "TStd.h"
#include "TSpriteObj.h"
#include "GameComponent.h"

class GameObject : public TObject
{
protected:
	std::map<std::wstring, std::shared_ptr<GameComponent>> _components;
public:
	void			AddComponent(std::wstring key, std::shared_ptr<GameComponent> component);
	void			DeleteComponent(std::wstring key);
	std::shared_ptr<GameComponent>	GetComponent(std::wstring key);
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

