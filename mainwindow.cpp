#include "mainwindow.h"

MainWindow::MainWindow(QString ip, int port) : QWidget() {
    ipAddress = ip ;
    numPort = QString::number(port) ;

    this->setWindowTitle("Wifibot Pilot | Robot " + ip + ":" + QString::number(port)) ;
    this->setWindowIcon(QIcon("")) ;
    QGridLayout *grille = new QGridLayout() ;
    grille->setHorizontalSpacing(60) ;

    QLabel *status = new QLabel("CONNECTED", this) ;
    status->setStyleSheet("color: #01DF01") ;
    status->setFont(QFont("System", 10, QFont::Bold)) ;
    grille->addWidget(status, 0, 0) ;

    QLabel *ipAddressLabel = new QLabel("IP address : " + ip, this) ;
    QLabel *numPortLabel = new QLabel("Port number : " + QString::number(port), this) ;
    grille->addWidget(ipAddressLabel, 0, 1) ;
    grille->addWidget(numPortLabel, 0, 2) ;

    QPushButton *disconnectButton = new QPushButton("Disconnect") ;
    disconnectButton->setIcon(QIcon("")) ;
    grille->addWidget(disconnectButton, 0, 3) ;

    this->setLayout(grille) ;

    QObject::connect(disconnectButton, SIGNAL(clicked()), this, SLOT(disconnect())) ;
}

void MainWindow::disconnect(){
    QMessageBox *information = new QMessageBox();
    information->setText("Disconnection asked!") ;
    information->setInformativeText("Do you really want to disconnect from " + this->ipAddress + ":" + this->numPort + "?") ;
    information->setWindowTitle("Wifibot Pilot | Disconnection") ;
    information->setMinimumWidth(300) ;
    information->setIcon(QMessageBox::Question) ;
    information->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    information->setDefaultButton(QMessageBox::No);
    int action = information->exec() ;
    switch (action) {
        case QMessageBox::Yes :
            this->close() ;
            break ;
        case QMessageBox::No :
            break ;
    }
}
