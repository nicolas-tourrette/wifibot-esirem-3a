#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT

    public:
        MainWindow(QString ip, int port) ;

    private:
};

#endif // MAINWINDOW_H
