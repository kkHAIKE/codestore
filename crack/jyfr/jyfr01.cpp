#include "StdAfx.h"
#include "mytype.h"
#include "jyfr01.h"


//////////////////////////////////////////////////////////////////////////
void sub_1000AC60(float *a1, int a2, int a3, float *a4)
{
  float *v4; // eax@1
  int v5; // ebp@1
  float *v6; // edi@1
  float *v7; // esi@1
  int v8; // eax@2
  float *v9; // edx@2
  float *v10; // ecx@2
  float *v11; // eax@5
  float *v12; // ebx@5
  float *v13; // edx@7
  float *v14; // ecx@7
  int v15; // edi@7
  float *v16; // esi@7
  double v17; // st7@8
  float *v19; // [sp+10h] [bp-4h]@1
  int v20; // [sp+1Ch] [bp+8h]@5
  int v21; // [sp+24h] [bp+10h]@5

  v5 = a2 + 1;
  v4 = (float *)malloc(4 * (a2 + 1));
  v6 = a4;
  v7 = v4;
  v19 = v4;
  if ( a2 + 1 > 0 )
  {
    v10 = v4;
    v9 = (float *)((char *)a4 - (char *)v4);
    v8 = a2 + 1;
    do
    {
      *(int *)((int)v9 + (int)v10) = 0;
      *(int *)v10 = 0;
      ++v10;
      --v8;
    }
    while ( v8 );
  }
  if ( a3 + 1 > 1 )
  {
    v11 = a1;
    v21 = 4 * a2;
    v12 = &v6[v5];
    v20 = a3;
    do
    {
      *(int *)v12 = 0;
      if ( v5 > 1 )
      {
        v14 = v7 + 1;
        v13 = v12 + 1;
        v16 = v11;
        v15 = v5 - 1;
        do
        {
          v17 = *v16 + *v14;
          ++v16;
          ++v14;
          ++v13;
          --v15;
          *(v14 - 1) = v17;
          *(v13 - 1) = v17 + *(v13 - 2);
        }
        while ( v15 );
        v7 = v19;
      }
      v12 += v5;
      v11 = (float *)((char *)v11 + v21);
    }
    while ( v20-- != 1 );
  }
  free(v7);
}
//////////////////////////////////////////////////////////////////////////
void sub_1000AB90(unsigned __int8 *a1, int a2, int a3, int *a4)
{
  int *v4; // eax@1
  int *v5; // edx@1
  int v6; // ebx@1
  int *v7; // edi@1
  int v8; // esi@1
  int *v9; // eax@2
  int *v10; // ecx@2
  int *v11; // eax@5
  unsigned __int8 *v12; // esi@5
  int *v13; // edx@7
  int *v14; // ecx@7
  int v15; // ebp@7
  int v16; // edi@8
  int v17; // edi@8
  char v18; // zf@10
  int *v19; // [sp+Ch] [bp-8h]@1
  unsigned __int8 *v20; // [sp+24h] [bp+10h]@5

  v8 = a2 + 1;
  v6 = 4 * (a2 + 1);
  v4 = (int *)malloc(4 * (a2 + 1));
  v5 = a4;
  v7 = v4;
  v19 = v4;
  if ( a2 + 1 > 0 )
  {
    v10 = v4;
    v9 = (int *)((char *)a4 - (char *)v4);
    do
    {
      *(int *)((int)v9 + (int)v10) = 0;
      *v10 = 0;
      ++v10;
      --v8;
    }
    while ( v8 );
  }
  if ( a3 + 1 > 1 )
  {
    v12 = a1;
    v20 = a1;
    v11 = (int *)((char *)v5 + v6);
    do
    {
      *v11 = 0;
      if ( a2 + 1 > 1 )
      {
        v13 = v11 + 1;
        v14 = v7 + 1;
        v15 = a2;
        do
        {
          v16 = *v14;
          ++v14;
          v17 = *v12 + v16;
          ++v13;
          *(v14 - 1) = v17;
          ++v12;
          *(v13 - 1) = v17 + *(v13 - 2);
          --v15;
        }
        while ( v15 );
        v7 = v19;
        v6 = 4 * (a2 + 1);
      }
      v12 = &v20[a2];
      v11 = (int *)((char *)v11 + v6);
      v18 = a3 == 1;
      v20 += a2;
      --a3;
    }
    while ( !v18 );
  }
  free(v7);
}
//////////////////////////////////////////////////////////////////////////
void sub_1000AD30(unsigned __int8 *a1, int a2, int a3, int *a4)
{
  int *v4; // eax@1
  int *v5; // edx@1
  int v6; // ebx@1
  int *v7; // edi@1
  int v8; // esi@1
  int *v9; // eax@2
  int *v10; // ecx@2
  int *v11; // eax@5
  unsigned __int8 *v12; // esi@5
  int *v13; // edx@7
  int *v14; // ecx@7
  int v15; // ebp@7
  unsigned __int8 *v16; // edi@7
  int v17; // esi@8
  char v18; // zf@10
  int *v19; // [sp+Ch] [bp-8h]@1
  unsigned __int8 *v20; // [sp+24h] [bp+10h]@5

  v8 = a2 + 1;
  v6 = 4 * (a2 + 1);
  v4 = (int *)malloc(4 * (a2 + 1));
  v5 = a4;
  v7 = v4;
  v19 = v4;
  if ( a2 + 1 > 0 )
  {
    v10 = v4;
    v9 = (int *)((char *)a4 - (char *)v4);
    do
    {
      *(int *)((int)v9 + (int)v10) = 0;
      *v10 = 0;
      ++v10;
      --v8;
    }
    while ( v8 );
  }
  if ( a3 + 1 > 1 )
  {
    v12 = a1;
    v20 = a1;
    v11 = (int *)((char *)v5 + v6);
    do
    {
      *v11 = 0;
      if ( a2 + 1 > 1 )
      {
        v14 = v7 + 1;
        v13 = v11 + 1;
        v16 = v12;
        v15 = a2;
        do
        {
          ++v14;
          ++v13;
          v17 = *v16 * *v16 + *(v14 - 1);
          *(v14 - 1) = v17;
          ++v16;
          *(v13 - 1) = v17 + *(v13 - 2);
          --v15;
        }
        while ( v15 );
        v7 = v19;
        v6 = 4 * (a2 + 1);
      }
      v12 = &v20[a2];
      v11 = (int *)((char *)v11 + v6);
      v18 = a3 == 1;
      v20 += a2;
      --a3;
    }
    while ( !v18 );
  }
  free(v7);
}

//////////////////////////////////////////////////////////////////////////
int sub_1000AE10(int *a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  return *(&a1[a4 - 1] + a2 * (a5 - 1)) + a1[a7 * a2 + a6] - a1[a2 * (a5 - 1) + a6] - *(&a1[a4 - 1] + a7 * a2);
}
//////////////////////////////////////////////////////////////////////////
int sub_1000AA20(unsigned __int8 *a1, signed int a2, signed int a3, signed int a4, signed int a5, unsigned __int8 *a6)
{
  int result; // eax@1
  unsigned __int8 *v7; // ebx@1
  float v8; // ST10_4@3
  signed int v9; // esi@2
  int v10; // edi@3
  int v11; // ebp@4
  int v12; // eax@5
  unsigned __int8 *v13; // ecx@5
  unsigned __int8 v14; // al@7
  unsigned __int8 v15; // sf@15
  unsigned __int8 v16; // of@15
  unsigned __int8 v17; // sf@16
  unsigned __int8 v18; // of@16
  float v19; // [sp+4h] [bp-Ch]@1
  signed int v20; // [sp+18h] [bp+8h]@3
  signed int v21; // [sp+28h] [bp+18h]@1

  result = a5;
  v7 = a6;
  v21 = 0;
  v19 = (double)a2 / (double)a4;
  if ( a5 > 0 )
  {
    v9 = a2;
    while ( 1 )
    {
      v8 = (double)a3 / (double)a5;
      v10 = double_to_int64((double)v21 * v8);
      v20 = 0;
      if ( a4 > 0 )
        break;
LABEL_16:
      result = v21 + 1;
	  ++v21;
      if ( v21>=a5 )
        return result;
    }
    v11 = a3 - 1;
    while ( 1 )
    {
      v12 = double_to_int64((double)v20 * v19);
      v13 = &a1[v9 * v10] + v12;
      if ( v10 != v11 )
      {
        if ( v12 != v9 - 1 )
        {
          v14 = double_to_int64(((double)v13[v9 + 1] + (double)v13[v9] + (double)v13[1] + (double)*v13) * 0.25);
          goto LABEL_15;
        }
        if ( v10 != v11 )
        {
          if ( v12 == v9 - 1 )
          {
            v14 = double_to_int64(((double)v13[v9] + (double)*v13) * 0.5);
            goto LABEL_15;
          }
          if ( v10 != v11 )
            goto LABEL_14;
        }
      }
      if ( v12 == v9 - 1 )
      {
LABEL_14:
        v14 = *v13;
        goto LABEL_15;
      }
      v14 = double_to_int64(((double)v13[1] + (double)*v13) * 0.5);
LABEL_15:
      *v7++ = v14;
	  ++v20;
      if ( v20>=a4 )
        goto LABEL_16;
    }
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////
void __stdcall sub_1000A940(unsigned __int8 *a2, int a3, int a4, int a5, int a6, unsigned __int8 *a7)
{
	unsigned __int8 *v11=a7;
    for(double yy=(((double)a4/(double)a6)+1.0)*0.5;yy<a4+0.5 && v11-a2<a5*a6;yy+=((double)a4/(double)a6))
 	   for(double xx=(((double)a3/(double)a5)+1.0)*0.5;xx<a3+0.5 && v11-a2<a5*a6;xx+=((double)a3/(double)a5),++v11)
 			*v11=a2[a3*(int)(yy-0.49999)+(int)(xx-0.49999)];
}
//////////////////////////////////////////////////////////////////////////
signed int class_1000AE60::sub_1000B060()
{
class_1000AE60 *v1; // ebp@1
  signed int v2; // esi@1
  signed int result; // eax@2
  signed int v4; // ecx@3
  unsigned __int8 *v5; // ebx@3
  unsigned __int8 *v6; // edi@3
  unsigned __int8 *v7; // eax@4
  signed int v8; // esi@4
  double v9; // st7@4
  signed int v10; // edx@5
  unsigned __int8 *v11; // eax@6
  signed int v12; // esi@6
  double v13; // st5@6
  double v14; // st7@6
  signed int v15; // edx@7
  signed int v16; // eax@12
  double v17; // st7@13
  float *v18; // edx@14
  signed int v19; // ecx@14
  double v20; // st7@14
  float v21; // [sp+8h] [bp-1E4h]@8
  signed int v22; // [sp+8h] [bp-1E4h]@14
  float v23[40]; // [sp+Ch] [bp-1E0h]@9
  float v24[40]; // [sp+ACh] [bp-140h]@6
  float v25[40]; // [sp+14Ch] [bp-A0h]@4

  v1 = this;
  v2 = 40 * this->a6 / this->a5;
  if ( v2 >= 20 )
  {
    v5 = (unsigned __int8 *)malloc(40 * v2);
    sub_1000A940(v1->lpMem, v1->a5, v1->a6, 40, v2, v5);
    v6 = v5;
    v4 = 0;
    do
    {
      *(int *)((char *)v25 + v4) = 0;
      v7 = v6;
      v9 = *(float *)((char *)v25 + v4);
      v8 = 15;
      do
      {
        v10 = *v7;
        v7 += 40;
        --v8;
        v9 = v9 + (double)v10;
      }
      while ( v8 );
      *(float *)((char *)v25 + v4) = v9;
      v14 = *(float *)((char *)v25 + v4) * 0.06666666666666667;
      *(int *)((char *)v24 + v4) = 0;
      v11 = v6;
      v12 = 15;
      *(float *)((char *)v25 + v4) = v14;
      v13 = *(float *)((char *)v24 + v4);
      do
      {
        v15 = *v11;
        v11 += 40;
        --v12;
        v13 = v13 + ((double)v15 - v14) * ((double)v15 - v14);
      }
      while ( v12 );
      *(float *)((char *)v24 + v4) = v13;
      v21 = sqrt(*(float *)((char *)v24 + v4) * 0.06666666666666667);
      *(float *)((char *)v24 + v4) = v21;
      if ( v21 >= 0.05 )
        *(float *)((char *)v23 + v4) = v14 * 10.0 / v21;
      else
        *(DWORD *)((char *)v23 + v4) = 1176256512;
      v4 += 4;
      ++v6;
    }
    while ( v4 < 160 );
    v16 = 0;
    do
    {
      v17 = *(float *)((char *)&v23[9] + v16) + *(float *)((char *)&v23[10] + v16);
      v16 += 4;
      *(float *)((char *)&v24[9] + v16) = (v17 + *(float *)((char *)&v23[10] + v16)) * 0.3333333333333333;
    }
    while ( v16 < 80 );
    v20 = 0.0;
    v18 = &v23[17];
    memcpy(&v23[10], &v24[10], 0x50u);
    v19 = 17;
    v22 = 17;
    do
    {
      if ( v20 < *v18 )
      {
        v20 = *v18;
        v22 = v19;
      }
      ++v19;
      ++v18;
    }
    while ( v19 < 23 );
    free(v5);
    result = double_to_int64(((double)v22 * 0.025 + 0.0125) * (double)v1->a5);
  }
  else
  {
    result = -1;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////
char class_100096D0::sub_1000A5A0(float *a2)
{
  int v2; // edx@1
  signed int v3; // ebp@1
  class_100096D0 *v4; // esi@1
  double v5; // st7@1
  int v6; // ecx@2
  double v7; // st6@2
  double v8; // st5@3
  double v9; // st5@5
  float *v10; // eax@5
  double v11; // st5@6
  float *v12; // eax@6
  int v13; // edx@7
  float *v14; // eax@7
  float *v15; // edi@7
  float *v16; // ebx@7
  double v17; // st5@7
  float *v18; // eax@8
  double v19; // st5@8
  char result; // al@21
  int v21; // [sp+10h] [bp-68Ch]@2
  int v22; // [sp+14h] [bp-688h]@1
  float v23; // [sp+18h] [bp-684h]@3
  float v24[416]; // [sp+1Ch] [bp-680h]@1

  v4 = this;
  sub_1000AC60(this->m_part2, 25, 15, v24);
  v5 = 0.0;
  v3 = (signed int)((char *)flt_10540DB4 - 16);
  v2 = 0;
  v22 = 0;
  while ( 2 )
  {
    v6 = *(int *)((char *)dword_10540D8C + v2);
    v7 = 0.0;
    v21 = *(int *)((char *)dword_10540D90 + v2);
    if ( v6 >= *(int *)((char *)dword_10540D90 + v2) )
      goto LABEL_17;
    v8 = v23;
    do
    {
      switch ( dword_10540E5C[v6]-1 )
      {
        case 0:
          v9 = v24[v4->m_part3[v6]];
          v10 = &v24[v4->m_part6[v6]];
          v8 = v9
             + v9
             + v24[v4->m_part5[v6]]
             + v24[v4->m_part4[v6]]
             - *v10
             - *v10
             - v24[v4->m_part7[v6]]
             - v24[v4->m_part8[v6]];
          break;
        case 1:
          v11 = v24[v4->m_part4[v6]];
          v12 = &v24[v4->m_part6[v6]];
          v8 = v11
             + v11
             + v24[v4->m_part5[v6]]
             + v24[v4->m_part3[v6]]
             - *v12
             - *v12
             - v24[v4->m_part7[v6]]
             - v24[v4->m_part8[v6]];
          break;
        case 2:
          v13 = v4->m_part3[v6];
          v14 = &v24[v4->m_part4[v6]];
          v15 = &v24[v4->m_part5[v6]];
          v16 = &v24[v4->m_part6[v6]];
          v17 = *v14 + v24[v13] - *v15 - *v16 + *v14 + v24[v13];
          v2 = v22;
          v8 = v17
             - *v15
             - *v16
             - (v24[v4->m_part8[v6]]
              + v24[v4->m_part7[v6]]
              - v24[v4->m_part9[v6]]
              - v24[v4->m_part10[v6]]);
          break;
        case 3:
          v18 = &v24[v4->m_part7[v6]];
          v19 = v24[v4->m_part6[v6]] + v24[v4->m_part5[v6]] + v24[v4->m_part4[v6]] + v24[v4->m_part3[v6]];
          v8 = v19
             + v19
             - *v18
             - *v18
             - *v18
             - *v18
             - v24[v4->m_part8[v6]]
             - v24[v4->m_part9[v6]]
             - v24[v4->m_part10[v6]]
             - v24[v4->m_part11[v6]];
          break;
        case 4:case 5:case 6:
          v8 = (v24[v4->m_part4[v6]] + v24[v4->m_part3[v6]] - v24[v4->m_part5[v6]] - v24[v4->m_part6[v6]])
             * v4->m_part12[v6]
             - (v24[v4->m_part8[v6]] + v24[v4->m_part7[v6]] - v24[v4->m_part9[v6]] - v24[v4->m_part10[v6]])
             * v4->m_part13[v6];
          break;
        default:
          break;
      }
      if ( byte_10548CA4[v6] )
      {
        if ( v8 >= flt_10547798[v6] )
          goto LABEL_15;
      }
      else
      {
        if ( v8 <= flt_10547798[v6] )
          goto LABEL_15;
      }
      v7 = v7 + flt_105491E8[v6];
LABEL_15:
      ++v6;
    }
    while ( v6 < v21 );
    v23 = v8;
LABEL_17:
    if ( v7 >= *(float *)((char*)flt_1054A6F4+v2) )
    {
      if ( v3 >= (signed int)flt_10540DB4 )
        v5 = ((v7 - *(float *)((char*)flt_1054A6F4+v2)) / (*(float *)((char*)flt_1054A6F4+v2) - *(float *)v3 * 0.5) + 1.0) * 50.0 + v5;
      v3 += 4;
      v2 += 4;
      v22 = v2;
      if ( v3 >= (signed int)dword_10540DC8 )
      {
        result = 1;
        *a2 = v5 * 0.2000000029802322;
        return result;
      }
      continue;
    }
    return 0;
  }
}
//////////////////////////////////////////////////////////////////////////
char __stdcall sub_1000CBB0(int *a1, int a2, int a3, int a4, int a5, float a6, float a7, int *a8)
{
  int v8; // edx@1
  int v9; // ecx@1
  int *v10; // edi@1
  double v11; // st7@1
  int v12; // ebp@2
  int v13; // ebx@3
  int v14; // esi@3
  int v15; // edx@4
  double v16; // st7@4
  int v17; // ecx@4
  int v18; // eax@4
  int v19; // ebx@4
  int v20; // edx@4
  int v21; // eax@5
  int v22; // ST4C_4@5
  int v23; // eax@6
  signed int v24; // ST48_4@6
  int v25; // eax@6
  int v26; // ST4C_4@6
  int v27; // edx@7
  int v28; // eax@7
  int v29; // ecx@7
  int v30; // ebx@7
  int v31; // ST48_4@8
  int v32; // ST4C_4@8
  int v33; // ST54_4@8
  int v34; // eax@8
  int v35; // ST48_4@8
  int v36; // ST64_4@8
  int v37; // ST4C_4@9
  int v38; // ST54_4@9
  int v39; // ST48_4@9
  int v40; // ST64_4@9
  int v41; // ST4C_4@10
  int v42; // ST54_4@10
  int v43; // ST48_4@10
  int v44; // ST64_4@10
  unsigned __int8 v45; // sf@22
  unsigned __int8 v46; // of@22
  float v48; // [sp+8h] [bp-18h]@2
  int v49; // [sp+10h] [bp-10h]@1
  int v50; // [sp+14h] [bp-Ch]@1
  signed int v51; // [sp+18h] [bp-8h]@1
  signed int v52; // [sp+24h] [bp+4h]@6
  int v53; // [sp+24h] [bp+4h]@7
  int v54; // [sp+24h] [bp+4h]@8
  int v55; // [sp+24h] [bp+4h]@9
  int v56; // [sp+24h] [bp+4h]@10

  v11 = *(float *)&a2;
  v9 = 0;
  v8 = (int)((char*)flt_1054A794-8);
  v10 = a1;
  v51 = 0;
  v50 = (int)((char*)flt_1054A794-8);
  v49 = 0;
  while ( 2 )
  {
    v12 = *(int *)((char *)dword_1054A774 + v9);
    *(int*)(&v48) = 0;
    if ( v12 >= *(int *)((char *)dword_1054A778 + v9) )
      goto LABEL_19;
    do
    {
      v14 = a4 + dword_1054DFB4[v12];
      v13 = a5 + dword_1054E674[v12];
      switch ( dword_1054D8F4[v12]-1 )
      {
        case 0:
          v15 = dword_1054F3F4[v12];
          v17 = a2 * (v13 - 1);
          v18 = v15 + v13 - 1;
          v19 = a2 * (v13 + 2 * v15 - 1);
          v20 = dword_1054ED34[v12];
          v16 = (double)(*(&v10[v14 - 1] + v17)
                       + *(&v10[v14 - 1] + v19)
                       + 2 * (*(&v10[v14 - 1] + v20 + a2 * v18) - *(&v10[v14 - 1] + a2 * v18))
                       - *(&v10[v14 - 1] + v17 + v20)
                       - *(&v10[v14 - 1] + v19 + v20));
          goto LABEL_11;
        case 1:
          v21 = a2 * (dword_1054F3F4[v12] + v13 - 1);
          v22 = a2 * (v13 - 1);
          v16 = (double)(*(&v10[v14 - 1] + v21)
                       + *(&v10[2 * dword_1054ED34[v12] - 1] + v14 + v21)
                       + 2
                       * (*(&v10[v14 - 1] + dword_1054ED34[v12] + v22) - *(&v10[v14 - 1] + dword_1054ED34[v12] + v21))
                       - *(&v10[2 * dword_1054ED34[v12] - 1] + v14 + v22)
                       - *(&v10[v14 - 1] + v22));
          goto LABEL_11;
        case 2:
          v23 = dword_1054F3F4[v12];
          v52 = v23;
          v24 = dword_1054ED34[v12];
          v25 = a2 * (v23 + v13 - 1);
          v26 = a2 * (v13 - 1);
          v11 = (double)(*(&v10[v14 - 1] + v25)
                       + *(&v10[3 * v24 - 1] + v14 + v26)
                       + 2
                       * (*(&v10[v14 - 1] + v26 + v24)
                        + *(&v10[2 * v24 - 1] + v14 + v25)
                        - *(&v10[v14 - 1] + v24 + v25)
                        - *(&v10[2 * v24 - 1] + v14 + a2 * (v13 - 1)))
                       - *(&v10[3 * v24 - 1] + v14 + v25)
                       - *(&v10[v26 - 1] + v14))
              * 40.0
              / a6
              - (double)v24 * (double)v52 * a7;
          break;
        case 3:
          v27 = dword_1054F3F4[v12];
          v28 = dword_1054ED34[v12];
          v29 = a2 * (v27 + v13 - 1);
          v53 = a2 * (v13 + 2 * v27 - 1);
          v30 = a2 * (v13 - 1);
          v16 = (double)(2
                       * (*(&v10[v14 - 1] + v29)
                        + *(&v10[v14 - 1] + v28 + v53)
                        + *(&v10[2 * v28 - 1] + v14 + v29)
                        + *(&v10[v14 - 1] + v28 + v30)
                        - 2 * *(&v10[v14 - 1] + v28 + v29))
                       - *(&v10[v14 - 1] + v30)
                       - *(&v10[2 * v28 - 1] + v14 + v53)
                       - *(&v10[v14 - 1] + v53)
                       - *(&v10[2 * v28 - 1] + v14 + v30));
          goto LABEL_11;
        case 4:
          v31 = dword_1054ED34[v12];
          v32 = dword_1054F3F4[v12] + v13 - 1;
          v33 = v31 + v14 - 1;
          v34 = v31 + v14 - 2;
          v35 = dword_1054ED34[v12];
          v54 = dword_1054F3F4[v12];
          v36 = v54
              * v35
              * sub_1000AE10(v10, a2, a3, v14 + 1, v13 + 1, v34, dword_1054F3F4[v12] + v13 - 2)
              / (2
               * (2 - v35 - v54));
          v16 = (double)((v54 - 2) * (v35 - 2) * sub_1000AE10(v10, a2, a3, v14, v13, v33, v32) / (2 * (v54 + v35) - 4)
                       + v36);
          goto LABEL_11;
        case 5:
          v37 = dword_1054F3F4[v12] + v13 - 1;
          v38 = dword_1054ED34[v12] + v14 - 1;
          v39 = dword_1054ED34[v12];
          v55 = dword_1054F3F4[v12];
          v40 = v55
              * v39
              * sub_1000AE10(
                  v10,
                  a2,
                  a3,
                  v14 + 2,
                  v13 + 2,
                  dword_1054ED34[v12] + v14 - 3,
                  dword_1054F3F4[v12] + v13 - 3)
              / (4
               * (4 - v39 - v55));
          v16 = (double)((v55 - 4) * (v39 - 4) * sub_1000AE10(v10, a2, a3, v14, v13, v38, v37) / (4 * (v55 + v39) - 16)
                       + v40);
          goto LABEL_11;
        case 6:
          v41 = dword_1054F3F4[v12] + v13 - 1;
          v42 = dword_1054ED34[v12] + v14 - 1;
          v43 = dword_1054ED34[v12];
          v56 = dword_1054F3F4[v12];
          v44 = v56
              * v43
              * sub_1000AE10(
                  v10,
                  a2,
                  a3,
                  v14 + 3,
                  v13 + 3,
                  dword_1054ED34[v12] + v14 - 4,
                  dword_1054F3F4[v12] + v13 - 4)
              / (6
               * (6 - v43 - v56));
          v16 = (double)((v56 - 6) * (v43 - 6) * sub_1000AE10(v10, a2, a3, v14, v13, v42, v41) / (6 * (v43 + v56 - 6))
                       + v44);
LABEL_11:
          v11 = v16 * 40.0 / a6;
          break;
        default:
          break;
      }
      if ( byte_10550174[v12] )
      {
        if ( v11 >= flt_1054FAB4[v12] )
          goto LABEL_17;
      }
      else
      {
        if ( v11 <= flt_1054FAB4[v12] )
          goto LABEL_17;
      }
      v48 = v48 + flt_10550324[v12];
LABEL_17:
      v9 = v49;
      ++v12;
    }
    while ( v12 < *(int *)((char *)dword_1054A778 + v49) );
    v8 = v50;
LABEL_19:
    if ( v48 >= (double)*(float *)((char*)flt_105509E4+v9  ) )
    {
      if ( v8 >= (signed int)flt_1054A794 )
        v51 = double_to_int64(v11);
      v8 = v50 + 4;
      v9 = v49 + 4;
//       v46 = __SETO__(v50 + 1, dword_1054A7A8);
//       v45 = (signed int)((char *)(v50 + 1) - (char *)dword_1054A7A8) < 0;
      v49 += 4;
      v50+=4;
      if ( v50>=(int)dword_1054A7A8 )
      {
        *a8 = v51 / 5;
        return 1;
      }
      continue;
    }
    return 0;
  }
}

//////////////////////////////////////////////////////////////////////////
char class_1000BCC0::sub_1000BD00(class_1000AE60 *a2)
{
  class_1000AE60 *v2; // edi@1
  int *v3; // ecx@3
  int v4; // edx@5
  signed int v5; // ebx@6
  int v6; // esi@6
  double v7; // st7@6
  int v8; // ecx@7
  //__int16 v9; // fps@7
  //char v10; // c0@7
  double v11; // st7@11
  double v12; // st7@11
  double v13; // st6@11
  int v14; // eax@11
  int v15; // eax@13
  int v16; // edx@13
  int *v17; // ebx@13
  int v18; // esi@13
  unsigned __int8 *v19; // eax@13
  signed int v20; // ecx@13
  unsigned __int8 *v21; // edx@13
  double v22; // st7@14
  int v23; // ecx@15
  int v24; // edx@16
  double v25; // st6@18
  int v26; // eax@18
  int v27; // ecx@18
  int v28; // edx@18
  long double v29; // st5@18
  signed int v30; // edx@19
  int v31; // ecx@19
  int v32; // edi@20
  int v33; // eax@20
  int v34; // eax@21
  int v35; // ecx@21
  int v36; // eax@23
  int v37; // edx@23
  int v38; // edx@23
  int v39; // eax@26
  int v40; // ST18_4@26
  int v41; // eax@26
  int v42; // eax@27
  int v43; // ST18_4@27
  int v44; // eax@27
  int v45; // eax@28
  int v46; // ST18_4@28
  int v47; // eax@28
  int v48; // eax@41
  int v49; // edi@43
  int v50; // esi@43
  int v51; // eax@43
  int v52; // eax@43
  int v53; // edi@43
  int v54; // edx@47
  unsigned __int8 v55; // sf@47
  unsigned __int8 v56; // of@47
  int v57; // eax@50
  int v58; // ecx@51
  int v59; // edx@52
  double v60; // st7@54
  int v61; // eax@54
  int v62; // ecx@54
  int v63; // edx@54
  long double v64; // st6@54
  //float v65; // edx@56
  int v66; // esi@56
  int v67; // esi@56
  int v68; // eax@56
  int v69; // ecx@56
  int v70; // edx@56
  signed int v71; // eax@56
  int v72; // esi@56
  void *v73; // ST40_4@58
  _SOME_40 *v74; // ecx@60
  int i; // ecx@61
  int v76; // edi@61
  void *v77; // eax@61
  float v78; // ecx@61
  char v79; // dl@61
  int k; // ecx@67
  int v81; // edi@67
  void *v82; // edi@67
  unsigned int v83; // ecx@67
  int v84; // eax@74
  float v85; // eax@79
  int j; // ecx@82
  int v87; // edi@82
  void *v88; // eax@82
  int v89; // ecx@82
  const void *v90; // esi@82
  int v91; // edx@82
  unsigned int v92; // ecx@82
  void *v93; // edi@82
  int v94; // ecx@85
  int v95; // edx@85
  unsigned __int8 v96; // zf@91
  char v97; // sf@91
  unsigned __int8 v98; // of@91
  double v100; // [sp+4h] [bp-C4h]@3
  double v101; // [sp+Ch] [bp-BCh]@11
  int v102; // [sp+18h] [bp-B0h]@13
  _SOME_40 v103; // [sp+1Ch] [bp-ACh]@43
  int v104; // [sp+44h] [bp-84h]@16
  int v105; // [sp+48h] [bp-80h]@13
  int v106; // [sp+4Ch] [bp-7Ch]@16
  int v107; // [sp+50h] [bp-78h]@11
  int *v108; // [sp+54h] [bp-74h]@3
  int v109; // [sp+58h] [bp-70h]@3
  int v110; // [sp+5Ch] [bp-6Ch]@26
  int v111; // [sp+60h] [bp-68h]@26
  class_1000BCC0 *v112; // [sp+64h] [bp-64h]@1
  int v113; // [sp+68h] [bp-60h]@5
 // CString v114; // [sp+6Ch] [bp-5Ch]@1
  float v115; // [sp+70h] [bp-58h]@20
  float v116; // [sp+74h] [bp-54h]@14
  int *a4; // [sp+78h] [bp-50h]@5
  int v118; // [sp+7Ch] [bp-4Ch]@13
  int a8; // [sp+80h] [bp-48h]@19
  int v120; // [sp+84h] [bp-44h]@3
  int a3; // [sp+88h] [bp-40h]@6
  int v122; // [sp+8Ch] [bp-3Ch]@18
  int v123; // [sp+90h] [bp-38h]@15
  int v124; // [sp+94h] [bp-34h]@24
  int a5; // [sp+98h] [bp-30h]@18
  float a7; // [sp+9Ch] [bp-2Ch]@13
  int v127; // [sp+A0h] [bp-28h]@18
  int v128; // [sp+A4h] [bp-24h]@24
  float a6; // [sp+A8h] [bp-20h]@6
  int v130; // [sp+ACh] [bp-1Ch]@6
  int v131; // [sp+B0h] [bp-18h]@22
  int v132; // [sp+B4h] [bp-14h]@18
  int v133; // [sp+B8h] [bp-10h]@22
  //int v134; // [sp+C4h] [bp-4h]@1

  v112 = this;
  //v114.m_pchData = (char *)afxEmptyString_m_pchData;
  v2 = a2;
  //v134 = 0;
  if ( a2->a5 < 20 || a2->a6 < 20 )
  {
   // v134 = -1;
   // CString_delete(&v114);
    return 0;
  }
  this->m_part3 = 2;
  v120 =  a2->sub_1000B060();
  v3 = (int *)dword_10063664;
  v109 = 1;
  v108 = (int *)dword_10063664;
  v100 = (double)v120;
  while ( 2 )
  {
    v4 = v2->a5;
    a4 = (int *)v2->a6;
    v120 = (int)((char *)a4 - v4);
    v113 = v4;
    if ( (double)(signed int)((char *)a4 - v4) <= 0.5 )
    {
      v8 = *v3;
      a3 = v8;
      *(int*)(&a6) = v8;
      //UNDEF(v9);
      v7 = (double)v8 / (double)(signed int)a4;
      if ( (double)(signed int)((char *)a4 - v4) < -0.5 )
        v130 = double_to_int64(v7);
      else
        v130 = v8;
      v5 = *(int*)(&a6);
      v6 = v130;
    }
    else
    {
      a3 = *v3;
      v6 = a3;
      v130 = a3;
      v7 = (double)a3 / (double)v113;
      v5 = double_to_int64(v7);
      *(int*)(&a6) = v5;
    }
    v107 = v6 - 23;
    v101 = 1.0 / v7;
    v12 = v7 * v100;
    v13 = (double)v130 * 0.05;
    v14 = double_to_int64(v12);
    v11 = v12 - v13;
    v120 = v14;
    if ( v11 <= 0.0 )
      v11 = 0.0;
    v102 = double_to_int64(v11);
    v105 = v5 / 2 - 11;
    v19 = (unsigned __int8 *)malloc(v6 * v5);
    v20 = v2->a5;
    v21 = (unsigned __int8 *)v2->lpMem;
    v113 = (int)v19;
    sub_1000AA20(v21, v20, v2->a6, v6, v5, v19);
    v18 = v6 + 1;
    a3 = v5 + 1;
    v118 = v18;
    *(int*)(&a7) = 4 * v18 * (v5 + 1);
    v17 = (int *)malloc(4 * v18 * (v5 + 1));
    a4 = (int *)malloc(*(int*)(&a7));
    sub_1000AB90((unsigned __int8 *)v113, v130, *(int*)(&a6), v17);
    sub_1000AD30((unsigned __int8 *)v113, v130, *(int*)(&a6), a4);
    v16 = v105;
    v15 = 0;
    v130 = 0;
    if ( v105 <= 0 )
      goto LABEL_50;
    v22 = v116;
    do
    {
      v23 = 0;
      v123 = 0;
      if ( v120 <= 0 )
        goto LABEL_49;
      v24 = v18 * (v15 + 12);
      v104 = v18 * (v15 + 12);
      v106 = v18 * v15;
      while ( 2 )
      {
        a5 = 4 * (v24 + v23 + 24);
        v132 = 4 * (v24 + v23);
        v26 = v106 + v23 + 24;
        v27 = 4 * (v106 + v23);
        v26 *= 4;
        v28 = *(int *)((char *)v17 + v27);
        v127 = v27;
        v122 = *(int *)((char *)v17 + a5) + v28 - *(int *)((char *)v17 + v26) - *(int *)((char *)v17 + v132);
        v25 = (double)v122 * 0.003472222248092294;
        v127 = *(int *)((char *)a4 + a5)
             + *(int *)((char *)a4 + v27)
             - *(int *)((char *)a4 + v26)
             - *(int *)((char *)a4 + v132);
        v29 = sqrt((double)v127 * 0.003472222248092294 - v25 * v25);
        a6 = v29;
        if ( v29 < 8.0 )
          goto LABEL_47;
        v31 = 0;
        v30 = (signed int)((char*)flt_1054A794-8);
        a8 = 0;
        v127 = 0;
        *(int*)(&v116) = (int)((char*)flt_1054A794-8);
        v122 = 0;
        a7 = 130.0 - v25 * 40.0 / a6;
        while ( 2 )
        {
          v32 = *(int *)((char *)dword_1054A754 + v31);
          v33 = *(int *)((char *)dword_1054A758 + v31);
          *(int*)(&v115) = 0;
          if ( v32 >= v33 )
            goto LABEL_39;
          do
          {
            v34 = dword_1054AEA8[v32] + v123 + 1;
            v35 = dword_1054B568[v32] + v130 + 1;
            switch ( dword_1054A7E8[v32]-1 )
            {
              case 0:
                v131 = v18 * (dword_1054C2E8[v32] + v35 - 1);
                v133 = v18 * (v35 - 1);
                v132 = v18 * (v35 + 2 * dword_1054C2E8[v32] - 1);
                v133 = *(&v17[v34 - 1] + v133)
                     + *(&v17[v34 - 1] + v132)
                     + 2 * (*(&v17[v34 - 1] + dword_1054BC28[v32] + v131) - *(&v17[v34 - 1] + v131))
                     - *(&v17[v34 - 1] + dword_1054BC28[v32] + v133)
                     - *(&v17[v34 - 1] + v132 + dword_1054BC28[v32]);
                goto LABEL_30;
              case 1:
                v131 = v18 * (dword_1054C2E8[v32] + v35 - 1);
                v38 = dword_1054BC28[v32];
                v133 = v18 * (v35 - 1);
                a5 = 2 * v38;
                v37 = *(&v17[2 * v38 - 1] + v34 + v131)
                    + 2 * (*(&v17[v34 - 1] + v38 + v133) - *(&v17[v34 - 1] + v131 + v38))
                    - *(&v17[2 * v38 - 1] + v133 + v34)
                    - *(&v17[v34 - 1] + v133);
                v36 = *(&v17[v34 - 1] + v131);
                goto LABEL_29;
              case 2:
                v128 = dword_1054C2E8[v32];
                v131 = v18 * (v128 + v35 - 1);
                v124 = dword_1054BC28[v32];
                v133 = v18 * (v35 - 1);
                v132 = 3 * v124;
                v133 = *(&v17[v34 - 1] + v131)
                     + *(&v17[3 * v124 - 1] + v34 + v133)
                     + 2
                     * (*(&v17[v34 - 1] + v124 + v133)
                      + *(&v17[2 * v124 - 1] + v34 + v131)
                      - *(&v17[v34 - 1] + v131 + v124)
                      - *(&v17[2 * v124 - 1] + v34 + v133))
                     - *(&v17[3 * v124 - 1] + v34 + v131)
                     - *(&v17[v133 - 1] + v34);
                v22 = (double)v133 * 40.0 / a6 - (double)v124 * (double)v128 * a7;
                goto LABEL_31;
              case 3:
                v131 = v18 * (dword_1054C2E8[v32] + v35 - 1);
                a5 = 2 * dword_1054BC28[v32];
                v132 = v18 * (v35 + 2 * dword_1054C2E8[v32] - 1);
                v133 = v18 * (v35 - 1);
                v133 = 2
                     * (*(&v17[a5 - 1] + v131 + v34)
                      + *(&v17[v34 - 1] + dword_1054BC28[v32] + v133)
                      + *(&v17[v34 - 1] + dword_1054BC28[v32] + v132)
                      + *(&v17[v34 - 1] + v131)
                      - 2 * *(&v17[v34 - 1] + v131 + dword_1054BC28[v32]))
                     - *(&v17[v34 - 1] + v133)
                     - *(&v17[a5 - 1] + v34 + v132)
                     - *(&v17[v34 - 1] + v132)
                     - *(&v17[a5 - 1] + v34 + v133);
                goto LABEL_30;
              case 4:
                v131 = dword_1054BC28[v32] + v34 - 1;
                v133 = v35 + dword_1054C2E8[v32] - 1;
                v132 = v34 + 1;
                a5 = v35 + 1;
                v111 = v131 - 1;
                v110 = v133 - 1;
                v124 = dword_1054BC28[v32];
                v128 = dword_1054C2E8[v32];
                v124 = dword_1054BC28[v32];
                v128 = dword_1054C2E8[v32];
                v39 = sub_1000AE10(v17, v18, a3, v34, v35, v131, v133);
                v40 = v132;
                v132 = (v128 - 2) * (v124 - 2) * v39 / (2 * (v128 + v124) - 4);
                v41 = sub_1000AE10(v17, v18, a3, v40, a5, v111, v110);
                v133 = v128 * v124 * v41 / (2 * (2 - v124 - v128)) + v132;
                goto LABEL_30;
              case 5:
                v131 = dword_1054BC28[v32] + v34 - 1;
                v133 = v35 + dword_1054C2E8[v32] - 1;
                v132 = v34 + 2;
                a5 = v35 + 2;
                v111 = v131 - 2;
                v110 = v133 - 2;
                v124 = dword_1054BC28[v32];
                v128 = dword_1054C2E8[v32];
                v124 = dword_1054BC28[v32];
                v128 = dword_1054C2E8[v32];
                v42 = sub_1000AE10(v17, v18, a3, v34, v35, v131, v133);
                v43 = v132;
                v132 = (v128 - 4) * (v124 - 4) * v42 / (4 * (v128 + v124) - 16);
                v44 = sub_1000AE10(v17, v18, a3, v43, a5, v111, v110);
                v133 = v128 * v124 * v44 / (4 * (4 - v124 - v128)) + v132;
                goto LABEL_30;
              case 6:
                v131 = dword_1054BC28[v32] + v34 - 1;
                v133 = v35 + dword_1054C2E8[v32] - 1;
                v132 = v34 + 3;
                a5 = v35 + 3;
                v111 = v131 - 3;
                v110 = v133 - 3;
                v124 = dword_1054BC28[v32];
                v128 = dword_1054C2E8[v32];
                v124 = dword_1054BC28[v32];
                v128 = dword_1054C2E8[v32];
                v45 = sub_1000AE10(v17, v18, a3, v34, v35, v131, v133);
                v46 = v132;
                v132 = (v128 - 6) * (v124 - 6) * v45 / (6 * (v124 + v128 - 6));
                v47 = sub_1000AE10(v17, v18, a3, v46, a5, v111, v110);
                v36 = v128 * v124 * v47 / (6 * (6 - v124 - v128));
                v37 = v132;
LABEL_29:
                v133 = v36 + v37;
LABEL_30:
                v22 = (double)v133 * 40.0 / a6;
LABEL_31:
                v18 = v118;
                break;
              default:
                break;
            }
            if ( byte_1054D068[v32] )
            {
              if ( v22 >= flt_1054C9A8[v32] )
                goto LABEL_37;
            }
            else
            {
              if ( v22 <= flt_1054C9A8[v32] )
                goto LABEL_37;
            }
            v115 = v115 + flt_1054D218[v32];
LABEL_37:
            ++v32;
          }
          while ( v32 < *(int *)((char *)dword_1054A758 + v122) );
          v30 = *(int*)(&v116);
          v31 = v122;
LABEL_39:
          if ( v115 >= (double)*(float *)((char*)flt_1054D8D8+v31) )
          {
            if ( v30 >= (signed int)flt_1054A794 )
            {
              v48 = double_to_int64(v22);
              v30 = *(int*)(&v116);
              v31 = v122;
              v127 = v48;
            }
            v30 += 4;
            v31 += 4;
            v122 = v31;
            *(int*)(&v116) = v30;
            if ( v30 >= (signed int)dword_1054A7A8 )
            {
              v116 = v22;
              a8 = v127 / 5;
              v132 = double_to_int64(v101);
              v49 = v123;
              *(int*)(&a7) = double_to_int64(v101);
              v127 = v123 + 23;
              v50 = v130;
              v127 = double_to_int64(v101);
              v122 = v130 + 11;
              v51 = double_to_int64(v101);
              v103.a1 = v109;
              v122 = v51;
              v103.a9 = v50;
              v52 = a2->a1;
              v103.a8 = v49;
              v103.a2 = v132 + v52;
              v103.a3 = *(int*)(&a7) + a2->a2;
              v103.a4 = v127 + a2->a1;
              v103.a5 = v122 + a2->a2;
              v103.a10 = a8;
              v53 = a2->a7.GetSize();
              v103.a6 = (v103.a4 + v132 + v52) / 2;
              v103.a7 = (v103.a5 + v103.a3) / 2;
			  a2->a7.SetSize(v53+1);
              v22 = v116;
              memcpy(&a2->a7[v53], &v103, sizeof(a2->a7[v53]));
              v18 = v118;
              goto LABEL_46;
            }
            continue;
          }
          break;
        }
        v116 = v22;
LABEL_46:
        v2 = a2;
LABEL_47:
        v54 = v112->m_part3;
		v123 += v54;
//         v56 = __SETO__(v54 + v123, v120);
//         v55 = v54 + v123 - v120 < 0;
//         
//         if ( v55 ^ v56 )
		if(v123<v120)
        {
          v23 = v123;
          v24 = v104;
          continue;
        }
        break;
      }
      v16 = v105;
      v15 = v130;
LABEL_49:
      v15 += v112->m_part3;
      v130 = v15;
    }
    while ( v15 < v16 );
LABEL_50:
    v57 = 0;
    v130 = 0;
    if ( v16 <= 0 )
      goto LABEL_91;
    while ( 2 )
    {
      v58 = v102;
      v123 = v102;
      if ( v102 >= v107 )
        goto LABEL_90;
      v59 = v18 * (v57 + 12);
      v104 = v18 * (v57 + 12);
      v106 = v18 * v57;
      while ( 2 )
      {
        a5 = 4 * (v59 + v58 + 24);
        v132 = 4 * (v59 + v58);
        v61 = v106 + v58 + 24;
        v62 = 4 * (v106 + v58);
        v61 *= 4;
        v63 = *(int *)((char *)v17 + v62);
        v127 = v62;
        v122 = *(int *)((char *)v17 + a5) + v63 - *(int *)((char *)v17 + v61) - *(int *)((char *)v17 + v132);
        v60 = (double)v122 * 0.003472222248092294;
        v127 = *(int *)((char *)a4 + a5)
             + *(int *)((char *)a4 + v62)
             - *(int *)((char *)a4 + v61)
             - *(int *)((char *)a4 + v132);
        v64 = sqrt((double)v127 * 0.003472222248092294 - v60 * v60);
        a6 = v64;
        if ( v64 >= 8.0 )
        {
          a8 = 0;
          a7 = 130.0 - v60 * 40.0 / a6;
          if ( sub_1000CBB0(v17, v18, a3, v123 + 1, v130 + 1, a6, a7, &a8) )
          {
            v67 = double_to_int64(v101);
            *(int*)(&a7) = double_to_int64(v101);
            v120 = v123 + 23;
            v127 = double_to_int64(v101);
            v120 = v130 + 11;
            v68 = double_to_int64(v101);
            v103.a1 = v109;
            v69 = v2->a1;
            v103.a2 = v2->a1 + v67;
            v70 = v2->a2;
            v103.a3 = v70 + *(int*)(&a7);
            v103.a8 = v123;
            v103.a9 = v130;
            v103.a10 = a8;
            v103.a4 = v127 + v69;
            v103.a5 = v70 + v68;
            v71 = v70 + v68 + v70 + *(int*)(&a7) - ((unsigned __int64)(v70 + v68 + v70 + *(int*)(&a7)) >> 32);
            //*(int*)(&v65) = v2->a8.GetSize();
            v72 = v2->a8.GetSize();
            v120 = v72;
            v66 = v72 + 1;
            v103.a6 = (v127 + v69 + v103.a2) / 2;
            v103.a7 = v71 >> 1;
            v2->a8.SetSize(v66);
            memcpy(&v2->a8[v120], &v103, sizeof(v2->a8[v120]));
            v18 = v118;
            v2 = a2;
          }
        }
        v123 += v112->m_part3;
        if ( v123 < v107 )
        {
          v58 = v123;
          v59 = v104;
          continue;
        }
        break;
      }
      v57 = v130;
LABEL_90:
      v57 += v112->m_part3;
      v130 = v57;
      if ( v57 < v105 )
        continue;
      break;
    }
LABEL_91:
    free((void *)v113);
    free(v17);
    free(a4);
//     v98 = __SETO__(v108 + 1, &unk_1006366C);
//     v96 = (_UNKNOWN *)(v108 + 1) == &unk_1006366C;
//     v97 = (signed int)((char *)(v108 + 1) - (char *)&unk_1006366C) < 0;
    ++v109;
    ++v108;
    if ( v108<= dword_1006366C)//(unsigned __int8)(v97 ^ v98) | v96 )
    {
      v3 = v108;
      continue;
    }
    break;
  }
  //v134 = -1;
  //CString_delete(&v114);
  return 1;
}
//////////////////////////////////////////////////////////////////////////
_EyePos_ALL * sub_10008970(_EyePos_ALL *arg0, unsigned __int8 *a3, int a5, int a4, int arg10, int a6, int arg18, int a8)
{
  class_1000AE60 *v8; // eax@1
  int v9; // ebx@1
  int v10; // eax@1
  void *v11; // esp@1
  int v12; // eax@4
  int v13; // ecx@4
  int v14; // edi@4
  int v15; // edx@4
  int v16; // edx@6
  int v17; // edi@6
  class_1000AE60 *v18; // edi@10
  int v19; // ebx@12
  _SOME_12 *v20; // edx@12
  float v21; // ecx@12
  int v22; // edi@14
  int v23; // esi@14
  int v24; // esi@18
  unsigned __int8 v25; // sf@19
  unsigned __int8 v26; // of@19
  unsigned __int8 v27; // sf@21
  unsigned __int8 v28; // of@21
  void *v29; // eax@28
  int v30; // eax@34
  int v31; // edx@34
  unsigned __int8 v32; // sf@39
  unsigned __int8 v33; // of@39
  signed int v34; // eax@42
  _SOME_20 *v35; // edx@43
  _SOME_20 *v36; // esi@44
  char v37; // zf@44
  double v38; // st7@46
  int v39; // esi@46
  class_1000BCC0 a1; // [sp+0h] [bp-7298h]@1
  class_100096D0 v68; // [sp+6A50h] [bp-848h]@1
  _SOME_20 v43; // [sp+71D4h] [bp-C4h]@12
  int v44; // [sp+71E8h] [bp-B0h]@15
  _EyePos_ALL v45; // [sp+71ECh] [bp-ACh]@1
  int a7; // [sp+7218h] [bp-80h]@12
  _SOME_20 v47; // [sp+721Ch] [bp-7Ch]@18
  CArray<SOME_12,SOME_12&> v48; // [sp+7230h] [bp-68h]@1
  CArray<SOME_12,SOME_12&> v49; // [sp+7244h] [bp-54h]@1
  CArray<SOME_20,SOME_20&> v50; // [sp+7258h] [bp-40h]@1
  int v51; // [sp+726Ch] [bp-2Ch]@6
  int i; // [sp+7270h] [bp-28h]@4
  int v53; // [sp+7274h] [bp-24h]@42
  int v54; // [sp+7278h] [bp-20h]@1
  float v55; // [sp+727Ch] [bp-1Ch]@17
  class_1000AE60 *a2; // [sp+7280h] [bp-18h]@2
  int v57; // [sp+7284h] [bp-14h]@6
  int v58; // [sp+7288h] [bp-10h]@6
  int v59; // [sp+728Ch] [bp-Ch]@1
  //int (__cdecl *v60)(int, int, int, int); // [sp+7290h] [bp-8h]@1
  //int v61; // [sp+7294h] [bp-4h]@1
  int v62; // [sp+72A8h] [bp+10h]@36
  int v63; // [sp+72A8h] [bp+10h]@43
  //int v64; // [sp+72A8h] [bp+10h]@46
  int v65; // [sp+72ACh] [bp+14h]@34
  int v66; // [sp+72B4h] [bp+1Ch]@31
  signed int v67; // [sp+72BCh] [bp+24h]@34

  //v61 = -1;
  //v60 = sub_10062629;
  //v59 = v10;
  //v11 = alloca(29324);
  v9 = 0;
  //v61 = 0;
  //LOBYTE(v61) = 4;
  v45.a1.xleft = 0;
  v45.a1.yleft = 0;
  v45.a1.xright = 0;
  v45.a1.yright = 0;
  v45.a4 = 0;
  v45.a5 = 0;
  v45.a6 = 0;
  v45.a7 = 0;
  v45.a2 = 0;
  v45.a3 = 0;

  //v54 = (int)v8;
  //LOBYTE(v61) = 5;
  a2=new class_1000AE60();
  //LOBYTE(v61) = 4;
  v54 = arg18 - arg10;
  v15 = (arg18 - arg10 + 1) / 12;
  v13 = v15 + a8;
  v12 = a6 - v15;
  v14 = arg18 - a8;
  for ( i = arg18 - a8; ; v14 = i )
  {
    v16 = arg10 - a6 + v12;
    v17 = v13 + v14;
    v57 = v12;
    v51 = v13;
    ++v12;
    --v13;
    v58 = v17;
    if ( v16 >= 0 )
    {
      if ( v17 < a4 && v57 >= 0 && v51 < a5 )
        break;
    }
  }
  v18 = a2;
  a2->class_1000AE60_Set(a3, a4, a5, v16, v57, v58, v51);
  a1.sub_1000BD00(v18);
  v18->sub_1000B230(&v48,&v49);
  v51 = 0;
  if ( v48.GetSize() > 0 )
  {
    i = 0;
    do
    {
      v20 = (_SOME_12 *)((char *)v48.GetData() + v9);
      v19 = *(int *)((char *)&v48.GetData()->a1 + v9);
      a7 = v20->a2;
      v21 = v20->a3;
      v58 = 0;
      v43.a5 = v21;
      if ( v49.GetSize() > 0 )
      {
        v57 = 0;
        do
        {
          v23 = *(int *)((char *)&v49.GetData()->a1 + v57);
          v22 = *(int *)((char *)&v49.GetData()->a2 + v57);
          *(int*)(&v43.a5) = *(int *)((char *)&v49.GetData()->a3 + v57);
          if ( v19 < v23 )
          {
            v44 = (a7 - v22) * (a7 - v22) + (v19 - v23) * (v19 - v23);
            if ( sqrt((double)v44) > (double)a2->a5 * 0.2000000029802322 )
            {
              if ( v68.sub_1000A090( a3, a4, a5, v19, a7, v23, v22) )
              {
                if ( v68.sub_1000A5A0( &v55) )
                {
                  v47.a3 = v23;
                  v24 = v50.GetSize();
                  v47.a1 = v19;
                  v47.a2 = a7;
                  v47.a4 = v22;
                  v47.a5 = v55;
				  v50.SetSize(v50.GetSize()+1);
                  memcpy(&v50[v24], &v47, sizeof(v50[v24]));
                }
              }
            }
          }
		  v57 += 12;
		  ++v58;
//           v26 = __SETO__(v58 + 1, v49.m_nSize);
//           v25 = v58++ + 1 - v49.m_nSize < 0;      
//         }
//         while ( v25 ^ v26 );
	    }
		while(v58<v49.GetSize());
        v18 = a2;
      }
      v9 = i + 12;
	  i += 12;
	  ++v51;
//       v28 = __SETO__(v51 + 1, v48.m_nSize);
//       v27 = v51++ + 1 - v48.m_nSize < 0;
//      
//     }
//     while ( v27 ^ v28 );
   }
   while(v51<v48.GetSize());
    v9 = 0;
  }
  if ( 1 )//reg_test()
  {
    if ( v50.GetSize() <= v9 )
    {
      v38 = (double)v54 * 0.25;
      v45.a1.xleft = double_to_int64(v38);
      //v64 = a8 - a6;
      v39 = double_to_int64(v38);
      v45.a1.yleft = v39;
      v45.a1.xright = double_to_int64(v38);
      v45.a1.yright = v39;
    }
    else
    {
      v66 = 3;
      if ( v50.GetSize() <= 3 )
        v66 = v50.GetSize();
      if ( v66 > v9 )
      {
        v31 = 0;
        v30 = 1;
        v65 = 0;
        v67 = 1;
        do
        {
          v58 = v30;
          memcpy(&v43, (char *)v50.GetData() + v31, sizeof(v43));
          if ( v30 < v50.GetSize() )
          {
            v62 = v31 + 20;
            do
            {
              memcpy(&v47, (char *)v50.GetData() + v62, sizeof(v47));
              if ( v43.a5 < (double)v47.a5 )
              {
                memcpy((char *)v50.GetData() + v62, &v43, 0x14u);
                memcpy(&v43, &v47, sizeof(v43));
                memcpy((char *)v50.GetData() + v65, &v47, 0x14u);
              }
			  v62 += 20;
			  ++v58;
//               v33 = __SETO__(v58 + 1, v50.m_nSize);
//               v32 = v58++ + 1 - v50.m_nSize < 0;
//               
//             }
//             while ( v32 ^ v33 );
		}
		while(v58<v50.GetSize());
            v30 = v67;
            v31 = v65;
          }
          ++v30;
          v31 += 20;
          v67 = v30;
          v65 = v31;
        }
        while ( v30 - 1 < v66 );
      }
      v34 = 0;
      v53 = 0;
      v54 = 0;
      if ( v66 > 0 )
      {
        v35 = v50.GetData();
        v63 = v66;
        do
        {
          v36 = v35;
          ++v35;
          memcpy(&v47, v36, sizeof(v47));
          v34 += v47.a1;
          v9 += v47.a2;
          v53 += v47.a3;
          v37 = v63 == 1;
          v54 += v47.a4;
          --v63;
        }
        while ( !v37 );
      }
      v45.a1.xleft = v34 / v66;
      v45.a1.yleft = v9 / v66;
      v45.a1.xright = v53 / v66;
      v45.a1.yright = v54 / v66;
      v18 = a2;
      v9 = 0;
    }
    if ( v18 != (class_1000AE60 *)v9 )
    {
      delete v18;
    }
	v48.SetSize(v9);
	v49.SetSize(v9);
	v50.SetSize(v9);

    memcpy(arg0, &v45, 0x28u);
    //LOBYTE(v61) = 9;
    v50.RemoveAll();
    //LOBYTE(v61) = 10;
    v49.RemoveAll();
    //LOBYTE(v61) = 11;
    v48.RemoveAll();
  }
  else
  { 
    memcpy(arg0, &v45, 0x28u);
    //LOBYTE(v61) = 6;
    v50.RemoveAll(); 
    //LOBYTE(v61) = 7;
    v49.RemoveAll();
    //LOBYTE(v61) = 8;
    v48.RemoveAll();
  }
  //LOBYTE(v61) = 0;
  //v61 = -1;
  return arg0;
}

//////////////////////////////////////////////////////////////////////////
EyePos * sub_10008F40(EyePos *a1, unsigned __int8 *a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
  EyePos *result; // eax@1
  _EyePos_ALL *v9; // esi@1
  int v10; // edx@1
  int v11; // esi@1
  int v12; // edi@1
  _EyePos_ALL v13; // [sp+Ch] [bp-28h]@1

  v9 = sub_10008970(&v13, a2, a3, a4, a5, a6, a7, a8);
  result = a1;
  memcpy(&v13, v9, sizeof(v13));
  v10 = v13.a1.yleft;
  v11 = v13.a1.xright;
  v12 = v13.a1.yright;
  a1->xleft = v13.a1.xleft;
  a1->yleft = v10;
  a1->xright = v11;
  a1->yright = v12;
  return result;
}
