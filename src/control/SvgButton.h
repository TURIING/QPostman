//
// Created by TURIING on 2023/7/5.
//

#ifndef QPOSTMAN_SVGBUTTON_H
#define QPOSTMAN_SVGBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QMouseEvent>
#include <QDebug>

class SvgButton: public QWidget {
    Q_OBJECT
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize);
public:
    explicit SvgButton(QWidget *_parent = Q_NULLPTR);
    SvgButton(const QString &_iconNormal, const QString &_iconHover, const QString &_iconPress, QWidget *_parent = Q_NULLPTR);
    SvgButton(const QString &_icon, QWidget *_parent = Q_NULLPTR);

    QSize iconSize() const;
    void setIconSize(const QSize &_size);

    void setBgColor(const QColor &_bgColorNormal, const QColor &_bgColorHover, const QColor &_bgColorpress);
protected:
    void paintEvent(QPaintEvent *_event) override;
    void enterEvent(QEvent *_event) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void leaveEvent(QEvent *_event) override;
private:
    void drawIcon(QPainter &_painter);
    void drawBg(QPainter &_painter);
private:
    bool m_isPressed = false;
    bool m_isHover = false;
    /* 不同状态下的图标svg路径 */
    QString m_iconNormal;
    QString m_iconHover;
    QString m_iconPress;
    /* 不同状态下的背景颜色 */
    QColor m_bgColorNormal = QColor(255, 255, 255);
    QColor m_bgColorHover = QColor(242, 242, 242);
    QColor m_bgColorPress = QColor(255, 255, 255);

    QSize m_iconSize = QSize(20, 20);
public: signals:
    void clicked();
};


#endif //QPOSTMAN_SVGBUTTON_H
