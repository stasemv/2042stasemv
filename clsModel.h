#ifndef CLSMODEL_H
#define CLSMODEL_H

#include <QObject>
#include <QList>

namespace nsp2042
{

class clsModel : public QObject
{
    Q_OBJECT

public:
    explicit clsModel(QObject *parent = 0);

    void getNumbers( int *num );
    void getNumbers( int **numbers, int &_score, bool &_isEnd );
    int * startNumbers( );
    int * clearNumbers( );

private:
    int cellNumbers4[4][4];
    int previousNumbers[4][4];
    int previousNumbers_1[4][4];
    bool isEnd;
    int score;
    int previousScore;

    int addNumber( void );
    int moveVertical( int *score, bool isUp, int startIndex = 0 );
    bool shiftVertical( bool isUp, int column, int startIndex = 0 );
    int mergeVertical( bool isUp, int column, int startIndex = 0 );
    int moveHorizontal( int *score, bool isLeft, int startIndex = 0 );
    bool shiftHorizontal( bool isLeft, int row, int startIndex = 0 );
    int mergeHorizontal( bool isLeft, int row, int startIndex = 0 );
    bool checkFull( );
    void setNumbers( int *numbers );
    void copyNumbers( int *, int * );

signals:

public slots:
    void on_move( int );
    void on_abort();

};

} // namespace nsp2042

#endif // CLSMODEL_H
