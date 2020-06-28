#pragma once

class CHikSample;
class CHikVRenderer;

class CHikVRInput:public IHikInput
{
public:
	CHikVRInput(void);

	int InputData(BYTE *Dst,ULONG a3,ULONG a4);
	static int SetInputSample(CHikSample *a2);
	~CHikVRInput(void);

	void SetParent(CHikVRenderer* a2);

protected:
	CHikVRenderer *m_pVidRender;
	DISPLAY_PARA *m_pPara;
};
