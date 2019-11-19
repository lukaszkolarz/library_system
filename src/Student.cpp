//
// Created by Łukasz Kolarz on 05/11/2019.
//

#include "Student.h"
#include "Book.h"
#include <fstream>
#include <iostream>
#include <vector>


Student::Student(string Name, string Surname, string Index) {
    name = move(Name);
    surname = move(Surname);
    index = move(Index);
    rentBookNumber = "0";
    reservedBookNumber = "0";

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
        }
        else{
            cout << "Can't add an user\n";
        }

}

Student::Student(string Index) {
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
        cout << "Student not found!\nAdd new one\n\n";
        string Name, Surname;
        cout << "Insert your first name:\n";
        cin >> Name;
        cout << "Insert your surname:\n";
        cin >> Surname;
        Student(Name, Surname, Index);
    }
}

void Student::display(){
    if(!index.empty()) {
        cout << index << "\n"
             << surname << "\n"
             << name << "\n"
             << rentBookNumber << "\n"
             << reservedBookNumber << "\n"
             << toPay << "\n";
    }
}

void Student::borrow() {
    string title;
    cout << "Please, insert title of the book you want to borrow:\n";
    getline(cin, title);
    cout << title;
    Book borrowed(title, "0");
    if (borrowed.isAvailable()) {
        borrowed.setTime();
        borrowed.setAvailable(false);
        rentBookNumber = borrowed.getISBN();
        borrowed.changesUpload();
        schangesUpload();
    }
    else{cout << "Not available at the moment!\n";}
}

void Student::giveBack() {
    //if(stol(rentBookNumber) != 0){
        cout << rentBookNumber << endl;
        Book borrowed("0",rentBookNumber);
        rentBookNumber = "0";
        borrowed.setAvailable(true);

        if(subDate(borrowed.getTimeBorrowed()) > 15){
            toPay += (static_cast<float>(subDate(borrowed.getTimeBorrowed()) * 0.2));
            cout << "Your book is overdue. You have to pay "
                 << (static_cast<float>(subDate(borrowed.getTimeBorrowed()) * 0.2))
                 << "PLN\n";
        }
        cout << "Your balance is " << toPay << endl;
        if(toPay > 0) {
            int pay = 0;
            while (pay != 1 && pay != 2) {
            cout << "Do you want to pay?\n"
                 << "[1] YES\n"
                 << "[2] NO\n";
            cin >> pay;
        }
           if (pay == 1){
               payPLN();
           }
        }

        borrowed.clearTime();
        borrowed.changesUpload();
        schangesUpload();

    //}
}

void Student::payPLN() {
    toPay = 0;
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
                   row[3] + "," +        //toPay
                   row[4] + "," +        //rented
                   row[5] + ",";         //reserved
        }
        temp << line << "\n";

    }
    file.close();
    temp.close();
    remove("Students.csv");
    rename("Temp.csv", "Students.csv");
}
