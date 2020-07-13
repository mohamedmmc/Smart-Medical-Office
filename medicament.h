#ifndef MEDICAMENT_H
#define MEDICAMENT_H
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



class medicament
{

private:
    int ref;
    QString nomProduit;
    int nbrMed;

public:
    medicament();
    medicament(int,QString,int);
    bool ajouter();
    int getRef() {return ref;}
    QString getNomProduit() {return nomProduit;}
    void setNomProduit(QString P) {nomProduit=P;}
    int getNbrMed() {return nbrMed;}
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,int);

};



#endif // MEDICAMENT_H
