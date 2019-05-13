#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QDebug>

class MainWindow : public QWidget {
    Q_OBJECT

    public:
        MainWindow(QString ip, int port) ;

    private:
        QString ipAddress, numPort ;
        QLabel *statusLabel, *ipAddressLabel, *numPortLabel ;
        QGroupBox *pilotBox, *sensorsBox, *cameraBox ;
        QPushButton *upButton, *downButton, *leftButton, *rightButton ;

    public slots:
        void disconnect() ;
};

#endif // MAINWINDOW_H
