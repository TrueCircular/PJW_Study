#include "GameObject.h"

void GameObject::AddComponent(wstring key, std::shared_ptr<GameComponent> component)
{
	if (!key.empty())
	{
		auto result = _components.insert(std::make_pair(key, component));
		
		if (!result.second)
		{
			throw std::runtime_error("Failed to Add Component. Duplicate key : " + wtm(key));
		}
		else
		{
			std::shared_ptr<GameObject> temp(this);
			component->SetOwner(temp);
		}
	}
	else
	{
		throw std::runtime_error("This Key is Empty");
	}
}

void GameObject::DeleteComponent(wstring key)
{
	auto delComponent = _components.find(key);

	if (delComponent != _components.end())
	{
		_components.erase(delComponent);
	}
	else
	{
		throw std::runtime_error("Component not found");
	}
}

std::shared_ptr<GameComponent> GameObject::GetComponent(wstring key)
{
	auto findIter = _components.find(key);

	if (findIter != _components.end())
	{
		std::shared_ptr<GameComponent> rFind = findIter->second;
		return rFind;
	}
	else
	{
		throw std::runtime_error("Component not found");
	}
}


bool GameObject::Init()
{
	for (auto a : _components)
	{
		a.second->Init();
	}
	return true;
}

bool GameObject::Frame()
{
	for (auto a : _components)
	{
		a.second->Frame();
	}
	return true;
}

bool GameObject::Render()
{
	for (auto a : _components)
	{
		a.second->Render();
	}
	return true;
}

bool GameObject::Release()
{
	//TObject::Release();

	for (auto a : _components)
	{
		a.second->Release();
	}
	return true;
}
