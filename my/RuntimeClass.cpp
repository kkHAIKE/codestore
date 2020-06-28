#include "StdAfx.h"
#include <RuntimeClass.h>

CRuntimeClass* CRuntimeClass::firstclass;
void* CRuntimeClass::CreateObjectByName(TCHAR *name)
{
	CRuntimeClass* now=firstclass;
	while(now!=NULL) 
	{
		if(_tcscmp(name,now->classname)==0)
		{
			return now->CreateObject();
		}
		now=now->nextclass;
	}
	return NULL;
}

CLASS_INIT::CLASS_INIT(CRuntimeClass *pNewClass)
{
	pNewClass->nextclass=CRuntimeClass::firstclass;
	CRuntimeClass::firstclass=pNewClass;
}
