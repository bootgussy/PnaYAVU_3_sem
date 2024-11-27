#ifndef ANIMATEDBUTTON_H
#define ANIMATEDBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QEnterEvent>

class AnimatedButton : public QPushButton
{
    Q_OBJECT

public:
    explicit AnimatedButton(const QString &text,const QString &color, const QString &borderColor, const QString &css, QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;  // Изменено на QEnterEvent
    void leaveEvent(QEvent *event) override;

private:
    QGraphicsDropShadowEffect *shadowEffect;
    QPropertyAnimation *shadowAnimation;
};

#endif // ANIMATEDBUTTON_H
