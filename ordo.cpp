#include "ordo.h"



ordo::ordo()
{
    numordonnance=0;
    nom="";
    prenom="";
    nomdocteur="";
    medicament1="";
    medicament2="";
    medicament3="";
    medicament4="";
    nump=0;

}
 ordo::ordo(QString nom,QString prenom,QString nomdocteur,QString medicament1,QString medicament2,QString medicament3,QString medicament4,int numordonnance, int nump)
{this->nom=nom;
    this->prenom=prenom;
    this->numordonnance=numordonnance;
    this->medicament1=medicament1;
    this->medicament2=medicament2;
     this->medicament3=medicament3;
     this->medicament4=medicament4;
     this->nomdocteur=nomdocteur;
     this->nump=nump;

}
QString ordo::get_nom(){return nom;}
QString ordo::get_prenom(){return prenom;}
int ordo::get_numordonnance(){return numordonnance;}
QString ordo::get_nomdocteur(){return nomdocteur;}
QString ordo::get_medicament1(){return medicament1;}
QString ordo::get_medicament2(){return medicament2;}
QString ordo::get_medicament3(){return medicament3;}
QString ordo::get_medicament4(){return medicament4;}
int ordo::get_nump(){return nump;}

bool ordo::ajouter()
{
QSqlQuery query;
QString res= QString::number(numordonnance);
QString res2= QString::number(nump);
query.prepare("INSERT INTO ordo (NOM , PRENOM , NOMDOCTEUR , MEDICAMENT1 , MEDICAMENT2 , MEDICAMENT3 , MEDICAMENT4 ,NUMORDONNANCE,NUMP) "
                    "VALUES (   :nom, :prenom, :nomdocteur, :medicament1,:medicament2 ,:medicament3,:medicament4, :numordonnance , :nump)");


query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":nomdocteur", nomdocteur);
query.bindValue(":medicament1", medicament1);
query.bindValue(":medicament2", medicament2);
query.bindValue(":medicament3", medicament3);
query.bindValue(":medicament4", medicament4);
query.bindValue(":numordonnance", res);
query.bindValue(":nump", res2);

return    query.exec();
}


    QSqlQueryModel * ordo::afficher()
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from ordo order by  nom asc ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMDOCTEUR"));


     model->setHeaderData(3, Qt::Horizontal, QObject::tr("MEDICAMENT1"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("MEDICAMENT2"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("MEDICAMENT3"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("MEDICAMENT4"));
             model->setHeaderData(7, Qt::Horizontal, QObject::tr("NUMORDONNANCE"));
              model->setHeaderData(8, Qt::Horizontal, QObject::tr("NUMPATIENT"));
        return model;
    }






    bool ordo::supprimer(int numordoo)
    {
    QSqlQuery query;
    query.prepare("Delete from ordo where NUMORDONNANCE =:numordonnance ");
    query.bindValue(":numordonnance",numordoo);
    return    query.exec();
    }

    bool ordo:: modifier(QString,QString,QString,QString,QString,QString,QString)
    {
        QSqlQuery query;

        query.prepare("UPDATE ordo SET   nom= :m, prenom= :p, nomdocteur= :d , medicament1= :a, medicament2= :b ,medicament3= :c,medicament4= :i where numordonnance=:o" );


        query.bindValue(":m", nom);
        query.bindValue(":p", prenom);
         query.bindValue(":d", nomdocteur);
        query.bindValue(":a", medicament1);
        query.bindValue(":b", medicament2);
        query.bindValue(":c", medicament3);
        query.bindValue(":i", medicament4);
         query.bindValue(":o", numordonnance);
        return  query.exec();

    }

    QSqlQueryModel * ordo::afficher2(QString numordonnance)
   { QSqlQueryModel * model= new QSqlQueryModel();
        //QString res= QString::number(numordonnance);
        QString cherche="Select * from ordo where numordonnance like '"+numordonnance+"%'";
    if (numordonnance=="")
    {
        model->setQuery("select * from ordo ");

    }
    else
    {
        model->setQuery(cherche);

    }



        model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nomdocteur"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("medicament1"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("medicament2"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("medicament3"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("medicament4"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("numordonnance"));
             model->setHeaderData(8, Qt::Horizontal, QObject::tr("nump"));

        return model;


    }


