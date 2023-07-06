//
// Created by TURIING on 2023/7/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QPostman.h" resolved

#include "qpostman.h"
#include "ui_QPostman.h"


QPostman::QPostman(QWidget *_parent): QWidget(_parent), ui(new Ui::QPostman)  {
    ui->setupUi(this);
    this->setObjectName("QPostman");
    m_loadStyle(this, ":/QPostman/qss/QPostman.qss");
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    memset(&m_monitorInfo, 0, sizeof(MONITORINFO));
    m_monitorInfo.cbSize = sizeof(MONITORINFO);

    m_vLayout = new QVBoxLayout(this);
    m_vLayout->setSpacing(0);
    m_vLayout->setContentsMargins(0, 0, 0, 0);

    /* 标题栏 */
    m_initTitleBar();


    WindowEffect::addWindowAnimation((HWND)winId());
    WindowEffect::addShadowEffect((HWND)winId());

    connect(windowHandle(), &QWindow::screenChanged, this, [=] {
        auto hWnd = reinterpret_cast<HWND>(windowHandle()->winId());
        SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    });
}

QPostman::~QPostman() {
    delete ui;
}

bool QPostman::nativeEvent(const QByteArray &_eventType, void *_message, long *_result) {
    MSG* msg = reinterpret_cast<MSG*>(_message);
    if (msg->message == WM_NCHITTEST)
    {
        int xPos = (LOWORD(msg->lParam) - frameGeometry().x()) % 65536;
        int yPos = HIWORD(msg->lParam) - frameGeometry().y();
        int w = width();
        int h = height();
        bool lx = xPos < BORDER_WIDTH;
        bool rx = xPos > w - BORDER_WIDTH;
        bool ty = yPos < BORDER_WIDTH;
        bool by = yPos > h - BORDER_WIDTH;

        if (lx && ty)
        {
            *_result = HTTOPLEFT;
            return true;
        }
        else if (rx && by)
        {
            *_result = HTBOTTOMRIGHT;
            return true;
        }
        else if (rx && ty) {
            *_result = HTTOPRIGHT;
            return true;
        }
        else if (lx && by) {
            *_result = HTBOTTOMLEFT;
            return true;
        }
        else if (ty) {
            *_result = HTTOP;
            return true;
        }
        else if (by) {
            *_result = HTBOTTOM;
            return true;
        }
        else if (lx) {
            *_result = HTLEFT;
            return true;
        }
        else if (rx) {
            *_result = HTRIGHT;
            return true;
        }
    }
    else if (msg->message == WM_NCCALCSIZE)
    {
        if (isWindowMaximized(msg->hwnd))
        {
            monitorNCCALCSIZE(msg);
        }

        *_result = HTNOWHERE;
        return true;
    }
    else if (msg->message == WM_GETMINMAXINFO)
    {
        if (isWindowMaximized(msg->hwnd))
        {
            RECT window_rect;
            if (!GetWindowRect(msg->hwnd, &window_rect))
            {
                *_result = HTNOWHERE;
                return false;
            }

            HMONITOR hMonitor = MonitorFromRect(&window_rect, MONITOR_DEFAULTTONULL);
            if (!hMonitor)
            {
                *_result = HTNOWHERE;
                return false;
            }

            GetMonitorInfoW(hMonitor, &m_monitorInfo);
            RECT monitor_rect = m_monitorInfo.rcMonitor;
            RECT work_area = m_monitorInfo.rcWork;

            LPMINMAXINFO info = reinterpret_cast<LPMINMAXINFO>(msg->lParam);

            info->ptMaxSize.x = work_area.right - work_area.left;
            info->ptMaxSize.y = work_area.bottom - work_area.top;
            info->ptMaxTrackSize.x = info->ptMaxSize.x;
            info->ptMaxTrackSize.y = info->ptMaxSize.y;

            info->ptMaxPosition.x = abs(window_rect.left - monitor_rect.left);
            info->ptMaxPosition.y = abs(window_rect.top - monitor_rect.top);
            *_result = HTCLIENT;
            return true;
        }
    }

    return QWidget::nativeEvent(_eventType, _message, _result);
}

bool QPostman::isWindowMaximized(HWND _hWnd) {
    WINDOWPLACEMENT wp;
    wp.length = sizeof(WINDOWPLACEMENT);
    if (!GetWindowPlacement(_hWnd, &wp))
    {

    }
    return wp.showCmd == SW_MAXIMIZE;
}

void QPostman::monitorNCCALCSIZE(MSG *_msg) {
    HMONITOR hMonitor = MonitorFromWindow(_msg->hwnd, MONITOR_DEFAULTTONULL);
    if (hMonitor != NULL)
    {
        GetMonitorInfoW(hMonitor, &m_monitorInfo);
    }

    NCCALCSIZE_PARAMS& params = *reinterpret_cast<NCCALCSIZE_PARAMS*>(_msg->lParam);
    params.rgrc[0].left = m_monitorInfo.rcWork.left;
    params.rgrc[0].top = m_monitorInfo.rcWork.top;
    params.rgrc[0].right = m_monitorInfo.rcWork.right;
    params.rgrc[0].bottom = m_monitorInfo.rcWork.bottom;
}

//void QPostman::changeEvent(QEvent *_event) {
//    if(_event->type() == QEvent::WindowStateChange)
//        RefreshStyle(m_titleBar->findChild<QToolButton *>("btnMaximize"), "MaxState", this->isMaximized());
//    QWidget::changeEvent(_event);
//}

/*
 * 初始化标题栏
 */
void QPostman::m_initTitleBar() {
    m_titleBar = new TitleBar(this);
    m_titleBar->setObjectName("titleBar");
    m_vLayout->addWidget(m_titleBar);
    m_vLayout->addStretch(1);
    m_loadStyle(m_titleBar, ":/TitleBar/qss/titlebar.qss");
}



