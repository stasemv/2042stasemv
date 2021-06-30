#include "clsModel.h"

#include "math.h"

namespace nsp2042
{

clsModel::clsModel(QObject *parent) :
    QObject(parent)
{
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            cellNumbers4[i][j] = 0;
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            if ( i == j )
            cellNumbers4[i][j] = i;
    int k = 0, dk = 1, value = 0;
    int r = 0;
    while ( r < 4 )
    {
        cellNumbers4[r][k] = value++;
        k += dk;
        if ( k < 0 )
            k = 0, dk = 1, r++;
        if ( k > 3 )
            k = 3, dk = -1, r++;
    }
    cellNumbers4[0][0] = 1;
    cellNumbers4[0][1] = 0;

    isEnd = false;
    score = 0;
    previousScore = 0;

    srand(0);
}

void clsModel::on_move( int key )
{
    int addScore = 0;
    bool isMoved = false;
    if ( !isEnd )
    {
        switch ( key )
        {
        case 1062 :
            isMoved = moveVertical( &addScore, true );
            break;
        case 1067 :
            isMoved = moveVertical( &addScore, false, 3 );
            break;
        case 1060 :
            isMoved = moveHorizontal( &addScore, true );
            break;
        case 1042 :
            isMoved = moveHorizontal( &addScore, false, 3 );
            break;
        default : break;
        }
        if ( isMoved )
        {
            previousScore = score;
            copyNumbers( &previousNumbers[0][0], &previousNumbers_1[0][0] );
            score += addNumber();
        }
        score += addScore;
    }
    isEnd = checkFull();
}

int clsModel::moveVertical( int *score, bool isUp, int startIndex )
{
    bool isShifted = false;
    int merged = 0;
    getNumbers( &previousNumbers_1[0][0] );
    for( int j = 0; j < 4; j++ )
    {
        isShifted = isShifted | shiftVertical( isUp, j, startIndex );
        merged += mergeVertical( isUp, j, startIndex );
        isShifted = isShifted | shiftVertical( isUp, j, startIndex );
    }
    *score = merged;
    return isShifted || merged;
}

bool clsModel::shiftVertical(bool isUp, int column, int startIndex)
{
    bool isShifted = false, isShifted_1, isShifted_2;
    int i0, iEnd, step;
    if ( isUp )
        i0 = startIndex, iEnd = 3, step = 1;
    else
        i0 = startIndex, iEnd = 0, step = -1;

    for( int i = i0; (iEnd - i0)*(iEnd - i) > 0; i += step )
        if ( cellNumbers4[i][column] == 0 )
        {
            if ( cellNumbers4[i+step][column] == 0 )
                isShifted_1 = shiftVertical( isUp, column, i+step );
            if ( cellNumbers4[i+step][column] != 0 )
            {
                cellNumbers4[i][column] = cellNumbers4[i+step][column];
                cellNumbers4[i+step][column] = 0;
                isShifted_2 = shiftVertical( isUp, column, i+step );
                isShifted = true;
            }
        }
    return isShifted;
}

int clsModel::mergeVertical( bool isUp, int column, int startIndex )
{
    int merged = 0, merged_1;
    int i0, iEnd, step;
    if ( isUp )
        i0 = startIndex, iEnd = 3, step = 1;
    else
        i0 = startIndex, iEnd = 0, step = -1;

        for( int i = i0; (iEnd - i0)*(iEnd - i) > 0; i += step )
            if ( cellNumbers4[i][column] != 0 )
                if ( cellNumbers4[i+step][column] == cellNumbers4[i][column] )
                {
                    cellNumbers4[i][column]++;
                    cellNumbers4[i+step][column] = 0;
                    merged = pow( 2, cellNumbers4[i][column] );
                    if ( ( isUp && (i < iEnd-1) ) || ( !isUp && (i > iEnd+1) ) )
                        merged_1 = mergeVertical( isUp, column, i+2*step );
                }
    return merged;
}

int clsModel::moveHorizontal( int *score, bool isLeft, int startIndex )
{
    bool isShifted = false;
    int merged = 0;
    getNumbers( &previousNumbers_1[0][0] );
    for( int j = 0; j < 4; j++ )
    {
        isShifted = isShifted | shiftHorizontal( isLeft, j, startIndex );
        merged += mergeHorizontal( isLeft, j, startIndex );
        isShifted = isShifted | shiftHorizontal( isLeft, j, startIndex );
    }
    *score = merged;
    return isShifted || merged;
}

bool clsModel::shiftHorizontal( bool isLeft, int row, int startIndex )
{
    bool isShifted = false, isShifted_1, isShifted_2;
    int i0, iEnd, step;
    if ( isLeft )
        i0 = startIndex, iEnd = 3, step = 1;
    else
        i0 = startIndex, iEnd = 0, step = -1;

    for( int i = i0; (iEnd - i0)*(iEnd - i) > 0; i += step )
        if ( cellNumbers4[row][i] == 0 )
        {
            if ( cellNumbers4[row][i+step] == 0 )
                isShifted_1 = shiftHorizontal( isLeft, row, i+step );
            if ( cellNumbers4[row][i+step] != 0 )
            {
                cellNumbers4[row][i] = cellNumbers4[row][i+step];
                cellNumbers4[row][i+step] = 0;
                isShifted_2 = shiftHorizontal( isLeft, row, i+step );
                isShifted = true;
            }
        }
    return isShifted;
}

int clsModel::mergeHorizontal( bool isLeft, int row, int startIndex )
{
    int merged = 0, merged_1;
    int i0, iEnd, step;
    if ( isLeft )
        i0 = startIndex, iEnd = 3, step = 1;
    else
        i0 = startIndex, iEnd = 0, step = -1;

        for( int i = i0; (iEnd - i0)*(iEnd - i) > 0; i += step )
            if ( cellNumbers4[row][i] != 0 )
                if ( cellNumbers4[row][i+step] == cellNumbers4[row][i] )
                {
                    cellNumbers4[row][i]++;
                    cellNumbers4[row][i+step] = 0;
                    merged = pow( 2, cellNumbers4[row][i] );
                    if ( ( isLeft && (i < iEnd-1) ) || ( !isLeft && (i > iEnd+1) ) )
                        merged_1 = mergeVertical( isLeft, row, i+2*step );
                }
    return merged;
}

bool clsModel::checkFull()
{
    bool isFull = true;
    for( int i = 0; i < 4; i++ )
    {
        for( int j = 0; j < 4; j++ )
            if ( cellNumbers4[i][j] == 0)
            {
                isFull = false;
                break;
            }
        if ( !isFull )
            break;
    }
    if ( isFull )
    {
        for( int i = 1; i < 3; i++ )
        {
            for( int j = 1; j < 3; j++ )
            {
                if ( ( cellNumbers4[i][j] == cellNumbers4[i-1][j] ) ||
                     ( cellNumbers4[i][j] == cellNumbers4[i][j-1] ) ||
                     ( cellNumbers4[i][j] == cellNumbers4[i+1][j] ) ||
                     ( cellNumbers4[i][j] == cellNumbers4[i][j+1] ) )
                {
                    isFull = false;
                    break;
                }
            }
            if ( !isFull )
                break;
        }
        int i = 0, j = 0;
        if ( ( cellNumbers4[i][j] == cellNumbers4[i+1][j] ) ||
             ( cellNumbers4[i][j] == cellNumbers4[i][j+1] ) )
            isFull = false;
        i = 0, j = 3;
        if ( ( cellNumbers4[i][j] == cellNumbers4[i+1][j] ) ||
             ( cellNumbers4[i][j] == cellNumbers4[i][j-1] ) )
            isFull = false;
        i = 3, j = 0;
        if ( ( cellNumbers4[i][j] == cellNumbers4[i-1][j] ) ||
             ( cellNumbers4[i][j] == cellNumbers4[i][j+1] ) )
            isFull = false;
        i = 3, j = 3;
        if ( ( cellNumbers4[i][j] == cellNumbers4[i-1][j] ) ||
             ( cellNumbers4[i][j] == cellNumbers4[i][j-1] ) )
            isFull = false;
        if ( ( cellNumbers4[0][1] == cellNumbers4[0][2] ) ||
             ( cellNumbers4[3][1] == cellNumbers4[3][2] ) ||
             ( cellNumbers4[1][0] == cellNumbers4[2][0] ) ||
             ( cellNumbers4[1][3] == cellNumbers4[2][3] ) )
            isFull = false;
    }
    return isFull;
}

void clsModel::getNumbers(int *num )
{
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            num[i*4 + j] = cellNumbers4[i][j];
}

void clsModel::getNumbers( int **numbers, int &_score, bool &_isEnd )
{
    *numbers = &cellNumbers4[0][0];
    _score = score;
    _isEnd = isEnd;
}

int * clsModel::startNumbers( )
{
    isEnd = false;
    score = 0;
    int *num = clearNumbers( );
    for( int i = 0; i < 3; i++ )
        score += addNumber();
    return &cellNumbers4[0][0];
}

int * clsModel::clearNumbers( )
{
    isEnd = false;
    score = 0;
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            cellNumbers4[i][j] = 0;
    return &cellNumbers4[0][0];
}

void clsModel::on_abort()
{
    if (!isEnd)
    {
        score = previousScore;
        setNumbers( &previousNumbers[0][0] );
    }
}

int clsModel::addNumber()
{
    int n1, n2, nV;
    int addScore = 0;
    while (true)
    {
        n1 = (rand() * 4) / RAND_MAX;
        n2 = (rand() * 4) / RAND_MAX;
        nV = (rand() * 8) / RAND_MAX;
        if ( cellNumbers4[n1][n2] == 0 )
        {
            cellNumbers4[n1][n2] = (nV > 1) ? 1 : 2;
            addScore = pow( 2, cellNumbers4[n1][n2] );
            break;
        }
    }
    return addScore;
}

void clsModel::setNumbers( int *numbers )
{
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            cellNumbers4[i][j] = numbers[i*4 + j];
}

void clsModel::copyNumbers( int *numbers, int *numbers_1 )
{
    for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            numbers[i*4 + j] = numbers_1[i*4 + j];
}

} // namespace nsp2042
