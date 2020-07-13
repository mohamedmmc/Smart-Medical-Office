#include "admin.h"
#include "ui_admin.h"
#include <QMessageBox>
#include "login.h"

admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    ui->tabetudiant->setModel(tmpcompte.afficher());
    QPixmap pix(":/img/img/s.jpg");
    ui->label->setPixmap(pix);

}

admin::~admin()
{
    delete ui;

}

void admin::on_pushButton_clicked()
{
    QMessageBox msgBox;
    QPushButton *connectButton = msgBox.addButton(tr("Confirmer"), QMessageBox::ActionRole);
     QPushButton *abortButton = msgBox.addButton(QMessageBox::Cancel);
     msgBox.setText("Voulez-vous vraiment vous déconnecter ?");
     msgBox.exec();

     if (msgBox.clickedButton() == connectButton)
     {
         msgBox.close();
         close();
         login c;
         c.exec();

     }
     else if (msgBox.clickedButton() == abortButton) {
         msgBox.close();
     }
}


void admin::on_tabetudiant_activated(const QModelIndex &index)
{
    QString nom=ui->tabetudiant->model()->data(index).toString();
    QSqlQuery qry;
    //qDebug()<<nom;

    qry.prepare("select * from compte where nom = '"+nom+"' or prenom ='"+nom+"' or id ='"+nom+"' or mdp ='"+nom+"' or daate ='"+nom+"' or statut ='"+nom+"'");
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_id_6->setText(nom);
        }
    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry.lastError().text());
    }
}

void admin::on_pb_supprimer_5_clicked()
{
    QString val=ui->lineEdit_id_6->text();
    QMessageBox msgBox;
    QPushButton *connectButton = msgBox.addButton(tr("Confirmer"), QMessageBox::ActionRole);
     QPushButton *abortButton = msgBox.addButton(QMessageBox::Cancel);
     msgBox.setText("Voulez-vous vraiment supprimer "+val+" ?");
     msgBox.exec();

     if (msgBox.clickedButton() == connectButton)
     {
         msgBox.close();
         tmpcompte.supprimer(val);
         ui->tabetudiant->setModel(tmpcompte.afficher());

     }
     else if (msgBox.clickedButton() == abortButton) {
         msgBox.close();
     }

}

void admin::on_tabetudiant_clicked(const QModelIndex &index)
{
    QString nom=ui->tabetudiant->model()->data(index).toString();
    QSqlQuery qry;

    qry.prepare("select * from compte where nom = '"+nom+"' or prenom ='"+nom+"' or id='"+nom+"' or mdp ='"+nom+"' or statut ='"+nom+"'");
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_id_6->setText(qry.value(0).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry.lastError().text());
    }
}

void admin::on_lineEdit_id_6_returnPressed()
{
    QString a=ui->lineEdit_id_6->text();
    ui->tabetudiant->setModel(tmpcompte.afficher2(a));//refresh
}

void admin::on_comboBox_activated(const QString &arg1)
{
    ui->tabetudiant->setModel( tmpcompte.filtre(arg1));
}
