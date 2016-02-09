#include <iostream>
#include <string>

using namespace std;

class Link {
public:
    string value;

    Link(const string &v, Link* p =nullptr, Link* s = nullptr)
    :value{v}, prev{p}, succ{s}
    {
    }
    Link* insert(Link* p, Link* n);
    // Link* add(Link *n);
    Link* erase();
    // Link* find(const string& s) const;

    // Link* advance(int n) const;

    Link* next() const {return succ;};
    Link* previous() const {return prev;};
private:
    Link* prev;
    Link* succ;
};

Link* Link::insert(Link* p, Link* n)
{
    if (n == nullptr) return p;
    if (p == nullptr) return n;
    n->succ = p;
    if (p->prev) {
        p->prev->succ = n;
    }
    n->prev = p->prev;
    p->prev = n;
    return n;
}

/**
 * modify the links and return the removed item
 */
Link* Link::erase()
{
    if (prev != nullptr) {
        prev->succ = succ;
    }
    if (succ != nullptr) {
        succ->prev = prev;
    }
    prev = nullptr;
    succ = nullptr;
    return this;
}

int main() {
    Link* norse_gods = new Link{"Thor"};
    cout << norse_gods << endl;
    norse_gods = norse_gods->insert(norse_gods, new Link{"Odin"});
    cout << norse_gods << endl;
    norse_gods = norse_gods->insert(norse_gods, new Link{"Freia"});
    Link* odin  = norse_gods->next();
    odin->erase();
    cout << odin << endl;
    delete(odin);
    cout << "freia prev" << norse_gods->previous() << endl;
    cout << "freia next" << norse_gods->next() << endl;
    Link* freia  = norse_gods;
    freia->erase();
    delete(freia);
    cout << "freia" << freia << endl;
    cout << "freia next" << freia->next() << endl;
    cout << "norse_gods" << norse_gods << endl;
    cout << "norse_gods next" << norse_gods->next() << endl;

    return 0;
}
