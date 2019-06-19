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
#include <QKeyEvent>
#include <QDebug>

#include "myrobot.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QString ip, int port, bool laConnexion) ;
        void keyPressEvent(QKeyEvent *event) ;
        void keyReleaseEvent(QKeyEvent *event) ;

    private:
        void showHelp() ;
        void showAbout() ;
        MyRobot *monRobot = new MyRobot();
        QString ipAddress, numPort ;
        QLabel *statusLabel, *ipAddressLabel, *numPortLabel, *speedLabel, *batteryLabel, *odometryLabel ;
        QGroupBox *pilotBox, *sensorsBox, *cameraBox ;
        QPushButton *upButton, *downButton, *leftButton, *rightButton ;

    public slots:
        void disconnect() ;
        void avancer() ;
        void arreter() ;
        void reculer() ;
        void gauche() ;
        void droite() ;
};

#endif // MAINWINDOW_H
