#ifndef CLSMAINWINDOW_H
#define CLSMAINWINDOW_H

#include <QMainWindow>

#include "clsModel.h"
#include "clsView.h"
#include "clsController.h"

namespace nsp2042
{

class clsMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    clsMainWindow(QWidget *parent = 0);
    ~clsMainWindow();

private:
    clsModel *model;
    clsView *view;
    clsController *controller;

    void keyPressEvent( QKeyEvent * event );

private slots:
    void test( void );
    void start( void );
    void clear( void );
    void abort( void );

};

} // namespace nsp2042

#endif // CLSMAINWINDOW_H
