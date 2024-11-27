#include "AnimatedButton.h"

AnimatedButton::AnimatedButton(const QString &text, const QString &color, const QString &borderColor, const QString &css, QWidget *parent)
    : QPushButton(text, parent),
    shadowEffect(new QGraphicsDropShadowEffect(this)),
    shadowAnimation(new QPropertyAnimation(shadowEffect, "blurRadius", this))
{
    setStyleSheet("QPushButton { "
                  "border-radius: 10px; "
                  "border: 2px solid " + borderColor + ";"
                  "color: white; "
                  "background: " + color + "; " + css +
                  "} ");

    shadowEffect->setBlurRadius(0);
    shadowEffect->setColor(QColor(color));
    shadowEffect->setOffset(0, 0);
    setGraphicsEffect(shadowEffect);

    shadowAnimation->setDuration(200);
    shadowAnimation->setStartValue(0);
    shadowAnimation->setEndValue(25);
}

// Используйте QEnterEvent* здесь
void AnimatedButton::enterEvent(QEnterEvent *event)
{
    shadowAnimation->setDirection(QPropertyAnimation::Forward);
    shadowAnimation->start();
    QPushButton::enterEvent(event);
}

void AnimatedButton::leaveEvent(QEvent *event)
{
    shadowAnimation->setDirection(QPropertyAnimation::Backward);
    shadowAnimation->start();
    QPushButton::leaveEvent(event);
}
