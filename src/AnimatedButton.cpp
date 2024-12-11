#include "AnimatedButton.h"

AnimatedButton::AnimatedButton(const QString &text, const QString &color, const QString &borderColor, const QString &shadowColor, const QString &css, QWidget *parent)
    : QPushButton(text, parent),
    shadowEffect(new QGraphicsDropShadowEffect(this)),
    shadowAnimation(new QPropertyAnimation(shadowEffect, "blurRadius", this)),
    colorAnimation(new QPropertyAnimation(this, "buttonColor", this)),
    currentColor(color),
    originalColor(color),
    disabledColor("gray"),
    borderColor(borderColor),
    css(css)
{
    setStyleSheet("QPushButton { "
                  "border-radius: 10px; "
                  "border: 2px solid " + borderColor + ";"
                  "color: white; "
                  "background: " + color + "; " + css +
                  "} ");

    shadowEffect->setBlurRadius(0);
    shadowEffect->setColor(QColor(shadowColor));
    shadowEffect->setOffset(0, 0);
    setGraphicsEffect(shadowEffect);

    shadowAnimation->setDuration(200);
    shadowAnimation->setStartValue(0);
    shadowAnimation->setEndValue(25);

    colorAnimation->setDuration(300);
    colorAnimation->setEasingCurve(QEasingCurve::InOutQuad);
}

QColor AnimatedButton::buttonColor() const
{
    return currentColor;
}

void AnimatedButton::setButtonColor(const QColor &color)
{
    currentColor = color;
    QString colorString = color.name();
    setStyleSheet("QPushButton { "
                  "border-radius: 10px; "
                  "border: 2px solid " + borderColor + ";"
                  "color: white; "
                  "background: " + colorString + "; " + css +
                  "} ");
    emit buttonColorChanged();
}

void AnimatedButton::enterEvent(QEnterEvent *event)
{
    if (isEnabled()) {
        shadowAnimation->setDirection(QPropertyAnimation::Forward);
        shadowAnimation->start();
    }
    QPushButton::enterEvent(event);
}


void AnimatedButton::leaveEvent(QEvent *event)
{
    if (isEnabled()) {
        shadowAnimation->setDirection(QPropertyAnimation::Backward);
        shadowAnimation->start();
    }
    QPushButton::leaveEvent(event);
}


void AnimatedButton::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::EnabledChange) {
        if (isEnabled()) {
            colorAnimation->setStartValue(disabledColor);
            colorAnimation->setEndValue(originalColor);
        } else {
            colorAnimation->setStartValue(originalColor);
            colorAnimation->setEndValue(disabledColor);
        }
        connect(colorAnimation, &QPropertyAnimation::valueChanged, [this](const QVariant &value) {
            setButtonColor(value.value<QColor>());
        });
        colorAnimation->start();
    }
    QPushButton::changeEvent(event);
}
