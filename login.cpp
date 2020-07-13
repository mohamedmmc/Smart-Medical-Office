#include "login.h"
#include "ui_login.h"
#include "creer_compte.h"
#include "connexion.h"
#include "compte.h"
#include "crud_materiel.h"
#include "compte_medecin.h"
#include "secretaire.h"
#include <QDebug>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    son=new QSound(":/son/son/1100.wav");
    QPixmap pix(":/img/img/doctor-gp-netherlands.jpg");
    ui->picture->setPixmap(pix);
    QPixmap logo(":/img/img/logooo.png");
    ui->labes_logo->setPixmap(logo);

}

login::~login()
{
    delete ui;
}


void login::on_pushButton_2_clicked()
{

    QString nomcom = ui->lineEdit_id->text();
    QString mdp = ui->lineEdit_mdp->text();
    bool test=tmpcompte.verifier_compte(nomcom,mdp);
    if (nomcom=="admin" && mdp=="admin")
    {
        close();
        Admin=new admin();
        Admin->show();
        test=true;
    }

    if (test)
    {
        son->play();
        QMessageBox::information(this,"Login","ID et MDP correct");
        close();
        if (tmpcompte.verifier_statut(nomcom,mdp)==1)
        {
            Compte_Medecin = new compte_medecin();
            Compte_Medecin->show();
        }
        else if (tmpcompte.verifier_statut(nomcom,mdp)==2)
        {
            Secretaire=new secretaire();
            Secretaire->show();
        }
        else if (tmpcompte.verifier_statut(nomcom,mdp)==3)
        {
            Crud_Materiel=new crud_materiel();
            Crud_Materiel->show();
        }
        else if (tmpcompte.verifier_statut(nomcom,mdp)==4)
        {
            Amedicament=new amedicament;
            Amedicament->show();
        }
    }
    else
    {
            QMessageBox::critical(this,"Login","ID et MDP non correct");
    }
}

void login::on_pushButton_clicked()
{
    //hide();
    Creer_Compte = new creer_compte();
    Creer_Compte->show();
}

void login::on_lineEdit_id_returnPressed()
{

    QString nomcom = ui->lineEdit_id->text();
    QString mdp = ui->lineEdit_mdp->text();
    bool test=tmpcompte.verifier_compte(nomcom,mdp);
    if (nomcom=="admin" && mdp=="admin")
    {
        close();
        Admin=new admin();
        Admin->show();
        test=true;
    }
    if (test)
    {
        son->play();
        QMessageBox::information(this,"Login","ID et MDP correct");
        close();
        if (tmpcompte.verifier_statut(nomcom,mdp)==1)
        {
            Compte_Medecin = new compte_medecin();
            Compte_Medecin->show();
        }
        else if (tmpcompte.verifier_statut(nomcom,mdp)==2)
        {
            Secretaire=new secretaire();
            Secretaire->show();
        }
        else if (tmpcompte.verifier_statut(nomcom,mdp)==3)
        {
            Crud_Materiel=new crud_materiel();
            Crud_Materiel->show();
        }
        else if (tmpcompte.verifier_statut(nomcom,mdp)==4)
        {
            Amedicament=new amedicament;
            Amedicament->show();
        }
    }
    else
    {
            QMessageBox::critical(this,"Login","ID et MDP non correct");
    }
}

void login::on_lineEdit_mdp_returnPressed()
{


    QString nomcom = ui->lineEdit_id->text();
    QString mdp = ui->lineEdit_mdp->text();
    bool test=tmpcompte.verifier_compte(nomcom,mdp);
    if (nomcom=="admin" && mdp=="admin")
    {
        close();
        Admin=new admin();
        Admin->show();
        test=true;
    }
    if (test)
    {
        son->play();
            QMessageBox::information(this,"Login","ID et MDP correct");
            close();
            if (tmpcompte.verifier_statut(nomcom,mdp)==1)
            {
                Compte_Medecin = new compte_medecin();
                Compte_Medecin->show();
            }
            else if (tmpcompte.verifier_statut(nomcom,mdp)==2)
            {
                Secretaire=new secretaire();
                Secretaire->show();
            }
            else if (tmpcompte.verifier_statut(nomcom,mdp)==3)
            {
                Crud_Materiel=new crud_materiel();
                Crud_Materiel->show();
            }
            else if (tmpcompte.verifier_statut(nomcom,mdp)==4)
            {
                Amedicament=new amedicament;
                Amedicament->show();
            }

    }
    else
    {
            QMessageBox::critical(this,"Login","ID et MDP non correct");
    }
}
