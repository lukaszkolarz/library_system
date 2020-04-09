#include <iostream>
#include "src/Student.h"
#include "src/Book.h"
#include "src/Root.h"
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    bool exit = true;
    while(exit) {
        system("clear");
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
                            system("clear");
                            logout = false;
                            break;
                        case 7:
                            system("clear");
                            logout = false;
                            exit = false;
                            break;
                        default:
                            system("clear");
                            cout << "Wrong number\n\n";
                    }

                }


            }
        }
        if(index == "root") {
            Root admin;
            bool logout = true;
            while (logout) {
                int choice = 0;
                while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6) {
                    cout << "\nWhat do you want to do?\n\n"
                         << "[1] New student\n"
                         << "[2] New book\n"
                         << "[3] Delete student\n"
                         << "[4] Delete book\n"
                         << "[5] Logout\n"
                         << "[6] EXIT\n"
                         << "\nEnter your choice:\n";
                    cin >> choice;
                    cin.ignore();

                    switch (choice) {
                        case 1:
                            admin.newStudent();
                            break;
                        case 2:
                            admin.newBook();
                            break;
                        case 3:
                            admin.deleteStudent();
                            break;
                        case 4:
                            admin.deleteBook();
                            break;
                        case 5:
                            system("clear");
                            logout = false;
                            break;
                        case 6:
                            system("clear");
                            logout = false;
                            exit = false;
                            break;
                        default:
                            system("clear");
                            cout << "Wrong number!\n\n";
                    }
                }
            }
        }
    }
    return 0;
}
