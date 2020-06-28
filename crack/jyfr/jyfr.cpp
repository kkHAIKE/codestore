#include "StdAfx.h"

#include "mytype.h"

EyePos * sub_10008F40(EyePos *a1, unsigned __int8 *a2, int a3, int a4, int a5, int a6, int a7, int a8);
signed int sub_100051A0(unsigned __int8 *a1, int a2, int a3, float *a4, int a5, int a6, int a7, int a8, int a9);
//////////////////////////////////////////////////////////////////////////
// class_10001000_new                                                   10001000  
// class_10001000_delete_true                                           100015F0  
// class_100022E0_new                                                   100022E0  
// class_100022E0_delete                                                10002330  
// class_100022E0_delete_true                                           100025F0  
// class_100031E0_new                                                   100031E0  
// class_100031E0_delete                                                100032A0  
// class_100031E0_delete_true                                           10003420  
// class_10004760_new                                                   10004760  
// class_10004760_delete                                                100047D0  
// class_10004760_delete_true                                           100048B0  
// class_10005DD0_new                                                   10005DD0  
// class_10005DD0_delete                                                10005E10  
// reg_test                                                             100061D0  
// nullsub_3                                                            100062E0  
// reg_test_2                                                           100062F0  
// CArray_32_SetSize                                                    10008000  
// CArray_32_SetAtGrow                                                  10008160  
// CArray_PTR_SOME_32_SetSize                                           100082D0  
// CArray_44_SetSize                                                    10008410  
// CArray_44_SetAtGrow                                                  10008590  
// CArray_12_SetSize                                                    10009410  
// CArray_20_SetSize                                                    10009570  
// class_100096D0_new                                                   100096D0  
// class_100096D0_delete                                                1000A000  
// class_1000AE60_new                                                   1000AE60  
// class_1000AE60_delete                                                1000AEA0  
// class_1000AE60_Set                                                   1000AF30  
// class_1000AE60_delete_true                                           1000B000  
// CArray_40_SetSize                                                    1000BB60  
// class_1000BCC0_new                                                   1000BCC0  
// double_to_int64                                                      10052D1C  
// __alloca_probe                                                       100536E0  
// CArray_PTR_CWordArray_new                                            1005B90B  
// CArray_PTR_CWordArray_delete                                         1005B93E  
// CArray_PTR_CWordArray_SetSize                                        1005B96B  
// CArray_PTR_CWordArray_SetAtGrow                                      1005BA84  
// CWordArray_new                                                       1005BAAB  
// CWordArray_SetAtGrow                                                 1005BC1E  
// malloc                                                               1005BFF2  
// free                                                                 1005C01B  
// CString_FreeData                                                     1005C2BA  
// CString_delete                                                       1005C3AD  
// RtlEnterCriticalSection                                              10063140  
// RtlLeaveCriticalSection                                              10063144  
// InterlockedDecrement                                                 10063178  
// GetProcessHeap                                                       100631B8  
// HeapAlloc                                                            100631BC  
// HeapFree                                                             100631C0  
// vptr_class_100022E0                                                  100633D0  
// vptr_class_100031E0                                                  100633EC  
// vptr_class_10004760                                                  10063410  
// vptr_CArray_PTR_SOME_32_                                             100634F0  
// vptr_class_10005DD0                                                  10063548  
// vptr_CArray_SOME_32_                                                 10063580  
// vptr_CArray_SOME_44_                                                 10063598  
// vptr_CArray_SOME_20_                                                 100635BC  
// vptr_CArray_SOME_12_                                                 100635C8  
// vptr_CArray_SOME_40_                                                 10063630  
// afxEmptyString_m_pchData                                             10551A50  
// _afxDataNil                                                          10551A54   
//////////////////////////////////////////////////////////////////////////
void sub_10006B70(CArray<SOME_32*,SOME_32*&> *a2)
{
  for (int i = 0; i < a2->GetSize(); ++i )
    delete (*a2)[i];
  a2->RemoveAll();
}
//////////////////////////////////////////////////////////////////////////
char sub_10006750(int *a1, int a2, int a3, int a4, int a5, float a6, float a7, float *a8)
{
  int v8; // edi@1
  int *v9; // esi@1
  int v10; // ebx@1
  char result; // al@2
  signed int v12; // ecx@3
  int v13; // edx@4
  double v14; // st7@4
  double v15; // st6@5
  int v16; // eax@6
  int v17; // ecx@6
  int v18; // ebp@7
  double v19; // st6@7
  int v20; // ebx@9
  signed int v21; // ST1C_4@9
  signed int v22; // ST14_4@9
  int v23; // ebx@9
  int v24; // ebp@10
  int v25; // ebx@10
  int v26; // ebp@10
  int v27; // ebx@10
  int v28; // ecx@10
  signed int v29; // [sp+18h] [bp-Ch]@3
  int v30; // [sp+20h] [bp-4h]@4
  int v31; // [sp+28h] [bp+4h]@7
  int v32; // [sp+28h] [bp+4h]@9
  int v33; // [sp+2Ch] [bp+8h]@1
  int v34; // [sp+2Ch] [bp+8h]@8
  int v35; // [sp+2Ch] [bp+8h]@10

  v8 = a2;
  v10 = a2 * (dword_105312F4[0] + a5 + 2 * dword_10537204[0] - 1);
  v9 = a1;
  v33 = double_to_int64((double)(*(&a1[a4 - 1] + dword_1052E36C[0] + a2 * (dword_105312F4[0] + a5 - 1))
                                        + *(&a1[a4 - 1] + dword_1052E36C[0] + v10)
                                        + 2
                                        * (*(&a1[a4 - 1]
                                           + dword_1052E36C[0]
                                           + a2 * (dword_10537204[0] + dword_105312F4[0] + a5 - 1)
                                           + dword_1053427C[0])
                                         - *(&a1[a4 - 1]
                                           + dword_1052E36C[0]
                                           + a2 * (dword_10537204[0] + dword_105312F4[0] + a5 - 1)))
                                        - *(&a1[a4 - 1]
                                          + dword_1052E36C[0]
                                          + a2 * (dword_105312F4[0] + a5 - 1)
                                          + dword_1053427C[0])
                                        - *(&a1[v10 - 1] + a4 + dword_1052E36C[0] + dword_1053427C[0]))
                               * 40.0 / a6);
  if ( (double)v33 >= 355.2936096191406 )
    return 0;
  v12 = 0;
  v29 = 0;
   while ( 2 )
   {
    v13 = *(int *)((char *)dword_1052B3A8 + v12);
    v14 = 0.0;
    v30 = *(int *)((char *)dword_1052B3AC + v12);
    if ( v13 >= *(int *)((char *)dword_1052B3AC + v12) )
      goto LABEL_19;
    //v15 = reinterpret_cast<float>(v33);
    do
    {
      v17 = a5 + dword_105312F4[v13];
      v16 = a4 + dword_1052E36C[v13];
      switch ( dword_1052B3E4[v13]-1 )
      { 
	  case 0:   
	   v18 = dword_10537204[v13];
          v31 = v8 * (v17 - 1);
          v19 = (double)(*(&v9[v16 - 1] + v31)
                       + *(&v9[v16 - 1] + v8 * (v17 + 2 * v18 - 1))
                       + 2
                       * (*(&v9[v16 - 1] + v8 * (v18 - 1 + v17) + dword_1053427C[v13])
                        - *(&v9[v16 - 1] + v8 * (v18 - 1 + v17)))
                       - *(&v9[v16 - 1] + dword_1053427C[v13] + v31)
                       - *(&v9[v16 - 1] + v8 * (v17 + 2 * v18 - 1) + dword_1053427C[v13]));
          goto LABEL_11; 
	case 1: 
		  v34 = v8 * (dword_10537204[v13] + v17 - 1);
          v19 = (double)(*(&v9[v16 - 1] + v34)
                       + *(&v9[2 * dword_1053427C[v13] - 1] + v16 + v34)
                       + 2
                       * (*(&v9[v16 - 1] + v8 * (v17 - 1) + dword_1053427C[v13])
                        - *(&v9[v16 - 1] + dword_1053427C[v13] + v34))
                       - *(&v9[2 * dword_1053427C[v13] - 1] + v16 + v8 * (v17 - 1))
                       - *(&v9[v16 - 1] + v8 * (v17 - 1)));
          goto LABEL_11; 
	case 2 :
		   v20 = dword_10537204[v13];
          v21 = v20;
          v22 = dword_1053427C[v13];
          v23 = v8 * (v20 + v17 - 1);
          v32 = v8 * (v17 - 1);
          v15 = (double)(*(&v9[v16 - 1] + v23)
                       + *(&v9[3 * v22 - 1] + v16 + v32)
                       + 2
                       * (*(&v9[v16 - 1] + v22 + v32)
                        + *(&v9[2 * v22 - 1] + v16 + v23)
                        - *(&v9[v16 - 1] + v23 + v22)
                        - *(&v9[2 * v22 - 1] + v16 + v32))
                       - *(&v9[3 * v22 - 1] + v16 + v23)
                       - *(&v9[v32 - 1] + v16))
              * 40.0
              / a6
              - (double)v22 * (double)v21 * a7;
          break; 
   case 3:  
		 v24 = dword_10537204[v13];
          v25 = v24 - 1 + v17;
          v26 = v8 * (v17 + 2 * v24 - 1);
          v35 = v8 * v25;
          v27 = dword_1053427C[v13];
          v28 = v8 * (v17 - 1);
          v19 = (double)(2
                       * (*(&v9[v16 - 1] + v35)
                        + *(&v9[v16 - 1] + v27 + v26)
                        + *(&v9[2 * v27 - 1] + v16 + v35)
                        + *(&v9[v16 - 1] + v27 + v28)
                        - 2 * *(&v9[v16 - 1] + v27 + v35))
                       - *(&v9[v16 - 1] + v28)
                       - *(&v9[2 * v27 - 1] + v16 + v26)
                       - *(&v9[v16 - 1] + v26)
                       - *(&v9[2 * v27 - 1] + v16 + v28));
LABEL_11:
          v15 = v19 * 40.0 / a6;
          break;
        default:
          break;
      }
      if ( byte_1053D114[v13] )
      {
        if ( v15 >= flt_1053A18C[v13] )
          goto LABEL_17;
      }
      else
      {
        if ( v15 <= flt_1053A18C[v13] )
          goto LABEL_17;
      }
      v14 = v14 + flt_1053DCF8[v13];
LABEL_17:
      ++v13;
    }
    while ( v13 < v30 );
    v33 = v15;
    v12 = v29;
LABEL_19:
    if ( v14 >= *(float *)((char*)flt_10540C84+v12) )
    {
      v12 += 4;
      v29 = v12;
      if ( v12 >= 56 )
      {
        result = 1;
        *a8 = v14 / 17.26079940795898 * 0.5;
        return result;
      }
      continue;
    }
    return 0;
  }
}
//////////////////////////////////////////////////////////////////////////
void sub_10007000(CArray<SOME_44,SOME_44&> *a1, CArray<SOME_44,SOME_44&> *a2)
{
  CArray<SOME_44,SOME_44&> *v2; // ebx@1
  int v3; // ebp@1
  int v4; // edx@6
  int v5; // ebx@6
  _SOME_44 *v6; // esi@6
  int v7; // edx@9
  _SOME_44 *v8; // edi@14
  int v9; // esi@14
  signed int v10; // ecx@15
  _SOME_44 *v11; // esi@15
  int v12; // edx@16
  int v13; // ecx@16
  int v14; // esi@19
  void *v15; // ecx@20
  signed int v16; // [sp+28h] [bp-B4h]@3
  int i; // [sp+28h] [bp-B4h]@18
  CArray<SOME_44,SOME_44&> v27; // [sp+2Ch] [bp-B0h]@1
  int v19; // [sp+40h] [bp-9Ch]@4
  RECT v20; // [sp+44h] [bp-98h]@6
  RECT v21; // [sp+54h] [bp-88h]@7
  _SOME_44 v22; // [sp+64h] [bp-78h]@3
  //int v23; // [sp+90h] [bp-4Ch]@7
  _SOME_44 v24; // [sp+94h] [bp-48h]@6
  RECT v25; // [sp+C0h] [bp-1Ch]@8
  //int v26; // [sp+D8h] [bp-4h]@1

  v3 = 0;
  v2 = a1;
  //v26 = 0;
  if ( !a1->GetSize() )
    return;
  memcpy(&v22, a1->GetData(), sizeof(v22));
  v27.SetSize(1);
  v16 = 1;
  memcpy(v27.GetData(), &v22, 0x2Cu);
  if ( a1->GetSize() <= 1 )
    goto LABEL_18;
  v19 = 44;
  while ( 2 )
  {
    v6 = (_SOME_44 *)((char *)v2->GetData() + v19);
    v5 = 0;
    memcpy(&v24, v6, sizeof(v24));
    v20.top = v24.a2.top;
    v4 = v27.GetSize();
    v20.left = v24.a2.left;
    v20.right = v24.a2.right;
    v20.bottom = v24.a2.bottom;
    if ( v27.GetSize() <= v3 )
    {
LABEL_14:
      v9 = v4;
	  v27.SetSize(v4+1);
      v8 = &v27[v9];
      goto LABEL_15;
    }
    while ( 1 )
    {
      memcpy(&v22, (char *)v27.GetData() + v3, sizeof(v22));
      v21.left = v22.a2.left;
      v21.right = v22.a2.right;
      v21.top = v22.a2.top;
      v21.bottom = v22.a2.bottom;
      //v23 = v24.a1 - v22.a1;
      if ( fabs((double)(v24.a1 - v22.a1)) <= 4.0 )
        break;
LABEL_13:
      ++v5;
      v3 += 44;
      if ( v5 >= v4 )
        goto LABEL_14;
    }
    if ( !IntersectRect(&v25, &v20, &v21) )
      goto LABEL_36;
    v7 = 4 * (v20.right - v20.left) * (v20.bottom - v20.top) / 5;
    if ( 4 * (v21.right - v21.left) * (v21.bottom - v21.top) / 5 < v7 )
      v7 = 4 * (v21.right - v21.left) * (v21.bottom - v21.top) / 5;
    if ( (v25.right - v25.left) * (v25.right - v25.left) < v7 )
    {
LABEL_36:
      v4 = v27.GetSize();
      goto LABEL_13;
    }
    if ( v24.a7 <= v22.a7 )
    {
      if ( v24.a7 >= v22.a7 )
      {
        if ( v24.a5 > v22.a5 )
        {
          v24.a8 += v22.a8;
          v8 = &v27[v5];
          goto LABEL_15;
        }
        v22.a8 += v24.a8;
        v11 = &v22;
        v10 = 11;
        v8 = &v27[v5];
      }
      else
      {
        v22.a8 += v24.a8;
        if ( v24.a5 > v22.a5 )
          v22.a5 = v24.a5;
        v11 = &v22;
        v8 = &v27[v5];
        v10 = 11;
      }
    }
    else
    {
      v24.a8 += v22.a8;
      if ( v24.a5 <= v22.a5 )
        v24.a5 = v22.a5;
      v8 = &v27[v5];
LABEL_15:
      v10 = 11;
      v11 = &v24;
    }
    v2 = a1;
    v12 = v19;
    memcpy(v8, v11, 4 * v10);
    v13 = a1->GetSize();
    ++v16;
    v19 = v12 + 44;
    if ( v16 < v13 )
    {
      v3 = 0;
      continue;
    }
    break;
  }
  v3 = 0;
LABEL_18:
  for ( i = v3; i < v27.GetSize(); ++i )
  {
    memcpy(&v22, (char *)v27.GetData() + v3, sizeof(v22));
    v14 = a2->GetSize();
	a2->SetSize(v14+1);
    v3 += 44;
    memcpy(&(*a2)[v14], &v22, sizeof((*a2)[v14]));
  }
  v27.SetSize(0);
  v27.RemoveAll();
  
  //v26 = 2;
}

//////////////////////////////////////////////////////////////////////////
void sub_100073F0(CArray<SOME_44,SOME_44&> *a1, CArray<SOME_44,SOME_44&> *a2)
{
  CArray<SOME_44,SOME_44&> *v2; // ebx@1
  int v3; // ebp@1
  int v4; // eax@6
  int v5; // ebx@6
  _SOME_44 *v6; // esi@6
  int v7; // eax@8
  int v8; // esi@8
  int v9; // eax@12
  int v10; // esi@12
  signed int v11; // ecx@13
  _SOME_44 *v12; // edi@13
  _SOME_44 *v13; // esi@13
  int v14; // edx@14
  int v15; // ecx@14
  int v16; // esi@17
  void *v17; // ecx@18
  signed int v18; // [sp+1Ch] [bp-B4h]@3
  int i; // [sp+1Ch] [bp-B4h]@16
  CArray<SOME_44,SOME_44&> v29; // [sp+20h] [bp-B0h]@1
  int v21; // [sp+34h] [bp-9Ch]@4
  int v22; // [sp+38h] [bp-98h]@8
  RECT v23; // [sp+3Ch] [bp-94h]@6
  RECT v24; // [sp+4Ch] [bp-84h]@7
  _SOME_44 v25; // [sp+5Ch] [bp-74h]@3
  _SOME_44 v26; // [sp+88h] [bp-48h]@6
  RECT v27; // [sp+B4h] [bp-1Ch]@7
 // int v28; // [sp+CCh] [bp-4h]@1

  v3 = 0;
  v2 = a1;
 // v28 = 0;
  if ( !a1->GetSize() )
    return;
  memcpy(&v25, a1->GetData(), sizeof(v25));
  v29.SetSize(1);
  v18 = 1;
  memcpy(v29.GetData(), &v25, 0x2Cu);
  if ( a1->GetSize() <= 1 )
    goto LABEL_16;
  v21 = 44;
  while ( 1 )
  {
    v6 = (_SOME_44 *)((char *)v2->GetData() + v21);
    v5 = 0;
    memcpy(&v26, v6, sizeof(v26));
    v23.left = v26.a2.left;
    v23.right = v26.a2.right;
    v23.bottom = v26.a2.bottom;
    v4 = v29.GetSize();
    v23.top = v26.a2.top;
    if ( v29.GetSize() <= v3 )
    {
LABEL_12:
      v10 = v4;
	  v29.SetSize(v4+1);
      v9 = 11 * v10;
LABEL_13:
      v13 = &v26;
      v12 = (_SOME_44 *)((char *)v29.GetData() + 4 * v9);
      v11 = 11;
      goto LABEL_14;
    }
    while ( 1 )
    {
      memcpy(&v25, (char *)v29.GetData() + v3, sizeof(v25));
      v24.left = v25.a2.left;
      v24.right = v25.a2.right;
      v24.top = v25.a2.top;
      v24.bottom = v25.a2.bottom;
      if ( IntersectRect(&v27, &v23, &v24) )
      {
        v22 = (v24.right - v24.left) * (v24.bottom - v24.top);
        v8 = double_to_int64((double)v22 * 0.6000000238418579);
        v22 = (v23.right - v23.left) * (v23.bottom - v23.top);
        v7 = double_to_int64((double)v22 * 0.6000000238418579);
        if ( v8 < v7 )
          v7 = v8;
        if ( (v27.right - v27.left) * (v27.right - v27.left) >= v7 )
          break;
      }
      v4 = v29.GetSize();
      ++v5;
      v3 += 44;
      if ( v5 >= v29.GetSize() )
        goto LABEL_12;
    }
    if ( v25.a8 < v26.a8 )
    {
LABEL_22:
      v26.a8 += v25.a8;
      if ( v26.a5 <= v25.a5 )
        v26.a5 = v25.a5;
      v9 = 11 * v5;
      goto LABEL_13;
    }
    if ( v25.a8 <= v26.a8 )
    {
      if ( v25.a5 <= v26.a5 )
        goto LABEL_22;
      v25.a8 += v26.a8;
      if ( v26.a5 > v25.a5 )
        v25.a5 = v26.a5;
      v13 = &v25;
      v11 = 11;
      v12 = &v29[v5];
    }
    else
    {
      v25.a8 += v26.a8;
      if ( v26.a5 > v25.a5 )
        v25.a5 = v26.a5;
      v13 = &v25;
      v12 = &v29[v5];
      v11 = 11;
    }
LABEL_14:
    v2 = a1;
    v14 = v21;
    memcpy(v12, v13, 4 * v11);
    v15 = a1->GetSize();
    ++v18;
    v21 = v14 + 44;
    if ( v18 >= v15 )
      break;
    v3 = 0;
  }
  v3 = 0;
LABEL_16:
  for ( i = v3; i < v29.GetSize(); ++i )
  {
    memcpy(&v25, (char *)v29.GetData() + v3, sizeof(v25));
    v16 = a2->GetSize();
	a2->SetSize(v16+1);
    v3 += 44;
    memcpy(&(*a2)[v16], &v25, sizeof((*a2)[v16]));
  }
  v29.SetSize(0);
  v29.RemoveAll();
  //v28 = 2;
}

//////////////////////////////////////////////////////////////////////////            0.33333
void sub_10008720(unsigned __int8 *pImage, int imgWidth, int imgHeight, double a5, unsigned __int8 *a6, int *a7, int *a8)
{
  int v7; // edi@1
  double v8; // st7@1
  unsigned __int8 *v11; // esi@2
  unsigned __int8 *v13; // ebx@4
  int v14; // edi@4
  double v15; // st7@4
  double v16; // st7@5
  int *v19; // eax@8
  int *v20; // edx@8
  int *v21; // ebp@8
  int v22; // edi@8
  int v23; // esi@8
  int *v24; // eax@8
  int *v25; // eax@9
  int v26; // ebx@9
  //int v27; // ecx@11
  int v28; // eax@12
  int *v29; // ebp@12
  unsigned __int8 *v30; // edi@12
  int v31; // ecx@12
  int *v32; // ecx@13
  int *v33; // eax@14
  int v34; // edx@14
  int *v35; // ebp@14
  int v36; // esi@14
  int v37; // edx@16
  int v38; // edx@16
  char v39; // zf@16
  char v40; // zf@18
  int v41; // [sp+0h] [bp-1Ch]@1
  int *v42; // [sp+4h] [bp-18h]@8
  int v43; // [sp+8h] [bp-14h]@14
  int v45; // [sp+Ch] [bp-10h]@8
  int *v46; // [sp+20h] [bp+4h]@12
  int *v47; // [sp+24h] [bp+8h]@8
  int v48; // [sp+28h] [bp+Ch]@1
  unsigned __int8 *v49; // [sp+28h] [bp+Ch]@12
  int v50; // [sp+2Ch] [bp+10h]@12
  int v51; // [sp+34h] [bp+18h]@14

   v41=imgWidth*a5;
   v48=imgHeight*a5;

  	v11 = a6;
// 	int cc=1.0/a5;
// 	for(int yy=(1.0/a5+1.0)*0.5;yy<imgHeight;yy+=cc)
// 		for(int xx=(1.0/a5+1.0)*0.5;xx<imgWidth;xx+=cc,++v11)
// 			*v11=pImage[imgWidth*yy+xx];
    for(double yy=(1.0/a5+1.0)*0.5;yy<imgHeight+0.5 && v11-a6<v41*v48;yy+=1.0/a5)
 		for(double xx=(1.0/a5+1.0)*0.5;xx<imgWidth+0.5 && v11-a6<v41*v48;xx+=1.0/a5,++v11)
 			*v11=pImage[imgWidth*(int)(yy-0.49999)+(int)(xx-0.49999)];
  
	ASSERT(v11-a6==v41*v48);

  v7=v41;
   v22 = v7 + 1;
  v23 = 4 * v22;
  v45 = 4 * v22;
  v24 = (int *)malloc(4 * v22);
  v21 = v24;
  v42 = v24;
  v19 = (int *)malloc(4 * v22);
  v20 = a7;
  v47 = v19;
  if ( v22 > 0 )
  {
    v26 = (char *)v19 - (char *)a7;
    v25 = a7;
    do
    {
      *(int *)((char *)v25 + (int)v21 - (char *)a7) = 0;
      *v25 = 0;
      *(int *)((char *)v25 + v26) = 0;
      *(int *)((char *)v25 + (int)a8 - (char *)a7) = 0;
      ++v25;
      --v22;
    }
    while ( v22 );
  }
  //v27 = v48 + 1;
  if ( v48 + 1 > 1 )
  {
    v30 = a6;
    v28 = (char *)a8 - (char *)a7;
    v29 = (int *)((char *)a7 + v23);
    v31 = v48;
    v49 = a6;
    v46 = (int *)((char *)a7 + v23);
    v50 = v31;
    do
    {
      v32 = (int *)((char *)v29 + v28);
      *v29 = 0;
      *(int *)((char *)v29 + v28) = 0;
      if ( v41 + 1 > 1 )
      {
        v34 = (char *)v20 - (char *)a8;
        v36 = (char *)v42 - (char *)v47;
        v33 = v47 + 1;
        v35 = v29 + 1;
        v43 = v34;
        v51 = v41;
        while ( 1 )
        {
          ++v33;
          ++v35;
          *(int *)((char *)v33 + v36 - 4) += *v30;
          v37 = *(int *)((char *)v32 + v34);
          ++v32;
          *(v35 - 1) = *(int *)((char *)v33 + v36 - 4) + v37;
          v38 = *v30 * *v30 + *(v33 - 1);
          *(v33 - 1) = v38;
          ++v30;
          *v32 = *(v32 - 1) + v38;
          v39 = v51-- == 1;
          if ( v39 )
            break;
          v34 = v43;
        }
        v20 = a7;
        v23 = v45;
        v28 = (char *)a8 - (char *)a7;
        v29 = v46;
      }
      v30 = &v49[v41];
      v29 = (int *)((char *)v29 + v23);
      //v27 = v50 - 1;
      v40 = v50 == 1;
      v49 += v41;
      v46 = v29;
      --v50;
    }
    while ( !v40 );
  }
  free(v42);
  free(v47);
}
//////////////////////////////////////////////////////////////////////////
void sub_10006BC0(CArray<SOME_32,SOME_32&> *a1, CArray<SOME_44,SOME_44&> *a2)//, int a3)
{
 signed int v3; // edi@1
  int v5; // ebp@2
  CWordArray *v6; // eax@3
  CWordArray *v7; // esi@4
  int v8; // ebp@6
  int v9; // ST08_4@6
  CWordArray *v10; // ecx@10
  int v11; // ebx@10
  WORD *v12; // ebp@11
  unsigned __int8 v13; // sf@16
  unsigned __int8 v14; // of@16
  int v15; // edi@19
  CWordArray *v16; // eax@20
  CWordArray *v17; // esi@21
  int v18; // ST08_4@23
  signed int v19; // edx@26
  _SOME_32 *v20; // ebx@26
  WORD *v21; // ebp@26
  CWordArray *v22; // eax@26
  WORD *v23; // ebp@27
  unsigned __int8 v24; // sf@38
  unsigned __int8 v25; // of@38
  int v26; // esi@39
  int j; // ebp@40
  int v28; // esi@40
  CWordArray *v29; // ecx@41
  int v30; // [sp+10h] [bp-C0h]@6
  signed int v31; // [sp+20h] [bp-B0h]@7
  signed int v32; // [sp+20h] [bp-B0h]@26
  signed int v33; // [sp+24h] [bp-ACh]@6
  int v34; // [sp+28h] [bp-A8h]@8
  signed int i; // [sp+28h] [bp-A8h]@25
  int v36; // [sp+2Ch] [bp-A4h]@6
  CWordArray **v37; // [sp+30h] [bp-A0h]@9
  CWordArray *v38; // [sp+34h] [bp-9Ch]@10
  CArray<CWordArray*,CWordArray*&> v69; // [sp+38h] [bp-98h]@1
  _SOME_32 v40; // [sp+4Ch] [bp-84h]@8
  _SOME_32 v41; // [sp+6Ch] [bp-64h]@12
  int v42; // [sp+8Ch] [bp-44h]@10
  _SOME_32 *v43; // [sp+90h] [bp-40h]@8
  int v44; // [sp+94h] [bp-3Ch]@1
  _SOME_44 v45; // [sp+98h] [bp-38h]@26
  //int v46; // [sp+CCh] [bp-4h]@1

  //v46 = 0;
  v44 = a1->GetSize();
  v3 = v44;
  if ( v44 )
  {
   // LOBYTE(v46) = 1;
	v7=new CWordArray();
    //v30 = v8;
    //LOBYTE(v46) = 0;
    v33 = 1;
	v7->Add(0);
	v69.Add(v7);
    v36 = 1;
    if ( v3 > 1 )
    {
      v31 = 32;
      do
      {
        v34 = 0;
        v43 = a1->GetData();
        memcpy(&v40, (char *)v43 + v31, sizeof(v40));
        if ( v33 <= 0 )
        {
LABEL_20:
          //LOBYTE(v46) = 2;   
		v17=new CWordArray();
          v15 = v36;
          //LOBYTE(v46) = 0;
		  v17->Add(v36);
          ++v33;
		  v69.Add(v17);
        }
        else
        {
          v37 = v69.GetData();
          while ( 1 )
          {
            v11 = 0;
            v10 = *v37;
            v38 = *v37;
            v42 = (*v37)->GetSize();
            if ( v42 <= 0 )
              break;
            v12 = v10->GetData();
            while ( 1 )
            {
              memcpy(&v41, &v43[*v12], sizeof(v41));
              if ( abs(v40.a3 - v41.a3) > 5 )
                break;
              if ( abs(v40.a4 - v41.a4) > 5 )
                break;
              ++v11;
              ++v12;
              if ( v11 >= v42 )
              {
                v10 = v38;
                goto LABEL_19;
              }
            }
			++v37;
			++v34;
			if(v34>=v33)
//             v14 = __SETO__(v34 + 1, v33);
//             v13 = v34++ + 1 - v33 < 0;
//             ++v37;
//             if ( !(v13 ^ v14) )
               goto LABEL_20;
          }
LABEL_19:
          v15 = v36;
		  v10->Add(v36);
        }
        v36 = v15 + 1;
        v31 += 32;
      }
      while ( v15 + 1 < v44 );
    }
    for ( i = 0; i < v33; ++i )
    {
      v22 = v69[i];
      v32 = 1;
      v20 = a1->GetData();
      v21 = v22->GetData();
      memcpy(&v41, &v20[*v21], sizeof(v41));
      v45.a1 = v41.a1;
      v19 = v22->GetSize();
      v45.a5 = v41.a5;
      v40.a1 = v41.a2.left;
      v40.a2.left = v41.a2.top;
      v45.a7 = v19;
      v45.a8 = v19;
      v40.a2.top = v41.a2.right;
      v40.a2.right = v41.a2.bottom;
      if ( v19 > 1 )
      {
        v23 = v21 + 1;
        do
        {
          memcpy(&v41, &v20[*v23], sizeof(v41));
          if ( v45.a5 <= v41.a5 )
            v45.a5 = v41.a5;
          if ( v40.a1 >= v41.a2.left )
            v40.a1 = v41.a2.left;
          if ( v40.a2.left >= v41.a2.top )
            v40.a2.left = v41.a2.top;
          if ( v40.a2.top <= v41.a2.right )
            v40.a2.top = v41.a2.right;
          if ( v40.a2.right <= v41.a2.bottom )
            v40.a2.right = v41.a2.bottom;
          ++v23;
//           v25 = __SETO__(v32 + 1, v19);
//           v24 = v32++ + 1 - v19 < 0;
//         }
//         while ( v24 ^ v25 );
		++v32;
		}
		while(v32<v19);
      }
      v26 = a2->GetSize();
      v45.a2.left = v40.a1;
      v45.a2.top = v40.a2.left;
      v45.a3 = 0;
      v45.a4 = 0;
      v45.a2.bottom = v40.a2.right;
      v45.a2.right = v40.a2.top;
	  a2->SetSize(v26+1);
      memcpy(&(*a2)[v26], &v45, sizeof((*a2)[v26]));
    }
    
    for ( v28 = 0; v28 < v69.GetSize(); ++v28 )//j = v30;
    {
      v29 = v69[v28];
      if ( v29 )
        delete v29;
    }
	v69.SetSize(0);
    //v46 = -1;
  }
  else
  {
    //v46 = -1;
  }
}


//////////////////////////////////////////////////////////////////////////
int sub_10007790(CArray<SOME_32,SOME_32&> *a1, CArray<SOME_32*,SOME_32*&> *a2, int a3)
{
  int v3; // ebp@1
  int result; // eax@2
  int v5; // edx@3
  _SOME_32 *v6; // ebx@4
  int v8; // ebx@10
  _SOME_32 *v9; // eax@13
  int v11; // ebp@17
  int v12; // ebx@18
  _SOME_32 *v13; // eax@26
  LONG v14; // ecx@26
  _SOME_32 *v15; // esi@26
  LONG v16; // eax@26
  LONG v17; // edx@26
  float v18; // eax@26
  int v19; // ecx@26
  int v20; // edx@26
  int v21; // edi@26
  unsigned __int8 v22; // sf@27
  unsigned __int8 v23; // of@27
  int v24; // ebx@28
  _SOME_44 v25; // [sp+48h] [bp-ECh]@14
  int v26; // [sp+74h] [bp-C0h]@17
  int v27; // [sp+84h] [bp-B0h]@4
  int i; // [sp+88h] [bp-ACh]@10
  int v29; // [sp+8Ch] [bp-A8h]@3
  int v30; // [sp+90h] [bp-A4h]@12
  CArray<SOME_44,SOME_44&> v31; // [sp+94h] [bp-A0h]@3
  CArray<SOME_32,SOME_32&> v32; // [sp+A8h] [bp-8Ch]@3
  CArray<SOME_44,SOME_44&> v33; // [sp+BCh] [bp-78h]@23
  CArray<SOME_44,SOME_44&> v34; // [sp+D0h] [bp-64h]@3
  CArray<SOME_44,SOME_44&> v35; // [sp+E4h] [bp-50h]@23
  int v36; // [sp+F8h] [bp-3Ch]@1
  _SOME_44 v37; // [sp+FCh] [bp-38h]@5
  //int v38; // [sp+130h] [bp-4h]@3

  v3 = 0;
  v36 = a1->GetSize();
  if ( v36 )
  {
    //v38 = 0;

    //LOBYTE(v38) = 2;
    v5 = 1000;
    v29 = -1;
    if ( v36 > 0 )
    {
      v6 = a1->GetData();
      v27 = v36;
      do
      {
        memcpy(&v37, v6, 0x20u);
        if ( v29 < v37.a1 )
          v29 = v37.a1;
        if ( v5 > v37.a1 )
          v5 = v37.a1;
        ++v6;
      }
      while ( v27-- != 1 );
    }
    v8 = v5;
    for ( i = v5; v8 <= v29; i = v8 )
    {
      v27 = v3;
	  v32.SetSize(v3);
	  v31.SetSize(v3);
      if ( v36 > v3 )
      {
        v30 = v36;
        do
        {
          v9 = (_SOME_32 *)((char *)a1->GetData() + v3);
          memcpy(&v37, (char *)a1->GetData() + v3, 0x20u);
          if ( v37.a1 == v8 )
          {
            memcpy(&v25, v9, 0x20u);
			v32.Add(*(SOME_32*)&v25);
            ++v27;
          }
          v3 += 32;
        }
        while ( v30-- != 1 );
        if ( v27 )
        {
          sub_10006BC0(&v32, &v31);//, v26);
          v11 = 0;
          if ( v31.GetSize() > 0 )
          {
            v12 = 0;
            do
            {
              memcpy(&v25, (char *)v31.GetData() + v12, sizeof(v25));
			  v34.Add(v25);
              ++v11;
              v12 += 44;
            }
            while ( v11 < v31.GetSize() );
            v8 = i;
          }
        }
        v3 = 0;
      }
      ++v8;
    }
	v32.SetSize(v3);
	v31.SetSize(v3);

    //LOBYTE(v38) = 3;
    sub_10007000(&v34, &v35);
    //LOBYTE(v38) = 4;
    sub_100073F0(&v35, &v33);
    i = v3;
    if ( v33.GetSize() > v3 )
    {
      v27 = v3;
      do
      {
        memcpy(&v37, (char *)v33.GetData() + v27, sizeof(v37));
        if ( v37.a8 >= a3 )
        {
          v13 = (_SOME_32 *)malloc(32);
          v14 = v37.a2.right;
          v15 = v13;
          v16 = v37.a2.top;
          v15->a2.left = v37.a2.left;
          v17 = v37.a2.bottom;
          v15->a2.top = v16;
          v18 = v37.a5;
          v15->a2.right = v14;
          v19 = v37.a3;
          v15->a2.bottom = v17;
          v20 = v37.a4;
          v15->a5 = v18;
          v15->a1 = v3;
          v15->a3 = v19;
          v15->a4 = v20;
          v21 = a2->GetSize();
		  a2->SetSize(v21+1);
          (*a2)[v21] = v15;
        }
		v27 += 44;
		++i;
//         v23 = __SETO__(i + 1, v33.m_nSize);
//         v22 = i++ + 1 - v33.m_nSize < 0;   
//       }
//       while ( v22 ^ v23 );
		}
		while(i<v33.GetSize());
    }
	v34.SetSize(v3);
	v35.SetSize(v3);
	v33.SetSize(v3);

    v24 = a2->GetSize();
	v33.RemoveAll();
    //LOBYTE(v38) = 5;
    v35.RemoveAll(); 
    //LOBYTE(v38) = 6;
    v34.RemoveAll();  
   // LOBYTE(v38) = 7;
    v31.RemoveAll();  
    //LOBYTE(v38) = 8;
    v32.RemoveAll(); 
    //v38 = 9; 
    result = v24;
  }
  else
  {
    result = 0;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////    60              2       2
int sub_10006340(unsigned __int8 *pImage, int imgWidth, int imgHeight, int a4, int a5, int a6, int a7, CArray<SOME_32*,SOME_32*&> *a8)
{
  void *v8; // ebx@1
  int v9; // esi@1
  signed int v10; // eax@3
  int v11; // ebx@3
  signed int v12; // edi@3
  int v13; // eax@3
  int *v14; // edi@5
  int *v15; // esi@5
  int v16; // esi@5
  int v17; // edx@6
  int v18; // ecx@6
  int v19; // ebx@7
  int v20; // edx@8
  int *v21; // esi@8
  int v22; // eax@10
  int v23; // ecx@10
  int v24; // edi@10
  int v25; // eax@10
  double v26; // st7@10
  LONG v27; // esi@12
  LONG v28; // edi@12
  int v29; // edi@12
  int result; // eax@23
  int v31; // edi@24
  _SOME_32 v32; // [sp+20h] [bp-A0h]@12
  float v33; // [sp+40h] [bp-80h]@2
  float v34; // [sp+44h] [bp-7Ch]@2
  int i; // [sp+48h] [bp-78h]@8
  int v36; // [sp+4Ch] [bp-74h]@5
  int a3; // [sp+50h] [bp-70h]@3
  int v38; // [sp+54h] [bp-6Ch]@6
  int v39; // [sp+58h] [bp-68h]@11
  int a2; // [sp+5Ch] [bp-64h]@3
  int v41; // [sp+60h] [bp-60h]@7
  unsigned __int8 *v42; // [sp+64h] [bp-5Ch]@5
  CArray<SOME_32,SOME_32&> v61; // [sp+68h] [bp-58h]@1
  int *v44; // [sp+7Ch] [bp-44h]@6
  int *v45; // [sp+80h] [bp-40h]@8
  int v46; // [sp+84h] [bp-3Ch]@1
  int v47; // [sp+88h] [bp-38h]@6
  int *v48; // [sp+8Ch] [bp-34h]@6
  int *v49; // [sp+90h] [bp-30h]@5
  int v50; // [sp+94h] [bp-2Ch]@1
  int v51; // [sp+98h] [bp-28h]@3
  float v52; // [sp+9Ch] [bp-24h]@3
  int *a1; // [sp+A0h] [bp-20h]@5
  int *v54; // [sp+A4h] [bp-1Ch]@3
  float v55; // [sp+A8h] [bp-18h]@11
  float v56; // [sp+ACh] [bp-14h]@10
  float v57; // [sp+B0h] [bp-10h]@10
  //int v58; // [sp+BCh] [bp-4h]@1
  float v59; // [sp+D4h] [bp+14h]@3
  int v60; // [sp+D4h] [bp+14h]@5

  v9 = 0;
  //v58 = 0;
  v46 = 1;
  v50 = a4;
  if ( a4 <= a5 )
  {
    v34 = (double)imgWidth;
    v33 = (double)imgHeight;
    do
    {
      v59 = 20.0 / (double)v50;
      v13 = double_to_int64(v34 * v59);
      v12 = v13;
      v54 = (int *)v13;
      v10 = double_to_int64(v33 * v59);
      v11 = v12 + 1;
      v51 = v10;
      a2 = v12 + 1;
      a3 = v10 + 1;
      v52 = 1.0 / v59;
      if ( v12 >= 20 )
      {
        if ( v10 >= 20 )
        {
          v16 = 4 * v11 * (v10 + 1);
          v42 = (unsigned __int8 *)malloc(v12 * v10);
          v14 = (int *)malloc(v16);
          a1 = v14;
          v15 = (int *)malloc(v16);
          v49 = v15;
          sub_10008720(pImage, imgWidth, imgHeight, v59, v42, v14, v15);

          v60 = 0;
          v36 = v51 - 19;
          if ( v51 - 19 > 0 )
          {
            v51 = (int)((char *)v54 - 19);
            v17 = a6;
            v38 = a6 * v11;
            v18 = 20 * v11;
            v47 = 20 * v11;
            v44 = v14;
            v48 = v15 + 20;
            do
            {
              v19 = 0;
              v41 = 0;
              if ( v51 > 0 )
              {
                v21 = v48;
                v45 = v44;
                v54 = v48;
                v20 = (char *)v14 - (char *)v49;
                for ( i = (char *)v14 - (char *)v49; ; v20 = i )
                {
                  v22 = 4 * (v18 + v19 + 20);
                  v23 = 4 * (v19 + v18);
                  v24 = *v45 + *(int *)((char *)v14 + v22) - *(int *)((char *)v21 + v20) - *(int *)((char *)a1 + v23);
                  v25 = *(int *)((char *)v49 + v22);
                  //LODWORD(v56) = v24;
                  v26 = (double)v24 * 0.002499999944120646;
                  v56 = sqrt((double)(*(v21 - 20) + v25 - *(int *)((char *)v49 + v23) - *v21) * 0.002499999944120646 - v26 * v26);
                  v57 = 130.0 - v26 * 40.0 / v56;
                  if ( v56 < 6.0 )
                  {
                    v14 = a1;
                  }
                  else
                  {
                    v14 = a1;
                    v39 = v60 + 19;
                    if ( sub_10006750(a1, a2, a3, v19 + 1, v60 + 1, v56, v57, &v55) )
                    {
                      v27 = double_to_int64(((double)v41 + 0.5) * v52);
                      v28 = double_to_int64(((double)v60 + 0.5) * v52);
                      //LODWORD(v57) = v19 + 19;
                     // LODWORD(v57) = double_to_int64(((double)(v19 + 19) + 0.5) * v52);
                      v32.a2.bottom = double_to_int64(((double)v39 + 0.5) * v52);
                      v32.a4 = v60;
                      v32.a1 = v46;
                      v32.a2.top = v28;
                      v29 = v61.GetSize();
                      v32.a5 = v55;
                      v32.a2.left = v27;
                      v32.a2.right = double_to_int64(((double)(v19 + 19) + 0.5) * v52);//LODWORD(v57);
                      v32.a3 = v19;
					  v61.SetSize(v61.GetSize()+1);
                      memcpy(&v61[v29], &v32, sizeof(v61[v29]));
                      v14 = a1;
                      v21 = v54;
                    }
                  }
                  v17 = a6;
                  v19 += a6;
                  v41 = v19;
                  v21 += a6;
                  v54 = v21;
                  v45 += a6;
                  if ( v19 >= v51 )
                    break;
                  v18 = v47;
                }
                v15 = v49;
                v18 = v47;
              }
              v60 += v17;
              v18 += v38;
              v47 = v18;
              v44 += v38;
              v48 += v38;
            }
            while ( v60 < v36 );
          }
          free(v42);
          free(v14);
          free(v15);
        }
      }
      v50 = double_to_int64((double)v50 * 1.25);
      ++v46;
    }
    while ( v50 <= a5 );
    v9 = 0;
  }
  if ( v61.GetSize() == v9 )
  {
    //v58 = 1;
    v61.RemoveAll();
    result = 0;
  }
  else
  {
    sub_10007790(&v61, a8, a7);
	v61.SetSize(v9);

    v31 = a8->GetSize(); 
    //v58 = 2;
    v61.RemoveAll();
    result = v31;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////
int __stdcall junyufr_JY_ExtractFaceFeatureAuto(unsigned __int8 *pImage, int imgWidth, int imgHeight, FaceInfo_t ***pFaceInfoList, int *pFaceCount)
{
  unsigned __int8 *v6; // edi@1
  int result; // eax@2
  double v9; // st7@3
  int v10; // eax@5
  void *v11; // ecx@5
  void *v12; // ecx@9
  FaceInfo_t **v13; // eax@13
  int *v14; // ecx@13
  unsigned __int8 v15; // zf@13
  unsigned __int8 v16; // sf@13
  int v17; // ebx@16
  int v18; // edi@16
  int v19; // esi@16
  EyePos *v20; // eax@16
  int v21; // ST14_4@16
  FaceInfo_t *v22; // eax@18
  int v23; // edx@18
  unsigned __int8 v24; // sf@19
  unsigned __int8 v25; // of@19
  void *v26; // ecx@21
  float v27[400]; // [sp+Ch] [bp-680h]@16
  EyePos a1; // [sp+64Ch] [bp-40h]@16
  double v29; // [sp+664h] [bp-28h]@3
  CArray<SOME_32*,SOME_32*&> v30; // [sp+66Ch] [bp-20h]@1
  //int v31; // [sp+688h] [bp-4h]@1
  int v32; // [sp+6A4h] [bp+18h]@13

  v6 = pImage;
  //v31 = 0;
  if ( pImage )
  {
    v9 = (double)imgWidth * 0.6666666666666666;
    v29 = (double)imgHeight * 0.6666666666666666;
    if ( v9 >= v29 )
      v9 = v29;
    v10 = double_to_int64(v9);
    if ( v10 >= 60 )
    {
      sub_10006340(pImage, imgWidth, imgHeight, 60, v10, 2, 2, &v30);
      if ( v30.GetSize() )
      {
        v13 = (FaceInfo_t **)malloc(4 * v30.GetSize());
        v14 = pFaceCount;
        v32 = 0;
        *pFaceInfoList = v13;
        v15 = v30.GetSize() == 0;
        v16 = v30.GetSize() < 0;
        *v14 = v30.GetSize();
        if ( !(v16 | v15) )
        {
          while ( 1 )
          {
             v20 = sub_10008F40(
                     &a1,
                     v6,
                     imgHeight,
                     imgWidth,
                     v30[v32]->a2.left,
                     v30[v32]->a2.top,
                     v30[v32]->a2.right,
                     v30[v32]->a2.bottom);
            v19 = v20->xleft;
            v18 = v20->yleft;
            v21 = v20->xleft;
            v17 = v20->xright;
            if (sub_100051A0(pImage, imgWidth, imgHeight, &v27, dword_10553068, v21, v18, v17,v20->yright) )
            {
              v22 = (FaceInfo_t *)malloc(1616);
              v23 = v20->yright;
              v22->stEyePos.xleft = v19;
              v22->stEyePos.yleft = v18;
              v22->stEyePos.xright = v17;
              v22->stEyePos.yright = v23;
              memcpy(v22->afFeature, &v27, sizeof(v22->afFeature));
              (*pFaceInfoList)[v32] = v22;
            }
            else
            {
              (*pFaceInfoList)[v32] = 0;
            }
            //v25 = __SETO__(v32 + 1, v30.GetSize());
            //v24v24 = v32++ + 1 - v30.GetSize() < 0;
            //if ( !(v24 ^ v25) )
			++v32;
			if(v32>=v30.GetSize())
              break;
            v6 = pImage;
          }
        }
        sub_10006B70(&v30);
        v30.RemoveAll();
        result = 0;
      }
      else
      {
        v30.RemoveAll();
        result = 1;
      }
    }
    else
    {
      v30.RemoveAll();
      result = 3;
    }
  }
  else
  {
    result = 3;
  }
  return result;
}
