#include "connexion.h"
#include "login.h"
#include <QApplication>
#include "crud_materiel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;
    c.createconnect();
    login s;
    s.show();
    return a.exec();
}
