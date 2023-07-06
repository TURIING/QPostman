//
// Created by TURIING on 2023/7/3.
//

#include "TitleBar.h"

TitleBar::TitleBar(QWidget *_parent): QWidget(_parent) {
    this->setFixedHeight(TITLE_BAR_HEIGHT);
    // 启用QSS
    this->setAttribute(Qt::WA_StyledBackground);

    /* 水平布局 */
    m_hLayout = new QHBoxLayout(this);
    m_hLayout->setSpacing(0);
    m_hLayout->setContentsMargins(0, 0, 0, 0);

    /* icon */
    m_iconLabel = new QLabel(this);
    m_iconLabel->setObjectName("iconLabel");
    m_hLayout->addWidget(m_iconLabel);
    m_hLayout->addStretch(1);

    /* 最小化按钮 */
    m_btnMinimize = new SvgButton(QStringLiteral(":/TitleBar/Resources/title_bar/btn_minimize_normal_hover_press.svg"), this);
    m_btnMinimize->setIconSize(QSize(15, 15));
    m_btnMinimize->setObjectName("btnMinimize");
    connect(m_btnMinimize, &SvgButton::clicked, this->window(), &QWidget::showMinimized);
    m_hLayout->addWidget(m_btnMinimize);

    /* 最大化按钮 */
    m_btnMaximize = new SvgButton(QStringLiteral(":/TitleBar/Resources/title_bar/btn_maximize_normal_hover_press.svg"), this);
    m_btnMaximize->setIconSize(QSize(15, 15));
    m_btnMaximize->setObjectName("btnMaximize");
    connect(m_btnMaximize, &SvgButton::clicked, this, &TitleBar::toggleMaximize);
    m_hLayout->addWidget(m_btnMaximize);

    /* 关闭按钮 */
    m_btnClose = new SvgButton(QStringLiteral(":/TitleBar/Resources/title_bar/btn_close_normal.svg"), QStringLiteral(":/TitleBar/Resources/title_bar/btn_close_hover_press.svg"),
                               QStringLiteral(":/TitleBar/Resources/title_bar/btn_close_hover_press.svg"), this);
    m_btnClose->setObjectName("btnClose");
    m_btnClose->setIconSize(QSize(15, 15));
    m_btnClose->setBgColor(QColor(255, 255, 255), QColor(142, 26, 16), QColor(142, 26, 16));
    connect(m_btnClose, &SvgButton::clicked, this->window(), &QWidget::close);
    m_hLayout->addWidget(m_btnClose);
}

void TitleBar::toggleMaximize() {
    if(this->window()->isMaximized())
        this->window()->showNormal();
    else
        this->window()->showMaximized();
}

void TitleBar::mousePressEvent(QMouseEvent *_event) {
    ReleaseCapture();
    SendMessage((HWND)window()->winId(), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
    _event->ignore();
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *_event) {
    toggleMaximize();
}
