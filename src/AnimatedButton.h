#ifndef ANIMATEDBUTTON_H
#define ANIMATEDBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QEnterEvent>
#include <QEvent>

class AnimatedButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor buttonColor READ buttonColor WRITE setButtonColor NOTIFY buttonColorChanged)

public:
    explicit AnimatedButton(const QString &text, const QString &color, const QString &borderColor, const QString &shadowColor, const QString &css, QWidget *parent = nullptr);

    QColor buttonColor() const;
    void setButtonColor(const QColor &color);

signals:
    void buttonColorChanged();

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void changeEvent(QEvent *event) override;

private:
    QGraphicsDropShadowEffect *shadowEffect;
    QPropertyAnimation *shadowAnimation;
    QPropertyAnimation *colorAnimation;
    QColor currentColor;
    QColor originalColor;
    QColor disabledColor;
    QString borderColor;
    QString css;
};

#endif // ANIMATEDBUTTON_H
