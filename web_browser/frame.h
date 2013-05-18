
#ifndef WEB_BROWSER_FRAME_H_
#define WEB_BROWSER_FRAME_H_

#include <QtGui/QtGui>
#include "view.h"
#include "keyboard_dialog.h"
#include "bookmark_model.h"

namespace webbrowser
{

struct BrowserKeyboardPrivate
{
    QString form_id;
    QString form_name;
    QString form_action;
    QString input_type;
    QString input_id;
    QString input_name;
};

enum BrowserKeyboardStatus
{
    KEYBOARD_FREE = -1,
    FORM_FOCUSED = 0,
    URL_INPUTTING
};

class BrowserFrame : public QWidget
{
    Q_OBJECT

public:
    BrowserFrame(QWidget *parent = 0);
    ~BrowserFrame();

public Q_SLOTS:
    void load(const QString & url_str);
    void onScreenSizeChanged(int);

protected:
    void keyPressEvent(QKeyEvent * ke);
    void keyReleaseEvent(QKeyEvent *ke);
    bool event(QEvent *e);
    void closeEvent(QCloseEvent *e);

private Q_SLOTS:
    void onInputFormFocused(const QString & form_id,
                            const QString & form_name,
                            const QString & form_action,
                            const QString & input_type,
                            const QString & input_id,
                            const QString & input_name);
    void onTextFinished(const QString & text);

    void onInputUrl();
    void onInputText();

private:
    void createLayout();
    void loadThumbnails();
    void thumbnailModel(QStandardItemModel & model);

private:
    QVBoxLayout            layout_;
    BrowserView            view_;
    KeyboardDialog         keyboard_;
    QStandardItemModel     model_;
    BrowserKeyboardPrivate keyboard_priv_;
    BrowserKeyboardStatus  keyboard_status_;
};

}   // namespace webbrowser

#endif  // WEB_BROWSER_FRAME_H_