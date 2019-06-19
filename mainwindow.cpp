#include "mainwindow.h"

MainWindow::MainWindow(QString ip, int port, bool laConnexion) : QMainWindow() {
    if(monRobot->doConnect(ip, QString::number(port)) && laConnexion){      //To use in test mode, comment this line.
    //if(laConnexion){                                                      //To use in real mode, comment this line.
        ipAddress = ip ;
        numPort = QString::number(port) ;

        QWidget *centralWidget = new QWidget() ;
        setCentralWidget(centralWidget) ;

        this->setWindowTitle("Wifibot Pilot | Robot " + ip + ":" + QString::number(port)) ;
        this->setWindowIcon(QIcon("../icons/baseline-android-24px.svg")) ;

        statusBar()->showMessage("Ready") ;

        QMenu *menuFichier = menuBar()->addMenu("File") ;
        QMenu *menuAbout = menuBar()->addMenu("Help") ;

        QAction *disconnectRobot = new QAction(QIcon("../icons/baseline-wifi_off-24px.svg"), "Disconnect", menuFichier) ;
        connect(disconnectRobot, &QAction::triggered, this, &MainWindow::disconnect) ;
        menuFichier->addAction(disconnectRobot) ;

        QAction *help = new QAction(QIcon("../icons/baseline-help-24px.svg"), "Help", menuAbout) ;
        connect(help, &QAction::triggered, this, &MainWindow::showHelp) ;
        menuAbout->addAction(help) ;
        QAction *about = new QAction(QIcon("../icons/baseline-info-24px.svg"), "About Wifibot Pilot", menuAbout) ;
        connect(about, &QAction::triggered, this, &MainWindow::showAbout) ;
        menuAbout->addAction(about) ;

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

        monRobot->speed = new QLCDNumber() ;
        speedLabel = new QLabel("Speed: ", this) ;
        innerSensorsPanelGrid->addWidget(speedLabel, 0, 0) ;
        innerSensorsPanelGrid->addWidget(monRobot->speed, 0, 1, 1, 2) ;

        batteryLabel = new QLabel("Battery: ", this) ;
        innerSensorsPanelGrid->addWidget(batteryLabel, 1, 0) ;
        innerSensorsPanelGrid->addWidget(monRobot->battery, 1, 1, 1, 2) ;

        odometryLabel = new QLabel("Odometry: ", this) ;
        innerSensorsPanelGrid->addWidget(odometryLabel, 2, 0) ;
        innerSensorsPanelGrid->addWidget(monRobot->odometryL, 2, 1) ;
        innerSensorsPanelGrid->addWidget(monRobot->odometryR, 2, 2) ;

        centralWidget->setLayout(grille) ;
        this->layout()->setSizeConstraint(QLayout::SetFixedSize) ;
        pilotBox->setLayout(innerPilotPanelGrid) ;
        sensorsBox->setLayout(innerSensorsPanelGrid) ;
        cameraBox->setLayout(innerCameraPanelGrid) ;

        QObject::connect(disconnectButton, SIGNAL(clicked()), this, SLOT(disconnect())) ;

        QObject::connect(upButton, SIGNAL(pressed()), this, SLOT(avancer())) ;
        QObject::connect(upButton, SIGNAL(released()), this, SLOT(arreter())) ;

        QObject::connect(downButton, SIGNAL(pressed()), this, SLOT(reculer())) ;
        QObject::connect(downButton, SIGNAL(released()), this, SLOT(arreter())) ;

        QObject::connect(leftButton, SIGNAL(pressed()), this, SLOT(gauche())) ;
        QObject::connect(leftButton, SIGNAL(released()), this, SLOT(arreter())) ;

        QObject::connect(rightButton, SIGNAL(pressed()), this, SLOT(droite())) ;
        QObject::connect(rightButton, SIGNAL(released()), this, SLOT(arreter())) ;
    }
}

void MainWindow::disconnect(){
    statusBar()->showMessage("Disconnection...") ;
    QMessageBox *information = new QMessageBox();
    information->setWindowTitle("Wifibot Pilot | Disconnection") ;
    information->setText(tr("<h2>Disconnection asked!</h2>")) ;
    information->setInformativeText("<p>Do you really want to disconnect from " + this->ipAddress + ":" + this->numPort + "?</p>") ;
    information->setIcon(QMessageBox::Question) ;
    information->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    information->setDefaultButton(QMessageBox::No);
    int action = information->exec() ;
    switch (action) {
        case QMessageBox::Yes :
            monRobot->disConnect();
            this->close() ;
            break ;
        case QMessageBox::No :
            statusBar()->showMessage("Ready") ;
            break ;
    }
}

void MainWindow::showHelp(){
    QMessageBox *information = new QMessageBox();
    information->setWindowTitle("Wifibot Pilot | Help") ;
    information->setText(tr("<h2>Wifibot Pilot Help</h2>")) ;
    information->setInformativeText(tr("<p>This interface has been developped to implement some classical features of a Wifibot robot, that is to say move ahead, backward, to the left and to the right. To move the robot, press either the buttons displayed on the left screen side or the keyboard touches Z, Q, S or D. The robot will move on your demand.</p><p>On the right side, you have the sensors information of the robot: speed rate, the battery level and the odometry sensor.</p><p>At the bottom of the screen, you have the video stream (if implemented).</p>")) ;
    information->setIcon(QMessageBox::Information) ;
    information->exec() ;
}

void MainWindow::showAbout(){
    QMessageBox *information = new QMessageBox();
    information->setWindowTitle("Wifibot Pilot | About") ;
    information->setText(tr("<h2>About this software</h2>")) ;
    information->setInformativeText(tr("<p>This software has been developped by Anindo MOUSSARD and Nicolas TOURRETTE, studying IE ingineering at ESIREM Dijon.</p><p>Version : 1.0 build 1</p><p>GUI : Nicolas TOURRETTE<br>TCP/IP layer : Anindo MOUSSARD</p>")) ;
    information->setIcon(QMessageBox::Information) ;
    information->exec() ;
}

void MainWindow::avancer(){
    monRobot->Avancer();
}

void MainWindow::arreter(){
    monRobot->Arreter();
}

void MainWindow::reculer(){
    monRobot->Reculer();
}

void MainWindow::gauche(){
    monRobot->Gauche();
}

void MainWindow::droite(){
    monRobot->Droite();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_Z :
            avancer() ;
            break ;
        case Qt::Key_S :
            reculer() ;
            break ;
        case Qt::Key_Q :
            gauche() ;
            break ;
        case Qt::Key_D :
            droite() ;
            break ;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_Z :
            arreter() ;
            break ;
        case Qt::Key_S :
            arreter() ;
            break ;
        case Qt::Key_Q :
            arreter() ;
            break ;
        case Qt::Key_D :
            arreter() ;
            break ;
    }
}
