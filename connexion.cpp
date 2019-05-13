#include "connexion.h"
#include "mainwindow.h"

Connexion::Connexion() : QWidget() {
    this->setWindowTitle("Wifibot Pilot | Connexion") ;
    this->setWindowIcon(QIcon("")) ;
    QGridLayout *grille = new QGridLayout() ;
    grille->setMargin(20) ;

    QLabel *connexionTitle = new QLabel("Connexion to Wifibot", this) ;
    connexionTitle->setAlignment(Qt::AlignCenter) ;
    connexionTitle->setFont(QFont("System", 12, QFont::Bold)) ;
    grille->addWidget(connexionTitle, 0, 0, 1, 2) ;

    ipAddressLabel = new QLabel("Robot IPv4 address : ", this) ;
    grille->addWidget(ipAddressLabel, 1, 0) ;
    ipAddressField = new QLineEdit(this) ;
    //ipAddressField->setFixedWidth(400) ;
    grille->addWidget(ipAddressField, 1, 1) ;

    numPortLabel = new QLabel("Port number to reach : ", this) ;
    grille->addWidget(numPortLabel, 2, 0) ;
    numPortField = new QLineEdit(this) ;
    grille->addWidget(numPortField, 2, 1) ;

    okButton = new QPushButton(" OK", this) ;
    okButton->setIcon(QIcon("../icons/baseline-check_circle-24px.svg")) ;
    okButton->setToolTip("Press ENTER key.") ;
    cancelButton = new QPushButton(" Cancel", this) ;
    cancelButton->setIcon(QIcon("../icons/baseline-cancel-24px.svg")) ;
    cancelButton->setToolTip("Press ESCAPE key.") ;
    resetButton = new QPushButton(" Reset", this) ;
    resetButton->setIcon(QIcon("../icons/baseline-delete-24px.svg")) ;
    grille->addWidget(okButton, 0, 2) ;
    grille->addWidget(cancelButton, 1, 2) ;
    grille->addWidget(resetButton, 2, 2) ;

    this->setLayout(grille) ;
    this->layout()->setSizeConstraint(QLayout::SetFixedSize) ;

    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClic())) ;
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close())) ;
    QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClic())) ;
}

void Connexion::okButtonClic(){
    QMessageBox *information = new QMessageBox();
    ipAddress = ipAddressField->text() ;
    numPort = numPortField->text().toInt() ;
    information->setWindowTitle("Wifibot Pilot | Information") ;
    if(ipAddress.isEmpty() && numPort == 0){
        information->setText("IP address and port number are empty! Please give values.") ;
        information->setIcon(QMessageBox::Warning) ;
        information->exec() ;
    }
    else if(ipAddress.isEmpty() || numPort == 0){
        information->setText("Some informations missing! Please give values.") ;
        information->setIcon(QMessageBox::Warning) ;
        information->exec() ;
    }
    else{
        information->setText("Trying to reach " + ipAddress + ":" + numPortField->text() + "... Please wait.") ;
        information->setIcon(QMessageBox::Information) ;
        information->exec() ;
        /*
         *
         * Ici devra être inséré le code qui établit la connexion avec le Wifibot...
         *
         */
        if(true){
            information->setText("Connexion established with " + ipAddress + ":" + numPortField->text() + "!") ;
            information->setIcon(QMessageBox::Information) ;
            information->exec() ;
            MainWindow *fenetrePrincipale = new MainWindow(ipAddress, numPort);
            fenetrePrincipale->show() ;
            this->close() ;
        }
        else{
            information->setText("Fail to reach " + ipAddress + ":" + numPortField->text() + "! Please check network.") ;
            information->setIcon(QMessageBox::Critical) ;
            information->exec() ;
        }
    }
}

void Connexion::resetButtonClic(){
    QMessageBox *information = new QMessageBox();
    ipAddressField->setText("") ;
    numPortField->setText("") ;
    information->setWindowTitle("Wifibot Pilot | Information") ;
    information->setText("IP address and port number have been reset!") ;
    information->setIcon(QMessageBox::Information) ;
    information->show() ;
}

void Connexion::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_Enter :
            okButtonClic() ;
            break ;
        case Qt::Key_Escape :
            this->close() ;
            break ;
    }
}
