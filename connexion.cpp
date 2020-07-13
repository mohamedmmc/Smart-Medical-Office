
#include "connexion.h"
Connexion::Connexion()
{

}

bool Connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test");
db.setUserName("melek");//inserer nom de l'utilisateur
db.setPassword("123");//inserer mot de passe de cet utilisateur


if (db.open())
test=true;

else
    qDebug()<<db.lastError().text();



    return  test;
}
