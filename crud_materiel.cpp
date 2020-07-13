#include "crud_materiel.h"
#include "ui_crud_materiel.h"
#include "QMessageBox"
#include "connexion.h"
#include "login.h"
#include "QStringListModel"
#include "modification.h"
#include <QFile>
#include <QTimer>
#include <QPrintDialog>
#include <QPrinter>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>

crud_materiel::crud_materiel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::crud_materiel)
{
    ui->setupUi(this);
    QPixmap pix(":/img/img/doctor-gp-netherlands2.jpg");
    ui->label_6->setPixmap(pix);
    ui->tabmateriel->setModel(tmpmateriel.afficher());
    ui->comboBox->setModel(tmpmateriel.affichernom());
    ui->comboBox_2->addItem("Trier par :");
    ui->comboBox_2->addItem("Référence");
    ui->comboBox_2->addItem("Nom");
    ui->comboBox_2->addItem("Nombre");
}

crud_materiel::~crud_materiel()
{
    delete ui;
}


void crud_materiel::on_pb_ajouter_clicked()
{

    int ref = ui->ref->text().toInt();
    QString nom= ui->nom->text();
    int nbr= ui->nbr->text().toInt();
    Materiel e(ref,nom,nbr);
     bool test=e.ajouter();
    if(test)
    {
        ui->tabmateriel->setModel(tmpmateriel.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un Materiel"),
        QObject::tr("Materiel ajouté"), QMessageBox::Ok);
        ui->comboBox->setModel(tmpmateriel.affichernom());

    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un Materiel"),
                  QObject::tr("Erreur !"), QMessageBox::Cancel);
}




void crud_materiel::on_pb_supprimer_3_clicked()
{
    int ref = ui->ref->text().toInt();
    QString nom=ui->nom->text();
    if (ref==0)
    {
        QMessageBox::warning(nullptr, QObject::tr("Modification"),
                          QObject::tr("Veuillez selectionner un matériel"), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox msgBox;
        QPushButton *connectButton = msgBox.addButton(tr("Confirmer"), QMessageBox::ActionRole);
         QPushButton *abortButton = msgBox.addButton(QMessageBox::Cancel);
         msgBox.setText("Voulez-vous vraiment supprimer "+nom+" de la liste ?");
         msgBox.exec();

         if (msgBox.clickedButton() == connectButton)
         {
             msgBox.close();
             tmpmateriel.supprimer(ref);
             ui->tabmateriel->setModel(tmpmateriel.afficher());
                 QMessageBox::information(nullptr, QObject::tr("Supprimer Matériel"),
                             QObject::tr("Matériel supprimé"), QMessageBox::Ok);
                 ui->comboBox->setModel(tmpmateriel.affichernom());


         }
         else if (msgBox.clickedButton() == abortButton) {
             msgBox.close();
         }
    }



}

void crud_materiel::on_pb_supprimer_4_clicked()
{
    QString ref=ui->ref->text();
    int reff=ui->ref->text().toInt();
    QString nom=ui->nom->text();
    if (nom=="" || reff ==0)
    {
        QMessageBox::warning(nullptr, QObject::tr("Modification"),
                          QObject::tr("Veuillez selectionner un matériel"), QMessageBox::Ok);
    }
    else
    {
        modification d;
        d.setnom(nom);
        d.setref(reff);
        d.exec();
    }
    ui->tabmateriel->setModel(tmpmateriel.afficher());
    ui->comboBox->setModel(tmpmateriel.affichernom());

}


void crud_materiel::on_lineEdit_id_6_returnPressed()
{
    QString ref=ui->lineEdit_id_6->text();
    ui->tabmateriel->setModel(tmpmateriel.afficher2(ref));//refresh
    QSqlQuery qry;
        qry.prepare("select * from materiel where ref = '"+ref+"'");
        if (qry.exec())
        {
            while(qry.next())
            {
                ui->ref->setText(qry.value(0).toString());
                ui->nom->setText(qry.value(1).toString());
                ui->nbr->setText(qry.value(2).toString());
            }
        }
        else
        {
            QMessageBox::critical(this,tr("error"),qry.lastError().text());
        }
}

void crud_materiel::on_pushButton_clicked()
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

bool crud_materiel::deconnexion()
{
    return  true;
}

void crud_materiel::on_lineEdit_id_6_textChanged(const QString &arg1)
{
    ui->tabmateriel->setModel(tmpmateriel.afficher2(arg1));//refresh
}

void crud_materiel::on_comboBox_activated(const QString &arg1)
{
    //QString nom=ui->comboBox->currentText();
    QSqlQuery qry;

    qry.prepare("select * from materiel where nom = '"+arg1+"'");
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->ref->setText(qry.value(0).toString());
            ui->nom->setText(qry.value(1).toString());
            ui->nbr->setText(qry.value(2).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry.lastError().text());
    }
}

void crud_materiel::on_tabmateriel_clicked(const QModelIndex &index)
{
    QString nom=ui->tabmateriel->model()->data(index).toString();
    QSqlQuery qry;

    qry.prepare("select * from materiel where nom = '"+nom+"' or ref ='"+nom+"'");
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->ref->setText(qry.value(0).toString());
            ui->nom->setText(qry.value(1).toString());
            ui->nbr->setText(qry.value(2).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry.lastError().text());
    }
}

void crud_materiel::on_comboBox_2_activated(const QString &arg1)
{
    ui->tabmateriel->setModel( tmpmateriel.affichernomtrie(arg1));

}

void crud_materiel::on_pb_ajouter_2_clicked()
{
    QString strStream;
                    QTextStream out(&strStream);

                    const int rowCount = ui->tabmateriel->model()->rowCount();
                    const int columnCount = ui->tabmateriel->model()->columnCount();
                    QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                    out <<"<html>\n"
                          "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        << "<title>ERP - COMmANDE LIST<title>\n "
                        << "</head>\n"
                        "<body bgcolor=#ffffff link=#5000A0>\n"
                        "<h1 style=\"text-align: center;\"><strong> ***** Materiel Medical ***** "+TT+"</strong></h1>"
                        "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                          "</br> </br>";
                    // headers
                    out << "<thead><tr bgcolor=#d6e5ff>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tabmateriel->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tabmateriel->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";

                    // data table
                    for (int row = 0; row < rowCount; row++) {
                        out << "<tr>";
                        for (int column = 0; column < columnCount; column++) {
                            if (!ui->tabmateriel->isColumnHidden(column)) {
                                QString data =ui->tabmateriel->model()->data(ui->tabmateriel->model()->index(row, column)).toString().simplified();
                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                            }
                        }
                        out << "</tr>\n";
                    }
                    out <<  "</table>\n"
                        "</body>\n"
                        "</html>\n";

                    QTextDocument *document = new QTextDocument();
                    document->setHtml(strStream);

                    QPrinter printer;

                    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                    if (dialog->exec() == QDialog::Accepted) {
                        document->print(&printer);
                    }

                    delete document;
}
