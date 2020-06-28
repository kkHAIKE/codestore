#pragma once
/*
Type Signature				Java Type
Z							boolean
B							byte
C							char
S							short
I							int
J							long
F							float
D							double
L fully-qualified-class ;	fully-qualified-class
[ type						type[]
( arg-types ) ret-type		method type
*/
#include <jni.h>
#include <jni_md.h>

#include <exception>
#include <memory>

#include <boost\thread.hpp>

namespace JNIPP
{
	class JException:public std::exception{};
	
	class JObject
	{
	public:
		JObject():m_object(NULL){}
		operator jobject(){return m_object;}

	protected:
		void init(jobject o)
		{
			m_object=o;
		}
		void init(JNIEnv*env,jclass clazz,jmethodID _init,va_list args)
		{
			m_object=env->NewObjectV(clazz,_init,args);
		}
		
	protected:
		jobject m_object;
	};

//////////////////////////////////////////////////////////////////////////
class PrivateHelper
{
private:
	PrivateHelper(){}
};
	
template<typename T>
inline
jclass Ref_or_NoRef(JNIEnv* env,jclass t)
{
	PrivateHelper();
}
template<>
inline
jclass Ref_or_NoRef<boost::thread_specific_ptr<jclass>>(JNIEnv* env,jclass t)
{
	return (jclass)env->NewWeakGlobalRef((jobject)t);
}
template<>
inline
jclass Ref_or_NoRef<std::auto_ptr<jclass>>(JNIEnv* env,jclass t)
{
	return t;
}
	
template<typename T>
inline
void initJClass(T &pthis,JNIEnv *env,jobject o)
{
	if(pthis.get())
		return;

	jclass t=env->GetObjectClass(o);
	pthis.reset(new jclass);
	*pthis=Ref_or_NoRef<T>(env,t);
}
template<typename T>
inline
void initJClass(T &pthis,JNIEnv *env,const char *name)
{
	if(pthis.get())
		return;

	jclass t=env->FindClass(name);
	if(t==NULL)
		throw JException();
	pthis.reset(new jclass);
	*pthis=Ref_or_NoRef<T>(env,t);
}
template<typename T>
inline
void initJClass(T &pthis,JNIEnv *env,jclass t)
{
	if(pthis.get())
		return;
	
	if(t==NULL)
		throw JException();
	pthis.reset(new jclass);
	*pthis=Ref_or_NoRef<T>(env,t);
}

template<typename T>
inline
void initJMethod(T &pthis,JNIEnv* env,jclass clazz,const char*name,const char* sig)
{
	if(pthis.get())
		return;

	jmethodID t=env->GetMethodID(clazz,name,sig);
	if(t==NULL)
		throw JException();
	pthis.reset(new jmethodID);
	*pthis=t;
}

template<typename T>
inline
void initStaticJMethod(T &pthis,JNIEnv* env,jclass clazz,const char*name,const char* sig)
{
	if(pthis.get())
		return;

	jmethodID t=env->GetStaticMethodID(clazz,name,sig);
	if(t==NULL)
		throw JException();
	pthis.reset(new jmethodID);
	*pthis=t;
}

template<typename T>
inline
void initJField(T &pthis,JNIEnv* env,jclass clazz,const char*name,const char *sig)
{
	if(pthis.get())
		return;

	jfieldID t=env->GetFieldID(clazz,name,sig);
	if(t==NULL)
		throw JException();
	pthis.reset(new jfieldID);
	*pthis=t;
}

template<typename T>
inline
void initStaticJField(T &pthis,JNIEnv* env,jclass clazz,const char*name,const char *sig)
{
	if(pthis.get())
		return;

	jfieldID t=env->GetStaticFieldID(clazz,name,sig);
	if(t==NULL)
		throw JException();
	pthis.reset(new jfieldID);
	*pthis=t;
}

//////////////////////////////////////////////////////////////////////////

template<typename r>
inline
r CallHelper(JNIEnv* env,jobject o,jmethodID m,va_list args)
{
	PrivateHelper();
}
template<typename r>
inline
r StaticCallHelper(JNIEnv* env,jclass clazz,jmethodID m,va_list args)
{
	PrivateHelper();
}
template<>
inline
void CallHelper<void>(JNIEnv* env,jobject o,jmethodID m,va_list args)
{
	env->CallVoidMethodV(o,m,args);
}
template<>
inline
void StaticCallHelper<void>(JNIEnv* env,jclass clazz,jmethodID m,va_list args)
{
	env->CallStaticVoidMethodV(clazz,m,args);
}

template<typename r>
inline
r getFieldHelper(JNIEnv* env,jobject o,jfieldID field)
{
	PrivateHelper();
}
template<typename r>
inline
void setFieldHelper(JNIEnv* env,jobject o,jfieldID field,r t)
{
	PrivateHelper();
}

template<typename r>
inline
r getStaticFieldHelper(JNIEnv* env,jclass clazz,jfieldID field)
{
	PrivateHelper();
}
template<typename r>
inline
void setStaticFieldHelper(JNIEnv* env,jclass clazz,jfieldID field,r t)
{
	PrivateHelper();
}

//////////////////////////////////////////////////////////////////////////
#define xFillAllType(jt,dt)  \
template<> inline  \
jt CallHelper<jt>(JNIEnv* env,jobject o,jmethodID m,va_list args)  \
{return env->Call##dt##MethodV(o,m,args);}  \
template<> inline  \
jt StaticCallHelper<jt>(JNIEnv* env,jclass clazz,jmethodID m,va_list args)  \
{return env->CallStatic##dt##MethodV(clazz,m,args);}  \
template<> inline  \
jt getFieldHelper<jt>(JNIEnv* env,jobject o,jfieldID field)  \
{return env->Get##dt##Field(o,field);}  \
template<> inline  \
void setFieldHelper<jt>(JNIEnv* env,jobject o,jfieldID field,jt t)  \
{env->Set##dt##Field(o,field,t);}  \
template<> inline  \
jt getStaticFieldHelper<jt>(JNIEnv* env,jclass clazz,jfieldID field)  \
{return env->GetStatic##dt##Field(clazz,field);}  \
template<> inline  \
void setStaticFieldHelper<jt>(JNIEnv* env,jclass clazz,jfieldID field,jt t)  \
{env->SetStatic##dt##Field(clazz,field,t);}

xFillAllType(jobject,Object)
xFillAllType(jboolean,Boolean)
xFillAllType(jbyte,Byte)
xFillAllType(jchar,Char)
xFillAllType(jshort,Short)
xFillAllType(jint,Int)
xFillAllType(jlong,Long)
xFillAllType(jfloat,Float)
xFillAllType(jdouble,Double)

//////////////////////////////////////////////////////////////////////////
#define DEFINE_JCLASS_CPP_MUST JavaVM* JNIPP::g_javaVM;

extern JavaVM* g_javaVM;
inline
void Initialize(JavaVM* vm) {
	if (!g_javaVM) {
		g_javaVM=vm;
	}
}
inline
void Initialize(JNIEnv* env) {
	JavaVM* vm=0;
	int error=env->GetJavaVM(&vm);
	if (error) {
		throw JException();
	}
	Initialize(vm);
}
inline
JNIEnv* GetEnv() {
	if (!g_javaVM) {
		throw JException();
	}
	JNIEnv* env=0;
	jint result=g_javaVM->AttachCurrentThread((void**)&env,0);
	if (result) {
		throw JException();
	}
	return env;
}

	class ArgsHelper
	{
	protected:
		va_list& m_args;
	public:
		ArgsHelper(va_list &args):m_args(args){}
		~ArgsHelper(){va_end(m_args);}
	};
//////////////////////////////////////////////////////////////////////////
}
#define xADD_END_(...) __VA_ARGS__##END
#define xADD_END(...) xADD_END_(__VA_ARGS__)
#define xADD_2_(a,b) a##b
#define xADD_2(a,b) xADD_2_(a,b)
#define xADD_3_(a,b,c) a##b##c
#define xADD_3(a,b,c) xADD_3_(a,b,c)

#define xDEFINE_JCLASS_BODY_init(sig,...)  \
	public: void xADD_2(create,__VA_ARGS__)(int nul,...){  \
	JNIEnv* env=JNIPP::GetEnv();  \
	JNIPP::initJClass(g_clazz,env,getc_name());  \
	JNIPP::initJMethod(xADD_2(g_init,__VA_ARGS__),env,*g_clazz,"<init>",sig);  \
	va_list args;va_start(args,nul);JNIPP::ArgsHelper hArgs(args);  \
	init(env,*g_clazz,*g_init,args);}

#define xDEFINE_JCLASS_HEAD_init(...)  \
	protected: std::auto_ptr<jmethodID> xADD_2(g_init,__VA_ARGS__);
#define xDEFINE_JCLASS_init_0_(sig,...)  \
	xDEFINE_JCLASS_HEAD_init(__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_init(sig,__VA_ARGS__) xDEFINE_JCLASS_init_1_
#define xDEFINE_JCLASS_init_1_(sig,...)  \
	xDEFINE_JCLASS_HEAD_init(__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_init(sig,__VA_ARGS__) xDEFINE_JCLASS_init_0_
#define xDEFINE_JCLASS_init(sig,...)  \
	xDEFINE_JCLASS_HEAD_init(__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_init(sig,__VA_ARGS__) xDEFINE_JCLASS_init_0_
#define xDEFINE_JCLASS_init_0_END 
#define xDEFINE_JCLASS_init_1_END

#define xDEFINE_JCLASS_EX_HEAD_init(...)  \
	protected: static boost::thread_specific_ptr<jmethodID> xADD_2(g_init,__VA_ARGS__);
#define xDEFINE_JCLASS_EX_init_0_(sig,...)  \
	xDEFINE_JCLASS_EX_HEAD_init(__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_init(sig,__VA_ARGS__) xDEFINE_JCLASS_EX_init_1_
#define xDEFINE_JCLASS_EX_init_1_(sig,...)  \
	xDEFINE_JCLASS_EX_HEAD_init(__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_init(sig,__VA_ARGS__) xDEFINE_JCLASS_EX_init_0_
#define xDEFINE_JCLASS_EX_init(sig,...)  \
	xDEFINE_JCLASS_EX_HEAD_init(__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_init(sig,__VA_ARGS__) xDEFINE_JCLASS_EX_init_0_
#define xDEFINE_JCLASS_EX_init_0_END 
#define xDEFINE_JCLASS_EX_init_1_END

#define xDEFINE_JCLASS_BODY_method(r,m,sig,...)  \
	public: r xADD_2(m,__VA_ARGS__)(int nul,...) { \
	JNIEnv* env=JNIPP::GetEnv();  \
	JNIPP::initJMethod(xADD_3(g_,m,__VA_ARGS__),env,*g_clazz,#m,sig); \
	va_list args;va_start(args,nul);JNIPP::ArgsHelper hArgs(args);  \
	return JNIPP::CallHelper<r>(env,m_object,*xADD_3(g_,m,__VA_ARGS__),args); }

#define xDEFINE_JCLASS_HEAD_method(m,...)  \
	protected: std::auto_ptr<jmethodID> xADD_3(g_,m,__VA_ARGS__);
#define xDEFINE_JCLASS_method_0_(r,m,sig,...)  \
	xDEFINE_JCLASS_HEAD_method(m,__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_method_1_
#define xDEFINE_JCLASS_method_1_(r,m,sig,...)  \
	xDEFINE_JCLASS_HEAD_method(m,__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_method_0_
#define xDEFINE_JCLASS_method(r,m,sig,...)  \
	xDEFINE_JCLASS_HEAD_method(m,__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_method_0_
#define xDEFINE_JCLASS_method_0_END 
#define xDEFINE_JCLASS_method_1_END

#define xDEFINE_JCLASS_EX_HEAD_method(m,...)  \
	protected: static boost::thread_specific_ptr<jmethodID> xADD_3(g_,m,__VA_ARGS__);
#define xDEFINE_JCLASS_EX_method_0_(r,m,sig,...)  \
	xDEFINE_JCLASS_EX_HEAD_method(m,__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_EX_method_1_
#define xDEFINE_JCLASS_EX_method_1_(r,m,sig,...)  \
	xDEFINE_JCLASS_EX_HEAD_method(m,__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_EX_method_0_
#define xDEFINE_JCLASS_EX_method(r,m,sig,...)  \
	xDEFINE_JCLASS_EX_HEAD_method(m,__VA_ARGS__)  \
	xDEFINE_JCLASS_BODY_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_EX_method_0_
#define xDEFINE_JCLASS_EX_method_0_END 
#define xDEFINE_JCLASS_EX_method_1_END

#define xDEFINE_JCLASS_BODY_static_method(r,m,sig,...)  \
	public: static r xADD_2(m,__VA_ARGS__)(jclass cls_nul,...) { \
	JNIEnv* env=JNIPP::GetEnv();  \
	jclass clazz=getClass(cls_nul);std::auto_ptr<jmethodID> method;  \
	JNIPP::initStaticJMethod(method,env,clazz,#m,sig); \
	va_list args;va_start(args,cls_nul);JNIPP::ArgsHelper hArgs(args);  \
	return JNIPP::StaticCallHelper<r>(env,clazz,*method,args); }

#define xDEFINE_JCLASS_static_method_0_(r,m,sig,...)  \
	xDEFINE_JCLASS_BODY_static_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_static_method_1_
#define xDEFINE_JCLASS_static_method_1_(r,m,sig,...)  \
	xDEFINE_JCLASS_BODY_static_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_static_method_0_
#define xDEFINE_JCLASS_static_method(r,m,sig,...)  \
	xDEFINE_JCLASS_BODY_static_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_static_method_0_
#define xDEFINE_JCLASS_static_method_0_END 
#define xDEFINE_JCLASS_static_method_1_END

#define xDEFINE_JCLASS_EX_BODY_static_method(r,m,sig,...)  \
	public: static r xADD_2(m,__VA_ARGS__)(jclass cls_nul,...) { \
	JNIEnv* env=JNIPP::GetEnv();getClass(cls_nul);  \
	JNIPP::initStaticJMethod(xADD_3(g_,m,__VA_ARGS__),env,*g_clazz,#m,sig); \
	va_list args;va_start(args,cls_nul);JNIPP::ArgsHelper hArgs(args);  \
	return JNIPP::StaticCallHelper<r>(env,*g_clazz,*xADD_3(g_,m,__VA_ARGS__),args); }

#define xDEFINE_JCLASS_EX_HEAD_static_method(m,...)  \
	protected: static boost::thread_specific_ptr<jmethodID> xADD_3(g_,m,__VA_ARGS__);
#define xDEFINE_JCLASS_EX_static_method_0_(r,m,sig,...)  \
	xDEFINE_JCLASS_EX_HEAD_static_method(m,__VA_ARGS__)  \
	xDEFINE_JCLASS_EX_BODY_static_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_EX_static_method_1_
#define xDEFINE_JCLASS_EX_static_method_1_(r,m,sig,...)  \
	xDEFINE_JCLASS_EX_HEAD_static_method(m,__VA_ARGS__)  \
	xDEFINE_JCLASS_EX_BODY_static_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_EX_static_method_0_
#define xDEFINE_JCLASS_EX_static_method(r,m,sig,...)  \
	xDEFINE_JCLASS_EX_HEAD_static_method(m,__VA_ARGS__)  \
	xDEFINE_JCLASS_EX_BODY_static_method(r,m,sig,__VA_ARGS__) xDEFINE_JCLASS_EX_static_method_0_
#define xDEFINE_JCLASS_EX_static_method_0_END 
#define xDEFINE_JCLASS_EX_static_method_1_END

#define xDEFINE_JCLASS_BODY_field(r,f,sig)  \
	public: r xADD_2(get,f)(){ \
	JNIEnv* env=JNIPP::GetEnv();  \
	JNIPP::initJField(xADD_2(g_,f),env,*g_clazz,#f,sig); \
	return JNIPP::getFieldHelper<r>(env,m_object,*xADD_2(g_,f));} \
	void xADD_2(set,f)(r t){ \
	JNIEnv* env=JNIPP::GetEnv();  \
	JNIPP::initJField(xADD_2(g_,f),env,*g_clazz,#f,sig); \
	JNIPP::setFieldHelper<r>(env,m_object,*xADD_2(g_,f),t);}

#define xDEFINE_JCLASS_HEAD_field(f)  \
	protected: std::auto_ptr<jfieldID> xADD_2(g_,f);
#define xDEFINE_JCLASS_field_0_(r,f,sig)  \
	xDEFINE_JCLASS_HEAD_field(f)  \
	xDEFINE_JCLASS_BODY_field(r,f,sig) xDEFINE_JCLASS_field_1_
#define xDEFINE_JCLASS_field_1_(r,f,sig)  \
	xDEFINE_JCLASS_HEAD_field(f)  \
	xDEFINE_JCLASS_BODY_field(r,f,sig) xDEFINE_JCLASS_field_0_
#define xDEFINE_JCLASS_field(r,f,sig)  \
	xDEFINE_JCLASS_HEAD_field(f)  \
	xDEFINE_JCLASS_BODY_field(r,f,sig) xDEFINE_JCLASS_field_0_
#define xDEFINE_JCLASS_field_0_END 
#define xDEFINE_JCLASS_field_1_END

#define xDEFINE_JCLASS_EX_HEAD_field(f)  \
	protected: static boost::thread_specific_ptr<jfieldID> xADD_2(g_,f);
#define xDEFINE_JCLASS_EX_field_0_(r,f,sig)  \
	xDEFINE_JCLASS_EX_HEAD_field(f)  \
	xDEFINE_JCLASS_BODY_field(r,f,sig) xDEFINE_JCLASS_EX_field_1_
#define xDEFINE_JCLASS_EX_field_1_(r,f,sig)  \
	xDEFINE_JCLASS_EX_HEAD_field(f)  \
	xDEFINE_JCLASS_BODY_field(r,f,sig) xDEFINE_JCLASS_EX_field_0_
#define xDEFINE_JCLASS_EX_field(r,f,sig)  \
	xDEFINE_JCLASS_EX_HEAD_field(f)  \
	xDEFINE_JCLASS_BODY_field(r,f,sig) xDEFINE_JCLASS_EX_field_0_
#define xDEFINE_JCLASS_EX_field_0_END 
#define xDEFINE_JCLASS_EX_field_1_END

#define xDEFINE_JCLASS_BODY_static_field(r,f,sig)  \
	public:static r xADD_2(get,f)(jclass cls_nul){ \
	JNIEnv* env=JNIPP::GetEnv();  \
	jclass clazz=getClass(cls_nul);std::auto_ptr<jfieldID> field;  \
	JNIPP::initStaticJField(field,env,clazz,#f,sig); \
	return JNIPP::getStaticFieldHelper<r>(env,clazz,*field);} \
	static void xADD_2(set,f)(jclass cls_nul,r t){ \
	JNIEnv* env=JNIPP::GetEnv();  \
	jclass clazz=getClass(cls_nul);std::auto_ptr<jfieldID> field;  \
	JNIPP::initStaticJField(field,env,clazz,#f,sig); \
	JNIPP::setStaticFieldHelper<r>(env,clazz,*field,t);}

#define xDEFINE_JCLASS_static_field_0_(r,f,sig)  \
	xDEFINE_JCLASS_BODY_static_field(r,f,sig) xDEFINE_JCLASS_static_field_1_
#define xDEFINE_JCLASS_static_field_1_(r,f,sig)  \
	xDEFINE_JCLASS_BODY_static_field(r,f,sig) xDEFINE_JCLASS_static_field_0_
#define xDEFINE_JCLASS_static_field(r,f,sig)  \
	xDEFINE_JCLASS_BODY_static_field(r,f,sig) xDEFINE_JCLASS_static_field_0_
#define xDEFINE_JCLASS_static_field_0_END 
#define xDEFINE_JCLASS_static_field_1_END

#define xDEFINE_JCLASS_EX_BODY_static_field(r,f,sig)  \
	public:static r xADD_2(get,f)(jclass cls_nul){ \
	JNIEnv* env=JNIPP::GetEnv();getClass(cls_nul);  \
	JNIPP::initStaticJField(xADD_2(g_,f),env,*g_clazz,#f,sig); \
	return JNIPP::getStaticFieldHelper<r>(env,*g_clazz,*xADD_2(g_,f));} \
	static void xADD_2(get,f)(jclass cls_nul,r t){ \
	JNIEnv* env=JNIPP::GetEnv();getClass(cls_nul);  \
	JNIPP::initStaticJField(xADD_2(g_,f),env,*g_clazz,#f,sig); \
	JNIPP::setStaticFieldHelper<r>(env,*g_clazz,*xADD_2(g_,f),t);}

#define xDEFINE_JCLASS_EX_HEAD_static_field(f)  \
	protected: static boost::thread_specific_ptr<jfieldID> xADD_2(g_,f);
#define xDEFINE_JCLASS_EX_static_field_0_(r,f,sig)  \
	xDEFINE_JCLASS_EX_HEAD_static_field(f)  \
	xDEFINE_JCLASS_EX_BODY_static_field(r,f,sig) xDEFINE_JCLASS_EX_static_field_1_
#define xDEFINE_JCLASS_EX_static_field_1_(r,f,sig)  \
	xDEFINE_JCLASS_EX_HEAD_static_field(f)  \
	xDEFINE_JCLASS_EX_BODY_static_field(r,f,sig) xDEFINE_JCLASS_EX_static_field_0_
#define xDEFINE_JCLASS_EX_static_field(r,f,sig)  \
	xDEFINE_JCLASS_EX_HEAD_static_field(f)  \
	xDEFINE_JCLASS_EX_BODY_static_field(r,f,sig) xDEFINE_JCLASS_EX_static_field_0_
#define xDEFINE_JCLASS_EX_static_field_0_END 
#define xDEFINE_JCLASS_EX_static_field_1_END

#define xDEFINE_JCLASS_HEAD(c,name)  \
class c:public JNIPP::JObject \
{protected: \
	static char* getc_name(){return name;} \
	std::auto_ptr<jclass> g_clazz; \
public: \
	c(){} \
	c(jobject o){JNIEnv* env=JNIPP::GetEnv();JNIPP::initJClass(g_clazz,env,o);init(o);} \
	c(jclass clazz){JNIEnv* env=JNIPP::GetEnv();JNIPP::initJClass(g_clazz,env,clazz);} \
	jclass getClass(){return *g_clazz;} \
	static jclass getClass(jclass cls_nul){  \
	JNIEnv* env=JNIPP::GetEnv();  \
	std::auto_ptr<jclass> clazz;  \
	if(cls_nul){clazz.reset(new jclass);*clazz=cls_nul;}else  \
	JNIPP::initJClass(clazz,env,getc_name());  \
	return *clazz;}

#define xDEFINE_JCLASS_EX_HEAD(c,name)  \
	class c:public JNIPP::JObject \
	{protected: \
	static char* getc_name(){return name;} \
	static boost::thread_specific_ptr<jclass> g_clazz; \
	public: \
	c(){} \
	c(jobject o){JNIEnv* env=JNIPP::GetEnv();JNIPP::initJClass(g_clazz,env,o);init(o);} \
	c(jclass clazz){JNIEnv* env=JNIPP::GetEnv();JNIPP::initJClass(g_clazz,env,clazz);} \
	jclass getClass(){return *g_clazz;}  \
	static jclass getClass(jclass cls_nul){  \
	JNIEnv* env=JNIPP::GetEnv();  \
	if(cls_nul)JNIPP::initJClass(g_clazz,env,cls_nul);else  \
	JNIPP::initJClass(g_clazz,env,getc_name()); \
	return *g_clazz;}

#define xDEFINE_JCLASS_extern(x) x xDEFINE_JCLASS_
#define xDEFINE_JCLASS_EX_extern(x) x xDEFINE_JCLASS_
#define xDEFINE_JCLASS_END
#define xDEFINE_JCLASS_EX_END

#define DEFINE_JCLASS(c,name,p1,p2,p3,p4,p5,p6)  \
	xDEFINE_JCLASS_HEAD(c,name)  \
	xADD_END(xADD_2(xDEFINE_JCLASS_,p1))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_,p2))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_,p3))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_,p4))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_,p5))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_,p6))  };

#define DEFINE_JCLASS_EX(c,name,p1,p2,p3,p4,p5,p6)  \
	xDEFINE_JCLASS_EX_HEAD(c,name)  \
	xADD_END(xADD_2(xDEFINE_JCLASS_EX_,p1))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_EX_,p2))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_EX_,p3))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_EX_,p4))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_EX_,p5))  \
	xADD_END(xADD_2(xDEFINE_JCLASS_EX_,p6))  };

#define DEFINE_JCLASS_EX_CPP(c) boost::thread_specific_ptr<jclass> c::g_clazz; 
#define DEFINE_JCLASS_EX_CPP_INIT(c,...) boost::thread_specific_ptr<jmethodID> xADD_2(c::g_init,__VA_ARGS__);
#define DEFINE_JCLASS_EX_CPP_METHOD(c,m,...) boost::thread_specific_ptr<jmethodID> xADD_3(c::g_,m,__VA_ARGS__);
#define DEFINE_JCLASS_EX_CPP_FIELD(c,f) boost::thread_specific_ptr<jfieldID> xADD_2(c::g_,f);

#define xJNIType_void "V"
#define xJNIType_jboolean "Z"
#define xJNIType_jbyte "B"
#define xJNIType_jchar "C"
#define xJNIType_jshort "S"
#define xJNIType_jint "I"
#define xJNIType_jlong "J"
#define xJNIType_jfloat "F"
#define xJNIType_jdouble "D"
#define xJNIType_jclass(c) "L"c";"
#define xJNIType_jarray(x) "["xADD_2(xJNIType_,x)
#define xJNIType_jobject xJNIType_jclass("java/lang/Object")
#define xJNIType_jstring xJNIType_jclass("java/lang/String")

#define xJNIType_0_(t) \
	xADD_2(xJNIType_,t) xJNIType_1_
#define xJNIType_1_(t) \
	xADD_2(xJNIType_,t) xJNIType_0_
#define xJNIType_0_END 
#define xJNIType_1_END
#define xJNIType_0_voidEND

#define MakeSig(t)  \
	xADD_2(xJNIType_,t)
#define MakeSigs(params)  \
	xADD_END(xADD_2(xJNIType_0_,params))
#define MakeMethodSig(rt,params) \
	"("MakeSigs(params)")"MakeSig(rt)

