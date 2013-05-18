#ifndef __INTERFACE_INCLUDED__
#define __INTERFACE_INCLUDED__

#include "dkBaseType.h"
#include "DKLoggerCWrapper.h"

#ifdef __cplusplus
#ifndef __ASM_FILE__
extern "C" {
#endif      // #ifndef __ASM_FILE__
#endif      // #ifdef __cplusplus

// �ɼ�һ��ͼ��ʱ�ĸ�����Ϣ
#ifdef __ASM_FILE__
    // ������Щ��������ΪĳЩ����������޷�ʹ�� struct �Ķ���, ����ڻ���з��ʽṹ�ĳ�Ա��ʹ����Щ����
    #define FIELD_INFO_iTime                0
    #define FIELD_INFO_dwID                 4
#else
    typedef struct {
        int iTime;      // ʱ��. �� 1970/01/01 00:00:00 ������������ʾ
        DWORD32 dwID;       // ���(����һ������). ��ʱ��ı�ǿ���Ψһ��ȷ��һ��ͼ��.
    } HV_FIELD_INFO;
#endif      // #ifdef __ASM_FILE__

#define LOG_CAT_LIST(MACRO_NAME)        \
    MACRO_NAME(DBG_CONSOLE)             \
    MACRO_NAME(COMM)                    \
    MACRO_NAME(ERROR)                   \
    MACRO_NAME(TIME)                    \
    MACRO_NAME(INPUT)                   \
    MACRO_NAME(FRAMEBUF)                \
    MACRO_NAME(EINK_PAINT)              \
    MACRO_NAME(GUI)                     \
    MACRO_NAME(GUI_VERBOSE)             \
    MACRO_NAME(WIFI)                    \
    MACRO_NAME(DOWNLOAD)                \
    MACRO_NAME(VERBOSE)                 \
    MACRO_NAME(MESSAGE)                 \
    MACRO_NAME(FOCUS)                   \
    MACRO_NAME(SETTINGS)                \
    MACRO_NAME(FORMAT_TXT)              \
    MACRO_NAME(THREAD)                  \
    MACRO_NAME(OTHER)                   \
    MACRO_NAME(TRACE)                   \
    MACRO_NAME(WANGYJ)                  \
    MACRO_NAME(ZHANGXB)                 \
    MACRO_NAME(CX)                      \
    MACRO_NAME(LIUJT)                   \
    MACRO_NAME(LIUHJ)                   \
    MACRO_NAME(XU_KAI)                  \
    MACRO_NAME(ZHANGJF)                 \
    MACRO_NAME(STRING)                  \
    MACRO_NAME(CHENM)                   \
    MACRO_NAME(PENGF)                   \
    MACRO_NAME(ZHAIGH)                  \
    MACRO_NAME(JUGH)                    \
    MACRO_NAME(FOR_KEYBOARD_DEBUG)      \
    MACRO_NAME(LIWEI)                   \
    MACRO_NAME(LUOXP)                   \
    MACRO_NAME(ZHY)                   \
    MACRO_NAME(UIHOMEPAGE)              \
    MACRO_NAME(UICOMPLEXDLG)            \
    MACRO_NAME(UITEXTBOX)               \
    MACRO_NAME(UIWINDOW)                \
    MACRO_NAME(UICONTAINER)             \
    MACRO_NAME(UIDIALOG)                \
    MACRO_NAME(UITITLEBAR)              \
    MACRO_NAME(UIBOTTOMBAR)             \
    MACRO_NAME(UIBOOKMENU)              \
    MACRO_NAME(UIBOOKLISTBOX)           \
    MACRO_NAME(UIBOOKLISTITEM)          \
    MACRO_NAME(UIDIRECTORYPAGE)         \
    MACRO_NAME(UIDIRECTORYLISTBOX)      \
    MACRO_NAME(UIDIRECTORYLISTITEM)     \
    MACRO_NAME(UIMESSAGEBOX)            \
    MACRO_NAME(UIWIFIDIALOG)            \
    MACRO_NAME(UISYSTEMSETTING)         \
    MACRO_NAME(UIBUTTONDLG)             \
    MACRO_NAME(UIDATESETTINGDLG)        \
    MACRO_NAME(UINUMINPUT)              \
    MACRO_NAME(UISINGLETEXTINPUTDLG)    \
    MACRO_NAME(UITOUCHCOMPLEXBUTTON)    \
    MACRO_NAME(UIPAGE)                  \
    MACRO_NAME(BOOKINFODLG)             \
    MACRO_NAME(BOOKOPENMANAGER)         \
    MACRO_NAME(DKREADERPAGE)            \
    MACRO_NAME(UIIMAGEREADERCONTAINER)  \
    MACRO_NAME(CDKFILEMANAGER)          \
    MACRO_NAME(SELECTEDCONTROLER)       \
    MACRO_NAME(UIBOOKREADERSELECTED)    \
    MACRO_NAME(UICOMMENTORSUMMARY)      \
    MACRO_NAME(UIBOOKREADERCONTAINER)   \
    MACRO_NAME(UIBOOKREADERPROGRESSBAR) \
    MACRO_NAME(UICOMPOUNDLISTBOX)       \
    MACRO_NAME(BOOKSTORE)               \
    MACRO_NAME(UIFOOTNOTEDIALOG)        \
    MACRO_NAME(UITEXT)                  \
    MACRO_NAME(TOUCHSTACK_LONGTAP)      \
    MACRO_NAME(DIAGNOSTIC)              \
    MACRO_NAME(UITEXTMULTILINE)         \
    MACRO_NAME(TIME_TEST)         \
    MACRO_NAME(GESTURE)         \
    MACRO_NAME(FRONTLIGHT)              \
    MACRO_NAME(BENCHMARK)         \
    MACRO_NAME(ACCOUNT)         \
    MACRO_NAME(UISOFTKEYBOARDIME)         \


#define DEFINE_LOG_CATEGORY_ENUM(a)     \
    DLC_##a,                \

enum DkLogCategory
{
    LOG_CAT_LIST(DEFINE_LOG_CATEGORY_ENUM)
    DLC_Count
};

extern int g_rgfDebugDeviceEnabled[ DLC_Count ];
extern LPCSTR g_rgkszDebugDeviceName[ DLC_Count ];
extern char g_rgkszDebugLogPath[ DLC_Count ][ 260 ];
extern BOOL g_fSaveLogFile;

__inline LPCSTR GetDebugDeviceName( int iDeviceID )
{
    return g_rgkszDebugDeviceName[iDeviceID];
}

__inline void EnableDebugDevice( int iDeviceID, int fEnable ) 
{
    g_rgfDebugDeviceEnabled[ iDeviceID ] = fEnable;

    LOG_EnableDebugDevice(g_rgkszDebugDeviceName[iDeviceID], fEnable);
}

__inline int IsDebugDeviceEnabled( int iDeviceID ) 
{
    return g_rgfDebugDeviceEnabled[ iDeviceID ];
}

__inline LPCSTR GetDebugLogPath(int iDeviceID)
{
    return g_rgkszDebugLogPath[iDeviceID];
}

__inline void SetSaveLogFile(BOOL fSave)
{
    g_fSaveLogFile=fSave;
}

extern int UartWriteData( BYTE8 *pDataSrc, int iDataLenb );
extern int UartReadData( BYTE8 *pDataDest, int iReadLen );
extern int UartWriteString( LPSTR pszString );

// ����ĳ��������� OutputString ��, ���� iDeviceID ���ܵ�ȡֵ.
#define NULL_DEVICE                 255 //a

// �궨��: int OutputString( char *pString, int iDeviceID )
// ����: �ڲ�ͬ���豸�����"����ַ���"
// ����: pString    ָ����Ҫ������ַ���. ����ò���Ϊ NULL, �������� INVALD_POINTER
//       iDeviceID  ������Ҫ��ʲô�豸�����"����ַ���". ����ܵ�ȡֵ������ĳ�������. �����ȡֵ��������ĳ����е�
//                  �κ�һ��, �򱾺������� INVALID_DEVICE.
//                  iDeviceID == NULL_DEVICE ������һ���պ�, û�е����κκ���, �������κ����п���. ��ʱ pImageInfo ��
//                  pImage ����ȡ�κ�ֵ, ���ᵼ�´���.
//                  iDeviceID == RESULT_STR_FILE ʱ pString ����д�����ļ���. ����ļ��Ĵ��λ����ʵ�־���.
//                  iDeviceID == DISPLAY_STR_COUNT ʱ pString ����ʾ�ڽ����"��������"�ı�����.
//                  iDeviceID == DISPLAY_STR_RESULT ʱ pString ����ʾ�ڽ����"ʶ����"�ı�����.
//                  iDeviceID == DEBUG_STR_DISPLAY1 ʱ pString ����ʾ�ڽ����"������Ϣ"�ı�����.
//                  iDeviceID == DEBUG_STR_DISPLAY2 ʱ pString ����ʾ�ڽ����"������Ϣ2"�ı�����. Ŀǰû��ʵ��"������
//                  Ϣ2"�ı���
//                  iDeviceID == DEBUG_STR_COMM_FILE ʱ pString ����д��"ͨ�õ�����Ϣ"�ļ���. "ͨ�õ�����Ϣ"�ļ��Ĵ��
//                  λ����ʵ�־���.
//                  iDeviceID == DEBUG_STR_DETECT_FILE ʱ pString ����д��"��������Ϣ"�ļ���. "��������Ϣ"�ļ��Ĵ��
//                  λ����ʵ�־���.
//                  iDeviceID == DEBUG_STR_SEGMENT_FILE ʱ pString ����д��"�ָ������Ϣ"�ļ���. "�ָ������Ϣ"�ļ��Ĵ��
//                  λ����ʵ�־���.
//                  iDeviceID == DEBUG_STR_RECOGNIZ_FILE ʱ pString ����д��"ʶ�������Ϣ"�ļ���. "ʶ�������Ϣ"�ļ��Ĵ��
//                  λ����ʵ�־���.
//                  iDeviceID == DEBUG_STR_OTHER_FILE ʱ pString ����д��"����������Ϣ"�ļ���. "����������Ϣ"�ļ��Ĵ��
//                  λ����ʵ�־���.
//                  ֮���Խ�������Ϣ�������ϸ�Ļ���, ����Ϊ��ͬ�׶ε���������ڲ�ͬ���߳�������, ��ϸ�Ļ��ֿ��Ա������
//                  ��Ϣ�ļ����������߳��ƽ�˳����������������
// ����: �ɹ�ʱ���� 0.
//       ��� pString Ϊ NULL, �������� INVALD_POINTER
//       ��� iDeviceID ��ȡֵ�Ƿ�, �򷵻� INVALID_DEVICE.
//       ����޷���ָ���豸�����, �򷵻� DEVICE_FAIL.
// ע��: ����Ŀǰ��ʵ������Ԥ����׶��ж� iDeviceID �Ƿ�Ϊ���豸, ��˵��ñ���ʱ iDeviceID ������һ������, ���򽫵���
//       �������.
#ifdef __ASM_FILE__
    .global _DoOutputString
#else
    int DoOutputString( LPCSTR pString, int iDeviceID );

    BOOL OpenLogFile(int iDeviceID, LPCSTR lpszFileName, LPCSTR lpszMode);
    BOOL CloseLogFile(int iDeviceID);
    BOOL IsLogFileOpened(int iDeviceID);

#ifdef _DEBUG
    #define DebugLog( iCategoryID, pString )        \
        if ( iCategoryID != NULL_DEVICE ) {            \
            DoOutputString( pString, iCategoryID );    \
        }
#else
    #define DebugLog( iCategoryID, pString )
#endif

    // TODO: This could make garbage in RTM
    int DebugPrintf(int iCategoryId, LPCSTR format, ... );

    #define SafeDeleteArrayEx(_pPointer)    \
        if ( NULL != _pPointer) {        \
            delete[] _pPointer;            \
            _pPointer = NULL;            \
        }

    #define SafeDeletePointerEx(_pPointer)    \
        if ( NULL != _pPointer) {            \
            delete _pPointer;                \
            _pPointer = NULL;                \
        }
        
    #define SafeFreePointerEx(_pPointer)        \
        if ( NULL != _pPointer) {            \
            free(_pPointer);                \
            _pPointer = NULL;                \
        }

#endif      // #ifdef __ASM_FILE__

// �궨��: int GetSystemTick( void )
// ����: ȡ��ϵͳ Tick
// ����: ��
// ����: �ɹ�ʱ����ϵͳ Tick. Ŀǰ����������.
// ע��: ϵͳ Tick ��ϵͳʵ���й�, �����ʱ�䳤�Ȳ�ȷ��. Ŀǰ�� DSP_BIOS �� WINDOWS ����ȡֵ���� 1 ms.
#ifdef __ASM_FILE__
    .global _GetSystemTick
#else
    DWORD32 GetSystemTick( void );
#endif      // #ifdef __ASM_FILE__

#ifdef __ASM_FILE__
    .global _BreakPoint
#else
    void BreakPoint();
#endif      // #ifdef __ASM_FILE__

#ifdef __ASM_FILE__
    .global _BreakPoint
#else
    int Random();
#endif      // #ifdef __ASM_FILE__

void SQM_IncCounter(int iActionId);
void SQM_LogEvent(int iActionId, const char * kszMessage);
void SQM_Flush();

#define RTN_HR_IF_FAILED(func)                          \
    hr=func;                                            \
    if (FAILED(hr))                                     \
    {                                                   \
        DebugPrintf(DLC_ERROR, "FAILED (%s:%d hr=0x%08X): " \
            #func, __FILE__, __LINE__, hr);                                 \
        return hr;                                      \
    }                                                   \

#ifdef __cplusplus
#ifndef __ASM_FILE__
}   // extern "C"
#endif      // #ifndef __ASM_FILE__
#endif      // #ifdef __cplusplus


#endif      // #ifndef __INTERFACE_INCLUDED__

