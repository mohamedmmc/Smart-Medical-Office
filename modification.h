#ifndef MODIFICATION_H
#define MODIFICATION_H

#include <QDialog>
#include "materiel.h"

namespace Ui {
class modification;
}

class modification : public QDialog
{
    Q_OBJECT

public:
    explicit modification(QWidget *parent = nullptr);
    ~modification();
    void setnom(QString );
    void setref(int);

private slots:
    void on_pb_supprimer_4_clicked();

    void on_pb_supprimer_3_clicked();

private:
    Ui::modification *ui;
    QString nom;
    int ref;
    Materiel tmpmateriel;
};

#endif // MODIFICATION_H
