#pragma once

#pragma region F_declaration
class GradeSystem;
namespace Gsys { struct sData; };
#pragma endregion

using namespace std;
using namespace Gsys;

#pragma region StateCollection

class SystemState
{
public:
	bool _isIn;
public:
	SystemState() : _isIn(false) {}
	virtual ~SystemState() {}
public:
	virtual bool Run(GradeSystem* system) = 0;
	virtual void Print() = 0;
};

class ViewState : public SystemState
{
public:
	ViewState();
	~ViewState() override;
public:
	bool Run(GradeSystem* system) override;
	void Print() override;
};

class AddState : public SystemState
{
public:
	AddState();
	~AddState() override;
public:
	bool Run(GradeSystem* system) override;
	void Print() override;
};

class DelState : public SystemState
{
public:
	DelState();
	~DelState() override;
public:
	bool Run(GradeSystem* system) override;
	void Print() override;
};

class SearchState : public SystemState
{
public:
	SearchState();
	~SearchState() override;
	bool Run(GradeSystem* system) override;
	void Print() override;
};

class LoadState : public SystemState
{
public:
	LoadState();
	~LoadState() override;
	bool Run(GradeSystem* system) override;
	void Print() override;
};

class SaveState : public SystemState
{
public:
	SaveState();
	~SaveState() override;
	bool Run(GradeSystem* system) override;
	void Print() override;

};

class ExitState : public SystemState
{
public:
	ExitState();
	~ExitState() override;
	bool Run(GradeSystem* system) override;
	void Print() override;
};

class MainState : public SystemState
{
public:
	MainState();
	~MainState() override;
	bool Run(GradeSystem* system) override;
	void Print() override;
};

#pragma endregion

