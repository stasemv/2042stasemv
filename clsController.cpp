#include "clsController.h"

namespace nsp2042
{

clsController::clsController( QObject *parent ) :
    QObject(parent)
{
}

void clsController::testSignal( int table[4][4], int score, bool isEnd )
{
    emit updateView( &table[0][0], score, isEnd );
}

} // namespace nsp2042
