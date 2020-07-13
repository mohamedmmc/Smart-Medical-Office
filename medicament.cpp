#include "medicament.h"
#include <QDebug>
medicament::medicament()
{   ref=0;
    nomProduit="";
    nbrMed=0;

}
medicament::medicament(int ref,QString nomProduit,int nbrMed)
{
    this->ref=ref;
    this->nomProduit=nomProduit;
    this->nbrMed=nbrMed;

}
bool medicament::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(ref);
    query.prepare("INSERT INTO TABMED (REFMEDICAMENT, NOMPRODUIT, NBRMED) "
                        "VALUES (:ref, :nomProduit, :nbrMed)");
    query.bindValue(":ref", res);
    query.bindValue(":nomProduit", nomProduit);
    query.bindValue(":nbrMed", nbrMed);
    return    query.exec();
}
bool medicament::modifier(int reff,QString N,int NB)
{
    QSqlQuery query;
    QString res= QString::number(reff);
    QString Nombre= QString::number(NB);
    query.prepare("UPDATE TABMED SET  NOMPRODUIT= :N,NBRMED= :NB where REFMEDICAMENT = :ref");
    query.bindValue(":ref", res);
    query.bindValue(":N", N);
    query.bindValue(":NB", Nombre);
    return    query.exec();

}
QSqlQueryModel * medicament::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from TABMED");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomProduit "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nbrMed"));
    return model;
}

bool medicament::supprimer(int reff)
{
QSqlQuery query;
QString res= QString::number(reff);
query.prepare("delete from TABMED where REFMEDICAMENT = :ref ");
query.bindValue(":ref", res);
return    query.exec();
}


