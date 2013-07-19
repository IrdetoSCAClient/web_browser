#include <QtGui>
#include <QString>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include "evernote_application.h"
#include "common/languages.h"

using namespace evernote_kindle;
using namespace ui;

#if 0
void customMessageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type)
    {
        //������Ϣ��ʾ
        case QtDebugMsg:
            txt = QString("Debug: %1").arg(msg);
            break;
        //һ���warning��ʾ
        case QtWarningMsg:
            txt = QString("Warning: %1").arg(msg);
            break;
        //���ش�����ʾ
        case QtCriticalMsg:
            txt = QString("Critical: %1").arg(msg);
            break;
        //����������ʾ
        case QtFatalMsg:
            txt = QString("Fatal: %1").arg(msg);
            abort();
        default:
            break;
    }
    QFile outFile("debuglog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}
#endif

int main(int argc, char * argv[])
{
    EvernoteApplication app(argc, argv);
    //ui::loadTranslator(QLocale::system().name());

#if 0
    qInstallMsgHandler(customMessageHandler);
#endif

    QString param;
    if (argc >= 2)
    {
        param = QString::fromLocal8Bit(argv[1]);
    }
    else{
        param = EvernoteApplication::defaultFolder();
    }
    
    if (param.compare("getuser") == 0){
        if (app.createSession()){
            app.getUser();
        }
    }
    else {
        if (app.open(param) && app.createSession()){
            app.exportAll();
        }
    }
    return 0;
}
