#ifndef DOCTEUR2_H
#define DOCTEUR2_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class docteur
{
private:
    QString nom,prenom,disponiblite;
    int id;
public:
    docteur();
    docteur(QString,QString,int,QString);
    QString get_nom();
    QString get_prenom();
    int get_id();



    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2(QString);
    bool supprimer(int);
    bool modifier(QString,QString);
    int etatdispo(QByteArray);


};

#endif // DOCTEUR2_H
