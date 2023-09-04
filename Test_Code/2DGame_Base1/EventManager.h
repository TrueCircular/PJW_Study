#pragma once
#include "TStd.h"
#include "TPlaneObj.h"


struct S_EVENT_ARGS
{
	TObject*	 _sender;
	std::wstring _msg;
};
struct S_EVENT_ARGS_UI
{
	std::wstring _sender;
	std::wstring _msg;
};

using Event = std::function<void(S_EVENT_ARGS)>;
using Event_Map = std::map<std::wstring, Event>;

class EventManager
{
private:
	EventManager(){}
public:
	~EventManager(){}

	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}

};

