#include "ui/DKPushButton.h"    

namespace ui
{
DKPushButton::DKPushButton(QWidget* parent)
    : QPushButton(parent)
{
}
DKPushButton::DKPushButton(const QString& text, QWidget* parent)
    : QPushButton(text, parent)
{
}

DKPushButton::DKPushButton(const QIcon& icon, const QString& text, QWidget* parent)
    : QPushButton(icon, text, parent)
{
}
}//ui