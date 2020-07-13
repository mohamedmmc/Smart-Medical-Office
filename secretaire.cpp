#include "secretaire.h"
#include "ui_secretaire.h"
#include "rdv.h"
#include <QMessageBox>
#include "login.h"
#include "patient.h"
#include "traitement.h"
#include "docteur2.h"
#include "ordo.h"
#include <QFile>
#include <QTimer>
#include <QPrintDialog>
#include <QPrinter>
#include <QDate>
#include <QTextDocument>
#include <QTextStream>
#include "arduino.h"


secretaire::secretaire(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::secretaire)
{
    ui->setupUi(this);
    ui->tabrdv_2->setModel(tmprdv.afficher());
    ui->tabpatient_3->setModel(tmppatient.afficher());
    QPixmap pic(":/img/img/secretariat2.jpg");
    QPixmap pic2(":/img/img/secretariat2.jpg");
    ui->p1_3->setPixmap(pic2);
    ui->p2_3->setPixmap(pic2);
    ui->p3_3->setPixmap(pic2);
    ui->p4_3->setPixmap(pic2);
    ui->p5_3->setPixmap(pic2);
    ui->p6_3->setPixmap(pic2);
    ui->picture_4->setPixmap(pic2);
    ui->picture_5->setPixmap(pic2);
    ui->picture_6->setPixmap(pic2);
    ui->p2_4->setPixmap(pic2);
    ui->pic5->setPixmap(pic2);
            ui->p3_4->setPixmap(pic2);
            ui->p4_4->setPixmap(pic2);
            ui->p5_4->setPixmap(pic2);
            ui->p6_4->setPixmap(pic2);
            ui->label->setPixmap(pic2);
    son=new QSound(":/son/son/button20.wav");
    ui->picture_ajoutrdv_2->setPixmap(pic);
    ui->picture_affichrdv_2->setPixmap(pic);
    ui->picture_modifrdv_2->setPixmap(pic);
    ui->picture_supprdv_2->setPixmap(pic);
    ui->tabdocteur_2->setModel(tmpdocteur.afficher());
    ui->tabpatient_4->setModel(tmptraitement.afficher());
    ui->tabr_4->setModel(tmptraitement.afficher());
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

secretaire::~secretaire()
{
    delete ui;
}

void secretaire::on_pb_ajouter_clicked()
{
    int cin = ui->cinline_2->text().toInt();
    QString nom= ui->nomline_2->text();
    QString prenom= ui->prenomline_2->text();
    int datee = ui->dateEdit_2->text().toInt();
    int heure = ui->lineEdit_6->text().toInt();
    QString objet= ui->lineEdit_5->text();
    QString medecin =ui->telline_2->text();


    rdv r(cin,nom,prenom,datee,heure,objet,medecin);
    bool test=r.ajouter();

    if(test)
    {
        ui->tabrdv_2->setModel(tmprdv.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Ajouter un rendez-vous"),
            QObject::tr("Rendez-vous ajouté.\n"
                              "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);

    }
    else
            QMessageBox::critical(nullptr, QObject::tr("Ajouter un rendez-vous"),
                  QObject::tr("Erreur,le rendez-vous n'est pas ajouté!\n"
                              "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);


}

void secretaire::on_pb_supprimer_clicked()
{
  int cin = ui->lineEdit_id_6->text().toInt();
  bool test=tmprdv.supprimer(cin);

  if(test)
  {
      ui->tabrdv_2->setModel(tmprdv.afficher());//refresh
          QMessageBox::information(nullptr, QObject::tr("Supprimer un Rendez-vous"),
                QObject::tr("Rendez-vous supprimé.\n"
                            "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);
  }
  else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un Rendez-vous"),
                QObject::tr("Erreur,le rendez-vous n'est pas supprimé!\n"
                            "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);

}

void secretaire::on_pb_modifier_clicked()
{
  int cin = ui->cinlinemod_2->text().toInt();
  int heure = ui->lineEdit_7->text().toInt();
  bool test = tmprdv.modifier(cin,heure);

  if(test)
  {
      ui->tabrdv_2->setModel(tmprdv.afficher());//refresh
          QMessageBox::information(nullptr, QObject::tr("Modifier un Rendez-vous"),
                QObject::tr("Rendez-vous modifié.\n"
                            "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);
  }
  else
    QMessageBox::critical(nullptr, QObject::tr("Modifier un Rendez-vous"),
                QObject::tr("Erreur,le rendez-vous n'est pas modifié!\n"
                            "Cliquer sur CANCEL pour quitter."), QMessageBox::Cancel);

}

void secretaire::on_recherche_patient_clicked()
{
    QString cin = ui->patient_recherche->text();
    bool test=tmprdv.recherche_patient(cin);

   if(test)
    {
        ui->tabrdv_2->setModel(tmprdv.afficher_patient(cin));//refresh
            QMessageBox::information(nullptr, QObject::tr("Recherche effectuée"),
            QObject::tr("Reussite.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
            QMessageBox::critical(nullptr, QObject::tr("Recherche non effectuée"),
                  QObject::tr("Echecs !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}



void secretaire::on_patient_recherche_returnPressed()
{
    QString cin = ui->patient_recherche->text();
    tmprdv.recherche_patient(cin);
   ui->tabrdv_2->setModel(tmprdv.afficher_patient(cin));//refresh
}

void secretaire::on_pushButton_clicked()
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

void secretaire::on_pb_ajouter_3_clicked()
{
    int id = ui->nump_3->text().toInt();
    QString nom= ui->nom_4->text();
    QString prenom= ui->prenom_4->text();
    int numtraitement= ui->drdv_3->text().toInt();
    QString maladie= ui->maladie_3->text();
    QString obs= ui->obs_3->text();


  patient e(id,nom,prenom,numtraitement,maladie,obs);
  bool test=e.ajouter();
  if(test)
{son->play();
      ui->tabpatient_3->setModel(tmppatient.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("patient ajouté"),
                  QObject::tr("Dossier ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("patient non ajouté"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void secretaire::on_pb_supprimer_3_clicked()
{
    int id = ui->lineEdit_id_7->text().toInt();
    bool test=tmppatient.supprimer(id);
    if(test)
    {son->play();
        ui->tabpatient_3->setModel(tmppatient.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un étudiant"),
                    QObject::tr("Etudiant supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un étudiant"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void secretaire::on_modif_2_clicked()
{
    int id = ui->m1_3->text().toInt();
    QString nom= ui->m2_3->text();
    QString prenom= ui->m3_3->text();
    int numtraitement= ui->m4_3->text().toInt();
    QString maladie= ui->m5_3->text();
    QString obs= ui->m6_3->text();


  patient e(0,nom,prenom,numtraitement,maladie,obs);
  e.set_nump(id);
  bool test=e.modifier();
  if(test)
{ui->tabpatient_3->setModel(tmppatient.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Dossier modifié"),
                  QObject::tr("Dossier modifié !!.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("patient non ajouté"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}


void secretaire::on_rech_2_returnPressed()
{
    QString rech;
    rech=ui->rech_2->text();

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

     qry->prepare("SELECT * from patient where nump like '"+rech+"%'");
     qry->bindValue("rech",rech);
     qry->exec();
     model->setQuery(*qry);
     ui->tabr_3->setModel(model);
}

void secretaire::on_rech_2_textChanged(const QString &arg1)
{

        QSqlQueryModel * model= new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();

         qry->prepare("SELECT * from patient where nump like '"+arg1+"%'");
         qry->bindValue("rech",arg1);
         qry->exec();
         model->setQuery(*qry);
         ui->tabr_3->setModel(model);
}

void secretaire::on_rech2_2_textChanged(const QString &arg1)
{


    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

     qry->prepare("SELECT * from ordo where numordonnance like '"+arg1+"%'");
     qry->bindValue("rech",arg1);
     qry->exec();
     model->setQuery(*qry);
     ui->tabr2_3->setModel(model);
}

void secretaire::on_pb_ajouter_4_clicked()
{
    int numt = ui->nump_4->text().toInt();
    QString nomt= ui->nom_5->text();
    QString datet= ui->prenom_5->text();



  traitement e(numt,nomt,datet);
  bool test=e.ajouter();
  if(test)
 {son->play();
      ui->tabpatient_4->setModel(tmptraitement.afficher());//refresh
 QMessageBox::information(nullptr, QObject::tr("traitement ajouté"),
                  QObject::tr("traitement ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

 }
  else
      QMessageBox::critical(nullptr, QObject::tr("traitement non ajouté"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void secretaire::on_pb_supprimer_4_clicked()
{
    int id = ui->lineEdit_id_10->text().toInt();
    bool test=tmptraitement.supprimer(id);
    if(test)
    {son->play();
       ui->tabpatient_4->setModel(tmptraitement.afficher());//refresh
       QMessageBox::information(nullptr, QObject::tr("Supprimer un traitement"),
                   QObject::tr("traitement supprimé.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
       QMessageBox::critical(nullptr, QObject::tr("Supprimer un traitement"),
                   QObject::tr("Erreur !.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void secretaire::on_modif_clicked()
{
    int numt= ui->m1_4->text().toInt();
  QString nomt= ui->m2_4->text();
  QString datet= ui->m3_4->text();





traitement e(0,nomt,datet);
e.set_numt(numt);
bool test=e.modifier();
if(test)
{ui->tabpatient_4->setModel(tmptraitement.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("traitement modifié"),
                QObject::tr("traitement modifié !!.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("traitement non ajouté"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void secretaire::on_rech_textChanged(const QString &arg1)
{

       QSqlQueryModel * model= new QSqlQueryModel();
       QSqlQuery* qry=new QSqlQuery();

        qry->prepare("SELECT * from traitement where numt like '"+arg1+"%'");
        qry->bindValue("rech",arg1);
        qry->exec();
        model->setQuery(*qry);
        ui->tabr_4->setModel(model);


}

void secretaire::on_rech2_textChanged(const QString &arg1)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();

     qry->prepare("SELECT * from ordo where numordonnance like '"+arg1+"%'");
     qry->bindValue("rech",arg1);
     qry->exec();
     model->setQuery(*qry);
     ui->tabr2_4->setModel(model);
}

void secretaire::on_modif_3_clicked()
{
    QString rech;
    rech=ui->ord_2->text();

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery qry;

     qry.prepare("SELECT * from tabmed where Refmedicament =  '"+rech+"' or  nomproduit = '"+rech+"' or nbrmed = '"+rech+"'");

     qry.exec();
     model->setQuery(qry);

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Refmedicament"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomproduit"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nbrmed"));
     ui->tabord_2->setModel(model);
}

void secretaire::on_pb_supprimer_2_clicked()
{
    QString strStream;
                    QTextStream out(&strStream);

                    const int rowCount = ui->tabpatient_4->model()->rowCount();
                    const int columnCount = ui->tabpatient_4->model()->columnCount();
                    QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                    out <<"<html>\n"
                          "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        << "<title>ERP - COMmANDE LIST<title>\n "
                        << "</head>\n"
                        "<body bgcolor=#ffffff link=#5000A0>\n"
                        "<h1 style=\"text-align: center;\"><strong> ***** Traitements ***** "+TT+"</strong></h1>"
                        "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                          "</br> </br>";
                    // headers
                    out << "<thead><tr bgcolor=#d6e5ff>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tabpatient_4->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tabpatient_4->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";

                    // data table
                    for (int row = 0; row < rowCount; row++) {
                        out << "<tr>";
                        for (int column = 0; column < columnCount; column++) {
                            if (!ui->tabpatient_4->isColumnHidden(column)) {
                                QString data =ui->tabpatient_4->model()->data(ui->tabpatient_4->model()->index(row, column)).toString().simplified();
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

void secretaire::on_pb_ajouter_2_clicked()
{
    int id= ui->lineEdit_id_8->text().toInt();
    QString nom= ui->lineEdit_nom_2->text();
    QString prenom= ui->lineEdit_prenom_2->text();
    QString disponiblite="";
    docteur e(nom,prenom,id,disponiblite);
  bool test=e.ajouter();
  if(test)
{ui->tabdocteur_2->setModel(tmpdocteur.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un medecin"),QObject::tr("medecin ajouté.\n""Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un émedecin"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void secretaire::on_pushButton_2_clicked()
{

    int id= ui->lineEdit_id_8->text().toInt();
 QString nom=ui->lineEdit_nom_2->text();
 QString prenom=ui->lineEdit_prenom_2->text();
 QString disponiblite="";


docteur e(nom,prenom,id,disponiblite);
e.modifier(nom,prenom);

if(e.modifier(nom,prenom))
{   ui->tabdocteur_2->setModel(e.afficher());
   QMessageBox::information(nullptr, QObject::tr("modifier un docteur"),
                       QObject::tr("info du docteurmodifié.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}
else
   QMessageBox::information(nullptr, QObject::tr("modifier un docteur"),
                       QObject::tr("info du docteur non modifié.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}



void secretaire::on_supprimer_clicked()
{
    int id = ui->lineEdit_id_9->text().toInt();
    bool test=tmpdocteur.supprimer(id);

    if(test)
    {ui->tabdocteur_2->setModel(tmpdocteur.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un docteur"),
                    QObject::tr("docteur supprimé.\n"), QMessageBox::Ok);

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("Supprimer un docteur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        }

}

void secretaire::on_lineEdit_3_textChanged(const QString &arg1)
{
   // ui->tabdocteur_2->setModel(tmpdocteur.afficher2(arg1));
}

void secretaire::on_pb_supprimer_5_clicked()
{
    QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->tabpatient_3->model()->rowCount();
                const int columnCount = ui->tabpatient_3->model()->columnCount();
                QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                out <<"<html>\n"
                      "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    << "<title>ERP - COMmANDE LIST<title>\n "
                    << "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"
                    "<h1 style=\"text-align: center;\"><strong> ***** Patients ***** "+TT+"</strong></h1>"
                    "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                      "</br> </br>";
                // headers
                out << "<thead><tr bgcolor=#d6e5ff>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tabpatient_3->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tabpatient_3->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                    out << "<tr>";
                    for (int column = 0; column < columnCount; column++) {
                        if (!ui->tabpatient_3->isColumnHidden(column)) {
                            QString data =ui->tabpatient_3->model()->data(ui->tabpatient_3->model()->index(row, column)).toString().simplified();
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

 void secretaire::update_label()
{
     data.clear();
    data=A.read_from_arduino();
    tmpdocteur.etatdispo(data);
    ui->tabdocteur_2->setModel(tmpdocteur.afficher());
   /* if(data=="1")
    A.write_to_arduino(("2"));
    else if (data=="0")
        A.write_to_arduino(("3"));*/
}

void secretaire::on_supprimer_2_clicked()
{
    QString nom=ui->lineEdit_3->text();
    if (nom=="")
    {
        QMessageBox::information(nullptr, QObject::tr("Selectionner un docteur"),
                    QObject::tr("Selectionner un docteur\n"), QMessageBox::Ok);
    }
    else
    {
        if(tmpdocteur.etatdispo(data)==1)
            A.updateRGB(QString("1"));
        else
        {
            A.updateRGB(QString("2"));
        }
    }
}

void secretaire::on_tabdocteur_2_clicked(const QModelIndex &index)
{
    QString nom=ui->tabdocteur_2->model()->data(index).toString();
    QSqlQuery qry;

    qry.prepare("select * from docteur where nom = '"+nom+"' or prenom ='"+nom+"' or id='"+nom+"'");
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_3->setText(qry.value(0).toString());
        }
    }
}

void secretaire::on_rechercher_medecin_2_clicked()
{

}

void secretaire::on_pb_ajouter_5_clicked()
{
    A.updateRGB(QString("3"));
}
