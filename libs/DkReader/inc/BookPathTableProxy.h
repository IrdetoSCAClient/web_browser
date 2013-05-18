#ifndef __BOOKPATHTABLEPROXY_INCLUDED__
#define __BOOKPATHTABLEPROXY_INCLUDED__

#include "dkBaseType.h"
#include "dkObjBase.h"

namespace DkFormat
{
    typedef struct 
    {
        UINT nFileId;        // �ļ�Id
        UINT nParentId;        // �������ļ�Id
        // TODO:define MAX_FILEPATHNAME
        CHAR rgPath[1024];        // ����ڸ��ļ������·��
    } DkpPathItem;

    // PathTable��Proxy��
    class IBookPathTableProxy
    {
    public:
        IBookPathTableProxy() {};
        virtual ~IBookPathTableProxy() {};

        STDMETHOD(GetPathTable)(DkpPathItem **ppList, PUINT pnCount)=0;
        STDMETHOD(SetPathTable)(DkpPathItem *pList, UINT nCount)=0;

        //�˽ӿ�ֻ�ͷ�GetPathTable��ȡ����Դ
        STDMETHOD(ReleasePathTable)(DkpPathItem *pList)=0;
    };
}
#endif // __BOOKPATHTABLEPROXY_INCLUDED__

