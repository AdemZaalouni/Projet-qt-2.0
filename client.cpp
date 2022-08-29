#include "client.h"
#include <QObject>
#include <QSqlQuery>
#include <QtDebug>
client::client()
{
nom="";
prenom="";
tel=0;
email="";
}

client::client(QString nom ,QString prenom,QString email,int tel)
{
this->nom=nom;
this->prenom=prenom;
    this->tel=tel;
    this->email=email;
}


QString client::getnom(){
    return nom;
}
int client::gettel(){
    return tel;
}
QString client::getprenom(){
    return prenom;
}
QString client::getemail(){
    return email;
}

void client::setnom(QString nom){
    this->nom=nom;
}
void client::settel(int tel){
  this->tel=tel;
}
void client::setprenom(QString prenom){
    this->prenom=prenom;
}
void client::setemail(QString email){
    this->email=email;
}


bool client::ajouter(){


    QSqlQuery query;
    QString tel_s=QString::number(tel);

    query.prepare("INSERT INTO CLIENT (NOM_CLIENT,PRENOM,EMAIL,TELEPHONE) "
                  "VALUES (:nom,:prenom,:email,:tel)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email",email);
    query.bindValue(":tel",tel_s);


    return query.exec();
}

QSqlQueryModel* client::afficher(){

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT");
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("telephone"));

       return model;



}

bool client::supprimer(int id){

    QSqlQuery query;
    QString idd=QString::number(id);
    query.prepare("DELETE FROM CLIENT WHERE ID_CLIENT=:id");
    query.bindValue(":id",idd);

    return query.exec();
}

bool client::recherche_id(int id)
{


    QSqlQuery query;
     QString id_string=QString::number(id);
    query.prepare("SELECT * FROM CLIENT WHERE ID_CLIENT= :id");
    query.bindValue(":id", id_string);
    if (query.exec() && query.next())
    {
            return true;
    }
    else
    {
        return false;
    }
}
bool client::modifier(int id){

    QSqlQuery query;
    QString tell=QString::number(tel);


    if (id)
    {

          query.prepare("UPDATE CLIENT SET NOM_CLIENT=:nom, PRENOM=:prenom , EMAIL=:email , TELEPHONE=:tel WHERE ID_CLIENT=:id");
           query.bindValue(":id",id);
          query.bindValue(":tel", tell);
          query.bindValue(":prenom", prenom);
          query.bindValue(":nom",nom);
          query.bindValue(":email",email);

    }
          return query.exec();
}
