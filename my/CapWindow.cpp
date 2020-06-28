#include "StdAfx.h"
#include "CapWindow.h"

#include <memory>

#pragma comment(lib,"strmiids.lib")
#pragma comment(lib,"Wmvcore.lib")
//////////////////////////////////////////////////////////////////////////
TCHAR g_profile_wmv9_fuck_fmt[]=L"        <profile version=\"589824\" "
L"             storageformat=\"1\" "
L"             name=\"WMV9 fuck\" "
L"             description=\"\"> "
L"                   <streamconfig majortype=\"{73646976-0000-0010-8000-00AA00389B71}\" "
L"                   streamnumber=\"1\" "
L"                   streamname=\"Video Stream\" "
L"                   inputname=\"Video804\" "
L"                   bitrate=\"7000\" "
L"                   bufferwindow=\"5000\" "
L"                   reliabletransport=\"0\" "
L"                   decodercomplexity=\"AU\" "
L"                   rfc1766langid=\"zh-cn\" "
L"                           vbrenabled=\"1\" "
L"                           vbrquality=\"80\" "
L"                           bitratemax=\"0\" "
L"                           bufferwindowmax=\"0\"> "
L"                     <videomediaprops maxkeyframespacing=\"80000000\" "
L"                                     quality=\"35\"/> "
L"             <wmmediatype subtype=\"{33564D57-0000-0010-8000-00AA00389B71}\"  "
L"                   bfixedsizesamples=\"0\" "
L"                   btemporalcompression=\"1\" "
L"                   lsamplesize=\"0\"> "
L"       <videoinfoheader dwbitrate=\"7000\" "
L"                        dwbiterrorrate=\"0\" "
L"                        avgtimeperframe=\"400000\"> "
L"        <rcsource left=\"0\" "
L"                  top=\"0\" "
L"                  right=\"0\" "
L"                  bottom=\"0\"/> "
L"        <rctarget left=\"0\" "
L"                  top=\"0\" "
L"                  right=\"0\" "
L"                  bottom=\"0\"/> "
L"            <bitmapinfoheader biwidth=\"%d\" "
L"                              biheight=\"%d\" "
L"                              biplanes=\"1\" "
L"                              bibitcount=\"24\" "
L"                              bicompression=\"WMV3\" "
L"                              bisizeimage=\"0\" "
L"                              bixpelspermeter=\"0\" "
L"                              biypelspermeter=\"0\" "
L"                              biclrused=\"0\" "
L"                              biclrimportant=\"0\"/> "
L"       </videoinfoheader>"
L"            </wmmediatype>"
L"            </streamconfig>"
L"    </profile> ";

//////////////////////////////////////////////////////////////////////////
#define ENUM_FOREACH_BEGIN_X(x,e,f)  e->Reset(); \
	for(ULONG feched=0;SUCCEEDED(e->Next(1,&x,&feched))&&feched;f)if(x){
	//ULONG feched=0;			\
	//while(SUCCEEDED(e->Next(1,&x,&feched))&&feched){	\
	//if(x){
	//while(SUCCEEDED(e->Next(1,&x,NULL))){	\	
#define ENUM_FOREACH_BEGIN(x,e)  ENUM_FOREACH_BEGIN_X(x,e,x.Release())
#define ENUM_FOREACH_END()	}
//#define ENUM_FOREACH_END(x)	x.Release();}}
//////////////////////////////////////////////////////////////////////////
template<typename T>
class ArrayWrap
{
public:
	ArrayWrap(T* a):m_a(a){}
	~ArrayWrap()
	{
		if(m_a)
			{delete[] m_a;m_a=NULL;}
	}
	T* get(){return m_a;}
protected:
	T* m_a;
};
//////////////////////////////////////////////////////////////////////////
template<typename T>
void FreeMediaType(T& mt)
{
	if (mt.cbFormat != 0)
	{
		CoTaskMemFree((PVOID)mt.pbFormat);
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if (mt.pUnk != NULL)
	{
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
}
template<typename T>
void DeleteMediaType(T *pmt)
{
	if (pmt != NULL)
	{
		FreeMediaType(*pmt); 
		CoTaskMemFree(pmt);
	}
}
//////////////////////////////////////////////////////////////////////////
HRESULT GetPinCategory(IPinPtr &pPin, GUID *pPinCategory )
{
	HRESULT hr;
	IKsPropertySetPtr pKs;
	hr = pPin->QueryInterface(IID_IKsPropertySet, (void **)&pKs);
	if (FAILED(hr))
		return hr;

	DWORD cbReturned;
	hr = pKs->Get(AMPROPSETID_Pin, AMPROPERTY_PIN_CATEGORY, NULL, 0, 
		pPinCategory, sizeof(GUID), &cbReturned);

	return hr;
}
//////////////////////////////////////////////////////////////////////////
CVideoDevice::CVideoDevice(void)
{
	ICreateDevEnumPtr enumHardware(CLSID_SystemDeviceEnum,NULL,CLSCTX_INPROC_SERVER);

	IEnumMonikerPtr enumMoniker=NULL;
	_com_util::CheckError(enumHardware->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&enumMoniker,0));
	if(enumMoniker==NULL)
		return;

	IMonikerPtr moniker=NULL;
	ENUM_FOREACH_BEGIN(moniker,enumMoniker)
		std::auto_ptr<MYDEVICE> device(new MYDEVICE);

		WCHAR* wzDisplayName=NULL;
		_com_util::CheckError(moniker->GetDisplayName(NULL,NULL,&wzDisplayName));
		if(wzDisplayName)
		{
			device->displayName=wzDisplayName;
			CoTaskMemFree(wzDisplayName);
		}

		IPropertyBagPtr propertyBag=NULL;
		_com_util::CheckError(moniker->BindToStorage(0,0,IID_IPropertyBag,(void**)&propertyBag));
		_variant_t name;name.ChangeType(VT_BSTR);
		_com_util::CheckError(propertyBag->Read(_T("FriendlyName"),name.GetAddress(),NULL));
		device->friendlyName=static_cast<TCHAR*>(static_cast<_bstr_t>(name));

		moniker->BindToObject(0,0,IID_IBaseFilter,(void**)&device->filter);

		if(device->filter)
			m_DeviceList.push_back(device.release());

	ENUM_FOREACH_END()
}

CVideoDevice& CVideoDevice::Instance()
{
	static CVideoDevice instance;
	return instance;
}
CVideoDevice::MYMEDIA::~MYMEDIA()
{
	if(pMedia)
	{
		DeleteMediaType(pMedia);
		pMedia=NULL;
	}
}
void CVideoDevice::InitMedialist( int id )
{
	m_MediaListCapt.clear_delete();
	m_MediaListPrev.clear_delete();

	IBaseFilterPtr &pCameraFilter=CVideoDevice::Instance().GetFilter(id);

	IAMVideoControlPtr vctrl=NULL;
	if(FAILED(pCameraFilter->QueryInterface(&vctrl)) || vctrl==NULL)
		return;

	IEnumPinsPtr enumpin=NULL;
	_com_util::CheckError(pCameraFilter->EnumPins(&enumpin));
	ASSERT(enumpin!=NULL);

	IPinPtr pin=NULL;
	ENUM_FOREACH_BEGIN(pin,enumpin)
		PIN_DIRECTION pd;
		VERIFY(SUCCEEDED(pin->QueryDirection(&pd)));
		if(pd==PINDIR_INPUT)
			continue;

		GUID guid;
		bool bCapt;
		if(FAILED(GetPinCategory(pin,&guid)))
			continue;
		if(memcmp(&guid,&PIN_CATEGORY_CAPTURE,sizeof(GUID))==0)
			bCapt=true;
		else if(memcmp(&guid,&PIN_CATEGORY_PREVIEW,sizeof(GUID))==0)
			bCapt=false;
		else
			continue;

		Pass(pin,bCapt,vctrl);
	ENUM_FOREACH_END()
}

void CVideoDevice::Pass( IPinPtr &pin ,bool bCapt,IAMVideoControlPtr &vctrl)
{
	IAMStreamConfigPtr amconf=NULL;
	_com_util::CheckError(pin->QueryInterface(&amconf));
	ASSERT(amconf!=NULL);

	int iCount,iSize;
	_com_util::CheckError(amconf->GetNumberOfCapabilities(&iCount, &iSize));

	if(iCount==0)
		return;

	std::auto_ptr<ArrayWrap<BYTE>> videocap(new ArrayWrap<BYTE>(new BYTE[iSize]));
	for(int i=0;i<iCount;++i)
	{
		std::auto_ptr<MYMEDIA> media(new MYMEDIA);
		_com_util::CheckError(amconf->GetStreamCaps(i,&media->pMedia,videocap.get()->get()));

		if(media->pMedia->majortype==MEDIATYPE_Video && 
		    media->pMedia->formattype == FORMAT_VideoInfo &&
			media->pMedia->cbFormat >= sizeof (VIDEOINFOHEADER) &&
			media->pMedia->pbFormat != NULL)
		{
			TCHAR fourcc[5];fourcc[4]=0;
			fourcc[3]=(media->pMedia->subtype.Data1>>24)&0xff;
			fourcc[2]=(media->pMedia->subtype.Data1>>16)&0xff;
			fourcc[1]=(media->pMedia->subtype.Data1>>8)&0xff;
			fourcc[0]=media->pMedia->subtype.Data1&0xff;

			VIDEOINFOHEADER *pVih = reinterpret_cast<VIDEOINFOHEADER*>(media->pMedia->pbFormat);

			media->mediaCont.Format(_T("%s,%d*%d,%.1f"),fourcc,pVih->bmiHeader.biWidth,pVih->bmiHeader.biHeight,static_cast<float>(10000000.0/(pVih->AvgTimePerFrame)));
			TRACE(LPCTSTR(media->mediaCont));

			SIZE rc={pVih->bmiHeader.biWidth,pVih->bmiHeader.biHeight};
			long szList=0;LONGLONG *rateList=NULL;
			_com_util::CheckError(vctrl->GetFrameRateList(pin,i,rc,&szList,&rateList));
			for(int j=0;j<szList;++j)
			{
				media->rateList.push_back(10000000.0/rateList[j]);
			}
			if(rateList)
				CoTaskMemFree(rateList);
			//VIDEO_STREAM_CONFIG_CAPS *caps=reinterpret_cast<VIDEO_STREAM_CONFIG_CAPS*>(videocap.get()->get());
			if(bCapt)
			{
				m_MediaListCapt.push_back(media.release());
				TRACE(_T("capt:%d"),m_MediaListCapt.size()-1);
			}
			else
			{
				m_MediaListPrev.push_back(media.release());
				TRACE(_T("prev:%d"),m_MediaListPrev.size()-1);
			}
		}
	}
}

void CVideoDevice::SetFPS( MYMEDIA *media ,float fps)
{
	VIDEOINFOHEADER *pVih = reinterpret_cast<VIDEOINFOHEADER*>(media->pMedia->pbFormat);
	pVih->AvgTimePerFrame=static_cast<LONGLONG>(10000000.0/fps);
}
//////////////////////////////////////////////////////////////////////////
class CPinConnHelper
{
public:
	explicit CPinConnHelper(IBaseFilterPtr &pBaseFilter):
	m_pGraphBuilder(getBuilder(pBaseFilter)),m_pBaseFilter(pBaseFilter),m_pPin(NULL)
		,m_bDirect(false),m_pmt(NULL),m_bNotAdd(false)
	{}
	CPinConnHelper(IGraphBuilderPtr &pGraphBuilder,IBaseFilterPtr &pBaseFilter,bool notadd=false):
	m_pGraphBuilder(pGraphBuilder),m_pBaseFilter(pBaseFilter),m_pPin(NULL)
		,m_bDirect(false),m_pmt(NULL),m_bNotAdd(notadd)
	{}
	CPinConnHelper(IGraphBuilderPtr &pGraphBuilder,const WCHAR *name):
	m_pGraphBuilder(pGraphBuilder),m_pBaseFilter(NULL),m_pPin(NULL)
		,m_bDirect(false),m_pmt(NULL),m_bNotAdd(false)
	{
		_com_util::CheckError(pGraphBuilder->FindFilterByName(name,&m_pBaseFilter));
		ASSERT(m_pBaseFilter!=NULL);
	}
	explicit CPinConnHelper(IPinPtr &pPin):
	m_pGraphBuilder(getBuilder(getBase(pPin))),m_pBaseFilter(NULL),m_pPin(pPin)
		,m_bDirect(false),m_pmt(NULL),m_bNotAdd(false)
	{}
	CPinConnHelper(IGraphBuilderPtr &pGraphBuilder,IPinPtr &pPin):
	m_pGraphBuilder(pGraphBuilder),m_pBaseFilter(NULL),m_pPin(pPin)
		,m_bDirect(false),m_pmt(NULL),m_bNotAdd(false)
	{}

	CPinConnHelper& setDirect(bool bDirect=true,AM_MEDIA_TYPE *pmt=NULL)
	{
		m_bDirect=bDirect;
		m_pmt=pmt;
		return *this;
	}

	IPinPtr operator >> (IPinPtr &pin)
	{
		if(m_pPin)
		{
			if(m_bDirect)
			{_com_util::CheckError(m_pGraphBuilder->ConnectDirect(m_pPin,pin,m_pmt));}
			else
			{_com_util::CheckError(m_pGraphBuilder->Connect(m_pPin,pin));}
		}
		else
		{
			if(m_bDirect)
			{_com_util::CheckError(m_pGraphBuilder->ConnectDirect(nextPins(PINDIR_OUTPUT),pin,m_pmt));}
			else
			{_com_util::CheckError(m_pGraphBuilder->Connect(nextPins(PINDIR_OUTPUT),pin));}
		}

		return pin;
	}

	CPinConnHelper& operator >> (CPinConnHelper &dist)
	{
		*this>>dist.nextPins(PINDIR_INPUT);
		return dist;
	}

	IPinPtr operator[](const WCHAR* name)
	{
		return nextPins(PINDIR_INPUT,name);
	}

protected:

	IPinPtr nextPins(PIN_DIRECTION dirc,const WCHAR* name=NULL)
	{
		if(m_bNotAdd)
		{
			_com_util::CheckError(m_pGraphBuilder->AddFilter(m_pBaseFilter,NULL));
			m_bNotAdd=false;
		}	

		IEnumPinsPtr enumpin=NULL;
		_com_util::CheckError(m_pBaseFilter->EnumPins(&enumpin));
		ASSERT(enumpin!=NULL);

		IPinPtr pin=NULL;
		ENUM_FOREACH_BEGIN(pin,enumpin)
			PIN_INFO pi;
			_com_util::CheckError(pin->QueryPinInfo(&pi));
			pi.pFilter->Release();
			if(name)
			{
				if(_wcsicmp(pi.achName,name)==0)
					return pin;
				continue;
			}
			if(pi.dir==dirc && testPin(pin))
				return pin;
		ENUM_FOREACH_END()
			_com_issue_error(-1);
	}
	IBaseFilterPtr getBase(IPinPtr &pPin)
	{
		PIN_INFO pi;
		_com_util::CheckError(pPin->QueryPinInfo(&pi));
		IBaseFilterPtr ret=NULL;
		ret.Attach(pi.pFilter);
		return ret;
	}
	IGraphBuilderPtr getBuilder(IBaseFilterPtr &pBase)
	{
		FILTER_INFO fi;
		_com_util::CheckError(pBase->QueryFilterInfo(&fi));
		ASSERT(fi.pGraph!=NULL);
		IGraphBuilderPtr ret=NULL;
		_com_util::CheckError(fi.pGraph->QueryInterface(IID_IGraphBuilder,(void**)&ret));
		ASSERT(ret!=NULL);
		VERIFY(SUCCEEDED(fi.pGraph->Release()));
		return ret;
	}

	bool testPin(IPinPtr &pin)
	{
		IPinPtr testpin=NULL;

		switch(pin->ConnectedTo(&testpin))
		{
		case VFW_E_NOT_CONNECTED:
			return true;
		case S_OK:
			return false;
		case E_POINTER:
		default:
			_com_issue_error(-1);
		}
	}

	IGraphBuilderPtr m_pGraphBuilder;
	IBaseFilterPtr m_pBaseFilter;
	IPinPtr m_pPin;

	bool m_bDirect;
	AM_MEDIA_TYPE *m_pmt;
	bool m_bNotAdd;
};

inline
CPinConnHelper& operator>> (IPinPtr &pPin,CPinConnHelper &dist)
{
	return CPinConnHelper(pPin)>>dist;
}
inline
IPinPtr operator>> (IPinPtr &pPin,IPinPtr &dist)
{
	return CPinConnHelper(pPin)>>dist;
}
//////////////////////////////////////////////////////////////////////////
CCapWindow::CCapWindow(bool bNullRender):m_iWidth(0),m_iHeight(0),m_x(0),m_y(0),m_cx(0),m_cy(0),m_hParentHwnd(NULL)
,m_bNullVR(bNullRender)
,m_pGraphBuilder(CLSID_FilterGraph,NULL,CLSCTX_INPROC_SERVER)
,m_pBuilder(CLSID_CaptureGraphBuilder2,NULL,CLSCTX_INPROC_SERVER)
,m_pSampleGrabber(QEdit::CLSID_SampleGrabber,NULL,CLSCTX_INPROC_SERVER)
,m_pVR(bNullRender?QEdit::CLSID_NullRenderer:CLSID_VideoMixingRenderer, NULL, CLSCTX_INPROC_SERVER)
,m_bInitCapt(false)
{
	_com_util::CheckError(m_pBuilder->SetFiltergraph(m_pGraphBuilder));

	QEdit::ISampleGrabberPtr pISampleGrabber=NULL;
	_com_util::CheckError(m_pSampleGrabber->QueryInterface(&pISampleGrabber));
	ASSERT(pISampleGrabber!=NULL);
	
	QEdit::_AMMediaType mt;
	ZeroMemory(&mt, sizeof(mt));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	mt.formattype = FORMAT_VideoInfo;
	pISampleGrabber->SetMediaType(&mt);

	pISampleGrabber->SetOneShot(FALSE);

	pISampleGrabber->SetBufferSamples(TRUE);
	VERIFY(SUCCEEDED(pISampleGrabber->SetCallback(&m_SampleGrabCB, 1)));
}

CCapWindow::~CCapWindow()
{
	RemoveAllFilters();
}
void CCapWindow::SetPos(HWND parent,int x,int y,int witdh,int height)//,bool after
{
	m_x=x;m_y=y;m_cx=witdh;m_cy=height;
	m_hParentHwnd=parent;

	//if(after)
		SetPos();
}
void CCapWindow::SetPos()
{
	IVideoWindowPtr pRenderWindow=NULL;
	_com_util::CheckError(m_pGraphBuilder->QueryInterface(&pRenderWindow));
	ASSERT(pRenderWindow!=NULL);
	VERIFY(SUCCEEDED(pRenderWindow->put_Visible(OAFALSE)));
	VERIFY(SUCCEEDED(pRenderWindow->put_Owner((OAHWND)m_hParentHwnd)));
	VERIFY(SUCCEEDED(pRenderWindow->put_WindowStyle(WS_CHILD| WS_CLIPSIBLINGS)));
	VERIFY(SUCCEEDED(pRenderWindow->SetWindowPosition(m_x,m_y,m_cx,m_cy)));
	VERIFY(SUCCEEDED(pRenderWindow->put_Visible(OATRUE)));
}
bool CCapWindow::ConnBuilder(IBaseFilterPtr &infilter,bool preview,int captmt,int prevmt)
{
	try
	{
		if(captmt!=-1)
		{
			IAMStreamConfigPtr amconf=NULL;
			_com_util::CheckError(m_pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,infilter,IID_IAMStreamConfig,(void**)&amconf));
			ASSERT(amconf!=NULL);
			_com_util::CheckError(amconf->SetFormat(CVideoDevice::Instance().GetMediaTypeCapt(captmt)));
		}
		
		if(prevmt!=-1)
		{
			IAMStreamConfigPtr amconf=NULL;
			_com_util::CheckError(m_pBuilder->FindInterface(&PIN_CATEGORY_PREVIEW,&MEDIATYPE_Video,infilter,IID_IAMStreamConfig,(void**)&amconf));
			ASSERT(amconf!=NULL);
			_com_util::CheckError(amconf->SetFormat(CVideoDevice::Instance().GetMediaTypePrev(prevmt)));
		}

		if(preview)
		{
			_com_util::CheckError(m_pGraphBuilder->AddFilter(m_pSampleGrabber,NULL));
			_com_util::CheckError(m_pGraphBuilder->AddFilter(m_pVR,NULL));
		
			_com_util::CheckError(m_pBuilder->RenderStream(&PIN_CATEGORY_PREVIEW,&MEDIATYPE_Video,infilter,
				m_pSampleGrabber,m_pVR));
		}
		else
		{
 			CPinConnHelper(infilter) >>
 				CPinConnHelper(m_pGraphBuilder,m_pSampleGrabber,true) >>
 					CPinConnHelper(m_pGraphBuilder,m_pVR,true);
		}

		QEdit::ISampleGrabberPtr pISampleGrabber=NULL;
 		_com_util::CheckError(m_pSampleGrabber->QueryInterface(&pISampleGrabber));
 		ASSERT(pISampleGrabber!=NULL);
 		QEdit::_AMMediaType mt;
 		_com_util::CheckError(pISampleGrabber->GetConnectedMediaType(&mt));

		VIDEOINFOHEADER * vih = reinterpret_cast<VIDEOINFOHEADER*>(mt.pbFormat);
		m_iWidth=m_SampleGrabCB.Width=vih->bmiHeader.biWidth;
		m_iHeight=m_SampleGrabCB.Height=vih->bmiHeader.biHeight;

		FreeMediaType(mt);

		//if(!m_bNullVR)
		//	SetPos();

	}
	catch(_com_error&)
	{
		return false;
	}

	return true;
}
bool CCapWindow::Open(const WCHAR *filepath)
{
	RemoveAllFilters();
	IBaseFilterPtr pFileFilter=NULL;
	if(FAILED(m_pGraphBuilder->AddSourceFilter(filepath,L"SourceFilter",&pFileFilter)))
		return false;

	ASSERT(pFileFilter!=NULL);
	return ConnBuilder(pFileFilter,false,-1,-1);
}
bool CCapWindow::Conn(int id,int captmt,int prevmt)
{
	IBaseFilterPtr &pCameraFilter=CVideoDevice::Instance().GetFilter(id);
	ASSERT(pCameraFilter!=NULL);

	RemoveAllFilters();
	if(FAILED(m_pGraphBuilder->AddFilter(pCameraFilter, L"SourceFilter")))
		return false;
	return ConnBuilder(pCameraFilter,true,captmt,prevmt);
}
void CCapWindow::RemoveAllFilters()
{
	Stop();

	m_bInitCapt=false;

	IEnumFiltersPtr pEnum = NULL;
	_com_util::CheckError(m_pGraphBuilder->EnumFilters(&pEnum));
	ASSERT(pEnum!=NULL);

	IBaseFilterPtr pFilter = NULL;
	ENUM_FOREACH_BEGIN(pFilter,pEnum)
		m_pGraphBuilder->RemoveFilter(pFilter);
		pEnum->Reset();
	ENUM_FOREACH_END()
}
void CCapWindow::Shot(BYTE *&buf,DWORD &bufsize)
{
	QEdit::ISampleGrabberPtr pISampleGrabber=NULL;
	_com_util::CheckError(m_pSampleGrabber->QueryInterface(&pISampleGrabber));
	ASSERT(pISampleGrabber!=NULL);

	bufsize=0;
	buf=NULL;
	_com_util::CheckError(pISampleGrabber->GetCurrentBuffer(reinterpret_cast<long*>(&bufsize),reinterpret_cast<long*>(buf)));
	buf=new BYTE[bufsize];
	ASSERT(buf);
	_com_util::CheckError(pISampleGrabber->GetCurrentBuffer(reinterpret_cast<long*>(&bufsize),reinterpret_cast<long*>(buf)));
}
void CCapWindow::Start()
{
	IMediaControlPtr pMediaControl=NULL;
	_com_util::CheckError(m_pGraphBuilder->QueryInterface(&pMediaControl));
	ASSERT(pMediaControl!=NULL);

	OAFilterState lstate;
	_com_util::CheckError(pMediaControl->GetState(1000,&lstate));
	if(lstate!=State_Running)
		_com_util::CheckError(pMediaControl->Run());
}
void CCapWindow::Stop()
{
	IMediaControlPtr pMediaControl=NULL;
	_com_util::CheckError(m_pGraphBuilder->QueryInterface(&pMediaControl));
	ASSERT(pMediaControl!=NULL);

	OAFilterState lstate;
	_com_util::CheckError(pMediaControl->GetState(1000,&lstate));
	if(lstate!=State_Stopped)
		_com_util::CheckError(pMediaControl->Stop());
}

void CCapWindow::StartCapture( const WCHAR* filepath ,bool bUseHD)
{
	Stop();

	if(!m_bInitCapt)
	{
		IBaseFilterPtr wmasfWriter=NULL;
		_com_util::CheckError(m_pBuilder->SetOutputFileName(&MEDIASUBTYPE_Asf,filepath,&wmasfWriter,&m_pFileSink));
		ASSERT(wmasfWriter!=NULL);

		IBaseFilterPtr source=NULL;
		_com_util::CheckError(m_pGraphBuilder->FindFilterByName(L"SourceFilter",&source));
		ASSERT(source!=NULL);

		_com_util::CheckError(m_pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,source,NULL,wmasfWriter));

		IConfigAsfWriterPtr asfconf=NULL;
		_com_util::CheckError(wmasfWriter->QueryInterface(&asfconf));
		ASSERT(asfconf!=NULL);

		IWMProfilePtr wmpro=NULL;
		if(!bUseHD)
		{
			_com_util::CheckError(asfconf->GetCurrentProfile(&wmpro));
			ASSERT(wmpro!=NULL);

			_com_util::CheckError(wmpro->RemoveStreamByNumber(1));
		}
		else
		{
			IWMProfileManagerPtr wmpManager=NULL;
			_com_util::CheckError(WMCreateProfileManager(&wmpManager));
			ASSERT(wmpManager!=NULL);

			TCHAR profile_wmv9_fuck[sizeof(g_profile_wmv9_fuck_fmt)+20];
			_stprintf(profile_wmv9_fuck,g_profile_wmv9_fuck_fmt,m_iWidth,m_iHeight);
			_com_util::CheckError(wmpManager->LoadProfileByData(profile_wmv9_fuck,&wmpro));
			ASSERT(wmpro!=NULL);
		}
		
		_com_util::CheckError(asfconf->ConfigureFilterUsingProfile(wmpro));
		
// 		int n,aid=-1;
// 		_com_util::CheckError(wmpro->GetStreamCount(&n));
// 		for(int i=0;i<n;++i)
// 		{
// 			IWMStreamConfigPtr streamconf=NULL;
// 			_com_util::CheckError(wmpro->GetStreamByNumber(i,&streamconf));
// 			ASSERT(streamconf!=NULL);
// 			
// 			GUID guid;
// 			_com_util::CheckError(streamconf->GetStreamType(&guid));
// 			if(memcmp(&guid,&MEDIATYPE_Video,sizeof(GUID))==0)
// 			{
// 				Pass(streamconf);
// 			}
// 			else if(memcmp(&guid,&MEDIATYPE_Audio,sizeof(GUID))==0)
// 			{
// 				aid=i;
// 			}
// 		}
// 
// 		if(aid!=-1)

		m_bInitCapt=true;
	}
	else
	{ 
		m_pFileSink->SetFileName(filepath,NULL);
	}
	
	Start();
}

void CCapWindow::ControlStream( bool bCapt,bool bStop )
{
	if(!bStop)
		Stop();

	IBaseFilterPtr source=NULL;
	_com_util::CheckError(m_pGraphBuilder->FindFilterByName(L"SourceFilter",&source));
	ASSERT(source!=NULL);

	REFERENCE_TIME tmp=MAXLONGLONG,*pstart=NULL,*pstop=NULL;
	if(bStop)
	{
		pstart=&tmp;
	}
	else
	{
		pstop=&tmp;
	}

	_com_util::CheckError(m_pBuilder->ControlStream((bCapt?&PIN_CATEGORY_CAPTURE:&PIN_CATEGORY_PREVIEW),&MEDIATYPE_Video,source,pstart,pstop,NULL,NULL));

	if(!bStop)
		Start();
}

void CCapWindow::Wait( int time/*=INFINITE*/ )
{
	IMediaEventPtr event=NULL;
	_com_util::CheckError(m_pGraphBuilder->QueryInterface(&event));
	ASSERT(event!=NULL);

	long code;
	event->WaitForCompletion(time,&code);
}

void CCapWindow::SetNotify( HWND hWnd,long msg )
{
	IMediaEventExPtr event=NULL;
	_com_util::CheckError(m_pGraphBuilder->QueryInterface(&event));
	ASSERT(event!=NULL);

	_com_util::CheckError(event->SetNotifyWindow(reinterpret_cast<OAHWND>(hWnd),msg,reinterpret_cast<LONG_PTR>(this)));
}

HRESULT CCapWindow::GetNotify( long *lEventCode,long *lParam1,long *lParam2,long msTimeout/*=0*/ )
{
	IMediaEventPtr event=NULL;
	_com_util::CheckError(m_pGraphBuilder->QueryInterface(&event));
	ASSERT(event!=NULL);

	return event->GetEvent(lEventCode,lParam1,lParam2,msTimeout);
}

void CCapWindow::FreeNotify( long lEventCode,long lParam1,long lParam2 )
{
	IMediaEventPtr event=NULL;
	_com_util::CheckError(m_pGraphBuilder->QueryInterface(&event));
	ASSERT(event!=NULL);

	event->FreeEventParams(lEventCode,lParam1,lParam2);
}
