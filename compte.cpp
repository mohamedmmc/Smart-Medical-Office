#include "compte.h"
#include "QDebug"
#include "login.h"

compte::compte()
{

}

compte::compte(QString nom,QString prenom,QString id,QString mdp, QString daate, QString statut)
{
    this->nom=nom;
    this->prenom=prenom;
    this->id=id;
    this->mdp=mdp;
    this->daate=daate;
    this->statut=statut;
}

bool compte::ajouter_compte()
{
QSqlQuery query;
query.prepare("INSERT INTO compte (nom, prenom, id, mdp, daate,statut) VALUES (:nom, :prenom, :id, :mdp, :daate, :statut)");
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":id", id);
query.bindValue(":mdp", mdp);
query.bindValue(":daate", daate);
query.bindValue(":statut", statut);

return    query.exec();
}

bool compte::verifier_compte(QString id, QString mdp)
{
    QSqlQuery query;
    QString mdpbd,idbd;

    if (mdp=="" || id=="")
    {
        return  false;
    }

    query.exec("SELECT mdp,id FROM compte WHERE"
                  " id= '"+id+"' AND"
                  " mdp= '"+mdp+"'");
    while (query.next()) {
       mdpbd = query.value("mdp").toString();
       idbd= query.value("id").toString();
        }
    if (mdpbd==mdp && id==idbd)
    {

        return true;
    }

    else
    {
        return  false;
    }

}
int compte::verifier_statut(QString id, QString mdp)
{
    QSqlQuery query;
    QString statut;
    query.exec("SELECT statut FROM compte WHERE"
               " id= '"+id+"' AND"
               " mdp= '"+mdp+"'");
    while (query.next())
    {
        statut=query.value("statut").toString();
    }
    if (statut=="medecin")
        return 1;
    else if (statut=="secretaire")
        return 2;
    else if (statut=="chef de depot")
        return 3;
    else if (statut=="pharmacien")
        return 4;
    else return 0;
}

QSqlQueryModel * compte::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from compte order by nom");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Login"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mot de passe"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));

    return model;
}

QSqlQueryModel * compte::afficher2(QString ref)
{QSqlQueryModel * model= new QSqlQueryModel();
    //QString res= QString::number(ref);
if (ref=="")
{
    model->setQuery("select * from compte");

}
else
{
    model->setQuery("Select * from compte where id = '"+ref+"' or mdp = '"+ref+"' or nom = '"+ref+"' or statut = '"+ref+"' or daate = '"+ref+"'");

}
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Login"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mot de passe"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
    return model;
}

bool compte::supprimer(QString nom)
{
QSqlQuery query;
//QString res= QString::number(idd);
query.prepare("Delete from compte where nom = '"+nom+"' or prenom ='"+nom+"' or id='"+nom+"' or mdp ='"+nom+"' or statut ='"+nom+"'" );
query.bindValue(":nom", nom);
return    query.exec();
}

QSqlQueryModel * compte::filtre(QString filtre)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    if (filtre=="Trier par Statut")
    {
        model->setQuery("select * from compte");
    }
    else
    {
        model->setQuery("select * from compte where statut='"+filtre+"'");
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Login"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
    return  model;
}
