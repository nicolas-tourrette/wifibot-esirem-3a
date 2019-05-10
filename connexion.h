#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
    class Connexion;
}

class Connexion : public QWidget {
    Q_OBJECT

    public:
        Connexion();

    private:
        QLabel ipAddressLabel, numPortLabel ;
        QLineEdit ipAddress, numPort ;
        QPushButton boutonValider, boutonAnnuler, boutonReset ;
};

#endif // CONNEXION_H
