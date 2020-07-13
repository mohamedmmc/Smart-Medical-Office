#include "docteur2.h"
#include <QObject>
#include <QDebug>
#

docteur::docteur()
{
    id=0;
    nom="";
    prenom="";
    disponiblite="";

}
docteur::docteur(QString nom,QString prenom,int id,QString disponiblite)
{this->nom=nom;
    this->prenom=prenom;
    this->id=id;
    this->disponiblite=disponiblite;


}
QString docteur::get_nom(){return nom;}
QString docteur::get_prenom(){return prenom;}
int docteur::get_id(){return id;}

bool docteur::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO docteur ( NOM, PRENOM,ID) "
                    "VALUES ( :nom, :prenom, :id)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);


return    query.exec();
}


    QSqlQueryModel * docteur::afficher()
    {QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from docteur order by nom asc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Disponiblité"));


        return model;
    }

    bool docteur::supprimer(int idd)
    {
    QSqlQuery query;
    query.prepare("Delete from docteur where ID =:id ");
    query.bindValue(":id",idd);
    return    query.exec();
    }

    bool docteur:: modifier(QString,QString)
    {
        QSqlQuery query;

        query.prepare("UPDATE docteur SET nom=:n , prenom= :p where id=:i" );
        query.bindValue(":n",nom);
        query.bindValue(":p",prenom);
        query.bindValue(":i",id);

        return  query.exec();

    }

    QSqlQueryModel * docteur::afficher2(QString id)
   { QSqlQueryModel * model= new QSqlQueryModel();
        //QString res= QString::number(id);
        QString cherche="Select * from docteur where id like '"+id+"%'";
    if (id=="")
    {
        model->setQuery("select * from docteur ");

    }
    else
    {
        model->setQuery(cherche);

    }



    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Disponiblité"));


        return model;


    }

    int docteur::etatdispo(QByteArray a)
    {
        QSqlQuery query;
        QString disp="disponible";
        QString nndisp="indisponible";
        if (a=="0")
        {
            QSqlQuery query;
            query.prepare("update docteur SET disponibilite= '"+disp+"'");
            query.bindValue(":n", disp);
            query.exec();
            return 0;
        }
        else
        {
            QSqlQuery query;
            query.prepare("update docteur SET disponibilite='"+nndisp+"' ");
            query.bindValue(":n", nndisp);
            query.exec();
            return  1;

        }
    }
