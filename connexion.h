#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>

namespace Ui {
    class Connexion;
}

class Connexion : public QWidget {
    Q_OBJECT

    public:
        Connexion() ;
        void keyPressEvent(QKeyEvent *event) ;

    private:
        QString ipAddress ;
        int numPort ;
        QLabel *ipAddressLabel, *numPortLabel ;
        QLineEdit *ipAddressField, *numPortField ;
        QPushButton *okButton, *cancelButton, *resetButton ;

    public slots:
        void okButtonClic() ;
        void resetButtonClic() ;
};

#endif // CONNEXION_H
