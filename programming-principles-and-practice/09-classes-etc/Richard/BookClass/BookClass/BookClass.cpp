// Chapter 9 Exercise 5
/*
5. This exercise and the next few require you to design and implement
a Book class, such as you can imagine as part of software for a library. 
Class Book should have members for the ISBN, title, author, and copyright 
date. Also store data on whether or not the book is checked out. Create 
functions for returning those data values. Create functions for checking 
a book in and out. Do simple validation of data entered into a Book; for 
example, accept ISBNs only of the form n-n-n-x where n is an integer and x 
is a digit or a letter. Store an ISBN as a string.
*/

#include "stdafx.h"
#include <string>
#include <iostream>
#include <regex>

using namespace std;

class Book {
public:
	class BadISBNException {
	public:
		BadISBNException(string argBadNumber)
			: badNumber{ argBadNumber } {}
		string badNumber;
	};

	Book(string argISBN, string argTitle, string argAuthor, string argCopyrightDate)
		: ISBN{ argISBN }, title{ argTitle }, author{ argAuthor }, copyrightDate{ argCopyrightDate }
	{
		std::regex regex( R"(^\d+-\d+-\d+-\d+-\d$)");
		if (!std::regex_match(argISBN, regex)) {
			throw BadISBNException(argISBN);
		}
		checkin();
	}
	void printDetails() {
		cout << "Book:\n" << "ISBN:\t" << ISBN <<
			"\nTitle:\t" << title << "\nAuthor:\t" <<
			author << "\nCopyright Date:\t" << copyrightDate << '\n';
	}

	string getAuthor() {
		return author;
	}

	string getISBN() {
		return ISBN;
	}
	string getTitle() {
		return title;
	}
	string getCopyrightDate() {
		return copyrightDate;
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

int main()
{
	try {
		vector<Book> library;

		Book firstBook{ "1234-333-4444-333-5", "The Old Man and the Sea", "Ernest Hemingway", "12 Dec 1954" };
		firstBook.printDetails();
		library.push_back(firstBook);

		Book secondBook{ "344-123-3455-222-5", "A Farewell to Arms", "Ernest Hemingway", "2 Mar 1929" };
		secondBook.printDetails();
		

		//cout << "Fist Book is checked out: " << firstBook.checkoutStatus() << "\n";
		firstBook.checkout();
		cout << "Fist Book is checked out: " << firstBook.checkoutStatus() << "\n";
		//firstBook.checkin();
		//cout << "Fist Book is checked out: " << firstBook.checkoutStatus() << "\n";
		

		library.push_back(secondBook);

		cout << "Books availabe in my library:\n";
		//for (Book b : library) {
		for (int i = 0; i < library.size(); ++i) {
			Book b = library[i];
			if (!b.checkoutStatus()) {
				cout << i << ": Author: " << b.getAuthor() << "\tTitle: " << b.getTitle() << "\tCopyright Date: " << b.getCopyrightDate() << '\n';
			}
		}
		
	}
	catch (Book::BadISBNException &e) {
		cout << "Ung\x81ltige ISBN Nummer: " << e.badNumber << "\n";
	}
	catch (...) {
		cout << "An unexpected error occurred!\n";
	}

	return 0;
}

