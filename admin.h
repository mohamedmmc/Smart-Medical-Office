#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include "compte.h"

namespace Ui {
class admin;
}

class admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

private slots:
    void on_pushButton_clicked();

    void on_tabetudiant_activated(const QModelIndex &index);

    void on_pb_supprimer_5_clicked();

    void on_tabetudiant_clicked(const QModelIndex &index);

    void on_lineEdit_id_6_returnPressed();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::admin *ui;
    compte tmpcompte;
};

#endif // ADMIN_H
