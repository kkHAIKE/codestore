#include "StdAfx.h"
#include "MediaManager.h"

CMediaManager::CMediaManager(void)
{
	part11 = 1.0;
	part10 = 1;
	part12 = 0xAA;
	part1 = 0;
	part2 = 0;
	m_cVDec = NULL;
	m_cADec = NULL;
	part5 = 0;
	part8 = 0;
	part6 = 0;
	part7 = 0;
	part9 = 0;
	part22 = 0;
	part23 = 1;
	part27 = 3;
	part24 = 1;
	part25 = 15;
	part26 = 25;
	part28 = 0;
	part30 = 0;
	part32 = 0;
	memset(part13,0, 36);
	memset(part34, 0, 20);
	memset(part39, 0, 40);
	part49 = 0;
	part50 = 0;
	part51 = 1;
}

CMediaManager::~CMediaManager(void)
{
	Release();
	part12 = 0;
}

int CMediaManager::Initial()
{
	try
	{

	}catch()
	{
		_LOG_RECORD("CMediaManager::Initial failed to new!\n");

	}
	try
	{
		
	}catch()
	{
		Release();
	}
}

void CMediaManager::Release()
{
	if ( !part23 )
	{
		if ( m_bIsFile )
			CloseFile();
		else
			CloseStream();
	}
	DeConstructAll();

	if ( m_cTimer )
	{delete m_cTimer;m_cTimer = NULL;}

	if ( m_cAudRender )
	{delete m_cAudRender;m_cAudRender = NULL;}

	if ( m_cVidRender )
	{delete m_cVidRender;m_cVidRender = NULL;}

	if ( m_cVidTrans )
	{delete m_cVidTrans;m_cVidTrans = NULL;}

	if ( m_cADec )
	{delete m_cADec;m_cADec = NULL;}

	if ( m_cVDec )
	{delete m_cVDec;m_cVDec = NULL;}

	if ( m_cPDec )
	{delete m_cPDec;m_cPDec = NULL;}

	if ( m_cDemux )
	{delete m_cDemux;m_cDemux=NULL;}

	if (m_cSource )
	{delete m_cSource;m_cSource=NULL;}

	if ( m_cImage )
	{delete m_cImage;m_cImage=NULL;}
}

void CMediaManager::DeConstructAll()
{
	if ( m_cSource )
		m_cSource->ReleaseSource();

	if ( m_cDemux )
		m_cDemux->ReleaseDemux();

	if ( m_cVDec )
		m_cVDec->ReleaseVDec();

	if ( m_cADec )
		m_cADec->ReleaseADec();

	if ( m_cPDec )
		m_cPDec->ReleasePDec();

	if ( m_cVidTrans )
		m_cVidTrans->ReleaseTransform();

	if ( m_cVidRender )
		m_cVidRender->ReleaseVR();

	if ( m_cAudRender )
		m_cAudRender->ReleaseAR();
}

int CMediaManager::DisconnectAll()
{
	if ( m_cSource )
		CHikSource::Disconnect();
	if ( m_cDemux )
		m_cDemux->Disconnect();
	if ( m_cVDec )
		CHikVDec::Disconnect();
	if ( m_cADec )
		CHikADec::Disconnect();
	if ( m_cPDec )
		CHikPDec::Disconnect();
	if ( m_cVidRender )
		m_cVidRender->Disconnect();
	if ( m_cAudRender )
		CAudioRenderer::Disconnect();

	return 0;
}

int CMediaManager::Close()
{
	int result; // eax@5

	if ( m_cTimer )
		CHikTimer::AppOperation(4);
	DisconnectAll();

	if ( !m_cVidRender || !m_cVidRender->IsInit() || (result = m_cVidRender->AppOperation(4)) == 0 )
	{
		if ( !m_cAudRender || !m_cAudRender->IsInit() || (result = m_cAudRender->AppOperation(4)) == 0 )
		{
			if ( !m_cVidTrans || !m_cVidTrans->IsInit() || (result = m_cVidTrans->AppOperation(4)) == 0 )
			{
				if ( !m_cVDec || !m_cVDec->IsInit() || (result = m_cVDec->AppOperation(4)) == 0 )
				{
					if ( !m_cADec || !m_cADec->IsInit() || (result = m_cADec->AppOperation(4)) == 0 )
					{
						if ( !m_cPDec || !m_cPDec->IsInit() || (result = m_cPDec->AppOperation(4)) == 0 )
						{
							if ( !m_cDemux || (result = m_cDemux->AppOperation(4)) == 0 )
							{
								m_nStatus = 3;
								result = 0;
							}
						}
					}
				}
			}
		}
	}
	return result;
}

int CMediaManager::Stop()
{
	int result; // eax@5

	part11 = 1.0;
	SetPlaySpeed(1.0);

	if ( m_cTimer )
		CHikTimer::AppOperation(3);

	if ( !m_cVidRender || !m_cVidRender->IsInit() || (result = m_cVidRender->AppOperation(3)) == 0 )
	{
		if ( !m_cAudRender || !m_cAudRender->IsInit() || (result = m_cAudRender->AppOperation(3)) == 0 )
		{
			if ( !m_cVidTrans || !m_cVidTrans->IsInit() || (result = m_cVidTrans->AppOperation(3)) == 0 )
			{
				if ( !m_cVDec || !m_cVDec->IsInit() || (result = m_cVDec->AppOperation(3)) == 0 )
				{
					if ( !m_cADec || !m_cADec->IsInit() || (result = m_cADec->AppOperation(3)) == 0 )
					{
						if ( !m_cPDec || !m_cPDec->IsInit() || (result = m_cPDec->AppOperation(3)) == 0 )
						{
							if ( !m_cDemux || (result = m_cDemux->AppOperation(3)) == 0 )
							{
								if ( !m_cSource || (result = m_cSource->AppOperation(3)) == 0 )
								{
									ResetBuffer(4);
									ResetBuffer(5);
									m_nStatus = 2;
									result = 0;
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}

int CMediaManager::TryClose()
{
	if ( m_nStatus < 0 )
		return -2147483632;
	if ( m_nStatus <= 1 )
	{
		Stop();
	}
	else if ( m_nStatus != 2 )
	{
		if ( m_nStatus == 3 )
			return -2147483639;
		if ( m_nStatus <= 3 || m_nStatus > 6 )
			return -2147483632;
		Stop();
	}
	return Close();
}

int CMediaManager::CloseFile()
{
	int result;

	TryClose();
	if ( m_cSource )
		result = m_cSource->CloseFile();
	else
		result = -2147483646;
	return result;
}

int CMediaManager::CloseStream()
{
	int result;

	TryClose();
	if ( !m_cSource || (result = m_cSource->CloseStream(m_cSource)) == 0 )
	{
		if ( part49)
		{
			delete part49;
			part49 = NULL;
		}
		result = 0;
	}
	return result;
}

int CMediaManager::ResetBuffer( ULONG a2 )
{
	if ( a2 )
	{
		if ( a2 != 1 )
		{
			if ( a2 == 4 )
			{
				if ( m_cVidTrans )
					return m_cVidTrans->ResetDisplayBuffer();
			}
			else
			{
				if ( a2 != 5 )
					return -2147483632;
				if ( m_cAudRender )
					return m_cAudRender->ResetPlayBuffer();
			}
			return -2147483646;
		}

		if ( m_cSource && m_cDemux )
		{
			m_cSource->ResetSrcStreamBuf(1);
			m_cDemux->ResetDemuxBuffer(1);
			return 0;
		}
	}
	else
	{

		if ( m_cSource && m_cDemux )
		{
			m_cSource->ResetSrcStreamBuf(0);
			m_cDemux->ResetDemuxBuffer(0);
			return 0;
		}
	}
	return -2147483646;
}

int CMediaManager::SetPlaySpeed( float a2 )
{
	if ( m_cSource )
		m_cSource->SetPlaySpeed(a2);

	if ( m_cDemux )
		m_cDemux->SetPlaySpeed(a2);

	if ( m_cVDec && m_cVDec->IsInit() )
		m_cVDec->SetPlaySpeed(a2);

	if ( m_cVidRender && m_cVidRender->IsInit() )
		m_cVidRender->SetPlaySpeed(a2);

	if ( m_cADec && m_cADec->IsInit() )
		m_cADec->SetPlaySpeed(a2);

	if ( m_cPDec && m_cPDec->IsInit() )
		m_cPDec->SetPlaySpeed(a2);

	if ( m_cAudRender && m_cAudRender->IsInit() )
		m_cAudRender->SetPlaySpeed(a2);

	if ( m_cTimer )
		m_cTimer->SetPlaySpeed(a2);
	return 0;
}

int CMediaManager::VenderIVS( int a2 )
{
	int result;

	if ( m_cVidRender )
	{
		part51 = a2;
		if ( a2 )
			result = m_cVidRender->EnableIVS();
		else
			result = m_cVidRender->DisableIVS();
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CMediaManager::TryFast()
{
	if ( m_nStatus )
	{
		if ( m_nStatus == 1 )
		{
			Resume();
		}
		else
		{
			if ( m_nStatus <= 1 )
				return -2147483632;
			if ( m_nStatus <= 3 )
				return -2147483639;
			if ( m_nStatus > 5 )
			{
				if ( m_nStatus != 6 )
					return -2147483632;
				return -2147483639;
			}
			Play();
		}
	}
	return Fast();
}

int CMediaManager::Resume()
{
	int result; // eax@5

	if ( m_cTimer )
		CHikTimer::AppOperation(2);

	if ( !m_cVidRender || !m_cVidRender->IsInit() || (result = m_cVidRender->AppOperation(2)) == 0 )
	{
		if ( !m_cAudRender || !m_cAudRender->IsInit() || (result = m_cAudRender->AppOperation(2)) == 0 )
		{
			if ( !m_cVDec || !m_cVDec->IsInit() || (result = m_cVDec->AppOperation(2)) == 0 )
			{
				if ( !m_cADec || !m_cADec->IsInit() || (result = m_cADec->AppOperation(2)) == 0 )
				{
					if ( !m_cPDec || !m_cPDec->IsInit() || (result = m_cPDec->AppOperation(2)) == 0 )
					{
						if ( !m_cDemux || (result = m_cDemux->AppOperation(2)) == 0 )
						{
							if ( !m_cSource || (result = m_cSource->AppOperation(2)) == 0 )
							{
								if ( !m_cVidTrans || !m_cVidTrans->IsInit() || (result = m_cVidTrans->AppOperation(2)) == 0 )
								{
									m_nStatus = 0;
									result = 0;
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}

int CMediaManager::Play()
{

}

int CMediaManager::AdjustWaveAudio( long a2 )
{
	int result; // eax@2

	if ( m_cAudRender )
		result = m_cAudRender->AdjustWaveAudio(a2);
	else
		result = -2147483646;
	return result;
}

int CMediaManager::AftSetPos( int a2 )
{
	int v3;

	try
	{
		if ( a2 )
		{
			v3 = 1;
			if ( a2 != 1 )
			{
				if ( a2 <= 1 )
					return -2147483645;
				if ( a2 <= 3 )
					return -2147483639;
				if ( a2 == 4 )
				{
					v3 = 8;
				}
				else
				{
					if ( a2 != 5 )
					{
						if ( a2 != 6 )
							return -2147483645;
						return -2147483639;
					}
					v3 = 9;
				}
			}

			if ( m_cTimer )
				m_cTimer->AppOperation(v3);

			if ( m_cVidRender && m_cVidRender->IsInit() && m_cVidRender->AppOperation(v3) )
			{
				throw 0;
			}

			if ( m_cVDec && m_cVDec->IsInit() && m_cVDec->AppOperation(v3) )
			{
				throw 0;
			}

			if ( m_cADec && m_cADec->IsInit() && m_cADec->AppOperation(v3) )
			{
				throw 0;
			}

			if ( m_cPDec && m_cPDec->IsInit() && m_cPDec->AppOperation(v3) )
			{
				throw 0;
			}

			if ( m_cDemux && m_cDemux->AppOperation(v3) )
			{
				throw 0;
			}
			if ( m_cSource && m_cSource->AppOperation(v3))
			{
				throw 0;
			}
		}
	}catch(int err)
	{
		return err;
	}
	return 0;
}

int CMediaManager::AnalyzeFile( LPCSTR a2,IVSPLAY_MEDIA_INFO* a3 )
{
	
}

