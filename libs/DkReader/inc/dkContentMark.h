#ifndef __DKCONTENTMARK_INCLUDED__
#define __DKCONTENTMARK_INCLUDED__

#include "dkBaseType.h"

namespace DkFormat
{
    #define    DK_INVALID_PAGE_NO    -1

    typedef struct
    {
        LPCSTR lpszTitle;                // �½ڱ���
        INT iPageNo;                    // �½���ʼҳ��
        INT iLevel;                        // Ŀ¼���
    } DK_CONTENT_MARK ;
}

#endif        // #ifndef __DKCONTENTMARK_INCLUDED__

