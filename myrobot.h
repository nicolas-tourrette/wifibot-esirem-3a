#ifndef MYROBOT_H
#define MYROBOT_H

#include <QMessageBox>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0); //anciennement MyTcpClient
    bool doConnect(QString ip, QString port);
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();
    void Avancer();
    void Arreter();
    void Reculer();
    void Gauche();
    void Droite();
    qint16 Crc16(QByteArray *Adresse_tab , unsigned char Taille_max);

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
};

#endif // MYROBOT_H
