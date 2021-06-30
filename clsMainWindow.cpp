#include "clsMainWindow.h"

#include <QKeyEvent>

namespace nsp2042
{

clsMainWindow::clsMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new clsModel( this );
    view = new clsView( this );
    controller = new clsController( this );
    setCentralWidget( view );

    // connections
    connect( controller, SIGNAL(updateView(int*,int,bool)),
             view, SLOT(on_updateView(int*,int,bool)) );
    connect( controller, SIGNAL(move(int)),
             model, SLOT(on_move(int)) );

    connect( view, SIGNAL(calcTest()),
             this, SLOT(test()) );
    connect( view, SIGNAL(letsStart()),
             this, SLOT(start()) );
    connect( view, SIGNAL(clearView()),
             this, SLOT(clear()) );
    connect( view, SIGNAL(abortAction()),
             this, SLOT(abort()) );
//    connect( view, SIGNAL(abortAction()),
//             model, SLOT(on_abort()) );

}

clsMainWindow::~clsMainWindow()
{

}

void clsMainWindow::keyPressEvent( QKeyEvent *event )
{
    emit controller->move( event->key() );
    int *numbers, score;
    bool isEnd;
    model->getNumbers( &numbers, score, isEnd );
    emit controller->updateView( numbers, score, isEnd );
}

void clsMainWindow::test()
{
    // test
    int numbers[4][4], *num;
    num = &numbers[0][0];
    int score;
    bool isEnd;
    model->getNumbers( &num, score, isEnd );
    emit controller->updateView( &numbers[0][0], score, isEnd );
}

void clsMainWindow::start()
{
    int *numbers;
    numbers = model->startNumbers( );
    int score;
    bool isEnd;
    model->getNumbers( &numbers, score, isEnd );
    emit controller->updateView( numbers, score, isEnd );
}

void clsMainWindow::clear()
{
    // clear
    int *numbers = NULL;
    numbers = model->clearNumbers( );
    int score;
    bool isEnd;
    model->getNumbers( &numbers, score, isEnd );
    emit controller->updateView( numbers, score, isEnd );
}

void clsMainWindow::abort()
{
    // abort
    model->on_abort();
    int *numbers = NULL;
//    numbers = model->clearNumbers( );
    int score;
    bool isEnd;
    model->getNumbers( &numbers, score, isEnd );
    emit controller->updateView( numbers, score, isEnd );
}

} // namespace nsp2042
