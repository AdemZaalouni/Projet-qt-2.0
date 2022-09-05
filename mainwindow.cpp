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
   E.notifcation();


   // stat event



       ui->ent_progressBar->setValue(0);
       ui->ent_progressBar_2->setValue(0);
       ui->ent_progressBar_3->setValue(0);
       int SA=0,SO=0,ST=0;
        int a =E.statistique_genre("musique");
       int o=E.statistique_genre("historique");
         int s=E.statistique_genre("Soiree");
        int t=E.statistique_event();
        SA=(a*100)/t;
        SO=(o*100)/t;
        ST=(s*100)/t;


    ui->ent_progressBar->setValue(SA);
     ui->ent_progressBar_2->setValue(SO);
    ui->ent_progressBar_3->setValue(ST);





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

//tri prenom

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery *b = new QSqlQuery();

      QSqlQueryModel *model = new QSqlQueryModel();

      b->prepare("SELECT * FROM CLIENT ORDER BY PRENOM");

      b->exec();

      model->setQuery(*b);

   ui->tabclient->setModel(model);
}

// tri nom
void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery *b = new QSqlQuery();

      QSqlQueryModel *model = new QSqlQueryModel();

      b->prepare("SELECT * FROM CLIENT ORDER BY NOM_CLIENT");

      b->exec();

      model->setQuery(*b);

   ui->tabclient->setModel(model);
}

//tri telephone
void MainWindow::on_pushButton_8_clicked()
{
    QSqlQuery *b = new QSqlQuery();

      QSqlQueryModel *model = new QSqlQueryModel();

      b->prepare("SELECT * FROM CLIENT ORDER BY TELEPHONE");

      b->exec();

      model->setQuery(*b);

   ui->tabclient->setModel(model);
}

//recherche id
void MainWindow::on_pushButton_6_clicked()
{
    QString id=ui->chercher_cl->text();


    QSqlQuery * q = new  QSqlQuery ();



                        QSqlQueryModel * model = new  QSqlQueryModel ();

                        q->prepare("select * FROM CLIENT where ID_CLIENT=:id");

                        q->bindValue(":id",id );

                        q->exec();



            model->setQuery(*q);

            model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));

            model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));

            model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));

            model->setHeaderData(4,Qt::Horizontal,QObject::tr("Telephone"));


ui->tabclient->setModel(model);
}
// rechercher nom
void MainWindow::on_pushButton_7_clicked()
{
    QString nomm=ui->chercher_cl->text();


    QSqlQuery * q = new  QSqlQuery ();



                        QSqlQueryModel * model = new  QSqlQueryModel ();

                        q->prepare("select * FROM CLIENT where NOM_CLIENT=:nom");

                        q->bindValue(":nom",nomm );

                        q->exec();



            model->setQuery(*q);

            model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));

            model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));

            model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));

            model->setHeaderData(4,Qt::Horizontal,QObject::tr("Telephone"));


ui->tabclient->setModel(model);
}
//recherche email
void MainWindow::on_pushButton_5_clicked()
{
    QString e=ui->chercher_cl->text();


    QSqlQuery * q = new  QSqlQuery ();



                        QSqlQueryModel * model = new  QSqlQueryModel ();

                        q->prepare("select * FROM CLIENT where EMAIL=:email");

                        q->bindValue(":email",e );

                        q->exec();



            model->setQuery(*q);

            model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));

            model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));

            model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));

            model->setHeaderData(4,Qt::Horizontal,QObject::tr("Telephone"));


ui->tabclient->setModel(model);
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
      E.notifcation();

     ui->tabevent->setModel(E.afficher());

     int SA=0,SO=0,ST=0;
      int a =E.statistique_genre("musique");
     int o=E.statistique_genre("historique");
       int s=E.statistique_genre("Soiree");
      int t=E.statistique_event();
      SA=(a*100)/t;
      SO=(o*100)/t;
      ST=(s*100)/t;


  ui->ent_progressBar->setValue(SA);
   ui->ent_progressBar_2->setValue(SO);
  ui->ent_progressBar_3->setValue(ST);
}

//PDF

void MainWindow::on_pushButton_2_clicked()
{
    QSqlDatabase db;
                        QTableView tabe;
                        QSqlQueryModel * Model=new  QSqlQueryModel();

                        QSqlQuery qry;
                         qry.prepare("SELECT * FROM CLIENT ");
                         qry.exec();
                         Model->setQuery(qry);
                         tabe.setModel(Model);

                         db.close();

                         QString strStream;
                         QTextStream out(&strStream);

                         const int rowCount = tabe.model()->rowCount();
                         const int columnCount =  tabe.model()->columnCount();

                         const QString strTitle ="Document";


                         out <<  "<html>\n"
                                 "<img src='C:/Users/Adem/Documents/qtcpp/clientimage.jpg' height='120' width='120'/>"
                             "<head>\n"
                                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             <<  QString("<title>%1</title>\n").arg(strTitle)
                             <<  "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"
                            << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des clients")
                            <<"<br>"

                            <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
                         out << "<thead><tr bgcolor=#f0f0f0>";
                         for (int column = 0; column < columnCount; column++)
                             if (!tabe.isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(tabe.model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr>";
                             for (int column = 0; column < columnCount; column++) {
                                 if (!tabe.isColumnHidden(column)) {
                                     QString data = tabe.model()->data(tabe.model()->index(row, column)).toString().simplified();
                                     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                 }
                             }
                             out << "</tr>\n";
                         }
                         out <<  "</table>\n"
                                 "<br><br>"
                                 <<"<br>"
                                 <<"<table border=1 cellspacing=0 cellpadding=2>\n";


                             out << "<thead><tr bgcolor=#f0f0f0>";

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

                         printer.setOutputFormat(QPrinter::PdfFormat);
                         printer.setPaperSize(QPrinter::A4);
                         printer.setOutputFileName("/tmp/fournisseur.pdf");
                         printer.setPageMargins(QMarginsF(15, 15, 15, 15));



                         delete document;
}


// chercher par nom
void MainWindow::on_pushButton_20_clicked()
{
    QString nomm=ui->chercher_ev->text();


    QSqlQuery * q = new  QSqlQuery ();



                        QSqlQueryModel * model = new  QSqlQueryModel ();

                        q->prepare("select * FROM EVENT where NOM=:nom");

                        q->bindValue(":nom",nomm );

                        q->exec();



            model->setQuery(*q);

            model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));

            model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prix"));

            model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));

            model->setHeaderData(4,Qt::Horizontal,QObject::tr("Genre"));


ui->tabevent->setModel(model);


}

// chercher id
void MainWindow::on_pushButton_21_clicked()
{
    QString id=ui->chercher_ev->text();


    QSqlQuery * q = new  QSqlQuery ();



                        QSqlQueryModel * model = new  QSqlQueryModel ();

                        q->prepare("select * FROM EVENT where ID_EVENT=:id");

                        q->bindValue(":id",id );

                        q->exec();



            model->setQuery(*q);

            model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));

            model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prix"));

            model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));

            model->setHeaderData(4,Qt::Horizontal,QObject::tr("Genre"));


ui->tabevent->setModel(model);
}

//chercher genre

void MainWindow::on_pushButton_22_clicked()
{
    QString genre=ui->chercher_ev->text();


    QSqlQuery * q = new  QSqlQuery ();



                        QSqlQueryModel * model = new  QSqlQueryModel ();

                        q->prepare("select * FROM EVENT where GENRE=:genre");

                        q->bindValue(":genre",genre );

                        q->exec();



            model->setQuery(*q);

            model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));

            model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prix"));

            model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));

            model->setHeaderData(4,Qt::Horizontal,QObject::tr("Genre"));


ui->tabevent->setModel(model);
}


// tri prix
void MainWindow::on_pushButton_19_clicked()
{
    QSqlQuery *b = new QSqlQuery();

      QSqlQueryModel *model = new QSqlQueryModel();

      b->prepare("SELECT * FROM EVENT ORDER BY PRIX");

      b->exec();

      model->setQuery(*b);

   ui->tabevent->setModel(model);


}

//tri genre
void MainWindow::on_pushButton_17_clicked()
{
    QSqlQuery *b = new QSqlQuery();

      QSqlQueryModel *model = new QSqlQueryModel();

      b->prepare("SELECT * FROM EVENT ORDER BY GENRE");

      b->exec();

      model->setQuery(*b);

   ui->tabevent->setModel(model);
}

//tri nom
void MainWindow::on_pushButton_18_clicked()
{
    QSqlQuery *b = new QSqlQuery();

      QSqlQueryModel *model = new QSqlQueryModel();

      b->prepare("SELECT * FROM EVENT ORDER BY NOM");

      b->exec();

      model->setQuery(*b);

   ui->tabevent->setModel(model);
}


