#include "helpfield.h"

HelpField::HelpField()
{
setFixedSize(300,40);
m_text="Score : 0\nPause - SPACE";
}

void HelpField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter;
    painter.begin(this);
    painter.drawRect(0,0,width()-1,height()-1);
    painter.setFont(QFont("Arial",10,700));
    painter.drawText(QRect(0,0,width(),height()),Qt::AlignHCenter,m_text);
    painter.end();


}

void HelpField::changeTextSlot(QString text)
{
   m_text=text;
   repaint();
}
