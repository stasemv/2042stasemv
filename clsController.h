#ifndef CLSCONTROLLER_H
#define CLSCONTROLLER_H

#include <QObject>

namespace nsp2042
{

class clsController : public QObject
{
    Q_OBJECT

public:
    explicit clsController(QObject *parent = 0);
    void testSignal( int table[4][4], int score, bool isEnd );

public slots:

signals:
    void updateView( int*, int, bool );
    void move( int );

};

} // namespace nsp2042

#endif // CLSCONTROLLER_H
