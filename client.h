#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class client
{


private:

    QString nom,prenom,email;
    int tel;
      public:
            client();
            client(QString,QString,QString,int);



            int gettel();
             QString getprenom();
            QString getnom();
             QString getemail();



            void settel(int tel);
            void setprenom(QString prenom);
            void setnom(QString nom);
            void setemail(QString email);




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

#endif // CLIENT_H
