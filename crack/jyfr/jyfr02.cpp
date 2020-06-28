#include "StdAfx.h"

#include "mytype.h"

//////////////////////////////////////////////////////////////////////////
signed int __stdcall sub_100049D0(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, signed int a9, int a10, int *a11)
{
  int *v11; // edx@1
  signed int result; // eax@2
  int i; // ecx@3
  signed int v14; // ebx@3
  int *v15; // edi@3
  unsigned int v16; // ecx@3
  int *v17; // edi@7
  signed int v18; // edx@8
  int *v19; // ecx@9
  double v20; // st7@9
  double v21; // st5@10
  unsigned __int8 v22; // sf@16
  unsigned __int8 v23; // of@16
  signed int v24; // [sp+24h] [bp+24h]@8
  signed int v25; // [sp+2Ch] [bp+2Ch]@3

  v11 = a11;
  if ( a11 )
  {
    v14 = a9;
    v16 = (unsigned int)(4 * a10 * a9) >> 2;
    memset(a11, 0, 4 * v16);
    v15 = &a11[v16];
    v25 = 0;
    for ( i = 4 * (_BYTE)a10 * (_BYTE)a9 & 3; i; --i )
    {
      *(_BYTE *)v15 = 0;
      v15 = (int *)((char *)v15 + 1);
    }
    if ( a10 > 0 )
    {
      v17 = v11;
      do
      {
        v18 = 0;
        v24 = 0;
        if ( v14 > 0 )
        {
          v20 = (double)v25;
          v19 = v17;
          do
          {
            v21 = (double)v24;
            if ( v21 > (v20 - a2) * (v20 - a2) * a1 + a3 )
            {
              if ( v21 < (v20 - a5) * (v20 - a5) * a4 + a6 )
              {
                if ( v20 > a7 )
                {
                  if ( v20 < a8 )
                    *v19 = 1;
                }
              }
            }
            ++v18;
            v19 += a10;
            v24 = v18;
          }
          while ( v18 < v14 );
        }
        ++v17;
        v23 = __SETO__(v25 + 1, a10);
        v22 = v25++ + 1 - a10 < 0;
      }
      while ( v22 ^ v23 );
    }
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}
//////////////////////////////////////////////////////////////////////////
signed int __stdcall sub_10004AD0(signed int a1, signed int a2, signed int a3, float a4, float a5, float a6, float a7, float a8, signed int a9, int a10, void *a11)
{
  double v12; // st7@1
  double v13; // st6@1
  double v14; // st5@1
  double v15; // st5@1
  float v16; // ST1C_4@1
  float v17; // ST18_4@1
  float v18; // ST14_4@1
  float v19; // ST10_4@1
  float v20; // ST0C_4@1
  float v21; // ST08_4@1
  float v22; // ST04_4@1
  float v23; // ST00_4@1
  float v24; // [sp+30h] [bp+4h]@1

  v12 = (double)a1;
  v13 = (double)a2;
  v14 = (double)a3;
  v24 = v14;
  v15 = v14 * a8 * 0.5;
  v16 = v15 + v12;
  v17 = v12 - v15;
  v18 = v24 * a7 + v13;
  v19 = v12;
  v20 = a5 * -1.0 / v24;
  v21 = v13 - v24 * a6;
  v22 = v12;
  v23 = a4 / v24;
  return sub_100049D0(v23, v22, v21, v20, v19, v18, v17, v16, a9, a10, (int *)a11);
}
//////////////////////////////////////////////////////////////////////////
int __stdcall sub_10003E70(_SOME_88 *a1, int *a2)
{
  int result; // eax@1
  int v3; // eax@3
  int v4; // ebp@3
  int v5; // esi@3
  int v6; // ecx@5
  int v7; // edi@6
  unsigned __int8 v8; // sf@12
  unsigned __int8 v9; // of@12
  int v10; // [sp+4h] [bp-8h]@4
  int v11; // [sp+8h] [bp-4h]@3
  int v12; // [sp+10h] [bp+4h]@3

  result = sub_10003DC0(a1, a2);
  if ( result )
  {
    v3 = a1->a13;
    v4 = a1->a14;
    v5 = a1->a5;
    v11 = v3;
    v12 = 0;
    if ( v3 > 0 )
    {
      v10 = 0;
      do
      {
        v6 = 0;
        if ( v4 > 0 )
        {
          v7 = v5 / 2;
          do
          {
            if ( v7 % v5 || (v5 / 2 + v12) % v5 )
              a2[v6 + v10] = 0;
            ++v6;
            ++v7;
          }
          while ( v6 < v4 );
          v3 = v11;
        }
        v9 = __SETO__(v12 + 1, v3);
        v8 = v12++ + 1 - v3 < 0;
        v10 += v4;
      }
      while ( v8 ^ v9 );
    }
    result = 1;
  }
  return result;
}
//////////////////////////////////////////////////////////////////////////
signed int __thiscall sub_10004330(class_100031E0 *this)
{
  void *v1; // eax@1
  int v2; // ebx@1
  int v3; // ebp@1
  int v4; // edi@1
  class_100031E0 *v5; // esi@1
  int v6; // edi@3
  int *v7; // eax@3
  int v9; // ebx@6
  _SOME_88 *v10; // ebp@6
  int v11; // edi@6
  unsigned __int8 v12; // sf@8
  unsigned __int8 v13; // of@8
  int v14; // [sp+10h] [bp-8h]@5
  int v15; // [sp+14h] [bp-4h]@1

  v5 = this;
  v1 = this->m_part29;
  v2 = this->m_part36.a1;
  v3 = this->m_part36.a2.a13;
  v4 = this->m_part36.a2.a14;
  v15 = this->m_part36.a1;
  if ( v1 )
    free(v1);
  v6 = v3 * v4;
  v7 = (int *)malloc(4 * v2 * v6);
  v5->m_part29 = v7;
  if ( !v7 )
    return 0;
  v14 = 0;
  if ( v2 > 0 )
  {
    v9 = 0;
    v10 = &v5->m_part36.a2;
    v11 = 4 * v6;
    while ( sub_10003E70(v10, (int *)((char *)v5->m_part29 + v9)) )
    {
      v9 += v11;
      ++v10;
      v13 = __SETO__(v14 + 1, v15);
      v12 = v14++ + 1 - v15 < 0;
      if ( !(v12 ^ v13) )
        return 1;
    }
    return 0;
  }
  return 1;
}

//////////////////////////////////////////////////////////////////////////
FUCK_44 *__stdcall sub_10004D10(_FUCK_44 *a1)
{
  _FUCK_44 *result; // eax@1

  result = a1;
  *(int*)(&a1->a5) = 1059760811;
  a1->a4 = 25;
  a1->a2 = 125;
  a1->a3 = 100;
  *(int*)(&a1->a7) = 1056964608;
  *(int*)(&a1->a8) = 1065353216;
  *(int*)(&a1->a9) = 1063675494;
  *(int*)(&a1->a10) = 1072064102;
  *(int*)(&a1->a11) = 1072064102;
  a1->a6 = 48;
  a1->a1 = 0;
  return result;
}
//////////////////////////////////////////////////////////////////////////
_SOME_664 *__stdcall sub_100045F0(_SOME_664 *a1)
{
  _SOME_664 *result; // eax@1

  result = a1;
  a1->a1 = 1;
  *(int*)(&a1->a7.a5) = 1059760811;
  a1->a7.a4 = 25;
  a1->a7.a2 = 125;
  a1->a7.a3 = 100;
  *(int*)(&a1->a7.a7) = 1056964608;
  *(int*)(&a1->a7.a8) = 1065353216;
  *(int*)(&a1->a7.a9) = 1063675494;
  *(int*)(&a1->a7.a10) = 1072064102;
  *(int*)(&a1->a7.a11) = 1072064102;
  a1->a7.a6 = 48;
  a1->a2.a5 = 5;
  *(int*)(&a1->a2.a17) = 1056964608;
  *(int*)(&a1->a2.a18) = 1065353216;
  *(int*)(&a1->a2.a19) = 1063675494;
  *(int*)(&a1->a2.a20) = 1072064102;
  *(int*)(&a1->a2.a21) = 1072064102;
  a1->a2.a1 = 5;
  a1->a2.a2 = 6;
  *(int*)(&a1->a2.a3) = 1082130432;
  *(int*)(&a1->a2.a4) = 0;
  *(int*)(&a1->a2.a7) = 1078530011;
  *(int*)(&a1->a2.a8) = 1086324736;
  a1->a2.a6 = sqrt(2.0);
  result->a2.a16 = result->a7.a5;
  result->a2.a15 = result->a7.a4;
  result->a2.a13 = result->a7.a2;
  result->a2.a14 = result->a7.a3;
  a1->a2.a9 = a1->a7.a2;
  a1->a2.a10 = a1->a7.a3;
  return result;
}
//////////////////////////////////////////////////////////////////////////
int class_10004760::sub_100048F0(_FUCK_44 *a2)
{
  class_100031E0 *v2; // ebx@1
  int v3; // eax@2
  double v5; // st7@3
  double v6; // st6@3
  double v7; // st6@3
  int v8; // eax@3
  char v9; // [sp-28h] [bp-40h]@1
  int v10; // [sp-24h] [bp-3Ch]@1
  int v11; // [sp-20h] [bp-38h]@1
  int v12; // [sp-1Ch] [bp-34h]@1
  int v13; // [sp-18h] [bp-30h]@1
  int v14; // [sp-14h] [bp-2Ch]@1
  int v15; // [sp-10h] [bp-28h]@1
  int v16; // [sp-Ch] [bp-24h]@1
  int v17; // [sp-8h] [bp-20h]@1
  int v18; // [sp-4h] [bp-1Ch]@1
  int v19; // [sp+0h] [bp-18h]@1
  int v20; // [sp+14h] [bp-4h]@3
  signed int v21; // [sp+1Ch] [bp+4h]@2

  v2 = this;
  sub_10004D10(v19);
 
  if ( 1 )
  {
    class_10004760_delete_true(v2);
    memcpy(&v2->m_part7, a2, sizeof(v2->m_part7));
    v3 = v2->m_part7.a4;
    v2->m_part24 = 1;
    v21 = v3;
    if ( v3 )
    {
      v5 = (double)v21;
      v20 = v2->m_part7.a3;
      v6 = (double)v20 / v5;
      v2->m_part22 = v20 / 2;
      v2->m_part19 = v6 * 0.5;
      v7 = (double)v2->m_part7.a2 / (v2->m_part7.a5 + 1.0) / v5;
      v2->m_part21 = v7;
      v2->m_part20 = v7 * v2->m_part7.a5;
      double_to_int64(v5);
      v2->m_part23 = v8;
      return v2->m_part24;
    }
  }
  else
  {
    class_10004760_delete_true(v2);
    v2->m_part24 = 0;
  }
  return v2->m_part24;
}
//////////////////////////////////////////////////////////////////////////
int class_100031E0::sub_10003300(_SOME_664 *a2)
{
  int result; // eax@1
  class_100031E0 *v3; // ebx@1
  _SOME_88 v4; // [sp+Ch] [bp-58h]@9

  v3 = this;
  sub_100045F0(a2);
  class_100031E0_delete_true();
  result = sub_100034D0(v3, a2);
  if ( result )
  {
    memcpy(&v3->m_part36, a2, sizeof(v3->m_part36));
    v3->m_part28 = v3->m_part36.a1;
    result = sub_100048F0(v3, &v3->m_part36.a7);
    if ( result )
    {
      result = sub_10004330(v3);
      if ( result )
      {
        result = sub_100043E0(v3);
        if ( result )
        {
          memcpy(&v4, &v3->m_part36.a2, sizeof(v4));
          v4.a22 = 1;
          result = sub_10002340(&v3->m_a2, &v4);
          if ( result )
          {
            v3->m_part35 = sub_10002690(&v3->m_a2);
            if ( v3->m_part34 )
              free(v3->m_part34);
            result = (int)malloc(4 * v3->m_part35);
            v3->m_part34 = (void *)result;
            if ( result )
            {
              v3->m_part27 = 1;
              result = 1;
            }
          }
        }
      }
    }
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////
signed int __stdcall sub_10001F90(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, signed int a9, int a10, int *a11)
{
  int i; // ecx@1
  signed int v12; // ebx@1
  int v13; // ebp@1
  int *v14; // edi@1
  unsigned int v15; // ecx@1
  char v16; // si@1
  int *v17; // edi@5
  signed int v18; // edx@6
  int *v19; // ecx@7
  double v20; // st7@7
  double v21; // st5@8
  unsigned __int8 v22; // sf@14
  unsigned __int8 v23; // of@14
  signed int v25; // [sp+34h] [bp+24h]@1
  signed int v26; // [sp+38h] [bp+28h]@6

  v12 = a9;
  v13 = a10;
  v15 = 4 * a10 * a9;
  v16 = 4 * a10 * (_BYTE)a9;
  v25 = 0;
  v15 >>= 2;
  memset(a11, 0, 4 * v15);
  v14 = &a11[v15];
  for ( i = v16 & 3; i; --i )
  {
    *(_BYTE *)v14 = 0;
    v14 = (int *)((char *)v14 + 1);
  }
  if ( a10 > 0 )
  {
    v17 = a11;
    do
    {
      v18 = 0;
      v26 = 0;
      if ( v12 > 0 )
      {
        v20 = (double)v25;
        v19 = v17;
        do
        {
          v21 = (double)v26;
          if ( v21 > (v20 - a2) * (v20 - a2) * a1 + a3 )
          {
            if ( v21 < (v20 - a5) * (v20 - a5) * a4 + a6 )
            {
              if ( v20 > a7 )
              {
                if ( v20 < a8 )
                  *v19 = 1;
              }
            }
          }
          ++v18;
          v19 += v13;
          v26 = v18;
        }
        while ( v18 < v12 );
      }
      ++v17;
//       v23 = __SETO__(v25 + 1, v13);
//       v22 = v25++ + 1 - v13 < 0;
	++v25;
    }
    while ( v25<v13 );
  }
  return 1;
}

//////////////////////////////////////////////////////////////////////////
int __stdcall sub_10002080(signed int a1, signed int a2, signed int a3, float a4, float a5, float a6, float a7, float a8, int a9, int a10, int *a11)
{
  double v12; // st7@1
  double v13; // st6@1
  double v14; // st5@1
  double v15; // st5@1
  float v16; // ST1C_4@1
  float v17; // ST18_4@1
  float v18; // ST14_4@1
  float v19; // ST10_4@1
  float v20; // ST0C_4@1
  float v21; // ST08_4@1
  float v22; // ST04_4@1
  float v23; // ST00_4@1
  float v24; // [sp+30h] [bp+4h]@1

  v12 = (double)a1;
  v13 = (double)a2;
  v14 = (double)a3;
  v24 = v14;
  v15 = v14 * a8 * 0.5;
  v16 = v15 + v12;
  v17 = v12 - v15;
  v18 = v24 * a7 + v13;
  v19 = v12;
  v20 = a5 * -1.0 / v24;
  v21 = v13 - v24 * a6;
  v22 = v12;
  v23 = a4 / v24;
  return sub_10001F90(v23, v22, v21, v20, v19, v18, v17, v16, a9, a10, a11);
}

//////////////////////////////////////////////////////////////////////////
int class_10001000::sub_10002110()
{
  int v1; // eax@1
  class_10001000 *v2; // esi@1
  signed int v3; // ebp@2
  int *v4; // eax@5
  int v5; // edi@5
  int v6; // ecx@5
  int i; // eax@6
  int result; // eax@8
  int v9; // [sp+10h] [bp-Ch]@3
  signed int v10; // [sp+14h] [bp-8h]@3
  signed int v11; // [sp+18h] [bp-4h]@3

  v2 = this;
  v1 = this->m_part12.a9;
  if ( v1 != this->m_part12.a13 || (v3 = this->m_part12.a10, this->m_part12.a10 != this->m_part12.a14) )
  {
    result = 0;
  }
  else
  {
    v9 = this->m_part12.a9;
    v11 = double_to_int64((double)v1 * this->m_part12.a16 / (this->m_part12.a16 + 1.0));
    v10 = v2->m_part12.a15;
    if ( v2->m_part8 )
      free(v2->m_part8);
    v5 = v9 * v3;
    v4 = (int *)malloc(4 * v9 * v3);
    v6 = v2->m_part12.a22;
    v2->m_part8 = v4;
    if ( v6 == 1 )
    {
      for ( i = 0; i < v5; v2->m_part8[i - 1] = 1 )
        ++i;
      result = 1;
    }
    else
    {
      result = sub_10002080(
                 v3 / 2,
                 v11,
                 v10,
                 v2->m_part12.a17,
                 v2->m_part12.a18,
                 v2->m_part12.a19,
                 v2->m_part12.a20,
                 v2->m_part12.a21,
                 v9,
                 v3,
                 v4);
    }
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////
signed int __stdcall sub_10001180(float a1, float a2, float a3, int a4, int a5, int a6, int a7)
{
	
}
//////////////////////////////////////////////////////////////////////////
signed int class_10001000::sub_10001340()
{
  int v1; // ebx@1
  class_10001000 *v2; // edi@1
  int v3; // esi@1
  signed int v4; // eax@7
  int v5; // ebx@8
  void *v6; // eax@12
  int v7; // ebx@12
  int v8; // ebx@12
  int v9; // ebp@14
  float v10; // ST54_4@18
  int v11; // esi@16
  unsigned __int8 v12; // sf@19
  unsigned __int8 v13; // of@19
  int *v15; // [sp+1Ch] [bp-34h]@15
  float v16; // [sp+20h] [bp-30h]@16
  int v17; // [sp+24h] [bp-2Ch]@1
  float v18; // [sp+28h] [bp-28h]@14
  float *v19; // [sp+2Ch] [bp-24h]@7
  int v20; // [sp+2Ch] [bp-24h]@16
  float v21; // [sp+30h] [bp-20h]@1
  int v22; // [sp+30h] [bp-20h]@14
  float v23; // [sp+34h] [bp-1Ch]@1
  float v24; // [sp+38h] [bp-18h]@1
  int v25; // [sp+3Ch] [bp-14h]@15
  int v26; // [sp+48h] [bp-8h]@16
  int v27; // [sp+4Ch] [bp-4h]@1

  v2 = this;
  v3 = this->m_part12.a1;
  v21 = this->m_part12.a3;
  v1 = this->m_part12.a2;
  v23 = this->m_part12.a6;
  v27 = this->m_part12.a1;
  v17 = this->m_part12.a2;
  v24 = this->m_part12.a4 * 0.01745329252;
  if ( this->m_part12.a3 > 0.0 && v23 > 0.0 && v3 >= 1 && v1 >= 1 && this->m_part12.a7 > 0.0 && sub_10001EE0() )
  {
    v19 = v2->m_part9;
    v4 = sub_10001070();
    if ( v4 <= 0 )
      goto LABEL_25;
    v5 = v1 * v4;
    if ( v2->m_part2 )
      free(v2->m_part2);
    if ( v2->m_part3 )
      free(v2->m_part3);
    v8 = 4 * v5;
    v2->m_part2 = malloc(v8);
    v6 = malloc(v8);
    v7 = (int)v2->m_part2;
    v2->m_part3 = v6;
    if ( v7 && v6 )
    {
      v18 = v21;
      v9 = (int)v6;
      v22 = 0;
      if ( v3 <= 0 )
        return 1;
      v15 = v2->m_part4;
      v25 = (char *)v19 - (char *)v2->m_part4;
      while ( 1 )
      {
        v16 = v24;
        v20 = 0;
        v11 = *v15;
        v26 = v11 * v11;
        if ( v17 > 0 )
          break;
LABEL_19:
		++v22;
//         v13 = __SETO__(v22 + 1, v27);
//         v12 = v22++ + 1 - v27 < 0;
        ++v15;
        v18 = v18 * v23;
        if ( v22>=v27 )
          return 1;
      }
      while ( sub_10001180(v18, v16, *(float *)((char *)v15 + v25), v11, v11, v7, v9) )
      {
        v7 += 4 * v26;
        v9 += 4 * v26;
        ++v20;
        v10 = 3.1415926536 / (double)v17;
        v16 = v10 + v16;
        if ( v20 >= v17 )
          goto LABEL_19;
      }
    }
    else
    {
LABEL_25:
      class_10001000_delete_true(v2);
    }
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////
int __stdcall sub_100060E0(float *a1, float *a2, float *a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
  int result; // eax@1
  float *v11; // edx@1
  int i; // ecx@1
  float *v13; // edi@1
  unsigned int v14; // ecx@1
  int v15; // eax@5
  float *v16; // ebx@7
  float *v17; // eax@8
  float *v18; // ecx@8
  int v19; // esi@9
  double v20; // st7@10
  char v22; // zf@12
  int v23; // [sp+0h] [bp-4h]@5
  int v24; // [sp+10h] [bp+Ch]@7
  int v25; // [sp+18h] [bp+14h]@5
  float *v26; // [sp+24h] [bp+20h]@5

  v11 = a3;
  result = 0;
  v14 = (unsigned int)(4 * a10 * a8) >> 2;
  memset(a3, 0, 4 * v14);
  v13 = &a3[v14];
  for ( i = 4 * (_BYTE)a10 * (_BYTE)a8 & 3; i; --i )
  {
    *(_BYTE *)v13 = 0;
    v13 = (float *)((char *)v13 + 1);
  }
  if ( a8 > 0 )
  {
    v15 = a5;
    v25 = a8;
    v23 = 4 * v15;
    v26 = a1;
    do
    {
      if ( a10 > 0 )
      {
        v16 = a2;
        v24 = a10;
        do
        {
          v17 = v26;
          v18 = v16;
          if ( a9 > 0 )
          {
            v19 = a9;
            do
            {
              v20 = *v18 * *v17;
              ++v17;
              v18 += a7;
              --v19;
              *v11 = v20 + *v11;
            }
            while ( v19 );
          }
          ++v16;
          ++v11;
        }
        while ( v24-- != 1 );
      }
      result = v25 - 1;
      v22 = v25 == 1;
      v26 = (float *)((char *)v26 + v23);
      --v25;
    }
    while ( !v22 );
  }
  return result;
}
//////////////////////////////////////////////////////////////////////////
signed int sub_10005060(unsigned __int8 *a1, int a2, int a3, float *a4, int a5, int a6, int a7, int a8)
{
   signed int result; // eax@2
  EyePos v9; // [sp+10h] [bp-670h]@1
  class_100031E0 v13; // [sp+20h] [bp-660h]@1
  char v11; // [sp+3DCh] [bp-2A4h]@1
  //int v12; // [sp+67Ch] [bp-4h]@1

  v9.xleft = a5;
  v9.yleft = a6;
  v9.xright = a7;
  v9.yright = a8;
  //class_100031E0_new(&v13);
  //v12 = 0;
  if ( sub_10003300(&v13, &v11) )
  {
    if ( sub_10004540(&v13, a1, a3, a2, &v9, 1, a4, dword_10553074) )
    {
      v13.class_100031E0_delete_true();
      //v12 = -1;
      //class_100031E0_delete(&v13);
      result = 1;
    }
    else
    {
      v13.class_100031E0_delete_true();
      //v12 = -1;
      //class_100031E0_delete(&v13);
      result = 0;
    }
  }
  else
  {
    //v12 = -1;
    //class_100031E0_delete(&v13);
    result = 0;
  }
  return result;
}

//////////////////////////////////////////////////////////////////////////
signed int sub_100051A0(unsigned __int8 *a1, int a2, int a3, float *a4, int a5, int a6, int a7, int a8, int a9)
{
  float *v9; // esi@2
  //class_10006070 v11; // [sp+Ch] [bp-10h]@1
  //int v12; // [sp+18h] [bp-4h]@1

  //v12 = 0;
  if ( a5 > dword_1055306C || (v9 = (float *)malloc(4 * dword_10553074), !v9) )
    goto LABEL_7;
  memset(v9, 0, 4 * dword_10553074);
  if ( !sub_10005060(a1, a2, a3, v9, a6, a7, a8, a9))
  {
    free(v9);
LABEL_7:
    //v12 = -1;
    //sub_100060A0(&v11);
    return 0;
  }
  sub_100060E0(v9, off_1052B39C, a4, 1, dword_10553074, dword_10553074, dword_10553068, 1, dword_10553074, a5);
  free(v9);
  //v12 = -1;
  return 1;
}
