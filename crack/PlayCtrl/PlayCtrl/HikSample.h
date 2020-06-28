#pragma once

struct BUF_NODE;

class CHikSample
{
public:
	CHikSample(void);
	virtual ~CHikSample(void);

	int AddNode(BUF_NODE *a2,int a3);
	int GetDataNodeCount(ULONG *a2);
	int GetDisplayNode(BUF_NODE** a2);
	int GetNode(BUF_NODE** a2,int a3);
	int GetSpareNodeCount(ULONG *a2);
	int InitBufList(DWORD a2,DWORD Size,DWORD a4,DWORD Alignment);
	int ReconfigNode(BUF_NODE* a2,DWORD Size,DWORD Alignment);
	int ReleaseBufList();
	int RemoveNode(BUF_NODE** a2,int a3);
	int ResetBufList();
	int SetDisplayNode(BUF_NODE* a2,int a3);
	int UsedDataNodeToSpareList(int a2);

protected:
	CRITICAL_SECTION m_cs;
	CBufList m_cDataNode;
	CBufList m_cSpareNode;
	BUF_NODE* m_pDisplayNode;
};
