#ifndef _READMODEDATAPROXY_H_
#define _READMODEDATAPROXY_H_

#include "dkBaseType.h"
#include "dkObjBase.h"

// ��������������������
typedef enum
{
    DKP_READ_NORMAL=0,
    DKP_READ_ZOOM,
    DKP_READ_FENLAN,
    DKP_READ_ADAPTIVE_WIDE,
    DKP_READ_REARRANGE
} DkpReadMode;

typedef struct
{
    UINT uStructSize;
    UINT uScreenWidth;
    UINT uScreenHeight;
} DkpZoomData;

typedef struct
{
    UINT uStructSize;
    UINT uFenLanType;
    UINT uSubPage;
    UINT uOrder;
    int x;
    int y;
} DkpFenLanData;

typedef union
{
    DkpZoomData stZoomData;
    DkpFenLanData stFenLanData;
} UDkpModeData;

typedef struct
{
    DkpReadMode eMode;
    UDkpModeData uniData;
} DkpReadModeData;

namespace DkFormat
{
    // ������Ϣ��Proxy��
    class IReadModeDataProxy
    {
    public:
        IReadModeDataProxy() {};
        virtual ~IReadModeDataProxy() {};
        STDMETHOD(SetReadModeData)(const DkpReadModeData &rstData)=0;
        STDMETHOD(GetReadModeData)(DkpReadModeData &rstData)=0;
    };
}

#endif //_READMODEDATAPROXY_H_

