#include "connexion.h"
#include "mainwindow.h"

Connexion::Connexion() : QWidget() {
    this->setWindowTitle("Wifibot Pilot | Connexion") ;
    //this->setWindowIcon("") ;
    QGridLayout *grille = new QGridLayout() ;
    grille->setMargin(20) ;

    QLabel *connexionTitle = new QLabel("Connexion to Wifibot", this) ;
    connexionTitle->setAlignment(Qt::AlignCenter) ;
    connexionTitle->setFont(QFont("System", 12, QFont::Bold)) ;
    grille->addWidget(connexionTitle, 0, 0, 1, 2) ;

    ipAddressLabel = new QLabel("Robot IPv4 address : ", this) ;
    grille->addWidget(ipAddressLabel, 1, 0) ;
    champIpAddress = new QLineEdit(this) ;
    //champIpAddress->setFixedWidth(400) ;
    grille->addWidget(champIpAddress, 1, 1) ;

    numPortLabel = new QLabel("Port number to reach : ", this) ;
    grille->addWidget(numPortLabel, 2, 0) ;
    champNumPort = new QLineEdit(this) ;
    grille->addWidget(champNumPort, 2, 1) ;

    boutonValider = new QPushButton("OK", this) ;
    boutonValider->setIcon(QIcon("../icons/baseline-check_circle-24px.svg")) ;
    boutonAnnuler = new QPushButton("Cancel", this) ;
    boutonAnnuler->setIcon(QIcon("../icons/baseline-cancel-24px.svg")) ;
    boutonReset = new QPushButton("Reset", this) ;
    boutonReset->setIcon(QIcon("../icons/baseline-delete-24px.svg")) ;
    grille->addWidget(boutonValider, 0, 2) ;
    grille->addWidget(boutonAnnuler, 1, 2) ;
    grille->addWidget(boutonReset, 2, 2) ;

    this->setLayout(grille) ;
    this->layout()->setSizeConstraint(QLayout::SetFixedSize) ;

    QObject::connect(boutonValider, SIGNAL(clicked()), this, SLOT(boutonValiderClic())) ;
    QObject::connect(boutonAnnuler, SIGNAL(clicked()), this, SLOT(close())) ;
    QObject::connect(boutonReset, SIGNAL(clicked()), this, SLOT(boutonResetClic())) ;
}

void Connexion::boutonValiderClic(){
    QMessageBox *information = new QMessageBox();
    ipAddress = champIpAddress->text() ;
    numPort = champNumPort->text().toInt() ;
    information->setWindowTitle("Wifibot Pilot | Information") ;
    information->setMinimumWidth(300) ;
    if(ipAddress.isEmpty() && numPort == 0){
        information->setText("IP address and port number are empty! Please give values.") ;
    }
    else if(ipAddress.isEmpty() || numPort == 0){
        information->setText("Some informations missing! Please give values.") ;
    }
    else{
        information->setText("Trying to reach " + ipAddress + ":" + champNumPort->text() + "... Please wait.") ;
        /*
         *
         * Ici devra être insérer le code qui établit la connexion avec le Wifibot...
         *
         */
    }
    information->show() ;
}

void Connexion::boutonResetClic(){
    QMessageBox *information = new QMessageBox();
    champIpAddress->setText("") ;
    champNumPort->setText("") ;
    information->setWindowTitle("Wifibot Pilot | Information") ;
    information->setText("IP address and port number have been reset!") ;
    information->setMinimumWidth(300) ;
    information->show() ;
}
