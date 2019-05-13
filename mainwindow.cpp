#include "mainwindow.h"

MainWindow::MainWindow(QString ip, int port) : QWidget() {
    ipAddress = ip ;
    numPort = QString::number(port) ;

    this->setWindowTitle("Wifibot Pilot | Robot " + ip + ":" + QString::number(port)) ;
    this->setWindowIcon(QIcon("")) ;
    QGridLayout *grille = new QGridLayout() ;
    QGridLayout *innerPilotPanelGrid = new QGridLayout() ;
    QGridLayout *innerSensorsPanelGrid = new QGridLayout() ;
    QGridLayout *innerCameraPanelGrid = new QGridLayout() ;
    grille->setHorizontalSpacing(60) ;

    statusLabel = new QLabel("CONNECTED", this) ;
    statusLabel->setStyleSheet("color: #01DF01") ;
    statusLabel->setFont(QFont("System", 10, QFont::Bold)) ;
    grille->addWidget(statusLabel, 0, 0) ;

    ipAddressLabel = new QLabel("IP address : " + ip, this) ;
    numPortLabel = new QLabel("Port number : " + QString::number(port), this) ;
    grille->addWidget(ipAddressLabel, 0, 1) ;
    grille->addWidget(numPortLabel, 0, 2) ;

    QPushButton *disconnectButton = new QPushButton(" Disconnect") ;
    disconnectButton->setIcon(QIcon("../icons/baseline-wifi_off-24px.svg")) ;
    grille->addWidget(disconnectButton, 0, 3) ;

    pilotBox = new QGroupBox("Pilot Panel") ;
    sensorsBox = new QGroupBox("Sensors Control Panel") ;
    cameraBox = new QGroupBox("Camera view") ;
    grille->addWidget(pilotBox, 1, 0, 1, 2) ;
    grille->addWidget(sensorsBox, 1, 2, 1, 2) ;
    grille->addWidget(cameraBox, 2, 0, 1, 4) ;

    upButton = new QPushButton("") ;
    upButton->setIcon(QIcon("../icons/baseline-expand_less-24px.svg")) ;
    upButton->setIconSize(QSize(30, 30)) ;
    upButton->setToolTip("Go ahead!") ;
    innerPilotPanelGrid->addWidget(upButton, 0, 0, 1, 2) ;

    downButton = new QPushButton("") ;
    downButton->setIcon(QIcon("../icons/baseline-expand_more-24px.svg")) ;
    downButton->setIconSize(QSize(30, 30)) ;
    downButton->setToolTip("Go back!") ;
    innerPilotPanelGrid->addWidget(downButton, 2, 0, 1, 2) ;

    leftButton = new QPushButton("") ;
    leftButton->setIcon(QIcon("../icons/baseline-chevron_left-24px.svg")) ;
    leftButton->setIconSize(QSize(30, 30)) ;
    leftButton->setToolTip("Go left!") ;
    innerPilotPanelGrid->addWidget(leftButton, 1, 0) ;

    rightButton = new QPushButton("") ;
    rightButton->setIcon(QIcon("../icons/baseline-chevron_right-24px.svg")) ;
    rightButton->setIconSize(QSize(30, 30)) ;
    rightButton->setToolTip("Go right!") ;
    innerPilotPanelGrid->addWidget(rightButton, 1, 1) ;

    this->setLayout(grille) ;
    this->layout()->setSizeConstraint(QLayout::SetFixedSize) ;
    pilotBox->setLayout(innerPilotPanelGrid) ;
    sensorsBox->setLayout(innerSensorsPanelGrid) ;
    cameraBox->setLayout(innerCameraPanelGrid) ;

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
