#include "commande.h"
#include "ui_commande.h"
#include "QMessageBox"
#include "QDebug"
#include "QSqlError"
#include <QDate>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>

commande::commande(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commande)
{
    ui->setupUi(this);
     ui->tableCommande->setModel(tmpcommande.afficher());
     QPixmap pix(":/img/img/doctor-gp-netherlands.jpg");
     ui->label_10->setPixmap(pix);}

commande::~commande()
{
    delete ui;
}
void commande::on_pushButton_ajout_C_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);
    int numC = ui->lineEdit_numC->text().toInt();
    QString nomProduit= ui->lineEdit_nomP_4->text();
    QString date= ui->lineEdit_date->text();
    int nbrMed_C= ui->lineEdit_nbrC->text().toInt();
    QString date_d= ui->lineEdit_date_delait->text();
    Commande c (numC,nomProduit,date,nbrMed_C,date_d);
    bool test=c.ajouter();
    if(test)
    {
        ui->tableCommande->setModel(tmpcommande.afficher());
    QMessageBox::information(nullptr, QObject::tr("Ajouter une commande"),
                  QObject::tr("Commande ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_numC->clear();
            ui->lineEdit_nomP_4->clear();
            ui->lineEdit_date->clear();
            ui->lineEdit_nbrC->clear();
            ui->lineEdit_date_delait->clear();

    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une commande"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}


void commande::on_pushButton_Modifier_C_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    int numC = ui->lineEdit_numC->text().toInt();
    QString nomProduit= ui->lineEdit_nomP_4->text();
    QString date= ui->lineEdit_date->text();
    int nbrMed_C= ui->lineEdit_nbrC->text().toInt();
    QString date_d= ui->lineEdit_date_delait->text();
    Commande c (numC,nomProduit,date,nbrMed_C,date_d);
    bool test=c.modifier(numC,nomProduit,date,nbrMed_C,date_d);
    if(test)
    { ui->tableCommande->setModel(tmpcommande.afficher());

            QMessageBox::information(nullptr, QObject::tr("Modifier une commande"),
                  QObject::tr("Commande modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_numC->clear();
            ui->lineEdit_nomP_4->clear();
            ui->lineEdit_date->clear();
            ui->lineEdit_nbrC->clear();
            ui->lineEdit_date_delait->clear();
    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Modifier une commande"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void commande::on_pushButton_supprimer_C_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    Commande c;
        int numC = ui->lineEdit_numC->text().toInt();
        bool test=c.supprimer(numC);
        if(test)
        { ui->tableCommande->setModel(tmpcommande.afficher());
            QMessageBox::information(nullptr, QObject::tr("Supprimer une commande"),
                        QObject::tr("Commande supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
               ui->lineEdit_numC->clear();
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer une commande"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
     //QSqlQueryModel *   model=c.afficher();
}

void commande::on_pushButton_chercherD_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    QString date= ui->lineEdit_date->text();
     qDebug()<< date << endl;
            QSqlQuery query;
            query.first();
            query.prepare("SELECT * from TABCOMM where DATE_COMM= '"+date+"'");
            if(query.exec())

            {
                while(query.next())
                {

                    ui->lineEdit_numC->setText(query.value(0).toString());//numC
                    ui->lineEdit_nomP_4->setText(query.value(1).toString());//nomProduit
                    ui->lineEdit_date->setText(query.value(2).toString());//date
                    ui->lineEdit_nbrC->setText(query.value(3).toString());//nbrComm
                    ui->lineEdit_date_delait->setText(query.value(4).toString());//date_delait

                }
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Chercher commande!"),
                                      QObject::tr("Erreur!.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
            }
}



void commande::on_pushButton_rechercher_C_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    QSqlQuery query;
         QString nomProduit= ui->lineEdit_nomP_6->text();
        nomProduit=nomProduit+"%";
        qDebug()<<nomProduit;
        query.prepare("SELECT * from TABCOMM where(NOMPRODUIT LIKE :nomProduit)");
        query.bindValue(":nomProduit",nomProduit);
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        QSqlQueryModel * modal= new QSqlQueryModel();
        modal->setQuery(query);
        qDebug()<<modal->rowCount();
        ui->tableCommande_2->setModel(modal);
}

void commande::on_pushButton_tri_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("select * from TABCOMM");
        qry.exec();
        model->setQuery(qry);

        QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
        m->setDynamicSortFilter(true);
        m->setSourceModel(model);
        ui->tableCommande->setModel(m);
        ui->tableCommande->setSortingEnabled(true);
}

void commande::on_pushButton_imprimer_2_clicked()
{
    QString strStream;
              QTextStream out(&strStream);

              const int rowCount = ui->tableCommande->model()->rowCount();
              const int columnCount = ui->tableCommande->model()->columnCount();
              QString TT = QDate::currentDate().toString("yyyy/MM/dd");
              out <<"<html>\n"
                    "<head>\n"
                     "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                  << "<title>ERP - COMmANDE LIST<title>\n "
                  << "</head>\n"
                  "<body bgcolor=#ffffff link=#5000A0>\n"
                  "<h1 style=\"text-align: center;\"><strong> ******LISTE DES Réservations ****** "+TT+"</strong></h1>"
                  "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                    "</br> </br>";
              // headers
              out << "<thead><tr bgcolor=#d6e5ff>";
              for (int column = 0; column < columnCount; column++)
                  if (!ui->tableCommande->isColumnHidden(column))
                      out << QString("<th>%1</th>").arg(ui->tableCommande->model()->headerData(column, Qt::Horizontal).toString());
              out << "</tr></thead>\n";

              // data table
              for (int row = 0; row < rowCount; row++) {
                  out << "<tr>";
                  for (int column = 0; column < columnCount; column++) {
                      if (!ui->tableCommande->isColumnHidden(column)) {
                          QString data =ui->tableCommande->model()->data(ui->tableCommande->model()->index(row, column)).toString().simplified();
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

              QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
              if (dialog->exec() == QDialog::Accepted) {
                  document->print(&printer);
              }

              delete document;
}
