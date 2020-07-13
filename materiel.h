#ifndef MATERIEL_H
#define MATERIEL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Materiel
{public:
    Materiel();
    Materiel(int,QString,int);
    QString get_nom();
    int get_nbr();
    int get_ref();
    void set_nom(QString a);
    void set_ref(int n);
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2(QString);
    bool supprimer(int);
    bool modifier(QString,int);
    QSqlQueryModel * affichernom();
    QSqlQueryModel * affichernomtrie(QString);
    QSqlQueryModel * afficherfiltre(QString);



private:
    QString nom;
    int nbr,ref;
};

#endif // MATERIEL_H
