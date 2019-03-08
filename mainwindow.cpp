#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect signals of buttons when they are clicked to appropriate functions

    connect(ui->mult,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->div,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->sum,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->sub,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->zero,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->one,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->two,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->three,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->four,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->five,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->six,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->seven,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->eight,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->nine,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->Abutton,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->Bbutton,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->Cbutton,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->Dbutton,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->Ebutton,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->Fbutton,SIGNAL(clicked()),this,SLOT(multi())) ;
    connect(ui->clear,SIGNAL(clicked()),this,SLOT(clr())) ;
    connect(ui->hex,SIGNAL(clicked()),this,SLOT(hex())) ;
    connect(ui->dec,SIGNAL(clicked()),this,SLOT(dec())) ;
    connect(ui->equ,SIGNAL(clicked()),this,SLOT(equ())) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}


//takes the text of the clicked button and displays it
//also appends it to vector "calc" with holds texts of all buttons pressed(calc is defined in mainwindow.h)
void MainWindow::multi(){

    QPushButton* pButton = qobject_cast<QPushButton*>(sender());    //cast the sender of signal to QPushButton
    QString s=ui->label->text()+pButton->text();
    ui->label->setText(s);
    calc.push_back(pButton->text());

}
//clears vector "calc" and sets Qlabel to display nothing
void MainWindow::clr(){
    calc.clear();
    ui->label->setText("");
}
//changes mode to be hexadecimal(mode=1 implies the mode is hexadecimal."int mode" is defined in mainwindow.h)
void MainWindow::hex(){
    mode=1;
}
//changes mode to be decimal
void MainWindow::dec(){
    mode=0;
}

//applies the given arithmetic operations
//if inputs are not valid (for example :if "1A" is used in decimal mode) ,displays error message.
void MainWindow::equ(){
    QString a1="*";
    QString a2="/";
    QString a3="+";
    QString a4="-";
    QRegExp re("\\-*\\w+");      //regex pattern matching positive or negative numbers(can include letters )
    QRegExp re2("[\\*-/+]") ;      //regex pattern matching arithmetic operators



    bool valid=true;                //true if inputs are valid

    QRegExp relet("[A-Za-z]");      //pattern matching letters


    //traverse clicked buttons to arrange them to be used in operations
    QString s="";
    vector<QString> calc2;          //holds the operators and numbers to be used in operations

    for(int i=0;i<(int)calc.size();i++){
        QString tem=calc[i];

        if(mode==0&&tem.contains(relet)){         //checks if inputs are valid(if mode is 0(decimal),and input contains a letter,valid is false )

            valid=false;

        }

        //we will append button texts to "s" until we see an arithmetic operator(if 1 , 2 ,5,+ are clicked in order we
        //append 1,2,5 to "s" to form number 125)


        if(re.exactMatch(tem)){                     //if button is not arithmetic operator append it to QString s
            s+=tem;
            if(i==(int)calc.size()-1){              //if current button is the last one in "calc" append it to calc2
                calc2.push_back(s);
            }
        }
        else if(re2.exactMatch(tem)){

           calc2.push_back(s);                      //if current button is arithmetic operator append "s" to calc2
           calc2.push_back(tem);                    //append arit. operator to calc2

            s="";                                   //clear "s" so that we can use it for the next number to be formed
        }


    }
    QRegExp re3("\\*");
    QRegExp re4("\\/");
    QRegExp re5("\\+");
    QRegExp re6("\\-");




if(valid){
    //we handle multiplications and divisions first since they have precedence over addition and subtraction

    for(int i=0;i<calc2.size()-1;i++){          //traverse "calc2" to find */ operators

        if(re3.exactMatch(calc2[i])){           //if operator is *


            int a;
            int b;
            int c;      //result
             QString s=""; //result as QString
            if(mode==0){                            //if decimal mode ,convert the numbers before and after the * operator to integer
             a=calc2[i-1].toInt();
             b=calc2[i+1].toInt();
             c=a*b;
             s=QString::number(c);
            }
            else{                               //if hex mode,convert Qstring to string.Then convert strings(for example:12A) to decimal number
                QString q1=calc2[i-1];

                std::string temp = q1.toLocal8Bit().constData();  //convert Qstring to string

                std::stringstream ss;
                ss << std::hex << temp;             //convert number string to decimal number
                ss >> a;
                //cout<<a<<endl;

                QString q2=calc2[i+1];

                std::stringstream ss2;                  //do the same for the other number
                std::string temp2 = q2.toLocal8Bit().constData();
                ss2 << std::hex << temp2;
                ss2 >> b;
                c=a*b;
                if(c<0){          //if result is negative,convert result to positive and display it by adding "-" to beginning
                    s="-";
                    c=c*(-1);
                }
                std::stringstream ss3;              //convert decimal result to hexa
                ss3<<std::hex<<c;
                std::string ht(ss3.str());
                s+=QString::fromStdString(ht);

            }

           // cout<<c<<endl;

            calc2.insert(calc2.begin()+i+2,s);                  //insert result to calc2. then delete the numbers multiplied and the * operator
            calc2.erase(calc2.begin()+i-1,calc2.begin()+i+2);   //so that calc2 does not contain operations which are already applied

            i--;                                            //decrement i,so that we don't jump over following operator


        }


        else if(re4.exactMatch(calc2[i])){              //same as above (this time for division)
            int a;
            int b;
            int c;      //result
             QString s=""; //result as QString
            if(mode==0){                            //if decimal mode ,convert the numbers before and after the * operator to integer
             a=calc2[i-1].toInt();
             b=calc2[i+1].toInt();
             c=a/b;
             s=QString::number(c);
            }
            else{                               //if hex mode,convert Qstring to string.Then convert strings(for example:12A) to decimal number
                QString q1=calc2[i-1];

                std::string temp = q1.toLocal8Bit().constData();  //convert Qstring to string

                std::stringstream ss;
                ss << std::hex << temp;             //convert number string to decimal number
                ss >> a;
                //cout<<a<<endl;

                QString q2=calc2[i+1];

                std::stringstream ss2;                  //do the same for the other number
                std::string temp2 = q2.toLocal8Bit().constData();
                ss2 << std::hex << temp2;
                ss2 >> b;
                c=a/b;
                if(c<0){          //if result is negative,convert result to positive and display it by adding "-" to beginning
                    s="-";
                    c=c*(-1);
                }
                std::stringstream ss3;              //convert decimal result to hexa
                ss3<<std::hex<<c;
                std::string ht(ss3.str());
                s+=QString::fromStdString(ht);

            }

           // cout<<c<<endl;

            calc2.insert(calc2.begin()+i+2,s);                  //insert result to calc2. then delete the numbers multiplied and the * operator
            calc2.erase(calc2.begin()+i-1,calc2.begin()+i+2);   //so that calc2 does not contain operations which are already applied

            i--;                                            //decrement i,so that we don't jump over following operator


        }


    }


    //we now handle addition and subtraction in following for loop
    //implementation is similar to above for loop

    for(int i=0;i<calc2.size()-1;i++){                  //same operations for addition and subtraction

        if(re5.exactMatch(calc2[i])){
            int a;
            int b;
            int c;      //result
             QString s=""; //result as QString
            if(mode==0){                            //if decimal mode ,convert the numbers before and after the * operator to integer
             a=calc2[i-1].toInt();
             b=calc2[i+1].toInt();
             c=a+b;
             s=QString::number(c);
            }
            else{                               //if hex mode,convert Qstring to string.Then convert strings(for example:12A) to decimal number
                QString q1=calc2[i-1];

                std::string temp = q1.toLocal8Bit().constData();  //convert Qstring to string

                std::stringstream ss;
                ss << std::hex << temp;             //convert number string to decimal number
                ss >> a;
                //cout<<a<<endl;

                QString q2=calc2[i+1];

                std::stringstream ss2;                  //do the same for the other number
                std::string temp2 = q2.toLocal8Bit().constData();
                ss2 << std::hex << temp2;
                ss2 >> b;
                c=a+b;
                if(c<0){          //if result is negative,convert result to positive and display it by adding "-" to beginning
                    s="-";
                    c=c*(-1);
                }
                std::stringstream ss3;              //convert decimal result to hexa( to add it to calc2 in hexa)
                ss3<<std::hex<<c;
                std::string ht(ss3.str());
                s+=QString::fromStdString(ht);

            }



            calc2.insert(calc2.begin()+i+2,s);                  //insert result to calc2. then delete the numbers multiplied and the * operator
            calc2.erase(calc2.begin()+i-1,calc2.begin()+i+2);   //so that calc2 does not contain operations which are already applied

            i--;                                            //decrement i,so that we don't jump over following operator


        }
        else if(re6.exactMatch(calc2[i])){
            int a;
            int b;
            int c;      //result
             QString s=""; //result as QString
            if(mode==0){                            //if decimal mode ,convert the numbers before and after the * operator to integer
             a=calc2[i-1].toInt();
             b=calc2[i+1].toInt();
             c=a-b;
             s=QString::number(c);
            }
            else{                               //if hex mode,convert Qstring to string.Then convert strings(for example:12A) to decimal number
                QString q1=calc2[i-1];

                std::string temp = q1.toLocal8Bit().constData();  //convert Qstring to string

                std::stringstream ss;
                ss << std::hex << temp;             //convert number string to decimal number
                ss >> a;
                //cout<<a<<endl;

                QString q2=calc2[i+1];

                std::stringstream ss2;                  //do the same for the other number
                std::string temp2 = q2.toLocal8Bit().constData();
                ss2 << std::hex << temp2;
                ss2 >> b;
                c=a-b;
                if(c<0){          //if result is negative,convert result to positive and display it by adding "-" to beginning
                    s="-";
                    c=c*(-1);
                }
                std::stringstream ss3;              //convert decimal result to hexa
                ss3<<std::hex<<c;
                std::string ht(ss3.str());
                s+=QString::fromStdString(ht);

            }

           // cout<<c<<endl;

            calc2.insert(calc2.begin()+i+2,s);                  //insert result to calc2. then delete the numbers multiplied and the * operator
            calc2.erase(calc2.begin()+i-1,calc2.begin()+i+2);   //so that calc2 does not contain operations which are already applied

            i--;                                            //decrement i,so that we don't jump over following operator


        }


    }





       //following part displays the result of all operations
       //above for loops continue till calc2 contains only the overall result

                                          //display the result.and clear calc and then add only the result to it
    ui->label->setText(calc2[0]);           //so that you can use the result with additional inputs
    calc.clear();                           //for example if you input 1+3 and click = ,display 4.Now calc only contains "4" and you can
    calc.push_back(calc2[0]);               //use result in another operation like 4+2


}
else{
    ui->label->setText("Arguments are not valid for decimal mode.Click 'clr'!!");       //error message if inputs are not valid

}




}

