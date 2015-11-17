#include <iostream>

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
class Date {
    public:
        class Invalid { }; // to throw as exception

        Date(int y, Month m, int d); // check for valid date and initialize

        int day() const { return d; }
        Month month() const { return m; }
        int year() const { return y; }

        // modifying operations:
    private:
        int y;
        Month m;
        int d;
};

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
}

void Date::next_day() { return d+1; } // OK

void f(Date d)
{
    int nd = d.d+1; // error: Date::d is private
    // . . .
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
        << ',' << d.month()
        << ',' << d.day() << ')';
}

istream& operator>>(istream& is, Date& dd)
{
    int y, m, d;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if (!is) return is;
    if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') { // oops: format error
        is.clear(ios_base::failbit);
        return is;
    }
    dd = Date{y,Date::Month(m),d}; // update dd
    return is;
}
