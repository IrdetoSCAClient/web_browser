#ifndef __ENCODEDTEXT_INCLUDED__
#define __ENCODEDTEXT_INCLUDED__

#include <vector>
#include "dkObjBase.h"
#include "dkTextBlock.h"
#include "TextSmartLayout.h"

namespace DkFormat
{
    class IBookmark;

    class IEncodedText
    {
    public:
        IEncodedText() {};
        virtual ~IEncodedText(){};
        
        // ��ȡ����lPos��TextBlock
        // pBlock�� ���ص�TextBlock
        // lPos�� TextBlock�Ŀ�ʼ�����λ�ã���fLoadForwards����
        // fForwards�� ���Ϊtrue����lPos��TextBlock�Ŀ�ʼλ�ã�����Ϊ����λ��
        STDMETHOD(GetTextBlock)(DK_TextBlock *pBlock, LONG lPos, BOOL fLoadForwards)=0;

        // ��ȡ���ı����ܳ���
        STDMETHOD(GetTextLength)(PLONG plLength)=0;

        // ��ȡ���������ڴ洢�����ļ�
        STDMETHOD(SetIndexTable)(PINT piIndexTable, INT iIndexCount)=0;

        // �������������ڴ������ļ��м���
        STDMETHOD(GetIndexTable)(PINT *ppiIndexTable, PINT piIndexCount)=0;
        
        // ���ݿ����ʼ�Ϳ���ƫ��(ת���)��������ԭ���е�ʵ��ƫ��
        STDMETHOD(GetOriginalOffset)(DK_TextBlock *pBlock, INT iUtf8Offset, PINT piOriginalOffset)=0;

        // ���ݿ����ʼ��ԭ���е�ʵ��ƫ�ƣ������ڿ���ƫ��(ת���
        STDMETHOD(GetUTF8Offset)(DK_TextBlock *pBlock, INT iOriginalOffset, PINT piUtf8Offset)=0;

        // ��������������Ҫ�Ĺ���
        STDMETHOD(SetSmartLayoutMode)(DKSmartLayoutMode eLayoutMode)=0;

        STDMETHOD(GetSmartLayoutMode)(PDKSmartLayoutMode peLayoutMode)=0;

        STDMETHOD(GetChapterList)(std::vector<IBookmark *> &rBookmarkList)=0;

        STDMETHOD(IsPosParaStart)(LONG lPos, PBOOL pfIsParaStart)=0;

        STDMETHOD(GetSearchResult)(IBookmark* searchResultTable[], INT iTableSize, PINT piUsedTableSize, PINT piNeedTableSize, LONG lLoadPos, PCCH pcchUTF8Keyword, UINT uTextLength)=0;
    };
}

#endif // def __ENCODEDTEXT_INCLUDED__

