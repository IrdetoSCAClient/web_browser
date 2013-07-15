#ifndef DEVICE_H
#define DEVICE_H

#ifdef BUILD_FOR_ARM
#include <unistd.h>
#endif

#include <QProcess>
#include <QDebug>
#include <QWSServer>

class Device
{
public:
    class Properties {
    public:
        int width;
        int height;
        int dpi;
        bool hasKeyboard;
        bool hasFiveWay;
    };

    static Device& instance();

    typedef enum MODEL {
        UNKNOWN = 0,
        EMULATOR, // qvfb qws environment
        K2,       // Kindle 2
        KDX,      // Kindle DX(G)
        K3,       // Kindle Keyboard
        K4NT,     // Kindle Non-Touch Silver 2011
        K4NTB,    // Kindle Non-Touch Black 2012
        KT,       // Kindle Touch
        KPW       // Kindle PaperWhite
    } Model;
#ifndef Q_WS_QWS
    static void setModel(MODEL model) {
        m_model = model;
    }
#endif
    static Model getModel() {
        return m_model;
    }

    static int getWidth() {
        return PROPS[m_model].width;
    }

    static int getHeight() {
        return PROPS[m_model].height;
    }

    static int getDpi() {
        return PROPS[m_model].dpi;
    }

    static bool hasKeyboard() {
        return PROPS[m_model].hasKeyboard;
    }

    static bool hasFiveWay() {
        return PROPS[m_model].hasFiveWay;
    }

    static bool isTouch() {
        return !hasKeyboard() && !hasFiveWay();
    }

    static bool hasLight() {
        return m_model == KPW;
    }

    static bool isEmulator() { return m_model == EMULATOR; }

    static void suspendFramework(bool fast = false);
    static void resumeFramework(bool fast = false);

    static void enableInput(bool enable);
    static void setFullScreenUpdateEvery(int n);
    static void forceFullScreenUpdate(bool fullScreen = false);

    static bool isTouch510();
    static int  getTouchVersion();

private:
    static const Properties PROPS[];
    static MODEL m_model;
    static int version;

    Device();
    Device(Device const&);
    void operator=(Device const&);
};

#endif // DEVICE_H
