#pragma once

struct CRuntimeClass
{
	TCHAR* classname;
	void* (*CreateObject)();
	static CRuntimeClass* firstclass;
	CRuntimeClass* nextclass;

	static void* CreateObjectByName(const TCHAR *name);
};

struct CLASS_INIT {
	CLASS_INIT(CRuntimeClass *pNewClass);
};

#define DECLARE_DYNCREATE(classname) \
public:static CRuntimeClass class##classname;\
		static void* Create##classnameObject();

#define IMPLEMENT_DYNCREATE(classname) \
TCHAR lpsz##classname[]=_T(#classname);\
CRuntimeClass classname::class##classname={lpsz##classname,classname::Create##classnameObject,CRuntimeClass::firstclass};\
CLASS_INIT init##classname(&classname::class##classname);\
void* classname::Create##classnameObject(){return new classname();}
