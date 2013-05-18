#ifndef __BOOKINFOENTITY_INCLUDED__
#define __BOOKINFOENTITY_INCLUDED__

#include "dkBaseType.h"
#include "dkObjBase.h"
#include "SequentialStream.h"
#include "BookmarkProxy.h"
#include "BookIndexProxy.h"
#include "BookInfoProxy.h"
#include "BookPathTableProxy.h"
#include "BookTagProxy.h"
#include "ReadModeDataProxy.h"
#include "SerialBookInfoProxy.h"

namespace DkFormat
{
    static const UINT knMainFileId = 0xFFFFFFFF;

    class IBookInfoEntity
    {
    public:
        IBookInfoEntity(void) {};
        virtual ~IBookInfoEntity(void) {};

        // �������ļ�Id����ȡ���ڷ��ʲ�ͬ�������ݵ�Proxy�ࡣ
        STDMETHOD(GetInfoProxy)(IBookInfoProxy **ppProxy, UINT nFileId = knMainFileId)=0;
        STDMETHOD(GetIndexProxy)(IBookIndexProxy **ppProxy, UINT nFileId = knMainFileId)=0;
        STDMETHOD(GetBookmarkProxy)(IBookmarkProxy **ppProxy, UINT nFileId = knMainFileId)=0;
        STDMETHOD(GetTagProxy)(IBookTagProxy **ppProxy, UINT nFileId = knMainFileId)=0;
        STDMETHOD(GetReadModeDataProxy)(IReadModeDataProxy **ppProxy, UINT nFileId = knMainFileId)=0;
        STDMETHOD(GetSerialDataProxy)(ISerialBookInfoProxy **ppProxy, UINT nFileId = knMainFileId)=0;
        STDMETHOD(GetPathTableProxy)(IBookPathTableProxy **ppProxy)=0;

        // ���浽�ļ�
        STDMETHOD(Save)(LPCSTR lpszFilename)=0;
        // ���浽��
        STDMETHOD(Save)(IDKSequentialStream *pStream)=0;
        // �����и���д��Entity
        STDMETHOD(Flush)()=0;
    };
}

#endif // __BOOKINFOENTITY_INCLUDED__

