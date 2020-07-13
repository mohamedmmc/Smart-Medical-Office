#include "creer_compte.h"
#include <QMessageBox>
#include "ui_creer_compte.h"
#include "compte.h"
#include "connexion.h"

creer_compte::creer_compte(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creer_compte)
{
    ui->setupUi(this);
    QPixmap pix(":/img/img/doctor-gp-netherlands.jpg");
    ui->picture->setPixmap(pix);
}

creer_compte::~creer_compte()
{
    delete ui;
}

void creer_compte::on_pushButton_clicked()
{
    Connexion c;
    c.createconnect();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->prenom->text();
    QString id = ui->identifiant->text();
    QString mdp = ui->motdepasse->text();
    QString date = ui->dateEdit->date().toString();
    //QString idmedical = ui->IDmedical->text();
    if (nom == "" || prenom == "" || id == "" || mdp == "" )
    {
        QMessageBox::information(this,"Login","Touts les champs sont obligatoires");
    }
    else if (!(ui->radioButton->isChecked() || ui->radioButton_2->isChecked() || ui->radioButton_3->isChecked()|| ui->radioButton_4->isChecked()))
    {
        QMessageBox::information(this,"Information","Selectionnez au moins un titre");
    }
    else
    {
        QString statut;
        if (ui->radioButton->isChecked())
        {
            statut="medecin";
        }
        else if (ui->radioButton_2->isChecked())
        {
            statut="secretaire";
        }
        else if (ui->radioButton_3->isChecked())
        {
            statut="chef de depot";
        }
        else if (ui->radioButton_4->isChecked())
        {
            statut="pharmacien";
        }
        compte e(nom,prenom,id,mdp,date,statut);
        bool test=e.ajouter_compte();
        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("Création de compte"),
            QObject::tr("Profil créer"), QMessageBox::Ok);
            hide();
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Création de compte"),
            QObject::tr("Nom de compte déjà existant"), QMessageBox::Ok);
        }
    }
}

void creer_compte::on_pushButton_2_clicked()
{
    close();
}

QString creer_compte::on_radioButton_clicked()
{
    QString a;
    a="medecin";
    return a;
}

