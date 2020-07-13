#include "compte_medecin.h"
#include "ui_compte_medecin.h"
#include "ordo.h"
#include <QMessageBox>
#include<QString>
#include <QFile>
#include <QTimer>
#include <QPrintDialog>
#include <QPrinter>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>
#include "login.h"

compte_medecin::compte_medecin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::compte_medecin)
{
    ui->setupUi(this);
    ui->tabordo_2->setModel(tmpordo.afficher());
    QPixmap pic(":/img/img/doctor-gp-netherlands.jpg");
    ui->picture_4->setPixmap(pic);
    ui->picture_5->setPixmap(pic);
    ui->picture_6->setPixmap(pic);
    son=new QSound(":/son/son/button20.wav");
}

compte_medecin::~compte_medecin()
{
    delete ui;
}

void compte_medecin::on_pb_ajouter_2_clicked()
{
    int numorodonnance= ui->num_3->text().toInt();
         int nump= ui->lineEdit_2->text().toInt();
        QString nomdocteur= ui->doc_2->text();
        QString nom= ui->nom_2->text();
        QString prenom= ui->prenom_2->text();
         QString medicament1= ui->med1_2->text();
         QString medicament2= ui->med2_2->text();
         QString medicament3= ui->med3_2->text();
         QString medicament4= ui->med4_2->text();
    ordo  o(nom,prenom,nomdocteur,medicament1,medicament2,medicament3,medicament4,numorodonnance,nump);
      bool test=o.ajouter();
      if(test)
    {
          son->play();
          ui->tabordo_2->setModel(tmpordo.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter une ordonnance"),QObject::tr("ordonnance ajoutée.\n""Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter une ordonnance"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void compte_medecin::on_pushButton_2_clicked()
{
    int numorodonnance= ui->num_3->text().toInt();
        QString nomdocteur= ui->doc_2->text();
        QString nom= ui->nom_2->text();
        QString prenom= ui->prenom_2->text();
         QString medicament1= ui->med1_2->text();
         QString medicament2= ui->med2_2->text();
         QString medicament3= ui->med3_2->text();
         QString medicament4= ui->med4_2->text();
        int nump= ui->lineEdit_2->text().toInt();

          ordo o(nom,prenom,nomdocteur,medicament1,medicament2,medicament3,medicament4,numorodonnance, nump);
          o.modifier(nom,prenom,nomdocteur,medicament1,medicament2,medicament3,medicament4);

           if(o.modifier(nom,prenom,nomdocteur,medicament1,medicament2,medicament3,medicament4))
           {        son->play();

               ui->tabordo_2->setModel(o.afficher());
               QMessageBox::information(nullptr, QObject::tr("modifier une ordonnance"),
                                   QObject::tr("info d'ordonnance modifié.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
           }
           else
               QMessageBox::information(nullptr, QObject::tr("modifier une ordonnance"),
                                   QObject::tr("info d'u docteur'ordonnance non modifié.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void compte_medecin::on_supprimer_2_clicked()
{
    int numordonnance = ui->num_4->text().toInt();
    bool test=tmpordo.supprimer(numordonnance);

    if(test)
    {      son->play();

        ui->tabordo_2->setModel(tmpordo.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une ordonnance"),
                    QObject::tr("ordonnance supprimé.\n"), QMessageBox::Ok);

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("Supprimer une ordonnance"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
}

void compte_medecin::on_numm_2_textChanged(const QString &arg1)
{
    ui->tabordo_2->setModel(tmpordo.afficher2(arg1));
}

void compte_medecin::on_pdf_2_clicked()
{
    QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->tabordo_2->model()->rowCount();
                const int columnCount = ui->tabordo_2->model()->columnCount();
                QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                out <<"<html>\n"
                      "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    << "<title>ERP - COMmANDE LIST<title>\n "
                    << "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"
                    "<h1 style=\"text-align: center;\"><strong> ******ordonnance ****** "+TT+"</strong></h1>"
                    "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                      "</br> </br>";
                // headers
                out << "<thead><tr bgcolor=#d6e5ff>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tabordo_2->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tabordo_2->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                    out << "<tr>";
                    for (int column = 0; column < columnCount; column++) {
                        if (!ui->tabordo_2->isColumnHidden(column)) {
                            QString data =ui->tabordo_2->model()->data(ui->tabordo_2->model()->index(row, column)).toString().simplified();
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

void compte_medecin::on_pushButton_clicked()
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
