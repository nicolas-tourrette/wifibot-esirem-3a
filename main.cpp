#include <QApplication>
#include "connexion.h"

int main(int argc, char *argv[]) {
    QApplication WifibotPilot(argc, argv) ;

    Connexion seConnecter ;
    seConnecter.show() ;

    return WifibotPilot.exec() ;
}
