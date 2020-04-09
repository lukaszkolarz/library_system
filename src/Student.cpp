//
// Created by Łukasz Kolarz on 05/11/2019.
//

#include "Student.h"
#include "Book.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "Date.h"

Student::Student(string Name, string Surname, string Index) {
    name = move(Name);
    surname = move(Surname);
    index = move(Index);
    rentBookNumber = "0";
    reservedBookNumber = "0";
    toPay = 0;

    fstream file;
    file.open("Students.csv", ios::out | ios::app); //open file for write & seek end of the stream b4 each write
        if (file.is_open()) {
            file << index << ","
                 << surname << ","
                 << name << ","
                 << rentBookNumber << ","
                 << toPay << ","
                 << reservedBookNumber << ",\n";
            file.close();
            schangesUpload();
        }
        else{
            cout << "Can't add an user\n";
        }

}

Student::Student(const string& Index) {
    fstream file;
    file.open("Students.csv", ios::in);
    vector<string> row;
    string line, temp;
    int count = 0;

    while(getline(file, line)) {
        row.clear();
        while (line.find(',') != string::npos) {
            row.push_back(line.substr(0, line.find(',')));
            line.erase(0, line.find(',') + 1);
        }
        if(row[0] == Index){
            count = 1;
            index = row[0];
            surname = row[1];
            name = row[2];
            rentBookNumber = row[3];
            toPay = stof(row[4]);
            reservedBookNumber = row[5];
            break;
        }
    }
    file.close();
    if(count == 0){
        cout << "Student not found!\nTry again\n\n";
    }
}

void Student::display(){
    system("clear");
    if(!index.empty()) {
        cout << "Your name: " << name << "\n"
             << "Your surname: " << surname << "\n"
             << "Your index " << index << "\n"
             << "Your debit " << toPay << " PLN\n";
        if(rentBookNumber != "0") {
            Book rented("", rentBookNumber);
            cout << "\nBook you rented: " << rented.getTitle() << "\n"
                 << "ISBN: " << rentBookNumber << "\n"
                 << "You rented it: " << rented.getTimeBorrowed().substr(0, (string::npos-1)) << "\n";

        }
        if(reservedBookNumber != "0") {
            Book reserved("", reservedBookNumber);
            cout << "\nBook you reserved: " << reserved.getTitle() << "\n"
                 << "ISBN: " << reservedBookNumber << "\n";

        }
    }
}

void Student::newDisplay() {
    system("clear");
    if (!index.empty()) {
        cout << "New student's name: " << name << "\n"
             << "New student's surname: " << surname << "\n"
             << "New student's index " << index << "\n"
             << "New student's debit " << toPay << " PLN\n";
    }
    else{
        cout<< "Adding student error :(\n" ;
    }
}

void Student::borrow() {
    system("clear");
    if(stol(rentBookNumber) == 0) {
        string title;
        cout << "Please, insert title of the book you want to BORROW:\n";
        title = "\n";
        getline(cin, title);
        Book borrowed(title);
        if (borrowed.isAvailable() && !borrowed.isReserved()) {
            cout << "You are borrowing \""
                 << title
                 << "\"\n";
            borrowed.setTime();
            borrowed.setAvailable(false);
            rentBookNumber = borrowed.getISBN();
            borrowed.changesUpload();
            schangesUpload();
        } else if(borrowed.isAvailable() && borrowed.isReserved() && reservedBookNumber == borrowed.getISBN()){
            cout << "You are borrowing book reserved earlier \""
                 << title
                 << "\"\n";
            borrowed.setTime();
            borrowed.setAvailable(false);
            borrowed.setReservation(false);
            rentBookNumber = borrowed.getISBN();
            reservedBookNumber = "0";
            borrowed.setReservation(false);
            borrowed.changesUpload();
            schangesUpload();
        } else { cout << "Not available at the moment!\n"; }
    }
    else{
        cout << "Operation unavailable if you have borrowed something :/\n";
    }
}

void Student::giveBack() {
    system("clear");
    if(stol(rentBookNumber) != 0){
        Book borrowed("",rentBookNumber);
        cout << "You are giving back \""
             << borrowed.getTitle()
             << "\""
             << endl;
        rentBookNumber = "0";
        borrowed.setAvailable(true);

        if(subDate(borrowed.getTimeBorrowed()) > 15){
            toPay += (static_cast<float>((subDate(borrowed.getTimeBorrowed()) -15) * 0.2));
            cout << "Your book is overdue. You have to pay "
                 << (static_cast<float>((subDate(borrowed.getTimeBorrowed())-15) * 0.2))
                 << " PLN\n";
        }
        cout << "Your balance is " << toPay << " PLN" << endl;
        if(toPay > 0) {
            int pay = 0;
            while (pay != 1) {
                cout << "Do you want to pay?\n"
                     << "[1] YES\n"
                     << "[2] NO\n";
                cin >> pay;
                if (pay == 1) {
                    payPLN();
                    cout << "Your balance is " << toPay << endl;
                }
                if (pay == 2) {
                    break;
                }

            }
        }

        borrowed.clearTime();
        borrowed.changesUpload();
        schangesUpload();

    }
    else{
        cout << "You have nothing to return :D\n";
        cout << "Your balance is " << toPay << endl;
    }
}

void Student::payPLN() {
    system("clear");
    toPay = 0;
    cout << "Debit paid succesfully!\n";
}

void Student::schangesUpload() {
    ifstream file;
    ofstream temp;
    file.open("Students.csv", ios::in);
    temp.open("Temp.csv", ios::out);
    vector<string> row;
    string line, tempLine;
    while (getline(file, line)) {
        row.clear();
        tempLine = line;
        while (tempLine.find(',') != -1) {
            row.push_back(tempLine.substr(0, tempLine.find(',')));
            tempLine.erase(0, tempLine.find(',') + 1);
        }
        if (row[0] == index) {
            row[4] = to_string(toPay);
            row[3] = rentBookNumber;
            row[5] = reservedBookNumber;
            line = row[0] + "," +        //index
                   row[1] + "," +        //name
                   row[2] + "," +        //surname
                   row[3] + "," +        //rented
                   row[4] + "," +        //toPay
                   row[5] + ",";         //reserved
        }
        temp << line << "\n";

    }
    file.close();
    temp.close();
    remove("Students.csv");
    rename("Temp.csv", "Students.csv");
}

void Student::reserve() {
    system("clear");
    cout << "Please, insert title of the book you want to RESERVE:\n";
    string title;
    getline(cin, title);
    Book reserved(title, "0");
    if(reserved.isAvailable() && !reserved.isReserved()){
        reservedBookNumber = reserved.getISBN();
        reserved.setReservation(true);
        cout << "RESERVATION CONFIRMED!\n";
    }else{
        cout << "Book is unavailable or reserved\n";
    }
    reserved.changesUpload();
    schangesUpload();
}

string Student::getIndex() {return index;}

Student::Student() {toPay = 0;}
