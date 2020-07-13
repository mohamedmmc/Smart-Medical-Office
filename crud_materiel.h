#ifndef GESTION_STOCK_H
#define GESTION_STOCK_H

#include <QMainWindow>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "materiel.h"

namespace Ui {
class crud_materiel;
}

class crud_materiel : public QMainWindow
{
    Q_OBJECT

public:
    explicit crud_materiel(QWidget *parent = nullptr);
    ~crud_materiel();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_3_clicked();

    void on_pb_supprimer_4_clicked();

    void on_lineEdit_id_6_returnPressed();

    void on_pushButton_clicked();
    bool deconnexion();

    void on_lineEdit_id_6_textChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_tabmateriel_clicked(const QModelIndex &index);

    void on_comboBox_2_activated(const QString &arg1);


    void on_pb_ajouter_2_clicked();

private:
    Ui::crud_materiel *ui;
    Materiel tmpmateriel;
};

#endif // GESTION_STOCK_H
