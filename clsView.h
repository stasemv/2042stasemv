#ifndef CLSVIEW_H
#define CLSVIEW_H

#include <QWidget>

#include "clsCell.h"

class QLabel;

namespace nsp2042
{

class clsView : public QWidget
{
    Q_OBJECT

public:
    explicit clsView(QWidget *parent = 0);
    void updateView( int [4][4] );

private:
    clsCell cells4[4][4];
    QLabel *lblEnd;
    QLabel *lblScore;
    int n;

    QColor getColor( int v );

signals:
    void calcTest( void );
    void letsStart( void );
    void clearView( void );
    void abortAction( void );

public slots:
    void on_updateView( int *table, int score, bool isEnd );

};

} // namespace nsp2042

#endif // CLSVIEW_H
