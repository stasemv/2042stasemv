#include "clsView.h"

#include <QLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QLabel>

namespace nsp2042
{

clsView::clsView(QWidget *parent) :
    QWidget(parent)
{
    n = 4;

    QVBoxLayout *L0 = new QVBoxLayout( this );
    L0->setSpacing( 0 );
    {
        QGridLayout *L1 = new QGridLayout( );
        L0->addLayout( L1 );
        L1->setSpacing( 0 );
        for ( int i = 0; i < n; i++ )
            for ( int j = 0; j < n; j++ )
                L1->addWidget( &cells4[i][j], i+1, j+1 );

        // Spacers
        QSpacerItem *S1 = new QSpacerItem( 0, 0,
                                           QSizePolicy::Expanding, QSizePolicy::Expanding );
        QSpacerItem *S2 = new QSpacerItem( 0, 0,
                                           QSizePolicy::Expanding, QSizePolicy::Expanding );
        //    L0->addItem( S1, 0, 0 );
        //    L0->addItem( S2, n+3, n+3 );

    }
    {
        // labels

        QHBoxLayout *L1 = new QHBoxLayout( );
        L0->addLayout( L1 );

        lblScore = new QLabel( tr("0"), this );
        L1->addWidget( lblScore );

        QSpacerItem *S1 = new QSpacerItem( 0, 0,
                                           QSizePolicy::Expanding,
                                           QSizePolicy::Minimum );
        L1->addItem( S1 );

        lblEnd = new QLabel( tr(""), this );
        L1->addWidget( lblEnd );

    }
    {
        // button

        QHBoxLayout *L1 = new QHBoxLayout( );
        L0->addLayout( L1 );

        QPushButton *btnTest = new QPushButton( tr("Test"), this );
        btnTest->setMinimumSize( 20, 20 );
        btnTest->setMaximumSize( 40, 40 );
        L1->addWidget( btnTest );

        QPushButton *btnStart = new QPushButton( tr("Start"), this );
        btnStart->setMinimumSize( 20, 20 );
        btnStart->setMaximumSize( 40, 40 );
        L1->addWidget( btnStart );

        QPushButton *btnClear = new QPushButton( tr("Clear"), this );
        btnClear->setMinimumSize( 20, 20 );
        btnClear->setMaximumSize( 40, 40 );
        L1->addWidget( btnClear );

        QPushButton *btnAbort = new QPushButton( tr("Abort"), this );
        btnAbort->setMinimumSize( 20, 20 );
        btnAbort->setMaximumSize( 40, 40 );
        L1->addWidget( btnAbort );

    //connects
    connect( btnTest, SIGNAL(clicked()),
             this, SIGNAL(calcTest()) );
    connect( btnStart, SIGNAL(clicked()),
             this, SIGNAL(letsStart()) );
    connect( btnClear, SIGNAL(clicked()),
             this, SIGNAL(clearView()) );
    connect( btnAbort, SIGNAL(clicked()),
             this, SIGNAL(abortAction()) );
    }

}

void clsView::on_updateView( int *table, int score, bool isEnd )
{
    for( int i = 0; i < n; i++ )
        for (int j = 0; j < n; j++ )
        {
            cells4[i][j].setColor( getColor( table[i*4 + j] ) );
            cells4[i][j].setValue( table[i*4 + j] );
            cells4[i][j].updateCell();
        }
    lblScore->setText( QString::number( score ) );
    if ( isEnd )
        lblEnd->setText( tr("The enD") );
    else
        lblEnd->setText( tr("") );
}

void clsView::updateView( int table[4][4] )
{
    for( int i = 0; i < n; i++ )
        for (int j = 0; j < n; j++ )
        {
            cells4[i][j].setColor( getColor( table[i][j] ) );
            cells4[i][j].setValue( table[i][j] );
            cells4[i][j].updateCell();
        }
}

QColor clsView::getColor( int v )
{
    switch ( v )
    {
    case 0 : return QColor( 200, 200, 200 );
    case 1 : return QColor( 220, 200, 180 );
    case 2 : return QColor( 230, 180, 120 );
    case 3 : return QColor( 240, 140, 80 );
    case 4 : return QColor( 240, 120, 60 );
    case 5 : return QColor( 240, 100, 40 );
    case 6 : return QColor( 240, 80, 20 );
    case 7 : return QColor( 190, 200, 60 );
    case 8 : return QColor( 170, 190, 40 );
    case 9 : return QColor( 170, 180, 30 );
    case 10 : return QColor( 180, 180, 20 );
    case 11 : return QColor( 200, 200, 20 );
    case 12 : return QColor( 200, 220, 0 );
    case 13 : return QColor( 200, 220, 0 );
    default : break;
    }
    if ( v > 13 )
        return QColor( 100, 100, 100 );
    else
        return QColor( 200, 200, 200 );
}

} // namespace nsp2042
