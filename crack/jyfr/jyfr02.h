#ifndef _JY_FR02
#define _JY_FR02
// class class_10006070
// {
// public:
// 
// };
//////////////////////////////////////////////////////////////////////////
class class_10001000
{
	public: 
		class_10001000()
		{
		m_part2=NULL;
		m_part3=NULL;
		m_part4=NULL;
		m_part5=NULL;
		m_part6=NULL;
		m_part7=NULL;
		m_part8=NULL;
		m_part9=NULL;
		m_part10=0;
		m_part11=0
		ZeroMemory(m_part12,sizeof(m_part12));
		m_part13=NULL; 
		m_part14=NULL;
		m_part15=NULL;
		m_part16=NULL;
		m_part17=NULL;
		}
		~class_10001000()
		{
			class_10001000_delete_true();
		}
//////////////////////////////////////////////////////////////////////////
		void class_10001000_delete_true()
		{
			ZeroMemory(m_part12,sizeof(m_part12));
			if(m_part2)free(m_part2);
			if(m_part3)free(m_part3);
			if(m_part4)free(m_part4);
			if(m_part5)free(m_part5);
			if(m_part6)free(m_part6);
			if(m_part7)free(m_part7);
			if(m_part8)free(m_part8);
			if(m_part9)free(m_part9);
			if(m_part13)free(m_part13);
			if(m_part14)free(m_part14);
			if(m_part15)free(m_part15);
			if(m_part16)free(m_part16);
			if(m_part17)free(m_part17);
			m_part10=0;
		}
//////////////////////////////////////////////////////////////////////////
		int sub_10001BD0()
		{
		int result; // eax@2

  if ( m_part10 )
    result = m_part11;
  else
    result = 0;
  return result;
		}
//////////////////////////////////////////////////////////////////////////
		bool sub_10001850()
{
   return m_part12.a3 > 0.0
      && m_part12.a7 > 0.0
      && m_part12.a6 > 0.0
      && m_part12.a8 > 0.0
      && m_part12.a2 > 0
      && m_part12.a1 > 0;

}
//////////////////////////////////////////////////////////////////////////
signed int sub_10001340();
int sub_10002110();
//////////////////////////////////////////////////////////////////////////
int sub_10001EE0()
{
  void *v1; // eax@1
  int v2; // edi@1
  class_10001000 *v3; // esi@1
  int result; // eax@3
  double v5; // st7@5
  float v6; // [sp+8h] [bp-Ch]@1
  float v7; // [sp+Ch] [bp-8h]@1
  float v8; // [sp+10h] [bp-4h]@1

  v3 = this;
  v2 = this->m_part12.a1;
  v7 = this->m_part12.a7;
  v1 = this->m_part9;
  v6 = this->m_part12.a3;
  v8 = this->m_part12.a6;
  if ( v1 )
    free(v1);
  result = (int)malloc(4 * v2);
  v3->m_part9 = (float *)result;
  if ( result )
  {
    v5 = v6;
    if ( v2 > 0 )
    {
      do
      {
        result += 4;
        --v2;
        *(float *)(result - 4) = v5 * v7 * 0.1591549430913783;
        v5 = v5 * v8;
      }
      while ( v2 );
    }
    result = 1;
  }
  return result;
}
//////////////////////////////////////////////////////////////////////////
signed int sub_10001070()
{
  int v1; // ebx@1
  class_10001000 *v2; // edi@1
  int *v3; // esi@8
  signed int result; // eax@9
  signed int v5; // ebp@12
  float *v6; // edi@12
  int v7; // edi@13
  char v8; // zf@14
  int v9; // eax@14
  float v10; // [sp+0h] [bp-4h]@1

  v2 = this;
  v1 = this->m_part12.a1;
  v10 = this->m_part12.a8;
  if ( this->m_part12.a3 <= 0.0 || this->m_part12.a6 <= 0.0 || v1 < 1 || this->m_part12.a7 <= 0.0 || v10 <= 0.0 )
    goto LABEL_23;
  if ( this->m_part4 )
    free(this->m_part4);
  v3 = (int *)malloc(4 * v1);
  v2->m_part4 = v3;
  if ( !v3 )
  {
    class_10001000_delete_true();
    return 0;
  }
  if ( v2->m_part9 || sub_10001EE0() )
  {
    v6 = v2->m_part9;
    v5 = 0;
    if ( v1 > 0 )
    {
      v7 = (char *)v6 - (char *)v3;
      do
      {
        v9 = double_to_int64(*(float *)((char *)v3 + v7) * v10 + 0.5);
        v8 = (v9 & 0x80000001) == 0;
        if ( (v9 & 0x80000001) < 0 )
          v8 = (((v9 & 0x80000001) - 1) | 0xFFFFFFFE) == -1;
        if ( v8 )
          ++v9;
        *v3 = v9;
        v5 += v9 * v9;
        ++v3;
        --v1;
      }
      while ( v1 );
    }
    result = v5;
  }
  else
  {
LABEL_23:
    result = -1;
  }
  return result;
}
//////////////////////////////////////////////////////////////////////////
signed int sub_100018B0()
{
  int v1; // ebx@1
  class_10001000 *v2; // esi@1
  unsigned int v3; // ebp@6
  int *v4; // edi@6
  int i; // ecx@7
  int *v6; // edi@7
  int *v7; // edi@10
  int j; // eax@11
  double v10; // st7@16
  int *v11; // ecx@17
  signed int v12; // eax@18
  float v13; // [sp+10h] [bp-Ch]@1
  float v14; // [sp+14h] [bp-8h]@1
  int v15; // [sp+18h] [bp-4h]@1

  v2 = this;
  v1 = this->m_part12.a1;
  v13 = this->m_part12.a3;
  v14 = this->m_part12.a6;
  v15 = this->m_part12.a5;
  if ( v1 <= 0 )
    return 0;
  if ( v13 <= 0.0 )
    return 0;
  if ( v14 <= 0.0 )
    return 0;
  if ( this->m_part5 )
    free(this->m_part5);
  v3 = 4 * v1;
  v4 = (int *)malloc(4 * v1);
  v2->m_part5 = v4;
  if ( !v4 )
    return 0;
  memset(v4, 0, 4 * (v3 >> 2));
  v6 = &v4[v3 >> 2];
  for ( i = v3 & 3; i; --i )
  {
    *(_BYTE *)v6 = 0;
    v6 = (int *)((char *)v6 + 1);
  }
  v7 = v2->m_part5;
  if ( v2->m_part12.a22 == 1 )
  {
    for ( j = 0; j < v1; v2->m_part5[j - 1] = 1 )
      ++j;
    return 1;
  }
  if ( !v2->m_part9 && !sub_10001EE0() )
    return 0;
  v10 = v13;
  if ( v1 > 0 )
  {
    v11 = v7;
    do
    {
      v12 = v15;
      if ( v15 < 1 )
        v12 = 1;
      v10 = v10 * v14;
      *v11 = v12;
      ++v11;
      --v1;
    }
    while ( v1 );
  }
  return 1;
}
//////////////////////////////////////////////////////////////////////////
signed int sub_100019D0()
{
  int v1; // eax@1
  int v2; // ecx@1
  int v3; // ebx@1
  class_10001000 *v4; // ebp@1
  class_10001000 *v5; // ecx@4
  int v6; // eax@4
  void *v7; // eax@6
  void *v8; // edi@8
  unsigned int v9; // esi@8
  int i; // ecx@9
  int v11; // edi@9
  int *v12; // ebp@12
  void *v13; // eax@14
  class_10001000 *v14; // edx@14
  unsigned int v15; // esi@14
  signed int result; // eax@15
  int j; // ecx@16
  int v18; // edi@16
  int v19; // eax@19
  int *v20; // esi@19
  int v21; // edx@20
  int *v22; // ecx@20
  signed int v23; // eax@21
  int v24; // ebx@21
  signed int v25; // edi@21
  signed int v26; // ecx@22
  int v27; // ebp@32
  int v28; // [sp+10h] [bp-30h]@1
  int v29; // [sp+14h] [bp-2Ch]@21
  int v30; // [sp+18h] [bp-28h]@19
  class_10001000 *v31; // [sp+1Ch] [bp-24h]@1
  int v32; // [sp+20h] [bp-20h]@1
  signed int v33; // [sp+24h] [bp-1Ch]@21
  int *v34; // [sp+28h] [bp-18h]@20
  int *v35; // [sp+2Ch] [bp-14h]@6
  int v36; // [sp+2Ch] [bp-14h]@20
  int *v37; // [sp+34h] [bp-Ch]@6
  int v38; // [sp+38h] [bp-8h]@20
  int v39; // [sp+3Ch] [bp-4h]@1

  v4 = this;
  v31 = v4;
  v3 = this->m_part12.a1;
  v1 = this->m_part12.a9;
  v2 = this->m_part12.a10;
  v28 = v1;
  v32 = v2;
  v39 = v4->m_part12.a2;
  if ( v3 <= 0 || v1 <= 0 || v2 <= 0 )
    return 0;
  v6 = sub_10002110();
  v5 = v4;
  if ( !v6 )
  {
LABEL_36:
    class_10001000_delete_true(v5);
    return 0;
  }
  if ( !sub_100018B0() )
    goto LABEL_40;
  v35 = v4->m_part5;
  v7 = v4->m_part6;
  v37 = v4->m_part8;
  if ( v7 )
    free(v7);
  v9 = 4 * v3;
  v8 = malloc(4 * v3);
  v4->m_part6 = (int *)v8;
  if ( !v8 )
  {
LABEL_40:
    v5 = v4;
    goto LABEL_36;
  }
  memset(v8, 0, 4 * (v9 >> 2));
  v11 = (int)((char *)v8 + 4 * (v9 >> 2));
  for ( i = v9 & 3; i; --i )
    *(_BYTE *)v11++ = 0;
  v12 = v4->m_part6;
  if ( v31->m_part7 )
    free(v31->m_part7);
  v15 = 4 * v3 * v28 * v32;
  v13 = malloc(4 * v3 * v28 * v32);
  v14 = v31;
  v31->m_part7 = (int *)v13;
  if ( v13 )
  {
    memset(v13, 0, 4 * (v15 >> 2));
    v18 = (int)((char *)v13 + 4 * (v15 >> 2));
    for ( j = v15 & 3; j; --j )
      *(_BYTE *)v18++ = 0;
    v20 = v31->m_part7;
    v19 = 0;
    v30 = 0;
    if ( v3 > 0 )
    {
      v22 = v12;
      v21 = (char *)v35 - (char *)v12;
      v34 = v12;
      v38 = (char *)v35 - (char *)v12;
      v36 = v3;
      do
      {
        v25 = *(int *)((char *)v22 + v21);
        v24 = 0;
        v23 = 0;
        v29 = 0;
        v33 = 0;
        if ( v28 > 0 )
        {
          do
          {
            v26 = 0;
            if ( v32 > 0 )
            {
              do
              {
                if ( v23 % v25 || v26 % v25 || v37[v24 + v26] != 1 )
                {
                  *v20 = 0;
                }
                else
                {
                  *v20 = 1;
                  ++v29;
                }
                ++v26;
                ++v20;
              }
              while ( v26 < v32 );
              v23 = v33;
            }
            ++v23;
            v24 += v32;
            v33 = v23;
          }
          while ( v23 < v28 );
          v21 = v38;
          v22 = v34;
          v24 = v29;
        }
        *v22 = v24;
        v27 = v24 + v30;
        ++v22;
        v30 += v24;
        v34 = v22;
        --v36;
      }
      while ( v36 );
      v14 = v31;
      v19 = v27;
    }
    v14->m_part11 = v39 * v19;
    result = 1;
  }
  else
  {
    class_10001000_delete_true(v31);
    result = 0;
  }
  return result;
}
//////////////////////////////////////////////////////////////////////////
bool sub_10002200()
{
  int v1; // ecx@1
  class_10001000 *v2; // esi@1
  int v3; // eax@1
  int v4; // eax@1
  int v5; // edi@1
  int *v6; // edx@2
  int v7; // edi@2
  int v8; // edi@6
  void *v9; // eax@6

  v2 = this;
  v3 = this->m_part12.a9;
  this->m_part13 = 0;
  v4 = this->m_part12.a10 * v3;
  this->m_part14 = 0;
  this->m_part15 = 0;
  v5 = 4 * v4;
  this->m_part16 = 0;
  this->m_part17 = 0;
  this->m_part13 = malloc(4 * v4);
  v2->m_part14 = malloc(v5);
  v2->m_part15 = malloc(v5);
  v1 = 0;
  if ( v2->m_part12.a1 > 0 )
  {
    v6 = v2->m_part4;
    v7 = v2->m_part12.a1;
    do
    {
      if ( v1 < *v6 )
        v1 = *v6;
      ++v6;
      --v7;
    }
    while ( v7 );
  }
  v8 = 4 * (v1 + v2->m_part12.a10) * (v1 + v2->m_part12.a9);
  v2->m_part17 = malloc(v8);
  v9 = malloc(v8);
  v2->m_part16 = v9;
  return v9 && v2->m_part13 && v2->m_part15 && v2->m_part14 && v2->m_part17;
}
//////////////////////////////////////////////////////////////////////////
signed int sub_100015A0()
{

  signed int result; // eax@2

  if ( sub_10001340() )
  {
    if ( sub_100019D0() )
    {
      if ( sub_10002200() )
      {
        result = 1;
      }
      else
      {
        class_10001000_delete_true();
        result = 0;
      }
    }
    else
    {
      class_10001000_delete_true();
      result = 0;
    }
  }
  else
  {
    class_10001000_delete_true();
    result = 0;
  }
  return result;
}
//////////////////////////////////////////////////////////////////////////
	public:
		void *m_part1;//虚
		void* m_part2;
		void* m_part3;
		int* m_part4;
		int* m_part5;
		int* m_part6;
		int* m_part7;
		int* m_part8;
		float* m_part9;
		int m_part10;
		int m_part11;
		SOME_88 m_part12;
		void* m_part13; 
		void* m_part14;
		void* m_part15;
		void* m_part16;
		void* m_part17;
};
//////////////////////////////////////////////////////////////////////////

class class_100022E0
{
public:
	class_100022E0()
	{
	 m_part2=NULL;m_part3=0;m_part5=NULL;m_part6=0;m_part7=NULL;m_part8=NULL;
	 ZeroMemory(m_part4,sizeof(m_part4));
	}
	~class_100022E0()
	{
	class_100022E0_delete_true();
}
//////////////////////////////////////////////////////////////////////////
void	class_100022E0_delete_true()
	{
	int v1; // eax@1
  class_100022E0 *v2; // esi@1
  int v3; // edi@3
  int v4; // ebx@4
  void *v5; // ecx@6
  void *v6; // ecx@8
  void *v7; // eax@9
  void *v8; // eax@11

  v2 = this;
  v1 = this->m_part3;
  if ( v1 > 0 )
  {
    if ( this->m_part2 )
    {
      v3 = 0;
      if ( v1 > 0 )
      {
        v4 = 0;
        do
        {
          sub_100015F0((int)((char *)v2->m_part2 + v4));
          ++v3;
          v4 += 152;
        }
        while ( v3 < v2->m_part3 );
      }
      v5 = v2->m_part2;
      if ( v5 )
        (**(void (__stdcall ***)(_DWORD))v5)(3);
      v6 = v2->m_part5;
      v2->m_part2 = 0;
      free(v6);
      v2->m_part5 = 0;
      v2->m_part3 = 0;
    }
  }
  memset(v2->m_part4, 0, sizeof(v2->m_part4));
  v7 = v2->m_part7;
  v2->m_part6 = 0;
  if ( v7 )
    free(v7);
  v8 = v2->m_part8;
  v2->m_part7 = 0;
  if ( v8 )
    free(v8);
  v2->m_part8 = 0;
	}
//////////////////////////////////////////////////////////////////////////
   int sub_10002340(const void *a2)
   {
		
   }
//////////////////////////////////////////////////////////////////////////
	int sub_10002690()
	{
		
	}
//////////////////////////////////////////////////////////////////////////
public:
	void* m_part1;//虚表
	class_10001000* m_part2;//一个指向152字节的类数组
	int m_part3;//个数
	SOME_88 m_part4;
	SOME_88* m_part5;//指针
	int m_part6;
	void* m_part7;//指针
	void* m_part8;//指针
};

//////////////////////////////////////////////////////////////////////////
class class_10005DD0
{
	public:
		class_10005DD0():m_part2(0),m_part3(0),m_part4(0),m_part5(0){}
	virtual ~class_10005DD0()
{
  if ( m_part2 == 1 )
  {
    if ( m_part5 )
    {
      if ( HeapFree(GetProcessHeap(), 0, m_part5) )
      {
        m_part2 = 0;
        m_part3 = 0;
        m_part4 = 0;
        m_part5 = 0;
      }
    }
  }
}
//////////////////////////////////////////////////////////////////////////
BOOL sub_10005EC0()
{
  class_10005DD0 *v1; // esi@1
  BOOL result; // eax@3
  HANDLE v3; // eax@3
  DWORD v4; // ST08_4@3
  LPVOID v5; // ST0C_4@3

  v1 = this;
  if ( this->m_part2 != 1 || !this->m_part5 )
    goto LABEL_6;
  v3 = GetProcessHeap();
  result = HeapFree(v3, v4, v5);
  if ( result )
  {
    v1->m_part2 = 0;
    v1->m_part3 = 0;
    v1->m_part4 = 0;
    v1->m_part5 = 0;
LABEL_6:
    result = 1;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////
signed int sub_10005E20(int a2, int a3)
{
  class_10005DD0 *v3; // esi@1
  signed int result; // eax@4
  HANDLE v5; // eax@7
  LPVOID v6; // eax@7
  DWORD v7; // ST08_4@7
  SIZE_T v8; // ST0C_4@7

  v3 = this;
  if ( this->m_part2 && this->m_part5 && this->m_part4 * this->m_part3 >= a3 * a2 )
  {
    this->m_part4 = a3;
    this->m_part3 = a2;
    result = 1;
  }
  else
  {
    sub_10005EC0(this);
    if ( a3 * a2 && !v3->m_part2 && (v5 = GetProcessHeap(), v6 = HeapAlloc(v5, v7, v8), v3->m_part5 = v6, v6) )
    {
      result = 1;
      v3->m_part4 = a3;
      v3->m_part3 = a2;
      v3->m_part2 = 1;
    }
    else
    {
      v3->m_part2 = 0;
      v3->m_part5 = 0;
      v3->m_part3 = 0;
      v3->m_part4 = 0;
      result = 0;
    }
  }
  return result;
}
//////////////////////////////////////////////////////////////////////////
signed int sub_10005F00( const void *a2, int a3, int a4)
{
  signed int result; // eax@1
  class_10005DD0 *v5; // edi@1
  void *v6; // edi@3
  unsigned int v7; // ecx@3

  v5 = this;
  result = sub_10005E20(this, a3, a4);
  if ( result )
  {
    v6 = v5->m_part5;
    v7 = (unsigned int)(a4 * a3) >> 2;
    memcpy(v6, a2, 4 * v7);
    result = 1;
    memcpy((char *)v6 + 4 * v7, (char *)a2 + 4 * v7, (_BYTE)a4 * (_BYTE)a3 & 3);
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////	
	public:

	void* m_part1;//虚表
	int m_part2;
	int m_part3;
	int m_part4;
	void* m_part5;//堆
};
//////////////////////////////////////////////////////////////////////////
class class_10004760:public class_10005DD0
{
	public:
		class_10004760():m_part8(90),m_part9(60),m_part12(1),m_part18(0),m_part24(0),m_part25(0),m_part26(NULL)
		{
		ZeroMemory(m_part6,sizeof(m_part6));
		};

	 ~class_10004760()
	{
		class_10004760_delete_true();
	}
//////////////////////////////////////////////////////////////////////////
	void class_10004760_delete_true()
	{
	  if(m_part26)
		free(m_part26);
		m_part18=0;
	   m_part24=0;
		m_part25=0;
		m_part26=0;
		class_10005DD0::~class_10005DD0();
	}
//////////////////////////////////////////////////////////////////////////
	int sub_100048F0(_FUCK_44 *a2);
//////////////////////////////////////////////////////////////////////////
	public:

	unsigned __int8 m_part6[40];
	FUCK_44 m_part7;//15
	int m_part18;
	float m_part19;
	float m_part20;
	float m_part21;
	int m_part22;
	int m_part23;
	int m_part24;
	int m_part25;
	void* m_part26;//34
};
//////////////////////////////////////////////////////////////////////////
class class_100031E0:public class_10004760
{
	public:
	class_100031E0()	
	{
		m_part27=0;m_part28=0;m_part29=NULL;m_part30=NULL;m_part31=NULL;m_part32=0;m_part33=1;m_part34=NULL;,m_part35=0;
		ZeroMemory(m_part36,sizeof(m_part36));
	}

	~class_100031E0()()
	{
		class_100031E0_delete_true();
	}
//////////////////////////////////////////////////////////////////////////
	void class_100031E0_delete_true()
	{
		class_10004760_delete_true();
		if ( m_part34 )
    free(m_part34);
 m_part34 = 0;
  m_part35 = 0;
  if ( m_part29 )
  {
    free(m_part29);
    m_part29 = 0;
  }
m_a2.class_100022E0_delete_true();
  memset(m_part36, 0, sizeof(m_part36));
  m_part28 = 0;
  if ( m_part30 )
  {
    free(m_part30);
    m_part30 = 0;
  }
  if ( m_part31 )
  {
    free(m_part31);
    m_part31 = 0;
  }
  m_part32 = 0;
  m_part33 = 1;
  m_part27 = 0;
	}
//////////////////////////////////////////////////////////////////////////
int sub_10003300(_SOME_664 *a2);

//////////////////////////////////////////////////////////////////////////
signed int sub_100034D0( _SOME_664 *a2)
{
  int v2; // ebx@1
  signed int v3; // edi@2
  char *v4; // esi@3
  signed int v5; // edi@18
  char *v6; // esi@19
  signed int v7; // edi@29
  char *v8; // esi@30

  v2 = a2->a1;
  if ( a2->a1 < 1 )
    return 0;
  v3 = 1;
  if ( a2->a1 > 1 )
  {
    v4 = (char *)&a2->a3.a4;
    while ( a2->a2.a16 == *((float *)v4 + 12)
         && a2->a2.a4 == *(float *)v4
         && a2->a2.a3 == *((float *)v4 - 1)
         && a2->a2.a7 == *((float *)v4 + 3)
         && a2->a2.a6 == *((float *)v4 + 2)
         && a2->a2.a8 == *((float *)v4 + 4)
         && a2->a2.a2 == *((_DWORD *)v4 - 2)
         && a2->a2.a1 == *((_DWORD *)v4 - 3)
         && a2->a2.a15 == *((_DWORD *)v4 + 11)
         && a2->a2.a13 == *((_DWORD *)v4 + 9)
         && a2->a2.a14 == *((_DWORD *)v4 + 10)
         && a2->a2.a9 == *((_DWORD *)v4 + 5)
         && a2->a2.a10 == *((_DWORD *)v4 + 6) )
    {
      ++v3;
      v4 += 88;
      if ( v3 >= v2 )
        goto LABEL_18;
    }
    return 0;
  }
LABEL_18:
  v5 = 1;
  if ( v2 > 1 )
  {
    v6 = (char *)&a2->a8.a4;
    while ( a2->a7.a5 == *((float *)v6 + 1)
         && a2->a7.a4 == *(_DWORD *)v6
         && a2->a7.a2 == *((_DWORD *)v6 - 2)
         && a2->a7.a3 == *((_DWORD *)v6 - 1) )
    {
      ++v5;
      v6 += 44;
      if ( v5 >= v2 )
        goto LABEL_25;
    }
    return 0;
  }
LABEL_25:
  if ( a2->a2.a16 != a2->a7.a5 )
    return 0;
  if ( a2->a2.a15 != a2->a7.a4 || a2->a2.a13 != a2->a7.a2 || a2->a2.a14 != a2->a7.a3 )
    return 0;
  v7 = 1;
  this->m_part33 = 1;
  if ( v2 > 1 )
  {
    v8 = (char *)&a2->a8.a8;
    while ( a2->a7.a7 == *((float *)v8 - 1)
         && a2->a7.a8 == *(float *)v8
         && a2->a7.a9 == *((float *)v8 + 1)
         && a2->a7.a10 == *((float *)v8 + 2)
         && a2->a7.a11 == *((float *)v8 + 3)
         && a2->a7.a6 == *((_DWORD *)v8 - 2) )
    {
      ++v7;
      v8 += 44;
      if ( v7 >= v2 )
        return 1;
    }
    this->m_part33 = 0;
  }
  return 1;
}
//////////////////////////////////////////////////////////////////////////
signed int sub_10004540( unsigned __int8 *a2, int a3, int a4, EyePos *a5, signed int a6, float *a7, signed int a8)
{
  int v9; // ebx@5
  signed int v10; // ebp@7
  EyePos *v11; // edi@8
  float *v12; // esi@8
  class_100031E0 *v13; // [sp+10h] [bp-4h]@1

  v13 = this;
  if ( !this->m_part27 )
    return 0;
  if ( a8 % a6 )
    return 0;
  v9 = a8 / a6;
  if ( a8 / a6 != this->m_part32 )
    return 0;
  v10 = 0;
  if ( a6 > 0 )
  {
    v11 = a5;
    v12 = a7;
    while ( sub_10003F20(this, a2, a3, a4, v11, v12, v9) )
    {
      ++v10;
      v12 += v9;
      ++v11;
      if ( v10 >= a6 )
        return 1;
      this = v13;
    }
    return 0;
  }
  return 1;
}

//////////////////////////////////////////////////////////////////////////
bool sub_100043E0()
{
  class_100031E0 *v1; // esi@1
  bool result; // eax@2
  int *v3; // eax@5
  int v4; // ecx@5
  int v5; // ebx@5
  int *v6; // edi@5
  int v7; // edx@5
  int *v8; // ebp@6
  int v9; // eax@7
  int *v10; // edx@8
  int v11; // ebx@8
  char v12; // zf@11
  int *v13; // eax@15
  int v14; // edi@16
  void *v15; // eax@17
  int v16; // [sp+4h] [bp-14h]@6
  int v17; // [sp+8h] [bp-10h]@5
  int v18; // [sp+Ch] [bp-Ch]@5
  int v19; // [sp+10h] [bp-8h]@5
  int *v20; // [sp+14h] [bp-4h]@5

  v1 = this;
  if ( this->m_part29 )
  {
    if ( this->m_part30 )
      free(this->m_part30);
    v3 = (int *)malloc(4 * v1->m_part28);
    v5 = v1->m_part28;
    v4 = v1->m_part36.a2.a13 * v1->m_part36.a2.a14;
    v6 = v1->m_part29;
    v19 = v1->m_part36.a2.a1;
    v7 = v1->m_part36.a2.a2;
    v20 = v3;
    v1->m_part30 = v3;
    v17 = v5;
    v18 = v7;
    if ( v5 > 0 )
    {
      v8 = v3;
      v16 = v5;
      do
      {
        v9 = 0;
        if ( v4 > 0 )
        {
          v10 = v6;
          v11 = v4;
          do
          {
            v9 += *v10;
            ++v10;
            --v11;
          }
          while ( v11 );
          v5 = v17;
        }
        *v8 = v19 * v18 * v9;
        ++v8;
        v12 = v16 == 1;
        v6 += v4;
        --v16;
      }
      while ( !v12 );
    }
    if ( v1->m_part31 )
      free(v1->m_part31);
    v1->m_part32 = 0;
    if ( v5 > 0 )
    {
      v13 = v20;
      do
      {
        v14 = *v13 + v1->m_part32;
        ++v13;
        --v5;
        v1->m_part32 = v14;
      }
      while ( v5 );
    }
    v15 = malloc(4 * v1->m_part32);
    v1->m_part31 = v15;
    result = v15 != 0;
  }
  else
  {
    result = 0;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////
	public:

int m_part27;//35
int m_part28;
int* m_part29;
int* m_part30;
void* m_part31;
int m_part32;
int m_part33;//41
class_100022E0 m_a2;
void* m_part34;
int m_part35;
_SOME_664 m_part36;

};
#endif