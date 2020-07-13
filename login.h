#ifndef LOGIN_H
#define LOGIN_H
#include "creer_compte.h"
#include "crud_materiel.h"
#include <QDialog>
#include "compte.h"
#include "connexion.h"
#include "admin.h"
#include "secretaire.h"
#include "amedicament.h"
#include "compte_medecin.h"
#include <QSound>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void updateRGB(QString);

   // private slots: void readlSerial();

private slots:
    void on_pushButton_2_clicked();
     void on_pushButton_clicked();

     void on_lineEdit_id_returnPressed();

     void on_lineEdit_mdp_returnPressed();

private:
    Ui::login *ui;
    creer_compte *Creer_Compte;
    crud_materiel *Crud_Materiel;
    compte tmpcompte;
    login *Login;
    Connexion connexion;
    admin *Admin;
    secretaire *Secretaire;
    compte_medecin *Compte_Medecin;
    QSound *son;
    amedicament *Amedicament;


};

#endif // LOGIN_H
