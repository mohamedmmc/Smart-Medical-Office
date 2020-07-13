#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
class Connexion
{
public:
    QSqlDatabase mydb;

    Connexion();
    bool createconnect();
    void connClose()
    {
        mydb.close();
    }
};

#endif // CONNECTION_H
