#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "event.h"

#include "QWidget"
#include <QMessageBox>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
#include <QTabWidget>
#include <QTableWidget>
#include<QDebug>
#include <QPrintDialog>
#include<QFileDialog>
#include<QPdfWriter>
#include<QPrinter>
#include<QFile>
#include <QAbstractSocket>
#include <QSslSocket>
#include<QStringList>
#include <iostream>
#include<QTextDocument>
#include <QValidator>
#include <QIntValidator>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QTabWidget setModel;
    ui->setupUi(this);
  ui->tabclient->setModel(C.afficher());
   ui->tabevent->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}
// **************************************************** * client * ******************************************************************
//button ajouter
void MainWindow::on_pushButton_clicked()
{
    int tel=ui->tel->text().toInt();
    QString nom=ui->nom_c->text();
    QString prenom=ui->prenom->text();
      QString email=ui->email->text();

    client C(nom, prenom, email , tel);
    bool test=C.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");


    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}

//button supprimer
void MainWindow::on_pushButton_9_clicked()
{
    int id=ui->supp_client->text().toInt();
    bool test=C.supprimer(id);
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("supprimer avec succée");


    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}


// button modifier recherche
void MainWindow::on_pushButton_10_clicked()
{
    client C;
    QSqlQuery query;
    int id=ui->id_m->text().toInt();
    QString id_string=QString::number(id);
   if(C.recherche_id(id))
   {
       query.prepare("SELECT * FROM CLIENT WHERE ID_CLIENT = :id");
       query.bindValue(":id",id_string);
       query.exec();
       while(query.next())
   {
       ui->nom_m->setText(query.value(1).toString());
       ui->prenom_m->setText(query.value(2).toString());
       ui->email_m->setText(query.value(3).toString());
       ui->tel_m->setText(query.value(4).toString());


    }
   }
}

//button modifier
void MainWindow::on_pushButton_11_clicked()
{
    client C;
    QMessageBox msg;
    int id=ui->id_m->text().toInt();
    QString nom_m=ui->nom_m->text();
    QString prenom_m=ui->prenom_m->text();
    QString email_m=ui->email_m->text();
    int tel_m=ui->tel_m->text().toInt();
    client *Cl = new client(nom_m,prenom_m,email_m,tel_m);

    bool test=Cl->modifier(id);



    if(test)
    {
        msg.setText("modification avec succès");

    }
    else
        msg.setText("echec de modification");

    msg.exec();
}

// button refreshe
void MainWindow::on_pushButton_23_clicked()
{

    ui->tabclient->setModel(C.afficher());
}

// **************************************************** * event * ******************************************************************

//ajouet button
void MainWindow::on_pushButton_13_clicked()
{
    int p=ui->prix->text().toInt();
    QString nom=ui->nom_e->text();
    QString genre=ui->genre->text();
      QString date=ui->date->text();

    class event E(date, p, nom , genre);
    bool test=E.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");


    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}

//supprimer button
void MainWindow::on_pushButton_12_clicked()
{
    int id=ui->supp_e->text().toInt();
    bool test=E.supprimer(id);
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("supprimer avec succée");


    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}

//modifier button recherche
void MainWindow::on_pushButton_15_clicked()
{
    client E;
    QSqlQuery query;
    int id=ui->id_m_e->text().toInt();
    QString id_string=QString::number(id);
   if(id)
   {
       query.prepare("SELECT * FROM EVENT WHERE ID_EVENT = :id");
       query.bindValue(":id",id_string);
       query.exec();
       while(query.next())
   {
       ui->date_m_e->setText(query.value(1).toString());
       ui->prix_m_e->setText(query.value(2).toString());
       ui->nom_m_e->setText(query.value(3).toString());
       ui->genre_m_e->setText(query.value(4).toString());


    }
   }
}

//modifier button
void MainWindow::on_pushButton_14_clicked()
{

    QMessageBox msg;
    int id=ui->id_m_e->text().toInt();
    QString nom_m=ui->nom_m_e->text();
    QString date=ui->date_m_e->text();
    QString genre=ui->genre_m_e->text();
    int p=ui->prix_m_e->text().toInt();
   class event *EV = new class event(date,p,nom_m,genre);

    bool test=EV->modifier(id);



    if(test)
    {
        msg.setText("modification avec succès");


    }
    else
        msg.setText("echec de modification");

    msg.exec();
}


//button refresh
void MainWindow::on_pushButton_24_clicked()
{

     ui->tabevent->setModel(E.afficher());
}
