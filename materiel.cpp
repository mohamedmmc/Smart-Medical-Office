#include "materiel.h"
#include <QDebug>

Materiel::Materiel()
{
ref=0;
nom="";
nbr=0;
}
Materiel::Materiel(int ref,QString nom,int nbr)
{
  this->ref=ref;
  this->nom=nom;
  this->nbr=nbr;
}

int Materiel::get_ref(){return  ref;}
QString Materiel::get_nom(){return  nom;}
int Materiel::get_nbr(){return nbr;}

bool Materiel::ajouter()
{
QSqlQuery query;
QString res= QString::number(ref);
QString res1= QString::number(nbr);
query.prepare("INSERT INTO materiel (ref, nom, nbr) "
                    "VALUES (:ref, :nom, :nbr)");
query.bindValue(":ref", res);
query.bindValue(":nom", nom);
query.bindValue(":nbr", res1);


return    query.exec();
}

QSqlQueryModel * Materiel::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from materiel order by ref");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre"));
    return model;
}

bool Materiel::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
if (idd==0)
{
    return false;
}
else
{
    query.prepare("Delete from materiel where ref = :ref ");
    query.bindValue(":ref", res);
    return    query.exec();
}

}

bool Materiel::modifier(QString ref,int nbr)
{

        QSqlQuery query;
        query.prepare("UPDATE materiel SET nbr=:nbr WHERE ref ='"+ref+"' ");
        query.bindValue(":nbr", nbr);
        return    query.exec();
}

QSqlQueryModel * Materiel::afficher2(QString ref)
{QSqlQueryModel * model= new QSqlQueryModel();
    //QString res= QString::number(ref);
    QString cherche="Select * from materiel where ref like '"+ref+"%' or nom like '"+ref+"%'";
if (ref=="")
{
    model->setQuery("select * from materiel order by ref");

}
else
{
    model->setQuery(cherche);

}
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre"));
    return model;
}

QSqlQueryModel * Materiel::affichernom()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select nom from materiel");
    return model;
}

QSqlQueryModel * Materiel::affichernomtrie(QString trie)
{QSqlQueryModel * model= new QSqlQueryModel();
    if(trie=="Référence")
    {
        model->setQuery("select * from materiel order by ref");

    }
    else if (trie=="Nom")
    {
        model->setQuery("select * from materiel order by nom");

    }
    else if (trie=="Nombre")
    {
        model->setQuery("select * from materiel order by nbr");

    }
    else
    {
        model->setQuery("select * from materiel");
    }
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre"));
    return model;
}

QSqlQueryModel * Materiel::afficherfiltre(QString trie)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from materiel where nbr<='"+trie+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre"));
    return  model;
}
