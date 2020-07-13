#ifndef COMPTE_H
#define COMPTE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class compte
{
public:
    compte();
    compte(QString,QString,QString,QString,QString,QString);
    bool ajouter_compte();
    bool verifier_compte(QString,QString);
    int verifier_statut(QString,QString);
    QSqlQueryModel * afficher();
    QSqlQueryModel * filtre(QString);
    QSqlQueryModel * afficher2(QString);
    bool supprimer(QString);

private:
    QString nom,prenom,id,mdp,daate,statut;

};

#endif // COMPTE_H
