#ifndef HELPFIELD_H
#define HELPFIELD_H

#include <QWidget>
#include <QPainter>

class HelpField: public QWidget
{
    Q_OBJECT
 public:
    HelpField();
private:
    QString m_text;

protected:
    void paintEvent(QPaintEvent *e) override;
   public slots:
     void changeTextSlot(QString text);


};


#endif // HELPFIELD_H
