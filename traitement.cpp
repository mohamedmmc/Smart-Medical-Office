#include <QTimer>
#include <QPrintDialog>
#include <QPrinter>

#include <QDate>
#include <QTextDocument>
#include <QTextStream>
#include "traitement.h"
#include <QDebug>

traitement::traitement()
{
    numt=0;
    nomt="";
    datet="";


    }
traitement::traitement(int numt,QString nomt,QString datet)
    {
      this->numt=numt;
      this->datet=datet;
      this->nomt=nomt;

    }
    QString traitement::get_nomt(){return  nomt;}

    void traitement::set_numt(int id) {numt=id;}


    bool traitement::ajouter()
    {
    QSqlQuery query;
    QString res= QString::number(numt);
    query.prepare("INSERT INTO traitement (numt, nomt, datet)"
                        "VALUES (:numt, :nomt, :datet)");
    query.bindValue(":numt", res);
    query.bindValue(":nomt", nomt);
    query.bindValue(":datet", datet);




    return    query.exec();
    }

    QSqlQueryModel * traitement::afficher()
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from traitement order by numt ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUMT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMT "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATET"));

        return model;
    }







    bool traitement::supprimer(int numt)
    {
    QSqlQuery query;
    QString res= QString::number(numt);
    query.prepare("Delete from traitement where NUMT = :NUMT ");
    query.bindValue(":NUMT", res);
    return    query.exec();
    }

















    bool traitement::modifier()
    {
        QSqlQuery query;
        QString res= QString::number(numt);
        query.prepare("update traitement set nomt=:nomt,numt=:numt,datet=:datet where numt= :numt");
        query.bindValue(":numt", res);
        query.bindValue(":nomt", this->nomt);
        query.bindValue(":datet", this->datet);


return query.exec();

    }
