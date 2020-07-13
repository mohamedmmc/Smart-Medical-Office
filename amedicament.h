#ifndef AMEDICAMENT_H
#define AMEDICAMENT_H

#include <QMainWindow>
#include "medicament.h"
#include <QMediaPlayer>
#include <QThread>
#include <QSortFilterProxyModel>

namespace Ui {
class amedicament;
}

class amedicament : public QMainWindow
{
    Q_OBJECT

public:
    explicit amedicament(QWidget *parent = nullptr);
    ~amedicament();
    QMediaPlayer* player= new QMediaPlayer;
private slots:
    void comboBox_nomP();
    void on_pushButton_ok_clicked();
    void on_pushButton_supp_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_chercherP_clicked();
    void on_pushButton_tri_clicked();
    void on_pushButton_imprimer_clicked();

    void on_pushButton_commander_clicked();

    void on_pushButton_clicked();
private:
    Ui::amedicament *ui;
    medicament tmpmedicament;
};

#endif // AMEDICAMENT_H
