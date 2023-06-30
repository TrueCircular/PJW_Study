#pragma once
#include <io.h>
#include <filesystem>

#pragma region F_declaration
class GradeSystem;
namespace Gsys { 
	enum class E_Sort;
	enum class E_SortingType;
	enum class E_SaveMode;
	enum class E_SaveType;
	enum class E_LoadMode;
	enum class E_LoadType;
	struct sData; 
};
template<typename T> class Info;
template<typename T, typename N> class GradeList;
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
private:
	void PrintStudentInfo(Info<sData>* data);
	void PrintSorting(GradeSystem* system, E_SortingType sType);
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
private:
	void ErrorPrint();
	void AddStudentInfo(GradeSystem* system);
	bool OverlapCheck(GradeSystem* system, int number);
	bool OverlapCheckName(GradeSystem* system, wstring name);
public:
	bool Run(GradeSystem* system) override;
	void Print() override;
};

class DelState : public SystemState
{
public:
	DelState();
	~DelState() override;
private:
	void ErrorPrint();
	void DelStudentInfo(GradeSystem* system);
	bool OverlapCheckIndexToDelete(GradeSystem* system, int idx);
	bool OverlapCheckNameToDelete(GradeSystem* system, wstring name);
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
private:
	struct _finddata_t		_fd;
	intptr_t				_handle;
	string					_rePath;
private:
	void PrintSaveFileList(string path);
	void ErrorPrint();
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

