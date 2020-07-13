#include "modification.h"
#include "ui_modification.h"
#include "materiel.h"
#include <QMessageBox>

modification::modification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modification)
{
    ui->setupUi(this);
    QPixmap pix(":/img/img/doctor-gp-netherlands.jpg");
    ui->label_4->setPixmap(pix);
}

modification::~modification()
{
    delete ui;
}

void modification::setnom(QString a)
{
    ui->nom->setText(a);
}

void modification::setref(int a)
{
    ui->ref->setText(QString::number(a));
}

void modification::on_pb_supprimer_4_clicked()
{
    close();
}

void modification::on_pb_supprimer_3_clicked()
{
    QString ref=ui->ref->text();
    int nbr=ui->nbr->text().toInt();
    bool test=tmpmateriel.modifier(ref,nbr);
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier Matériel"),
                    QObject::tr("Matériel modifié"), QMessageBox::Ok);
    }
    close();
}
