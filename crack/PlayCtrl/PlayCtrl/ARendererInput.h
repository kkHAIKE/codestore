#pragma once

class CHikARenderer;

class CARendererInput:public IHikInput
{
public:
	CARendererInput(void);

	int InputData(BYTE *Dst,ULONG a3,ULONG a4);
	static int SetInputSample(CHikSample *a2);
	~CARendererInput(void);

	int SetParent(CHikARenderer* a2);

protected:
	CHikARenderer *m_pAudRender;
	int part3;
};
