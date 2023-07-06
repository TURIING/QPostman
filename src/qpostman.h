//
// Created by TURIING on 2023/7/3.
//

#ifndef QPOSTMAN_QPOSTMAN_H
#define QPOSTMAN_QPOSTMAN_H

#include <QWidget>
#include <windows.h>
#include <QVBoxLayout>
#include "component/TitleBar.h"
#include <QLabel>
#include "utility/windoweffect.h"
#include <QWindow>
#include <QScreen>
#include <QApplication>
#include <QStyle>

QT_BEGIN_NAMESPACE
namespace Ui { class QPostman; }
QT_END_NAMESPACE

constexpr int BORDER_WIDTH = 5;

class QPostman : public QWidget {
Q_OBJECT
public:
    explicit QPostman(QWidget *_parent = Q_NULLPTR);
    ~QPostman() override;
protected:
    bool nativeEvent(const QByteArray& _eventType, void* _message, long* _result) override;
    //void changeEvent(QEvent* _event) override;
private:
    void m_initTitleBar();
    bool isWindowMaximized(HWND _hWnd);
    void monitorNCCALCSIZE(MSG* _msg);
    static void RefreshStyle(QWidget* widget, const char* name, const QVariant& _value)
    {
        widget->setProperty(name, _value);

        qApp->style()->unpolish(widget);
        qApp->style()->polish(widget);

        widget->update();
    }
    static void m_loadStyle(QWidget *_widget, const QString& _filePath)
    {
        QString styleSheet;

        QFile file(_filePath);
        if (file.open(QFile::ReadOnly))
        {
            styleSheet.append(QString::fromLocal8Bit(file.readAll()));

            file.close();
        }

        _widget->setStyleSheet(styleSheet);

    }
private:
    Ui::QPostman *ui;

    MONITORINFO m_monitorInfo;
    QVBoxLayout *m_vLayout;
    TitleBar *m_titleBar;                                               // 标题栏

};


#endif //QPOSTMAN_QPOSTMAN_H
