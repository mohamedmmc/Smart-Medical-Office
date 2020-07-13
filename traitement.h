#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class traitement
{
public:
    traitement();
    traitement(int,QString,QString);
    QString get_nomt();
    void set_numt(int id);

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * rechercher(int);

    bool supprimer(int);
    bool modifier();

private:
    QString nomt,datet;
    int numt;
};


#endif // TRAITEMENT_H
