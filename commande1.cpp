#include "commande1.h"
#include <QDebug>
Commande::Commande()
{
  numC=0;
  nomProduit="";
  date="";
  date_d="";
  nbrMed_C=0;
};
Commande::Commande(int numC,QString nomProduit,QString date,int nbrMed_C,QString date_d)
{
  this->numC=numC;
  this->nomProduit=nomProduit;
  this->date=date;
  this->nbrMed_C=nbrMed_C;
  this->date_d=date_d;
};
bool Commande::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(numC);
    query.prepare("INSERT INTO TABCOMM (NUM_COMM, NOMPRODUIT,DATE_COMM,DATE_DELAIT, NBRMED_C) "
                        "VALUES (:numC, :nomProduit,:date,:date_d, :nbrMed_C)");
    query.bindValue(":numC", res);
    query.bindValue(":nomProduit", nomProduit);
    query.bindValue(":date", date);
    query.bindValue(":date_d", date_d);
    query.bindValue(":nbrMed_C", nbrMed_C);
    return    query.exec();
}
bool Commande::modifier(int reff,QString N,QString D,int NB,QString DD)
{
    QSqlQuery query;
    QString res= QString::number(reff);
    QString Nombre= QString::number(NB);
    query.prepare("UPDATE TABCOMM SET  NOMPRODUIT= :N,DATE_COMM= :D,NBRMED_C= :NB where NUM_COMM = :numC");
    query.bindValue(":numC", res);
    query.bindValue(":N", N);
    query.bindValue(":D", D);
    query.bindValue(":NB", Nombre);
    query.bindValue(":DD",DD);
    return    query.exec();

}
QSqlQueryModel * Commande::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from TABCOMM");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("numC"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomProduit "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("nbrMed_C"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_d "));
    return model;
}

bool Commande::supprimer(int reff)
{
QSqlQuery query;
QString res= QString::number(reff);
query.prepare("delete from TABCOMM where NUM_COMM = :numC ");
query.bindValue(":numC", res);
return    query.exec();
}
