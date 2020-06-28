#pragma once

typedef struct _BUF_NODE
{
	BYTE* data1;
	int size1;
	int part3;
	BYTE* data2;
	int size2;
	int part6;
	_BUF_NODE* next;
	_BUF_NODE* prev;
	CRITICAL_SECTION cs;
}BUF_NODE;

class CBufList
{
public:
	CBufList(void);
	~CBufList(void);

	int InitBufList(DWORD a2,DWORD Size,DWORD a4,DWORD Alignment);
	void RemoveAll();
	void AddTail(BUF_NODE* a2);
	void AddHead(BUF_NODE* a2);
	int GetEleCount();
	BUF_NODE* GetHead();
	BUF_NODE* GetTail();
	BUF_NODE* RemoveHead();
	BUF_NODE* RemoveTail();

protected:
	BUF_NODE* m_pBegin;
	BUF_NODE* m_pEnd;
	int m_nCount;
};
