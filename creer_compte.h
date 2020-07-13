#ifndef CREER_COMPTE_H
#define CREER_COMPTE_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class creer_compte;
}

class creer_compte : public QDialog
{
    Q_OBJECT

public:
    explicit creer_compte(QWidget *parent = nullptr);
    ~creer_compte();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    QString on_radioButton_clicked();



private:
    Ui::creer_compte *ui;
};

#endif // CREER_COMPTE_H
