#include <iostream>
#include "script/gradeSystem/GradeSystem.h"

int main()
{
	//Gsys머신
	GradeSystem* machine = new GradeSystem();
	//Exit이전까지
	while (machine->Run());
	//할당 해제
	delete machine;

	return 0;
}

