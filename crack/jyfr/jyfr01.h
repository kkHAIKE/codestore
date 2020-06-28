#ifndef _JY_FR01
#define _JY_FR01

class class_100096D0
{
public:
	class_100096D0()
	{
		signed int v1; // eax@1
  int v2; // esi@1
  int v3; // edi@7
  double v4; // st7@7
  int v5; // ecx@7
  int v6; // edx@7
  int v7; // ST3C_4@7
  int v8; // ST44_4@7
  int v9; // edx@7
  int v10; // ecx@7
  int v11; // edi@8
  int v12; // ecx@8
  int v13; // edx@8
  int v14; // ST3C_4@8
  int v15; // ST44_4@8
  int v16; // edx@8
  int v17; // ecx@8
  int v18; // edi@9
  int v19; // ecx@9
  int v20; // edx@9
  int v21; // ST3C_4@9
  int v22; // ST44_4@9
  int v23; // edx@9
  int v24; // ecx@9

		m_part1=0;m_part2[0]=0;
		m_part3=(int*)malloc(5388);
		m_part4=(int*)malloc(5388);
		m_part5=(int*)malloc(5388);
		m_part6=(int*)malloc(5388);
		m_part7=(int*)malloc(5388);
		m_part8=(int*)malloc(5388);
		m_part9=(int*)malloc(5388);
		m_part10=(int*)malloc(5388);
		m_part11=(int*)malloc(5388);
		m_part12=(float*)malloc(5388);
		m_part13=(float*)malloc(5388);

		 v1 = 0;

  do
  {
    switch ( *(int *)((char *)dword_10540E5C + v1) )
    {
      case 1:
        *(int *)((char*)m_part3 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_1054628C + v1)
                                                  + *(int *)((char *)dword_10543874 + v1));
         *(int *)((char*)m_part4 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26 * *(int *)((char *)dword_10543874 + v1);
         *(int *)((char*)m_part5 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_10543874 + v1)
                                                  + 2 * *(int *)((char *)dword_1054628C + v1));
         *(int *)((char*)m_part6+v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_1054628C + v1)
                                                  + *(int *)((char *)dword_10543874 + v1));
       *(int *)((char*)m_part7+ v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26 * *(int *)((char *)dword_10543874 + v1);
        *(int *)((char*)m_part8+v1 ) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_10543874 + v1)
                                                  + 2 * *(int *)((char *)dword_1054628C + v1));
        break;
      case 2:
        *(int *)((char*)m_part3 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 2
                                                 * (*(int *)((char *)dword_10544D80 + v1)
                                                  + 13
                                                  * (*(int *)((char *)dword_1054628C + v1)
                                                   + *(int *)((char *)dword_10543874 + v1)));
        *(int *)((char*)m_part4 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26 * *(int *)((char *)dword_10543874 + v1);
        *(int *)((char*)m_part5 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_1054628C + v1)
                                                  + *(int *)((char *)dword_10543874 + v1));
        *(int *)((char*)m_part6+v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_1054628C + v1)
                                                  + *(int *)((char *)dword_10543874 + v1));
       *(int *)((char*)m_part7+ v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 2
                                                 * (*(int *)((char *)dword_10544D80 + v1)
                                                  + 13 * *(int *)((char *)dword_10543874 + v1));
        *(int *)((char*)m_part8+v1 ) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26 * *(int *)((char *)dword_10543874 + v1);
        break;
      case 3:
        *(int *)((char*)m_part3 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 2
                                                 * (*(int *)((char *)dword_10544D80 + v1)
                                                  + 13
                                                  * (*(int *)((char *)dword_1054628C + v1)
                                                   + *(int *)((char *)dword_10543874 + v1)));
         *(int *)((char*)m_part4 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26 * *(int *)((char *)dword_10543874 + v1);
         *(int *)((char*)m_part5 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_1054628C + v1)
                                                  + *(int *)((char *)dword_10543874 + v1));
        *(int *)((char*)m_part6+v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 2
                                                 * (*(int *)((char *)dword_10544D80 + v1)
                                                  + 13 * *(int *)((char *)dword_10543874 + v1));
        *(int *)((char*)m_part7+ v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 3 * *(int *)((char *)dword_10544D80 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_1054628C + v1)
                                                  + *(int *)((char *)dword_10543874 + v1));
        *(int *)((char*)m_part8+v1 ) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26 * *(int *)((char *)dword_10543874 + v1);
        *(int *)((char*)m_part9+v1 ) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_1054628C + v1)
                                                  + *(int *)((char *)dword_10543874 + v1));
        *(int *)((char*)m_part10+v1 ) = *(int *)((char *)dword_10542368 + v1)
                                                 + 3 * *(int *)((char *)dword_10544D80 + v1)
                                                 + 26 * *(int *)((char *)dword_10543874 + v1);
        break;
      case 4:
        *(int *)((char*)m_part3 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26 * *(int *)((char *)dword_10543874 + v1);
        *(int *)((char*)m_part4 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_1054628C + v1)
                                                  + *(int *)((char *)dword_10543874 + v1));
        *(int *)((char*)m_part5 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_10543874 + v1)
                                                  + 2 * *(int *)((char *)dword_1054628C + v1));
        *(int *)((char*)m_part6 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 2
                                                 * (*(int *)((char *)dword_10544D80 + v1)
                                                  + 13
                                                  * (*(int *)((char *)dword_1054628C + v1)
                                                   + *(int *)((char *)dword_10543874 + v1)));
       *(int *)((char*)m_part7 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + *(int *)((char *)dword_10544D80 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_1054628C + v1)
                                                  + *(int *)((char *)dword_10543874 + v1));
        *(int *)((char*)m_part8 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26 * *(int *)((char *)dword_10543874 + v1);
        *(int *)((char*)m_part9 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 2
                                                 * (*(int *)((char *)dword_10544D80 + v1)
                                                  + 13
                                                  * (*(int *)((char *)dword_10543874 + v1)
                                                   + 2 * *(int *)((char *)dword_1054628C + v1)));
        *(int *)((char*)m_part10 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 26
                                                 * (*(int *)((char *)dword_10543874 + v1)
                                                  + 2 * *(int *)((char *)dword_1054628C + v1));
        *(int *)((char*)m_part11 + v1) = *(int *)((char *)dword_10542368 + v1)
                                                 + 2
                                                 * (*(int *)((char *)dword_10544D80 + v1)
                                                  + 13 * *(int *)((char *)dword_10543874 + v1));
        break;
      case 5:
        v3 = *(int *)((char *)dword_10542368 + v1);
        v5 = *(int *)((char *)dword_10543874 + v1);
        v6 = v5 + *(int *)((char *)dword_1054628C + v1);
        v7 = *(int *)((char *)dword_10544D80 + v1) + v3;

        *(int *)((char*)m_part3 + v1) = v7 + 26 * v6;
        v8 = 2 * (v5 + 4 * (3 * v5 + 3) + 1) - 26;
        *(int *)((char*)m_part4 + v1) = v3 + v8;
        *(int *)((char*)m_part5 + v1) = v3 + 26 * v6;
        *(int *)((char*)m_part6 + v1) = v7 + v8;
        v9 = 2 * (v6 + 4 * (3 * v6 - 3) - 1);
        *(int *)((char*)m_part7 + v1) = v9 + v7 - 1;
        v10 = 2 * (v5 + 4 * (3 * v5 + 6) + 2) - 26;
        *(int *)((char*)m_part8 + v1) = v10 + v3 + 1;
        *(int *)((char*)m_part9 + v1) = v9 + v3 + 1;
        *(int *)((char*)m_part10 + v1) = v10 + v7 - 1;
       *(float *)((char*)m_part12 + v1) = (double)((*(int *)((char *)dword_1054628C + v1) - 2)
                                                         * (*(int *)((char *)dword_10544D80 + v1) - 2))
                                                / (double)(2
                                                         * (*(int *)((char *)dword_1054628C + v1)
                                                          + *(int *)((char *)dword_10544D80 + v1))
                                                         - 4);
        v4 = (double)(*(int *)((char *)dword_1054628C + v1) * *(int *)((char *)dword_10544D80 + v1))
           / (double)(2 * (*(int *)((char *)dword_1054628C + v1) + *(int *)((char *)dword_10544D80 + v1)) - 4);
        goto LABEL_10;
      case 6:
        v11 = *(int *)((char *)dword_10542368 + v1);
        v12 = *(int *)((char *)dword_10543874 + v1);
        v13 = v12 + *(int *)((char *)dword_1054628C + v1);
        v14 = *(int *)((char *)dword_10544D80 + v1) + v11;

        *(int *)((char*)m_part3 + v1) = v14 + 26 * v13;
        v15 = 2 * (v12 + 4 * (3 * v12 + 3) + 1) - 26;
        *(int *)((char*)m_part4 + v1) = v11 + v15;
        *(int *)((char*)m_part5 + v1) = v11 + 26 * v13;
        *(int *)((char*)m_part6 + v1) = v14 + v15;
        v16 = 2 * (v13 + 4 * (3 * v13 - 6) - 2);
        *(int *)((char*)m_part7 + v1) = v16 + v14 - 2;
        v17 = 2 * (v12 + 4 * (3 * v12 + 9) + 3) - 26;
        *(int *)((char*)m_part8 + v1) = v17 + v11 + 2;
        *(int *)((char*)m_part9 + v1) = v16 + v11 + 2;
        *(int *)((char*)m_part10 + v1) = v17 + v14 - 2;
        *(float *)((char*)m_part12 + v1) = (double)((*(int *)((char *)dword_1054628C + v1) - 4)
                                                         * (*(int *)((char *)dword_10544D80 + v1) - 4))
                                                / (double)(4
                                                         * (*(int *)((char *)dword_1054628C + v1)
                                                          + *(int *)((char *)dword_10544D80 + v1))
                                                         - 16);
        v4 = (double)(*(int *)((char *)dword_1054628C + v1) * *(int *)((char *)dword_10544D80 + v1))
           / (double)(4 * (*(int *)((char *)dword_1054628C + v1) + *(int *)((char *)dword_10544D80 + v1)) - 16);
        goto LABEL_10;
      case 7:
        v18 = *(int *)((char *)dword_10542368 + v1);
        v19 = *(int *)((char *)dword_10543874 + v1);
        v20 = v19 + *(int *)((char *)dword_1054628C + v1);
        v21 = *(int *)((char *)dword_10544D80 + v1) + v18;

        *(int *)((char*)m_part3 + v1) = v21 + 26 * v20;
        v22 = 2 * (v19 + 4 * (3 * v19 + 3) + 1) - 26;
        *(int *)((char*)m_part4 + v1) = v18 + v22;
       *(int *)((char*)m_part5 + v1) = v18 + 26 * v20;
       *(int *)((char*)m_part6 + v1) = v21 + v22;
        v23 = 2 * (v20 + 4 * (3 * v20 - 9) - 3);
        *(int *)((char*)m_part7 + v1) = v23 + v21 - 3;
        v24 = 2 * (v19 + 4 * (3 * v19 + 12) + 4) - 26;
        *(int *)((char*)m_part8 + v1) = v24 + v18 + 3;
        *(int *)((char*)m_part9 + v1) = v23 + v18 + 3;
        *(int *)((char*)m_part10 + v1) = v24 + v21 - 3;
        *(float *)((char*)m_part12 + v1) = (double)((*(int *)((char *)dword_1054628C + v1) - 6)
                                                         * (*(int *)((char *)dword_10544D80 + v1) - 6))
                                                / (double)(6
                                                         * (*(int *)((char *)dword_10544D80 + v1)
                                                          + *(int *)((char *)dword_1054628C + v1)
                                                          - 6));
        v4 = (double)(*(int *)((char *)dword_1054628C + v1) * *(int *)((char *)dword_10544D80 + v1))
           / (double)(6 * (*(int *)((char *)dword_10544D80 + v1) + *(int *)((char *)dword_1054628C + v1) - 6));
LABEL_10:
        *(float *)((char*)m_part13 + v1) = v4;
        break;
      default:
        break;
    }
    v1 += 4;
  }
  while ( v1 < 5388 );

	}
	~class_100096D0()
	{
		free(m_part3);
		free(m_part4);
		free(m_part5);
		free(m_part6);
		free(m_part7);
		free(m_part8);
		free(m_part9);
		free(m_part10);
		free(m_part11);
		free(m_part12);
		free(m_part13);
	}
//////////////////////////////////////////////////////////////////////////
	char sub_1000A090(unsigned __int8 * a3, int a4, int a5, int a6, int a7, int a8, int a9)
	{
		return 0;
	}

	char sub_1000A5A0(float *a2);
//////////////////////////////////////////////////////////////////////////
public:
    int m_part1;
	float m_part2[469];
	int *m_part3;
	int *m_part4;
	int *m_part5;
	int *m_part6;
	int *m_part7;
	int *m_part8;
	int *m_part9;
	int *m_part10;
	int *m_part11;
	float *m_part12;
	float *m_part13;
};

//////////////////////////////////////////////////////////////////////////
class class_1000AE60
{
public:
	class_1000AE60()
	{
		a1=a2=a3=a4=a5=a6=0;
		lpMem=NULL;
	}
	~class_1000AE60()
	{
	   class_1000AE60_delete_true();
	}
//////////////////////////////////////////////////////////////////////////
	char class_1000AE60_delete_true()
	{
	  class_1000AE60 *v1; // esi@1
	  void *v2; // ST08_4@2
	  HANDLE v3; // eax@2

	  v1 = this;
	  if ( this->lpMem )
	  {
		v2 = this->lpMem;
		v3 = GetProcessHeap();
		HeapFree(v3, 0, v2);
	  }
	  v1->a5 = 0;
	  v1->a6 = 0;
	  v1->a1 = 0;
	  v1->a2 = 0;
	  v1->a3 = 0;
	  v1->a4 = 0;
	  v1->lpMem = 0;
	  a7.SetSize(0);
	  a8.RemoveAll();
	  return 1;
	}
//////////////////////////////////////////////////////////////////////////
	char class_1000AE60_Set(unsigned __int8 * a2, int a3, int a4, int a5, int a6, int a7, int a8)
	{
	  class_1000AE60 *v8; // ebx@1
	  int v9; // edx@1
	  int v10; // ecx@1
	  int v11; // ST08_4@1
	  HANDLE v12; // eax@1
	  int v13; // eax@2
	  int v14; // ecx@4
	  int v15; // edx@6
	  unsigned int v16; // ecx@7
	  const void *v17; // esi@7
	  void *v18; // edi@7
	  int v19; // ebp@7
	  char result; // al@8

	  v8 = this;
	  this->a1 = a5;
	  this->a2 = a6;
	  this->a3 = a7;
	  this->a4 = a8;
	  v9 = this->a4 - this->a2;
	  v10 = v8->a3 - v8->a1 + 1;
	  v8->a5 = v10;
	  v8->a6 = v9 + 1;
	  v11 = v10 * (v9 + 1);
	  v12 = GetProcessHeap();
	  v8->lpMem = (unsigned __int8 *)HeapAlloc(v12, 8, v11);
	  if ( v8->a1 < 0 || (v13 = v8->a2, v13 < 0) || v8->a3 >= a3 || (v14 = v8->a4, v14 >= a4) )
	  {
		result = 0;
	  }
	  else
	  {
		if ( v13 <= v14 )
		{
		  v15 = a3 * v13;
		  do
		  {
			v16 = v8->a5;
			v17 = &a2[v8->a1] + v15;
			v18 = (char *)v8->lpMem + v16 * (v13 - v8->a2);
			v19 = v8->a5;
			v16 >>= 2;
			memcpy(v18, v17, 4 * v16);
			++v13;
			memcpy((char *)v18 + 4 * v16, (char *)v17 + 4 * v16, v19 & 3);
			v15 += a3;
		  }
		  while ( v13 <= v8->a4 );
		}
		result = 1;
	  }
	  return result;

	}
//////////////////////////////////////////////////////////////////////////
	void sub_1000B230(CArray<SOME_12,SOME_12&> *a2, CArray<SOME_12,SOME_12&> *a3)
	{
		int v3; // ecx@1
  class_1000AE60 *v4; // ebx@1
  int *v5; // eax@1
  int *v6; // eax@2
  int v7; // ebp@4
  int *v8; // eax@5
  int v9; // edx@5
  int v10; // eax@5
  int v11; // ecx@5
  int v12; // ecx@7
  unsigned __int8 v13; // sf@7
  unsigned __int8 v14; // of@7
  int v15; // ebp@9
  int *v16; // eax@10
  int v17; // edx@10
  int v18; // eax@10
  int v19; // ecx@10
  int v20; // ecx@12
  unsigned __int8 v21; // sf@12
  unsigned __int8 v22; // of@12
  int v23; // eax@13
  int v24; // ecx@13
  signed int v25; // esi@13
  int v26; // eax@13
  int v27; // ecx@16
  int v28; // ebx@16
  signed int v29; // ebp@16
  int v30; // edx@18
  int v31; // eax@20
  int v32; // edi@20
  int *v33; // esi@21
  int *v34; // edx@24
  signed int v35; // eax@25
  int v36; // eax@36
  int v37; // ebx@36
  CArray<SOME_12,SOME_12&> *v38; // ebp@36
  int v39; // esi@36
  _SOME_12 *v40; // edx@40
  int i; // ecx@41
  char *v42; // edi@41
  _SOME_12 *v43; // edi@41
  unsigned int v44; // ecx@41
  int v45; // edi@45
  int k; // ecx@47
  _SOME_12 *v47; // edi@47
  _SOME_12 *v48; // edi@47
  int v49; // ecx@51
  int j; // ecx@58
  _SOME_12 *v51; // ebp@58
  int v52; // edi@58
  int v53; // ecx@58
  void *v54; // edi@58
  unsigned int v55; // ecx@58
  char v56; // dl@58
  _SOME_12 *v57; // ecx@63
  signed int v58; // ebx@65
  int v59; // edi@65
  int v60; // esi@65
  int v61; // edx@66
  int *v62; // ecx@67
  unsigned int v63; // ebp@67
  signed int v64; // eax@68
  int v65; // eax@78
  int v66; // ebx@78
  CArray<SOME_12,SOME_12&> *v67; // ebp@78
  int v68; // esi@78
  float v69; // ST6C_4@105
  _SOME_12 *v70; // edx@82
  int l; // ecx@83
  char *v72; // edi@83
  _SOME_12 *v73; // edi@83
  unsigned int v74; // ecx@83
  int v75; // edi@87
  int n; // ecx@89
  int v77; // edi@89
  void *v78; // edi@89
  int v79; // ecx@93
  int m; // ecx@100
  void *v81; // ebp@100
  int v82; // edi@100
  int v83; // ecx@100
  void *v84; // edi@100
  unsigned int v85; // ecx@100
  char v86; // dl@100
  _SOME_12 *v87; // ecx@105
  int v88; // [sp+10h] [bp-78h]@4
  int v89; // [sp+10h] [bp-78h]@8
  int v90; // [sp+10h] [bp-78h]@13
  class_1000AE60 *v91; // [sp+14h] [bp-74h]@1
  int v92; // [sp+18h] [bp-70h]@16
  int v93; // [sp+1Ch] [bp-6Ch]@36
  int v94; // [sp+20h] [bp-68h]@36
  int *v95; // [sp+24h] [bp-64h]@21
  signed int v96; // [sp+24h] [bp-64h]@35
  int v97; // [sp+24h] [bp-64h]@56
  signed int v98; // [sp+24h] [bp-64h]@77
  int v99; // [sp+28h] [bp-60h]@14
  int *v100; // [sp+2Ch] [bp-5Ch]@1
  int *v101; // [sp+30h] [bp-58h]@1
  int *v102; // [sp+34h] [bp-54h]@1
  int v103; // [sp+38h] [bp-50h]@20
  int v104; // [sp+38h] [bp-50h]@98
  int *v105; // [sp+3Ch] [bp-4Ch]@1
  int v106; // [sp+40h] [bp-48h]@13
  int v107; // [sp+44h] [bp-44h]@15
  int v108; // [sp+48h] [bp-40h]@21
  int v109; // [sp+48h] [bp-40h]@36
  int v110; // [sp+48h] [bp-40h]@78
  int v111; // [sp+4Ch] [bp-3Ch]@16
  int v112; // [sp+50h] [bp-38h]@13
  //int v113; // [sp+54h] [bp-34h]@36
  //int v114; // [sp+54h] [bp-34h]@78
  int v115; // [sp+58h] [bp-30h]@36
  int v116; // [sp+58h] [bp-30h]@78
  float v117; // [sp+5Ch] [bp-2Ch]@36
  _SOME_40 v118; // [sp+60h] [bp-28h]@5

  v4 = this;
  v91 = this;
  v105 = (int *)malloc(4 * this->a6 * this->a5);
  v100 = (int *)malloc(4 * v4->a6 * v4->a5);
  v101 = (int *)malloc(4 * v4->a6 * v4->a5);
  v5 = (int *)malloc(4 * v4->a6 * v4->a5);
  v3 = 0;
  v102 = v5;
  if ( v4->a6 * v4->a5 > 0 )
  {
    v6 = v100;
    do
    {
      *(int *)((char *)v6 + (int)v105 - (char *)v100) = 0;
      *v6 = 0;
      *(int *)((char *)v6 + (int)v101 - (char *)v100) = 0;
      *(int *)((char *)v6 + (int)v102 - (char *)v100) = 0;
      ++v3;
      ++v6;
    }
    while ( v3 < v4->a6 * v4->a5 );
  }
  v7 = 0;
  v88 = 0;
  if ( v4->a7.GetSize() > 0 )
  {
    do
    {
      v9 = v4->a5;
      memcpy(&v118, (char *)v4->a7.GetData() + v7, sizeof(v118));
      v10 = v118.a6 - v4->a1;
      v11 = v118.a7 - v4->a2;
      ++v105[v10 + v11 * v9];
      v8 = &v101[v10 + v11 * v4->a5];
      if ( v118.a10 > *v8 )
        *v8 = v118.a10;
      v12 = v4->a7.GetSize();
      v7 += 40;
	  ++v88;
    }
    while ( v88<v12 );
  }
  v89 = 0;
  if ( v4->a8.GetSize() > 0 )
  {
    v15 = 0;
    do
    {
      v17 = v4->a5;
      memcpy(&v118, (char *)v4->a8.GetData() + v15, sizeof(v118));
      v18 = v118.a6 - v4->a1;
      v19 = v118.a7 - v4->a2;
      ++v100[v18 + v19 * v17];
      v16 = &v102[v18 + v19 * v4->a5];
      if ( v118.a10 > *v16 )
        *v16 = v118.a10;
      v20 = v4->a8.GetSize();
      v15 += 40;
	  ++v89;
    }
    while ( v89<v20 );
  }
  v25 = v4->a5;
  v26 = double_to_int64((double)(v25 / 50) + 0.005);
  v106 = v26 + 1;
  v23 = double_to_int64((double)((v26 + 1) / 2) + 0.005) + 1;
  v24 = 0;
  v112 = v23;
  v90 = 0;
  if ( v4->a6 <= 0 )
    goto LABEL_109;
  do
  {
    v99 = 0;
    if ( v25 <= 0 )
      goto LABEL_108;
    v107 = v24 + v23;
    do
    {
      v27 = v99;
      v29 = 0;
      v28 = 0;
      v111 = v99 + v106;
      v92 = v99 + v106;
      if ( v99 + v106 >= v25 )
        v92 = v25;
      v30 = v107;
      if ( v107 >= v91->a6 )
        v30 = v91->a6;
      v31 = v90;
      v103 = v30;
      v32 = v90;
      if ( v90 >= v30 )
        goto LABEL_65;
      v108 = 4 * v25;
      v33 = &v101[v99 + v90 * v25];
      v95 = v33;
      while ( 2 )
      {
        if ( v27 >= v92 )
          goto LABEL_34;
        v34 = v33;
        do
        {
          v35 = *(int *)((char *)v34 + (int)v105 - (char *)v101);
          if ( v35 > v29 )
          {
            v28 = *v34;
            v29 = *(int *)((char *)v34 + (int)v105 - (char *)v101);
LABEL_31:
            v93 = v27;
            v94 = v32;
            goto LABEL_32;
          }
          if ( v35 == v29 && v29 >= 1 && *v34 > v28 )
          {
            v28 = *v34;
            goto LABEL_31;
          }
LABEL_32:
          ++v27;
          ++v34;
        }
        while ( v27 < v92 );
        v33 = v95;
LABEL_34:
        v30 = v103;
        ++v32;
        v33 = (int *)((char *)v33 + v108);
        v95 = v33;
        if ( v32 < v103 )
        {
          v27 = v99;
          continue;
        }
        break;
      }
      v96 = v29;
      if ( v29 > 0 )
      {
        v38 = a2;
        v39 = v91->a1 + v93;
        v115 = v94 + v91->a2;
        v36 = a2->GetSize();
        v117 = (double)v96;
        v109 = v36;
        v37 = v36 + 1;
        //v113 = v91->a1 + v93;
        a2->SetSize(v37);
        v57 = &(*v38)[v109];
        v57->a1 = v39;
        v57->a2 = v115;
        v30 = v103;
        v57->a3 = v117;
      }
      v31 = v90;
LABEL_65:
      v58 = 0;
      v59 = 0;
      v60 = v31;
      if ( v31 >= v30 )
        goto LABEL_106;
      while ( 2 )
      {
        v61 = v99;
        if ( v99 < v92 )
        {
          v62 = &v102[v99 + v60 * v91->a5];
          v63 = (char *)v100 - (char *)v102;
          do
          {
            v64 = *(int *)((char *)v62 + v63);
            if ( v64 <= v58 )
            {
              if ( v64 != v58 || v58 < 1 || *v62 <= v59 )
                goto LABEL_75;
              v59 = *v62;
            }
            else
            {
              v59 = *v62;
              v58 = *(int *)((char *)v62 + v63);
            }
            v93 = v61;
            v94 = v60;
LABEL_75:
            ++v61;
            ++v62;
          }
          while ( v61 < v92 );
        }
        ++v60;
        if ( v60 < v103 )
          continue;
        break;
      }
      v98 = v58;
      if ( v58 > 0 )
      {
        v67 = a3;
        v68 = v91->a1 + v93;
        v116 = v94 + v91->a2;
        v65 = a3->GetSize();
        //v114 = v91->a1 + v93;
        v110 = v65;
        v66 = v65 + 1;
		a3->SetSize(v66);
        v87 = &(*v67)[v110];
        v87->a1 = v68;
        v87->a2 = v116;
        v69 = (double)v98;
        v87->a3 = v69;
      }
LABEL_106:
      v99 += v106;
      v25 = v91->a5;
    }
    while ( v111 < v25 );
    v24 = v90;
    v4 = v91;
    v23 = v112;
LABEL_108:
    v24 += v23;
    v90 = v24;
  }
  while ( v24 < v4->a6 );
LABEL_109:
  free(v105);
  free(v100);
  free(v101);
  free(v102);
	}
//////////////////////////////////////////////////////////////////////////
signed int sub_1000B060();

public:
	int a1;
	int a2;
	int a3;
	int a4;
	int a5;
	int a6;
	unsigned __int8 *lpMem;
	CArray<SOME_40,SOME_40&> a7;
	CArray<SOME_40,SOME_40&> a8;
};

//////////////////////////////////////////////////////////////////////////
class class_1000BCC0
{
public:
	class_1000BCC0()
	{   //此类有继承 
		//m_part1=off_10063670;虚析构
		m_part2[132]=0;
		
	}
	char sub_1000BD00(class_1000AE60 *a2);
public:
	//off_10063670* m_part1;
	unsigned __int8 m_part2[136];
	int m_part3;
};

#endif
