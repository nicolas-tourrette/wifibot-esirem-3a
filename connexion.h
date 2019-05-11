#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
    class Connexion;
}

class Connexion : public QWidget {
    Q_OBJECT

    public:
        Connexion();

    private:
        QString ipAddress ;
        int numPort ;
        QLabel *ipAddressLabel, *numPortLabel ;
        QLineEdit *champIpAddress, *champNumPort ;
        QPushButton *boutonValider, *boutonAnnuler, *boutonReset ;

    public slots:
        void boutonValiderClic() ;
        void boutonResetClic() ;
};

#endif // CONNEXION_H
