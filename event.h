#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class event
{
private:

    QString nom,genre,date;
    int prix;
      public:
            event();
            event(QString,int,QString,QString);



            int getprix();
             QString getdate();
            QString getnom();
             QString getgenre();



            void setprix(int prix);
            void setdate(QString date);
            void setnom(QString nom);
            void setgenre(QString ge);




            bool ajouter();
            QSqlQueryModel* afficher();

            bool modifier(int);
             bool recherche_id(int);
            QSqlQueryModel* recherche_nom(QString);
           QSqlQueryModel* recherche_prenom(QString);
           QSqlQueryModel* recherche_email(QString);
           QSqlQueryModel* tri_nom();
             QSqlQueryModel* tri_tel();
             QSqlQueryModel* tri_prenom();
            bool supprimer(int);
};

#endif // EVENT_H
