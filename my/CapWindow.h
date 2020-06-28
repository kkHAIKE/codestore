#pragma once
#include <Debug.h>

typedef void (CALLBACK *CBFORRGB24)(BYTE* buf,int width,int height);
#import <qedit.dll> rename_namespace("QEdit") raw_interfaces_only named_guids 

#include <comdef.h>
#include <dshow.h>
#include <dshowasf.h>

#define COM_SMARTPTR_TYPEDEF(x) _COM_SMARTPTR_TYPEDEF(x,__uuidof(x))

COM_SMARTPTR_TYPEDEF(IBaseFilter);
COM_SMARTPTR_TYPEDEF(IGraphBuilder);
COM_SMARTPTR_TYPEDEF(IPin);
COM_SMARTPTR_TYPEDEF(ICreateDevEnum);
COM_SMARTPTR_TYPEDEF(IEnumMoniker);
COM_SMARTPTR_TYPEDEF(IMoniker);
COM_SMARTPTR_TYPEDEF(IPropertyBag);
COM_SMARTPTR_TYPEDEF(IEnumPins);
COM_SMARTPTR_TYPEDEF(IVideoWindow);
COM_SMARTPTR_TYPEDEF(IEnumFilters);
COM_SMARTPTR_TYPEDEF(IMediaControl);
COM_SMARTPTR_TYPEDEF(ICaptureGraphBuilder2);
COM_SMARTPTR_TYPEDEF(IFileSinkFilter);
COM_SMARTPTR_TYPEDEF(IWMProfile);
COM_SMARTPTR_TYPEDEF(IConfigAsfWriter);
COM_SMARTPTR_TYPEDEF(IAMStreamConfig);
COM_SMARTPTR_TYPEDEF(IKsPropertySet);
COM_SMARTPTR_TYPEDEF(IWMProfileManager);
COM_SMARTPTR_TYPEDEF(IMediaEvent);
COM_SMARTPTR_TYPEDEF(IMediaEventEx);
COM_SMARTPTR_TYPEDEF(IAMVideoControl);

#if !defined(__CSTRINGT_H__) && !defined(_WTL_USE_CSTRING)
#include <StdString.h>
#define CSTRING CStdString
#else
#define CSTRING CString
#endif

#include <vector_ptr.h>

class CVideoDevice
{
friend class CCapWindow;

public:
	static CVideoDevice& Instance();

	const CSTRING& GetFiendlyName(int id)
	{
		ASSERT(id>=0 && id<GetCount());
		return m_DeviceList[id]->friendlyName;
	}
	const CSTRING& GetDisplayName(int id)
	{
		ASSERT(id>=0 && id<GetCount());
		return m_DeviceList[id]->displayName;
	}
	int GetCount() const
	{
		return m_DeviceList.size();
	}

	void InitMedialist(int id);
	int GetCountCapt() const
	{
		return static_cast<int>(m_MediaListCapt.size());
	}
	const CSTRING& GetMediaContCapt(int id)
	{
		ASSERT(id>=0 && id<GetCountCapt());
		return m_MediaListCapt[id]->mediaCont;
	}
	int GetCountPrev() const
	{
		return static_cast<int>(m_MediaListPrev.size());
	}
	const CSTRING& GetMediaContPrev(int id)
	{
		ASSERT(id>=0 && id<GetCountPrev());
		return m_MediaListPrev[id]->mediaCont;
	}
	const std::vector<float>& GetFPSCapt(int id)
	{
		ASSERT(id>=0 && id<GetCountCapt());
		return m_MediaListCapt[id]->rateList;
	}
	const std::vector<float>& GetFPSPrev(int id)
	{
		ASSERT(id>=0 && id<GetCountPrev());
		return m_MediaListPrev[id]->rateList;
	}
	void SetFPSCapt(int id,float fps)
	{
		SetFPS(m_MediaListCapt[id],fps);
	}

	void SetFPSPrev(int id,float fps)
	{
		SetFPS(m_MediaListPrev[id],fps);
	}

protected:
	CVideoDevice(void);
	void Pass(IPinPtr &pin,bool bCapt,IAMVideoControlPtr &vctrl);
	
	IBaseFilterPtr& GetFilter(int id)
	{
		ASSERT(id>=0 && id<GetCount());
		return m_DeviceList[id]->filter;
	}
	AM_MEDIA_TYPE* GetMediaTypeCapt(int id)
	{
		ASSERT(id>=0 && id<GetCountCapt());
		return m_MediaListCapt[id]->pMedia;
	}
	AM_MEDIA_TYPE* GetMediaTypePrev(int id)
	{
		ASSERT(id>=0 && id<GetCountPrev());
		return m_MediaListPrev[id]->pMedia;
	}

	class MYDEVICE
	{
	public:
		~MYDEVICE()
		{
			//com会先释放，所以这里直接分离避免出错
			filter.Detach();
		}
		CSTRING friendlyName;
		CSTRING displayName;
		IBaseFilterPtr filter;
	};

	class MYMEDIA
	{
	public:
		MYMEDIA():pMedia(NULL){}
		~MYMEDIA();
		CSTRING mediaCont;
		AM_MEDIA_TYPE *pMedia;
		std::vector<float> rateList;

	private:
		MYMEDIA(const MYMEDIA&);
		void operator=(const MYMEDIA&);
	};

	vector_ptr<MYDEVICE> m_DeviceList;
	vector_ptr<MYMEDIA> m_MediaListCapt;
	vector_ptr<MYMEDIA> m_MediaListPrev;

	void SetFPS(MYMEDIA *media,float fps);

private:
	CVideoDevice(const CVideoDevice &);
	void operator=(const CVideoDevice &);
};
//////////////////////////////////////////////////////////////////////////
class CCapWindow
{
public:
	explicit CCapWindow(bool bNullRender=false);
	~CCapWindow(void);

	bool Conn(int id,int captmt=-1,int prevmt=-1);
	bool Open(const WCHAR * filepath);
	void SetPos(HWND parent,int x,int y,int witdh,int height);//,bool after=false
	void Start();
	void Stop();
	void Shot(BYTE *&buf,DWORD &bufsize);
	int GetWidth() const {return m_iWidth;}
	int GetHeight() const {return m_iHeight;}

	void SetCallBack(CBFORRGB24 cb){m_SampleGrabCB.cb=cb;}

	void StartCapture(const WCHAR* filepath,bool bUseHD=false);
	void StopCapture(){ControlStream(true,true);}
	void StartPreview(){ControlStream(false,false);}
	void StopPreview(){ControlStream(false,true);}

	void Wait(int time=INFINITE);
	void SetNotify(HWND hWnd,long msg);
	HRESULT GetNotify(long *lEventCode,long *lParam1,long *lParam2,long msTimeout=0);
	void FreeNotify(long lEventCode,long lParam1,long lParam2);

protected:
	void ControlStream( bool bCapt,bool bStop );
	void RemoveAllFilters();
	bool ConnBuilder(IBaseFilterPtr &infilter,bool preview,int captmt,int prevmt);
	void SetPos();

	int m_iWidth,m_iHeight;
	int m_x,m_y,m_cx,m_cy;
	HWND m_hParentHwnd;
	bool m_bNullVR;
	ICaptureGraphBuilder2Ptr m_pBuilder;
	IGraphBuilderPtr m_pGraphBuilder;

	IBaseFilterPtr m_pSampleGrabber;
	IBaseFilterPtr m_pVR;

	bool m_bInitCapt;
	IFileSinkFilterPtr m_pFileSink;

	class CSampleGrabberCB : public QEdit::ISampleGrabberCB
	{	
	public:
		CSampleGrabberCB():Width(0),Height(0),cb(NULL){};

		long Width;
		long Height;
		CBFORRGB24 cb;

		STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
		{
			if (ppv==NULL) 
			{
				return E_POINTER;
			}
			if( riid == QEdit::IID_ISampleGrabberCB||riid == IID_IUnknown) 
			{
				*ppv =static_cast<QEdit::ISampleGrabberCB*> ( this );
				return NOERROR;
			}

			return E_NOINTERFACE;
		}

		STDMETHODIMP BufferCB( double SampleTime, BYTE * pBuffer, long BufferSize )
		{
			if(cb)
				cb(pBuffer,Width,Height);
			return S_OK;
		}

		STDMETHODIMP SampleCB( double SampleTime, QEdit::IMediaSample * pSample )
		{
			return 0;
		}

		STDMETHODIMP_(ULONG) AddRef() { return 2; }
		STDMETHODIMP_(ULONG) Release() { return 1; }
	};

	CSampleGrabberCB m_SampleGrabCB;
};