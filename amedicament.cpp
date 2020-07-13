#include "amedicament.h"
#include "ui_amedicament.h"
#include "medicament.h"
#include "QMessageBox"
#include "QDebug"
#include "QSqlError"
#include <QDate>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include "commande.h"
#include "login.h"

amedicament::amedicament(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::amedicament)
{
    ui->setupUi(this);
    ui->tablemedicament->setModel(tmpmedicament.afficher());
    QPixmap pix(":/img/img/doctor-gp-netherlands.jpg");
    ui->label_10->setPixmap(pix);
    comboBox_nomP();
}

amedicament::~amedicament()
{
    delete ui;
}

void amedicament::comboBox_nomP()
{   QString nomProduit= ui->comboBox->currentText();
    qDebug()<< nomProduit << endl;
    QSqlQuery query;
    query.prepare("select NOMPRODUIT from TABCOMM");
    query.exec();
    QSqlQueryModel *modal =new QSqlQueryModel();
    modal->setQuery(query);
    qDebug()<<modal->rowCount();
    ui->comboBox->setModel(modal);
    ui->lineEdit_nomP->setText(nomProduit);

}

void amedicament::on_pushButton_ok_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);
    int ref = ui->lineEdit_ref->text().toInt();
    QString nomProduit= ui->lineEdit_nomP->text();
    int nbrMed= ui->lineEdit_nb->text().toInt();
    if(nbrMed<=20){
        QMessageBox::critical(nullptr, QObject::tr("ALERT!!"),
                                         QObject::tr("veuillez recharger le stocke de ce médicament à nouveau.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    medicament m (ref,nomProduit,nbrMed);
    bool test=m.ajouter();
    if(test)
    {
        ui->tablemedicament->setModel(tmpmedicament.afficher());
    QMessageBox::information(nullptr, QObject::tr("Ajouter un médicament"),
                  QObject::tr("médicament ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_ref->clear();
            ui->comboBox->clear();
            ui->lineEdit_nb->clear();

    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un médicament"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void amedicament::on_pushButton_modifier_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    int ref = ui->lineEdit_ref->text().toInt();
    QString nomProduit= ui->lineEdit_nomP->text();
    int nbrMed= ui->lineEdit_nb->text().toInt();
    if(nbrMed<=20){
        QMessageBox::critical(nullptr, QObject::tr("ALERT!!"),
                                         QObject::tr("veuillez recharger le stocke de ce médicament à nouveau!.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
    medicament m (ref,nomProduit,nbrMed);
    bool test=m.modifier(ref,nomProduit,nbrMed);
    if(test)
    { ui->tablemedicament->setModel(tmpmedicament.afficher());

            QMessageBox::information(nullptr, QObject::tr("Modifier un médicament"),
                  QObject::tr("médicament modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_ref->clear();
            ui->lineEdit_nomP->clear();
            ui->lineEdit_nb->clear();
    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Modifier un médicament"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}



void amedicament::on_pushButton_supp_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    medicament m;
        int ref = ui->lineEdit_ref->text().toInt();
        bool test=m.supprimer(ref);
        if(test)
        { ui->tablemedicament->setModel(tmpmedicament.afficher());
            QMessageBox::information(nullptr, QObject::tr("Supprimer un médicament"),
                        QObject::tr("Médicament supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
               ui->lineEdit_ref->clear();
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un médicament"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
     QSqlQueryModel *   model=m.afficher();
}

void amedicament::on_pushButton_chercherP_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);
    QString nomProduit1= ui->comboBox->currentText();
    ui->lineEdit_nomP->setText(nomProduit1);
    QString nomProduit= ui->lineEdit_nomP->text();
     qDebug()<< nomProduit << endl;
            QSqlQuery query;
            query.first();
            query.prepare("SELECT * from TABMED where NOMPRODUIT= '"+nomProduit+"'");
            if(query.exec())

            {
                while(query.next())
                {

                    ui->lineEdit_ref->setText(query.value(0).toString());//Ref
                    ui->lineEdit_nomP->setText(query.value(1).toString());//nomProduit
                    ui->lineEdit_nb->setText(query.value(2).toString());//nbrmed


                }
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Chercher médicament!"),
                                      QObject::tr("Erreur!.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void amedicament::on_pushButton_rechercher_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);

    QSqlQuery query;
         QString nomProduit= ui->lineEdit_nomP_3->text();
        nomProduit=nomProduit+"%";
        qDebug()<<nomProduit;
        query.prepare("SELECT * from TABMED where(NOMPRODUIT LIKE :nomProduit)");
        query.bindValue(":nomProduit",nomProduit);
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
        QSqlQueryModel * modal= new QSqlQueryModel();
        modal->setQuery(query);
        qDebug()<<modal->rowCount();
        ui->tablemedicament_2->setModel(modal);
}



void amedicament::on_pushButton_tri_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("select * from TABMED");
        qry.exec();
        model->setQuery(qry);

        QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
        m->setDynamicSortFilter(true);
        m->setSourceModel(model);
        ui->tablemedicament->setModel(m);
        ui->tablemedicament->setSortingEnabled(true);
}


void amedicament::on_pushButton_imprimer_clicked()
{
    QString strStream;
              QTextStream out(&strStream);

              const int rowCount = ui->tablemedicament->model()->rowCount();
              const int columnCount = ui->tablemedicament->model()->columnCount();
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
                  if (!ui->tablemedicament->isColumnHidden(column))
                      out << QString("<th>%1</th>").arg(ui->tablemedicament->model()->headerData(column, Qt::Horizontal).toString());
              out << "</tr></thead>\n";

              // data table
              for (int row = 0; row < rowCount; row++) {
                  out << "<tr>";
                  for (int column = 0; column < columnCount; column++) {
                      if (!ui->tablemedicament->isColumnHidden(column)) {
                          QString data =ui->tablemedicament->model()->data(ui->tablemedicament->model()->index(row, column)).toString().simplified();
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





void amedicament::on_pushButton_commander_clicked()
{
    player->setMedia(QUrl::fromLocalFile("C:/Users/asus/Documents/medicaments/medicament/click.mp3"));
    player->play();
    qDebug()<<player->errorString();
    QThread::sleep(1);
    commande C;
    C.setModal(true);
    C.exec();
}

void amedicament::on_pushButton_clicked()
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
