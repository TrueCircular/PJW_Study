#pragma once
#include "TStd.h"
#include "TSpriteObj.h"
#include "GameComponent.h"

using std::map;
using std::wstring;

class GameObject : public TObject
{
protected:
	map<wstring, std::shared_ptr<GameComponent>> _components;
public:
	void			AddComponent(wstring key, std::shared_ptr<GameComponent> component);
	void			DeleteComponent(wstring key);
	std::shared_ptr<GameComponent>	GetComponent(wstring key);
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

