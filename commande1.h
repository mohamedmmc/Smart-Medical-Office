#ifndef COMMANDE1_H
#define COMMANDE1_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QTcpSocket>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QObject>

class Commande
{
private:
    int numC;
    QString nomProduit;
    QString date;
    QString date_d;
    int nbrMed_C;

public:
    Commande();
    Commande(int,QString,QString,int,QString);
    bool ajouter();
    int getnumC() {return numC;}
    QString getNomProduit() {return nomProduit;}
    void setNomProduit(QString P1) {nomProduit=P1;}
    QString getdate() {return date;}
    int getNbrComm() {return nbrMed_C;}
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,int,QString);

};
#endif // COMMANDE1_H
