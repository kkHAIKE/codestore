#pragma once
//Std0
template<typename _ADDR>
inline int AnyCallStd(_ADDR addr)
{
	int r;
	__asm
	{
		call addr;
		mov r,eax;
	}
	return r;
}
//Std1
template<typename _ADDR,typename _P1>
inline int AnyCallStd(_ADDR addr,_P1 p1)
{
	int r;
	__asm
	{
		push p1;
		call addr;
		mov r,eax;
	}
	return r;
}
//Std2
template<typename _ADDR,typename _P1,typename _P2>
inline int AnyCallStd(_ADDR addr,_P1 p1,_P2 p2)
{
	int r;
	__asm
	{
		push p2;
		push p1;
		call addr;
		mov r,eax;
	}
	return r;
}
//Std3
template<typename _ADDR,typename _P1,typename _P2,typename _P3>
inline int AnyCallStd(_ADDR addr,_P1 p1,_P2 p2,_P3 p3)
{
	int r;
	__asm
	{
		push p3;
		push p2;
		push p1;
		call addr;
		mov r,eax;
	}
	return r;
}
//Std4
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4>
inline int AnyCallStd(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4)
{
	int r;
	__asm
	{
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		mov r,eax;
	}
	return r;
}
//Std5
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5>
inline int AnyCallStd(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5)
{
	int r;
	__asm
	{
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		mov r,eax;
	}
	return r;
}
//Std6
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6>
inline int AnyCallStd(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6)
{
	int r;
	__asm
	{
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		mov r,eax;
	}
	return r;
}
//Std7
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6,typename _P7>
inline int AnyCallStd(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6,_P7 p7)
{
	int r;
	__asm
	{
		push p7;
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		mov r,eax;
	}
	return r;
}
//Std8
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6,typename _P7,typename _P8>
inline int AnyCallStd(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6,_P7 p7,_P8 p8)
{
	int r;
	__asm
	{
		push p8;
		push p7;
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		mov r,eax;
	}
	return r;
}
//Std9
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6,typename _P7,typename _P8,typename _P9>
inline int AnyCallStd(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6,_P7 p7,_P8 p8,_P9 p9)
{
	int r;
	__asm
	{
		push p9;
		push p8;
		push p7;
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		mov r,eax;
	}
	return r;
}
//////////////////////////////////////////////////////////////////////////
//Cdecl0
template<typename _ADDR>
inline int AnyCallCdecl(_ADDR addr)
{
	int r;
	__asm
	{
		call addr;
		mov r,eax;
	}
	return r;
}
//Cdecl1
template<typename _ADDR,typename _P1>
inline int AnyCallCdecl(_ADDR addr,_P1 p1)
{
	int r;
	__asm
	{
		push p1;
		call addr;
		add esp,4;
		mov r,eax;
	}
	return r;
}
//Cdecl2
template<typename _ADDR,typename _P1,typename _P2>
inline int AnyCallCdecl(_ADDR addr,_P1 p1,_P2 p2)
{
	int r;
	__asm
	{
		push p2;
		push p1;
		call addr;
		add esp,8;
		mov r,eax;
	}
	return r;
}
//Cdecl3
template<typename _ADDR,typename _P1,typename _P2,typename _P3>
inline int AnyCallCdecl(_ADDR addr,_P1 p1,_P2 p2,_P3 p3)
{
	int r;
	__asm
	{
		push p3;
		push p2;
		push p1;
		call addr;
		add esp,12;
		mov r,eax;
	}
	return r;
}
//Cdecl4
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4>
inline int AnyCallCdecl(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4)
{
	int r;
	__asm
	{
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		add esp,16;
		mov r,eax;
	}
	return r;
}
//Cdecl5
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5>
inline int AnyCallCdecl(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5)
{
	int r;
	__asm
	{
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		add esp,20;
		mov r,eax;
	}
	return r;
}
//Cdecl6
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6>
inline int AnyCallCdecl(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6)
{
	int r;
	__asm
	{
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		add esp,24;
		mov r,eax;
	}
	return r;
}
//Cdecl7
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6,typename _P7>
inline int AnyCallCdecl(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6,_P7 p7)
{
	int r;
	__asm
	{
		push p7;
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		add esp,28;
		mov r,eax;
	}
	return r;
}
//Cdecl8
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6,typename _P7,typename _P8>
inline int AnyCallCdecl(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6,_P7 p7,_P8 p8)
{
	int r;
	__asm
	{
		push p8;
		push p7;
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		add esp,32;
		mov r,eax;
	}
	return r;
}
//Cdecl9
template<typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6,typename _P7,typename _P8,typename _P9>
inline int AnyCallCdecl(_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6,_P7 p7,_P8 p8,_P9 p9)
{
	int r;
	__asm
	{
		push p9;
		push p8;
		push p7;
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		call addr;
		add esp,36;
		mov r,eax;
	}
	return r;
}
//////////////////////////////////////////////////////////////////////////
//This0
template<typename _PCLASS,typename _ADDR>
inline int AnyCallThis(_PCLASS p,_ADDR addr)
{
	int r;
	__asm
	{
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}
//This1
template<typename _PCLASS,typename _ADDR,typename _P1>
inline int AnyCallThis(_PCLASS p,_ADDR addr,_P1 p1)
{
	int r;
	__asm
	{
		push p1;
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}
//This2
template<typename _PCLASS,typename _ADDR,typename _P1,typename _P2>
inline int AnyCallThis(_PCLASS p,_ADDR addr,_P1 p1,_P2 p2)
{
	int r;
	__asm
	{
		push p2;
		push p1;
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}
//This3
template<typename _PCLASS,typename _ADDR,typename _P1,typename _P2,typename _P3>
inline int AnyCallThis(_PCLASS p,_ADDR addr,_P1 p1,_P2 p2,_P3 p3)
{
	int r;
	__asm
	{
		push p3;
		push p2;
		push p1;
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}
//This4
template<typename _PCLASS,typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4>
inline int AnyCallThis(_PCLASS p,_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4)
{
	int r;
	__asm
	{
		push p4;
		push p3;
		push p2;
		push p1;
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}
//This5
template<typename _PCLASS,typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5>
inline int AnyCallThis(_PCLASS p,_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5)
{
	int r;
	__asm
	{
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}
//This6
template<typename _PCLASS,typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6>
inline int AnyCallThis(_PCLASS p,_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6)
{
	int r;
	__asm
	{
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}
//This7
template<typename _PCLASS,typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6,typename _P7>
inline int AnyCallThis(_PCLASS p,_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6,_P7 p7)
{
	int r;
	__asm
	{
		push p7;
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}
//This8
template<typename _PCLASS,typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6,typename _P7,typename _P8>
inline int AnyCallThis(_PCLASS p,_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6,_P7 p7,_P8 p8)
{
	int r;
	__asm
	{
		push p8;
		push p7;
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}
//This9
template<typename _PCLASS,typename _ADDR,typename _P1,typename _P2,typename _P3,typename _P4,typename _P5,typename _P6,typename _P7,typename _P8,typename _P9>
inline int AnyCallThis(_PCLASS p,_ADDR addr,_P1 p1,_P2 p2,_P3 p3,_P4 p4,_P5 p5,_P6 p6,_P7 p7,_P8 p8,_P9 p9)
{
	int r;
	__asm
	{
		push p9;
		push p8;
		push p7;
		push p6;
		push p5;
		push p4;
		push p3;
		push p2;
		push p1;
		mov ecx,p;
		call addr;
		mov r,eax;
	}
	return r;
}