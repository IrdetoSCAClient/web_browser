#ifndef _BOOKLOCATOR_H_
#define _BOOKLOCATOR_H_

#include "dkObjBase.h"
#include "dkBaseType.h"

namespace DkFormat
{
    typedef enum
    {
        /*
            ��������͵��ļ���λ����(txt,umd,pdf��ʹ��)
            �����͵�CBookLocator�ṩ�����ӿ�GetBlockId()��GetBlockOffset()
        */
        FILE_LOCATOR_BASE = 0,
    } BookLocatorType;

    class IBookLocator
    {
    public:
        IBookLocator(){};
        virtual ~IBookLocator(){};

        STDMETHOD(GetType)(BookLocatorType &rType)=0;
        STDMETHOD(Clone)(IBookLocator **pBookLocator) = 0;

        STDMETHOD(ReadData)(const BYTE8 *pbData, UINT nLength, int *piReadBytes) = 0;
        STDMETHOD(WriteData)(BYTE8 *pbData, UINT nLength, int *piWriteBytes) = 0;
        STDMETHOD(GetDataSize)(int *piSize) = 0;
        STDMETHOD(LocatorCmp)(const IBookLocator *pLocator, INT *piCmpResult) = 0;
    };
}

#endif // _BOOKLOCATOR_H_

