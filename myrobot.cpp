// myrobot.cpp

#include "myrobot.h"

int vitesse = 0;
bool robotAvance = false;
bool robotRecule = false;
bool robotGauche = false;
bool robotDroite = false;

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


bool MyRobot::doConnect(QString ip, QString port) {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    //socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    socket->connectToHost(ip, port.toInt());
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        QMessageBox *information = new QMessageBox();
        information->setText("Fail to reach " + ip + ":" + port + "! Error message: \"" + socket->errorString() + "\".") ;
        information->setIcon(QMessageBox::Critical) ;
        information->exec() ;
        return false;
    }
    TimerEnvoi->start(75);
    return true;
}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    DataReceived = socket->readAll();
    qDebug() << "reading..."; // read the data from the socket

    unsigned char batteryValue = DataReceived[2];
    battery->display(batteryValue);

    unsigned char speedRate = (int)((DataReceived[1] << 8) + DataReceived[0]) ;
    //speed->display(speedRate) ;

    double mphspeed=double(speedRate)/2048;
    qDebug()<<"pm "<<mphspeed;
    double perimeter= 2*3.1415*0.07;
    mphspeed=mphspeed*perimeter*200;
    qDebug()<<"speed "<<mphspeed<<" m/s";
    speed->display(mphspeed) ;

    unsigned char odemetryRateL = (((long)DataReceived[8] << 24))+(((long)DataReceived[7] << 16))+(((long)DataReceived[6] << 8))+((long)DataReceived[5]) ;
    odometryL->display(odemetryRateL) ;

    unsigned char odemetryRateR = (((long)DataReceived[16] << 24))+(((long)DataReceived[15] << 16))+(((long)DataReceived[14] << 8))+((long)DataReceived[13]);
    odometryR->display(odemetryRateR) ;

    unsigned char infraRedFLValue = DataReceived[3] ;
    infraRedFL->display(infraRedFLValue);

    unsigned char infraRedFRValue = DataReceived[11] ;
    infraRedFR->display(infraRedFRValue);

    unsigned char infraRedBLValue = DataReceived[4] ;
    infraRedBL->display(infraRedBLValue);

    unsigned char infraRedBRValue = DataReceived[12] ;
    infraRedBR->display(infraRedBRValue);
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

qint16 MyRobot::Crc16(QByteArray *Adresse_tab , unsigned char Taille_max){
    const unsigned char *data = ((const unsigned char*)Adresse_tab->constData())+1;
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;
    Crc=0xFFFF;
    Polynome= 0xA001;
    for ( CptOctet= 0 ; CptOctet < Taille_max ; CptOctet++){
        Crc ^= *( data + CptOctet);
        for ( CptBit = 0; CptBit <= 7 ; CptBit++){
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true)
                Crc ^= Polynome;
        }
    }
    return(Crc);
}

void MyRobot::Avancer(){
    DataToSend[2] = 120;
    DataToSend[4] = 120;
    DataToSend[6] = 0x50;
    qint16 crc=Crc16(&DataToSend, 6);
    DataToSend[7] =char(crc);
    DataToSend[8] =char(crc>> 8);
}

void MyRobot::Arreter(){
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    DataToSend[6] = 0;
    DataToSend[7] = 0;
    DataToSend[8] = 0;
}

void MyRobot::Reculer(){
    DataToSend[2] = 180;
    DataToSend[4] = 180;
    DataToSend[6] = 0;
    qint16 crc=Crc16(&DataToSend, 6);
    DataToSend[7] =char(crc);
    DataToSend[8] =char(crc>> 8);
}

void MyRobot::Gauche(){
    DataToSend[2] = 90;
    DataToSend[4] = 180;
    DataToSend[6] = 0x50;
    qint16 crc=Crc16(&DataToSend, 6);
    DataToSend[7] =char(crc);
    DataToSend[8] =char(crc>> 8);
}


void MyRobot::Droite(){
    DataToSend[2] = 180;
    DataToSend[4] = 90;
    DataToSend[6] = 0x50;
    qint16 crc=Crc16(&DataToSend, 6);
    DataToSend[7] =char(crc);
    DataToSend[8] =char(crc>> 8);
}

void MyRobot::avancer_progressive() {
    qDebug() << "Avance";
    DataToSend[2] = vitesse;
    DataToSend[4] = vitesse;
    DataToSend[6] = 0xF8;
    qint16 crc=Crc16(&DataToSend, 6);
    DataToSend[7] =char(crc);
    DataToSend[8] =char(crc>> 8);
    robotAvance = true;
    robotRecule = false;
    robotGauche = false;
    robotDroite = false;
}

void MyRobot::reculer_progressive() {
    qDebug() << "Recule";
    DataToSend[2] = vitesse;
    DataToSend[4] = vitesse;
    DataToSend[6] = 0xA0;
    qint16 crc=Crc16(&DataToSend, 6);
    DataToSend[7] =char(crc);
    DataToSend[8] =char(crc>> 8);
    robotAvance = true;
    robotRecule = false;
    robotGauche = false;
    robotDroite = false;
}

void MyRobot::gauche_progressive() {
    qDebug() << "Gauche";
    DataToSend[2] = vitesse;
    DataToSend[4] = vitesse;
    DataToSend[6] = 0xB0;
    qint16 crc=Crc16(&DataToSend, 6);
    DataToSend[7] =char(crc);
    DataToSend[8] =char(crc>> 8);
    robotAvance = false;
    robotRecule = false;
    robotGauche = true;
    robotDroite = false;
}

void MyRobot::droite_progressive() {
    qDebug() << "Droite";
    DataToSend[2] = vitesse;
    DataToSend[4] = vitesse;
    DataToSend[6] = 0xE0;
    qint16 crc=Crc16(&DataToSend, 6);
    DataToSend[7] =char(crc);
    DataToSend[8] =char(crc>> 8);
    robotAvance = false;
    robotRecule = false;
    robotGauche = false;
    robotDroite = true;
}

void MyRobot::setVitesse(int value){
    vitesse = value;
    if(robotAvance)
        avancer_progressive();

    if(robotRecule)
        reculer_progressive();

    if(robotGauche)
        gauche_progressive();

    if(robotDroite)
        droite_progressive();
}
