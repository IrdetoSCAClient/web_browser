#ifndef __DKTEXTBLOCK_INCLUDED__
#define __DKTEXTBLOCK_INCLUDED__

#include <stdlib.h>
#include "dkBaseType.h"

namespace DkFormat
{
    typedef struct DK_TextBlock{
        
        INT iOriginalStart;    // ���ı���ԴIEncodedText�е���ʼƫ��
        INT iOriginalEnd;        // ���ı���ԴIEncodedText�еĽ���ƫ��, iOriginalStart��iOriginalEnd������ҿ���һ������
        PBYTE8 pUTF8Text;    // ���ı�����ת��֮���UTF-8�ı�
        INT iTextCapacity;    // pUTF8Text������ڴ��С
        INT iTextLength;        // UTF-8�ı�����
        INT iStartIndex;        // UTF-8�ı��е���Ч�ı��Σ���iStartIndex��iEndIndex��ʶ��iStartIndex��iEndIndex������ҿ���һ�����䣩
        INT iEndIndex;        // UTF-8��Ч�ı��εĽ����±꣬���±�Ϊ��Ч�ı����һ���ַ��±��һ������Ч�ı��β��������±�λ�ô����ַ���
        INT *pMappingTable;    // ת��ǰ���ַ�ƫ�Ƶ�ӳ���: ż���±�(��0��ʼ)��ת����ƫ�ƣ������±��ת��ǰ��ƫ��
        INT iTableCapacity;     // ӳ�����ڴ��С
        INT iTableLength;    // ӳ�����
        BOOL fIsLoaded;        // ΪTRUEʱ��ʾ��ǰ���Ƿ񱻼��أ������أ����������ݶ�Ϊ��Ч����

        DK_TextBlock()
            : iOriginalStart(0)
            , iOriginalEnd(0)
            , pUTF8Text(NULL)
            , iTextCapacity(0)
            , iTextLength(0)
            , iStartIndex(0)
            , iEndIndex(0)
            , pMappingTable(NULL)
            , iTableCapacity(0)
            , iTableLength(0)
            , fIsLoaded(FALSE)
        {            
        }

        ~DK_TextBlock()
        {
            if (pUTF8Text != NULL)
            {
                free(pUTF8Text);
                pUTF8Text = NULL;
            }
            
            if (pMappingTable != NULL)
            {
                free(pMappingTable);
                pMappingTable = NULL;
            }
        }    
    } DK_TextBlock;
}

#endif         // #ifndef __DKTEXTBLOCK_INCLUDED__

