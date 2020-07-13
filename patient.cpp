#include "patient.h"
#include <QDebug>

patient::patient()
{
    nump=0;
    nom="";
    prenom="";
    numtraitement=0;
    maladie="";
    observation="";

    }
patient::patient(int nump,QString nom,QString prenom,int numtraitement,QString maladie,QString observation)
    {
      this->nump=nump;
      this->nom=nom;
      this->prenom=prenom;
    this->numtraitement=numtraitement;
    this->maladie=maladie;
    this->observation=observation;
    }
    QString patient::get_nom(){return  nom;}
    QString patient::get_prenom(){return prenom;}
    int patient::get_nump(){return  nump;}
    int patient::getnumtraitement(){return  numtraitement;}
    QString patient::getmaladie(){return  maladie;}
    QString patient::getobservation(){return  observation;}
    void patient::set_nump(int id) {nump=id;}


    bool patient::ajouter()
    {
    QSqlQuery query;
    QString res= QString::number(nump);
    query.prepare("INSERT INTO patient (nump, nom, prenom, numtraitement, maladie, observation)"
                        "VALUES (:nump, :nom, :prenom, :numtraitement, :maladie, :observation)");
    query.bindValue(":nump", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":numtraitement", numtraitement);
    query.bindValue(":maladie", maladie);
    query.bindValue(":observation", observation);


    return    query.exec();
    }

    QSqlQueryModel * patient::afficher()
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select p.NUMP, p.nom, p.prenom, p.numtraitement,p.maladie,p.observation , t.nomt,t.datet from patient p,traitement t where t.numt=p.numtraitement order by p.nump ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUMP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("numtraitement"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MALADIE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("OBSERVATION"));

        return model;
    }


    bool patient::supprimer(int nump)
    {
    QSqlQuery query;
    QString res= QString::number(nump);
    query.prepare("Delete from PATIENT where NUMP = :NUMP ");
    query.bindValue(":NUMP", res);
    return    query.exec();
    }



    bool patient::modifier()
    {
        QSqlQuery query;
        QString res= QString::number(nump);
        query.prepare("update patient set nom=:nom,prenom=:prenom,numtraitement=:numtraitement,maladie=:maladie,observation=:observation where nump= :nump");
        query.bindValue(":nump", res);
        query.bindValue(":nom", this->nom);
        query.bindValue(":prenom", this->prenom);
        query.bindValue(":numtraitement", this->numtraitement);
        query.bindValue(":maladie", this->maladie);
        query.bindValue(":observation", this->observation);

return query.exec();

    }
