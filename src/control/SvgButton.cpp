//
// Created by TURIING on 2023/7/5.
//

#include "SvgButton.h"

SvgButton::SvgButton(QWidget *_parent): QWidget(_parent) {
}

void SvgButton::paintEvent(QPaintEvent *_event) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    drawBg(painter);

    drawIcon(painter);
}

void SvgButton::drawIcon(QPainter &_painter) {
    _painter.save();

    QSvgRenderer renderer;

    if(m_isHover)
        renderer.load(m_iconHover);
    else if(m_isPressed)
        renderer.load(m_iconPress);
    else
        renderer.load(m_iconNormal);

    auto x = (this->width() - m_iconSize.width()) / 2;
    auto y = (this->height() - m_iconSize.height()) / 2;
    renderer.render(&_painter, QRect(x, y, m_iconSize.width(), m_iconSize.height()));

    _painter.restore();
}

SvgButton::SvgButton(const QString &_iconNormal, const QString &_iconHover, const QString &_iconPress, QWidget *_parent): QWidget(_parent), m_iconNormal(_iconNormal), m_iconHover(_iconHover), m_iconPress(_iconPress) {

}

SvgButton::SvgButton(const QString &_icon, QWidget *_parent) : QWidget(_parent), m_iconNormal(_icon), m_iconHover(_icon), m_iconPress(_icon) {

}

QSize SvgButton::iconSize() const {
    return m_iconSize;
}

void SvgButton::setIconSize(const QSize &_size) {
    m_iconSize = _size;
    this->update();
}

void SvgButton::enterEvent(QEvent *_event) {
    m_isHover = true;
    this->update();

    QWidget::enterEvent(_event);
}

void SvgButton::mousePressEvent(QMouseEvent *_event) {
    if(_event->button() == Qt::LeftButton) {
        m_isPressed = !m_isPressed;
        this->update();
        emit clicked();
    }

    QWidget::mousePressEvent(_event);
}

void SvgButton::leaveEvent(QEvent *_event) {
    m_isHover = false;
    this->update();

    QWidget::leaveEvent(_event);
}

/*
 * 绘制背景
 */
void SvgButton::drawBg(QPainter &_painter) {
    _painter.save();
    if(m_isHover)
        _painter.setBrush(m_bgColorHover);
    else if(m_isPressed)
        _painter.setBrush(m_bgColorPress);
    else
        _painter.setBrush(m_bgColorNormal);

    _painter.drawRect(this->rect());

    _painter.restore();
}

void SvgButton::setBgColor(const QColor &_bgColorNormal, const QColor &_bgColorHover, const QColor &_bgColorPress) {
    m_bgColorNormal = _bgColorNormal;
    m_bgColorHover = _bgColorHover;
    m_bgColorPress = _bgColorPress;
}




