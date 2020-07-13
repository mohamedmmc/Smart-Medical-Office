#ifndef DOCTEUR_H
#define DOCTEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QWidget>
class ordo
{
private:
     int numordonnance , nump;
    QString nom,prenom,nomdocteur,medicament1,medicament2,medicament3,medicament4;

public:
   ordo();
   ordo(QString,QString,QString,QString,QString,QString,QString,int, int);
      int get_numordonnance();
      int get_nump();
   QString get_nom();
    QString get_prenom();
    QString get_nomdocteur();
    QString get_medicament1();
    QString get_medicament2();
    QString get_medicament3();
    QString get_medicament4();





    bool ajouter();
    QSqlQueryModel * afficher();
      QSqlQueryModel * afficher2(QString);
    bool supprimer(int);
    bool modifier(QString,QString,QString,QString,QString,QString,QString);


};

#endif // DOCTEUR_H

