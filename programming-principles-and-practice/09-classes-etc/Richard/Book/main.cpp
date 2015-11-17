//  #include "stdafx.h" 
#include <string>
#include <iostream>
//#include <regex>
#include <boost/regex.hpp>

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>


using namespace std;

class Book {
public:

    class BadISBNException {
    public:

        BadISBNException(string argBadNumber)
        : badNumber {
            argBadNumber
        }
        {
        }
        string badNumber;
    };

    Book(string argISBN, string argTitle, string argAuthor, string argCopyrightDate)
    : ISBN {
        argISBN
    }, title{argTitle}, author{argAuthor}, copyrightDate{argCopyrightDate}
    {
        //boost::regex ISBNPattern{ R"(^[[:digit:]]+-[[:digit:]]+-[[:digit:]]+-[[:digit:]]+-[[:digit:]]$)"};
        boost::regex ISBNPattern{R"(^\d+-\d+-\d+-\d+-\d$)"};
        //std::regex ISBNPattern{ R"(^\d+-\d+-\d+-\d]+-\d$()"};

        if (!boost::regex_match(argISBN, ISBNPattern)) {
            //if (! std::regex_match(argISBN, ISBNPattern)) {
            throw BadISBNException(argISBN);
        }
        checkin();
    }

    void printDetails() {
        cout << "Book:\n" << "ISBN:\t" << ISBN <<
                "\nTitle:\t" << title << "\nAuthor:\t" <<
                author << "\nCopyright Date:\t" << copyrightDate << '\n';
    }

    bool checkoutStatus() {
        return isCheckedOut;
    }

    void checkin() {
        isCheckedOut = false;
    }

    void checkout() {
        isCheckedOut = true;
    }

private:
    string ISBN;
    string title;
    string author;
    string copyrightDate;
    bool isCheckedOut;
};

void main2() {
    boost::regex ISBNPattern{R"(^\d+-\d+-\d+-\d+-\d$)"};
    string isbn1 = "978-0-321-99278-9";
    string isbn2 = "978-0-321-99278";
    cout << isbn1 << " regex_match " << boost::regex_match(isbn1, ISBNPattern) << '\n';
    cout << isbn2 << " regex_match " << boost::regex_match(isbn2, ISBNPattern) << '\n';
}

int main(int argc, char *argv[]) {
    try {
        Book firstBook{"1234-333-4444-333-5", "The Old Man and the Sea", "Ernest Hemingway", "1 Sep 1952"};
        firstBook.printDetails();
        Book secondBook{"344-123-3455-222-5", "A Farewell to Arms", "Ernest Hemingway", "1 Sep 1929"};
        secondBook.printDetails();

        cout << "Fist Book is checked out: " << firstBook.checkoutStatus() << "\n";
        firstBook.checkout();
        cout << "Fist Book is checked out: " << firstBook.checkoutStatus() << "\n";
        firstBook.checkin();
        cout << "Fist Book is checked out: " << firstBook.checkoutStatus() << "\n";

    } catch (Book::BadISBNException &e) {
        cout << "Ung\x81ltige ISBN Nummer: " << e.badNumber << "\n";
    } catch (...) {
        cout << "An unexpected error occurred!\n";
    }

    main2();


    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    window->setWindowTitle("Enter Your Age");

    QLabel *label = new QLabel("Hello There!");
    QLabel *label2 = new QLabel("<h2><i>Hello</i><font color=red>Qt!</font></h2>");

    label->show();
    label2->show();

    QPushButton *button = new QPushButton("Quit");
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
    button->show();

    QSpinBox *spinBox = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);
    spinBox->setRange(0, 130);
    slider->setRange(0, 130);
    QObject::connect(spinBox, SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)),
            spinBox, SLOT(setValue(int)));
    spinBox->setValue(42);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(label);
    verticalLayout->addWidget(label2);
    verticalLayout->addWidget(button);
    verticalLayout->addLayout(layout);

    window->setLayout(verticalLayout);
    window->show();


    return app.exec();


    //return 0;
}

