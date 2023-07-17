#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QTimer>
#include <fstream>
#include<QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->BtnAnnuler, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->BtnValider, SIGNAL(clicked()), this, SLOT(checked()));
    connect(ui->BtnQuitte, SIGNAL(clicked()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cancel()
{
    ui->textEdit->clear();
}

void MainWindow::close()
{
    close();
}

void MainWindow::checked()
{
    QString plate = ui->textEdit->toPlainText();

    bool isValid = false;

    if (plate.length() == 9 && plate[2] == '-' && plate [6] == '-')
    {
        bool isLetter1 = plate[0].isLetter() && plate[0].isUpper();
        bool isLetter2 = plate[1].isLetter() && plate[1].isUpper();
        bool isNumber1 = plate[3].isDigit();
        bool isNumber2 = plate[4].isDigit();
        bool isNumber3 = plate[5].isDigit();
        bool isLetter3 = plate[7].isLetter() && plate [7].isUpper();
        bool isLetter4 = plate[8].isLetter() && plate [8].isUpper();

        isValid = isLetter1 && isLetter2 && isNumber1 && isNumber2 && isNumber3 && isLetter3 && isLetter4;

        if(isValid)
        {
            QString folderCertification = "C:/Users/lenovo/Documents" + plate;
            QDir folder(folderCertification);

            if (!folder.exists())
            {
                if(folder.mkpath(folderCertification))
                {
                   QString fileCertification = folderCertification + "/certificat.txt";
                   std::string fileCertificationStr = fileCertification.toStdString();
                   std::ofstream file(fileCertificationStr);
                   if (file.is_open())
                    {
                        file << plate.toStdString();
                        file.close();
                    }
                }
            }
            ui->Message1->setText( "La plaque" " " +plate+ " est conforme aux exigences française");
            ui->Message2->setText("");
           // ui->textEdit->clear();
        }
        else
        {
            ui->Message1->setText( "La plaque " " " +plate+ " n'est pas conforme aux exigences française");
            ui->Message2->setText("");
        }
    }

    else if(plate.length () == 10 && plate[4] == ' ' && plate [7] == ' ')
    {
        bool isNumber1 = plate[0].isDigit();
        bool isNumber2 = plate[1].isDigit();
        bool isNumber3 = plate[2].isDigit();
        bool isNumber4 = plate[3].isDigit();
        bool isLetter1 = plate[5].isLetter() && plate[5].isUpper();
        bool isLetter2 = plate[6].isLetter() && plate[6].isUpper();
        bool isNumber5 = plate[8].isDigit();
        bool isNumber6 = plate[9].isDigit();

        bool isDepartementValid = (plate.mid(8, 2).toInt() >= 1 && plate.mid(8, 2).toInt() <= 70);


        isValid = isNumber1 && isNumber2 && isNumber3 && isNumber4 && isLetter1 && isLetter2 && isNumber5 && isNumber6 && isDepartementValid;
        if(isValid)
        {
            ui->Message1->setText( "La plaque" " " +plate+ " est conforme aux exigences française");
            ui->Message2->setText("Il s'agit d'une ancienne plaque");
            ui->textEdit->clear();
        }
        else
        {
            ui->Message1->setText( "La plaque " " " +plate+ "n'est pas conforme aux exigences française");
        }
    }

    QTimer::singleShot(5000, this, [this]() {
        ui->Message1->clear();
        ui->Message2->clear();
    });

}
