#ifndef CLSCELL_H
#define CLSCELL_H

#include <QFrame>

class QLabel;

namespace nsp2042
{

class clsCell : public QFrame
{
    Q_OBJECT

public:
    explicit clsCell(QWidget *parent = 0);
    void setColor( QColor _color );
    void setValue( int _value );
    void updateCell();

private:
    QColor color;
    int value;
    QLabel *label;


signals:

public slots:

};

} // namespace nsp2042

#endif // CLSCELL_H
