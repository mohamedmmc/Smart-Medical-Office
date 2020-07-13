#ifndef COMPTE_MEDECIN_H
#define COMPTE_MEDECIN_H

#include "ordo.h"
#include <QMainWindow>
#include <QWidget>
#include <QSound>

namespace Ui {
class compte_medecin;
}

class compte_medecin : public QMainWindow
{
    Q_OBJECT

public:
    explicit compte_medecin(QWidget *parent = nullptr);
    ~compte_medecin();

private slots:
    void on_pb_ajouter_2_clicked();

    void on_pushButton_2_clicked();

    void on_supprimer_2_clicked();

    void on_numm_2_textChanged(const QString &arg1);

    void on_pdf_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::compte_medecin *ui;
    ordo tmpordo;
    QSound *son;
};

#endif // COMPTE_MEDECIN_H
