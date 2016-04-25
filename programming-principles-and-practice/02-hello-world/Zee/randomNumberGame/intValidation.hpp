// check if a input is a integer

#ifndef intValidation_h
#define intValidation_h

int getInt() {
            int x = 0;
            while (!(cin >> x)) {
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "U need to type a number. Try again!\n";
            }
            return x;
        }


#endif /* intValidation_h */