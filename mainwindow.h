#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QDebug>

#include "myrobot.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QString ip, int port) ;

    private:
        void showHelp() ;
        void showAbout() ;
        MyRobot monRobot;
        QString ipAddress, numPort ;
        QLabel *statusLabel, *ipAddressLabel, *numPortLabel ;
        QGroupBox *pilotBox, *sensorsBox, *cameraBox ;
        QPushButton *upButton, *downButton, *leftButton, *rightButton ;

    public slots:
        void disconnect() ;
        void avancer();
};

#endif // MAINWINDOW_H
