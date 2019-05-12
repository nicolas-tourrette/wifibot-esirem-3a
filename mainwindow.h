#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

class MainWindow : public QWidget {
    Q_OBJECT

    public:
        MainWindow(QString ip, int port) ;

    private:
        QString ipAddress, numPort ;

    public slots:
        void disconnect() ;
};

#endif // MAINWINDOW_H
