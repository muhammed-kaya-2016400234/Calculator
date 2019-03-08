#include <QApplication>
#include "mainwindow.h"
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


int main(int argc,char *argv[])
{
  /*  QString qrt="-54";
    int newnum=qrt.toInt();
    QString news=QString::number(newnum);
    int newnum2=news.toInt();
    QRegExp re("\\-*\\w+");
    QRegExp re2("[\\*+/-]") ;
    QRegExp re3("[A-Za-Z]");
    QString ch="A";
    if(re2.exactMatch("12"))
        cout<<"true"<<newnum<<" "<<newnum2<<endl;
    if(ch.contains(re3))
        cout<<"thats right"<<endl;
*/
  /*  int hex=0x200;
    std::stringstream ss;
    ss<<std::hex<<hex;



    hex=-10;
    std::string st="-12a";

    std::stringstream ss3;
    ss3<<std::hex<<st;
    ss3>>hex;
    std::string ht(ss3.str());
    cout<<hex<<endl;
*/

   QApplication app(argc,argv) ;


   MainWindow f ;
   f.show() ;
   return app.exec() ;

}
