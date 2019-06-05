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
#include <QLCDNumber>
#include <QDebug>

#include "myrobot.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QString ip, int port, bool laConnexion) ;

    private:
        void showHelp() ;
        void showAbout() ;
        MyRobot *monRobot = new MyRobot();
        QString ipAddress, numPort ;
        QLabel *statusLabel, *ipAddressLabel, *numPortLabel, *speedLabel, *batteryLabel ;
        QGroupBox *pilotBox, *sensorsBox, *cameraBox ;
        QPushButton *upButton, *downButton, *leftButton, *rightButton ;
        QLCDNumber *speed, *battery ;

    public slots:
        void disconnect() ;
        void avancer() ;
        void arreter() ;
        void reculer() ;
        void gauche() ;
        void droite() ;
};

#endif // MAINWINDOW_H
