#pragma once

#include <Debug.h>

class CThunk
{
private:
	CThunk(const CThunk &);
	void operator=(const CThunk &);

	BYTE* m_code;
	void tfree()
	{
		if(m_code)
		{
			VirtualFree(m_code,0,MEM_RELEASE);
			m_code=NULL;
		}
	}
	void talloc()
	{
		tfree();
		m_code=reinterpret_cast<BYTE*>(VirtualAlloc(NULL,16, MEM_COMMIT,PAGE_EXECUTE_READWRITE));
		ASSERT(m_code);
	}

public:
	enum CALLINGCONVENTIONS
	{
		STDCALL = 1,
		THISCALL= 2
	};
	CThunk():m_code(NULL) {};
	~CThunk() {tfree();};

	template <class T>
	void* Init(void* pThis,T MemberOffset,CALLINGCONVENTIONS CallingConvention = STDCALL)
	{
		union
		{
			T From;
			DWORD To;
		} union_cast;

		// these codes only use in stdcall
		if(CallingConvention == STDCALL)
		{
			// Encoded machine instruction Equivalent assembly languate notation
			// --------------------------- -------------------------------------
			// FF 34 24 push dword ptr [esp] ; Save (or duplicate) ; the Return Addr into stack
			// C7 44 24 04 ?? ?? ?? ?? mov dword ptr [esp+4], pThis ; Overwite the old ; Return Addr with 'this pointer'
			// E9 ?? ?? ?? ?? jmp target addr ; Jump to target message handler

			// char Buf[33]={0};
			// sprintf(Buf,"%d",MemberOffset);

			talloc();

			union_cast.From = MemberOffset;
			DWORD JmpAddr = union_cast.To -  reinterpret_cast<DWORD>(&m_code[0]) - 16;

			m_code[11] = 0xE9;
			*(reinterpret_cast<DWORD*>(&m_code[ 0])) = 0x002434FF;
			*(reinterpret_cast<DWORD*>(&m_code[ 3])) = 0x042444C7;
			*(reinterpret_cast<DWORD*>(&m_code[ 7])) = reinterpret_cast<DWORD>(pThis);
			*(reinterpret_cast<DWORD*>(&m_code[12])) = JmpAddr;

			FlushInstructionCache(GetCurrentProcess(),m_code,16);

			return m_code;
		}
		// these codes only use in thiscall
		else if(CallingConvention == THISCALL)
		{
			// Encoded machine instruction Equivalent assembly languate notation
			// --------------------------- -------------------------------------
			// B9 ?? ?? ?? ?? mov ecx, pThis ; Load ecx with this pointer
			// E9 ?? ?? ?? ?? jmp target addr ; Jump to target message handler
			talloc();

			union_cast.From = MemberOffset;
			DWORD JmpAddr = union_cast.To -  reinterpret_cast<DWORD>(&m_code[0]) - 10;

			m_code[0] = 0xB9;
			m_code[5] = 0xE9;
			*(reinterpret_cast<DWORD*>(&m_code[1])) = reinterpret_cast<DWORD>(pThis);
			*(reinterpret_cast<DWORD*>(&m_code[6])) = JmpAddr;

			FlushInstructionCache(GetCurrentProcess(),m_code,16);
			return m_code;
		}
		return NULL;
	}
	void* Callback()
	{
		return m_code;
	}
};
