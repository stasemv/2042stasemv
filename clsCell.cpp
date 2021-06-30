#include "clsCell.h"

#include <QLabel>
#include <QLayout>
#include <QSpacerItem>
#include "math.h"

namespace nsp2042
{

clsCell::clsCell(QWidget *parent) :
    QFrame(parent)
{
    setMinimumSize( 50, 50 );
    setMaximumSize( 300, 300 );
    setFrameShadow( QFrame::Sunken );
    setFrameShape( QFrame::Panel );
    setAutoFillBackground( true );

    label = new QLabel( this );
    value = 0;
    color = QColor( 200, 200, 200 );

    QGridLayout *L0 = new QGridLayout( this );
    L0->setMargin( 0 );
    L0->setSpacing( 0 );
    L0->addWidget( label, 1, 1 );

    QSpacerItem *S1 = new QSpacerItem( 0, 0,
                                       QSizePolicy::Expanding,
                                       QSizePolicy::Expanding );
    QSpacerItem *S2 = new QSpacerItem( 0, 0,
                                       QSizePolicy::Expanding,
                                       QSizePolicy::Expanding );
    L0->addItem( S1, 0, 0 );
    L0->addItem( S2, 2, 2 );

    updateCell();
}

void clsCell::updateCell( )
{
    if ( value != 0 )
        label->setText( QString::number( pow( 2, value ) ) );
    else
        label->setText( "" );

    QPalette P = palette();
    P.setColor( QPalette::Window, QColor( color ));
    setPalette( P );

}

void clsCell::setColor( QColor _color )
{
    color = _color;
}

void clsCell::setValue( int _value )
{
    value = _value;
}

} // namespace nsp2042
