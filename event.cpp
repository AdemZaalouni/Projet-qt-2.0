#include "event.h"

event::event()
{
nom="";
genre="";
prix=0;
date="";
}

event::event(QString date ,int prix,QString nom,QString genre)
{
this->nom=nom;
this->genre=genre;
    this->prix=prix;
    this->date=date;
}


QString event::getnom(){
    return nom;
}
int event::getprix(){
    return prix;
}
QString event::getgenre(){
    return genre;
}
QString event::getdate(){
    return date;
}

void event::setnom(QString nom){
    this->nom=nom;
}
void event::setprix(int prix){
  this->prix=prix;
}
void event::setgenre(QString genre){
    this->genre=genre;
}
void event::setdate(QString date){
    this->date=date;
}


bool event::ajouter(){


    QSqlQuery query;
    QString pr=QString::number(prix);

    query.prepare("INSERT INTO EVENT (DATE_EVENT,PRIX,NOM,GENRE) "
                  "VALUES (:date,:prix,:nom,:genre)");
    query.bindValue(":date", date);
    query.bindValue(":prix", pr);
    query.bindValue(":nom",nom);
    query.bindValue(":genre",genre);


    return query.exec();
}

 QSqlQueryModel* event::afficher(){

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENT");
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prix"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("Genre"));

       return model;



}

bool event::supprimer(int id){

    QSqlQuery query;
    QString idd=QString::number(id);
    query.prepare("DELETE FROM event WHERE ID_EVENT=:id");
    query.bindValue(":id",idd);

    return query.exec();
}

bool event::recherche_id(int id)
{


    QSqlQuery query;
     QString id_string=QString::number(id);
    query.prepare("SELECT * FROM EVENT WHERE ID_EVENT= :id");
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

bool event::modifier(int id){

    QSqlQuery query;
    QString p=QString::number(prix);


    if (id)
    {

          query.prepare("UPDATE EVENT SET DATE_EVENT=:date, PRIX=:prix , NOM=:nom , GENRE=:genre WHERE ID_EVENT=:id");
           query.bindValue(":id",id);
          query.bindValue(":prix", p);
          query.bindValue(":date", date);
          query.bindValue(":nom",nom);
          query.bindValue(":genre",genre);

    }
          return query.exec();
}

