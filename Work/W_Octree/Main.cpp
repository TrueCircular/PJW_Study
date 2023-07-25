#pragma once
#include"Myheaders.h"


int main()
{
	vector<QObject*> StaticObjList;
	QObject* user;

	QTree ocTree;
	SpaceData sData;
	sData.pos = { 0,0,0 };
	sData.surf = { 600,600,600 };

	ocTree.SetSpaceData(sData);
	ocTree.BuildTree();


	return 0;
}