void skip_to_int()
{
    if (cin.fail()) { // we found something that wasn’t an integer
        cin.clear(); // we'd like to look at the characters
        for (char ch; cin>>ch; ) { // throw away non-digits
            if (isdigit(ch) || ch=="-") {
                cin.unget(); // put the digit back,
                // so that we can read the number
                return;
            }
        }
    }
    error("no input"); // eof or bad: give up
}

int get_int()
{
    int n = 0;
    while (true) {
        if (cin >> n) return n;
        cout << "Sorry, that was not a number; please try again\n";
        skip_to_int();
    }
}

int get_int(int low, int high, const string& greeting, const string& sorry)
{
    cout << greeting << ": [" << low << ':' << high << "]\n";

    while (true) {
        int n = get_int();
        if (low<=n && n<=high) return n;
        cout << sorry << ": [" << low << ':' << high << "]\n";
    }
}

int main() {
    int strength = get_int(1,10, "enter strength", "Not in range, try again");
    cout << "strength: " << strength << '\n';

    int altitude = get_int(0,50000,
            "Please enter altitude in feet",
            "Not in range, please try again");
    cout << "altitude: " << altitude << "f above sea level\n";
}
