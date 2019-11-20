#include <iostream>
#include "src/Student.h"
#include "src/Book.h"
#include <string>


using namespace std;

int main() {
    bool exit = true;
    while(exit) {
        cout << "Welcome in our LIBRARY SYSTEM\n"
             << "Please LOG IN\n"
             << "Your index:\n";
        string index;
        getline(cin, index);


        if (index != "root") {
            Student user;
            while (true) {
                Student trial(index);
                if (!trial.getIndex().empty()) {
                    user = trial;
                    break;
                }
                cout << "Your index:\n";
                getline(cin, index);
            }
            bool logout = true;
            while (logout) {
                int choice = 0;
                while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 &&
                       choice != 7) {
                    cout << "\nWhat do you want to do?\n\n"
                         << "[1] Borrow a book\n"
                         << "[2] Return a book\n"
                         << "[3] Reserve a book\n"
                         << "[4] Pay your balance\n"
                         << "[5] Display user data\n"
                         << "[6] Logout\n"
                         << "[7] EXIT\n"
                         << "\nEnter your choice:\n";
                    cin >> choice;
                    cin.ignore();

                }

                switch (choice) {
                    case 1:
                        user.borrow();
                        break;
                    case 2:
                        user.giveBack();
                        break;
                    case 3:
                        user.reserve();
                        break;
                    case 4:
                        user.payPLN();
                        break;
                    case 5:
                        user.display();
                        break;
                    case 6:
                        logout = false;
                        break;
                    case 7:
                        logout = false;
                        exit = false;
                        break;
                    default:
                        cout << "Wrong number\n";
                }
            }
        }
    }
    return 0;
}
