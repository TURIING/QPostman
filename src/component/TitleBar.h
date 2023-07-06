//
// Created by TURIING on 2023/7/3.
//

#ifndef QTDEMO_TITLEBAR_H
#define QTDEMO_TITLEBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <windows.h>
#include <QMouseEvent>

#include "../control/SvgButton.h"

constexpr int TITLE_BAR_HEIGHT = 62;                                    // 标题栏的高度


class TitleBar: public QWidget {
    Q_OBJECT
public:
    explicit TitleBar(QWidget *_parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent* _event) override;
    void mouseDoubleClickEvent(QMouseEvent* _event) override;
private:
    QHBoxLayout *m_hLayout;
    QLabel *m_iconLabel;                                                // 程序图标
    SvgButton *m_btnMinimize;
    SvgButton *m_btnMaximize;
    SvgButton *m_btnClose;
    QColor m_bgColor;

private slots:
    void toggleMaximize();
};


#endif //QTDEMO_TITLEBAR_H
