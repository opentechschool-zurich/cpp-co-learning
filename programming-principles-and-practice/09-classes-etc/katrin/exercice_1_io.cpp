/*
* Introduction in classes
*/

#include <iostream>
#include <string>
#include <exception>
#include <vector>

using namespace std;



class Date{
		
	  public:
         Date() : y(0), m(0), d(0)  {
	     }		
      
	     Date(int i, int j, int k ) : y(i), m(j), d(k) 
		 {
	     }
	
	  private:
	    int y;
        int m;
	    int d;
		
	
	};


class Book {
	
	enum class  Books_state { in=1, out,lost,reserved };
	
	
	public: 
    Book(string isbn, string t, string a, Date cprght_d){
	   ISBN = isbn;
	   title = t;
	   author = a;
	   copyright_d = cprght_d;
	   status = Books_state::in;	
	}
	
	string get_title() {
	   return title;
	} 
	
	string get_author() {
	   return author;
	}
	
	string get_isbn() {
	   return ISBN;
	}
	
	Date get_copyright_date() {
	   return copyright_d;
	}
	
	void rent_out(){
	   status = Books_state::out;
	}
	
	void check_in(){
	   status = Books_state::in;
	}
	
	int get_book_status() {
       int st;
	   st = int( status);
	   return st;
	}
	
	private:
	string ISBN;
	string  title;
	string author;
	Date copyright_d;
	Books_state status;
	
	
	
     		
};

//------------------------------------------------------------------------------

int main()
{
	string current_author;
	Date d_frisch = Date{1980, 12, 8};
    Book frisch = Book{"a12e5", "Andorra", "Frisch", d_frisch};
	current_author = frisch.get_author();
	
	cout << "the current author is:" << current_author << "\n\n";
	frisch.rent_out();
	cout << "the current bookstate is:" << frisch.get_book_status() << "\n\n";
	
	
}


