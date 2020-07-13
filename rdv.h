#ifndef RDV_H
#define RDV_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class rdv
{
public:
    rdv();
    rdv(int,QString,QString,int,int,QString,QString);
    QString get_nom();
    QString get_prenom();
    QString get_objet();
    QString get_medecin();
    int get_cin();
    int get_heure();
    int get_datee();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_patient(QString);
    bool recherche_patient(QString);
   // QSqlQueryModel * afficher_medecin();
   // QSqlQueryModel * afficher_chambre();
    bool supprimer(int);
    bool modifier(int,int);
private:
    QString nom,prenom,objet,medecin;
    int cin,datee,heure;
};

#endif // RDV_H



