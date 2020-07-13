#ifndef COMMANDE_H
#define COMMANDE_H
#include "commande1.h"
#include <QDialog>
#include <QDialog>
#include <QMediaPlayer>
#include <QThread>
#include <QSortFilterProxyModel>

namespace Ui {
class commande;
}

class commande : public QDialog
{
    Q_OBJECT

public:
    explicit commande(QWidget *parent = nullptr);
    ~commande();
QMediaPlayer* player= new QMediaPlayer;
private slots:
void on_pushButton_ajout_C_clicked();

void on_pushButton_Modifier_C_clicked();

void on_pushButton_supprimer_C_clicked();

void on_pushButton_chercherD_clicked();


void on_pushButton_rechercher_C_clicked();

void on_pushButton_tri_2_clicked();

void on_pushButton_imprimer_2_clicked();



private:
    Ui::commande *ui;
    Commande tmpcommande;

};

#endif // COMMANDE_H
