//
// Created by Łukasz Kolarz on 20/11/2019.
//

#include "Root.h"
#include <iostream>
#include <string>
#include "Student.h"
#include "Book.h"
#include <fstream>

using namespace std;

void Root::newStudent() {
    system("clear");
    string name, surname, index;
    cout << "Enter student parameters:\n\n";
    cout << "Name:\n";
    getline(cin, name);
    cout << "Surname:\n";
    getline(cin, surname);
    cout << "Index:\n";
    getline(cin, index);
    Student fresh(name, surname, index);
    cout << "New record has been entered!\n";
    fresh.newDisplay();
}

void Root::newBook() {
    system("clear");
    string title, ISBN, pages;
    cout << "Enter book parameters:\n\n";
    cout << "Title:\n";
    getline(cin, title);
    cout << "ISBN code:\n";
    getline(cin, ISBN);
    cout << "Amount of pages:\n";
    getline(cin, pages);
    Book fresh(title, ISBN, stoi(pages));
    cout << "New record has been entered!\n";
}

void Root::deleteStudent() {
    system("clear");
    string index;
    cout << "Enter student's index you want to delete\n";
    getline(cin, index);
    ifstream file;
    ofstream temp;

    file.open("Students.csv", ios::in);
    temp.open("Temp.csv", ios::out);
    string row;
    string line, tempLine;
    while (getline(file, line)) {
        tempLine = line;
        row = tempLine.substr(0, tempLine.find(','));
        if (row == index) {
            continue;
        }
        temp << line << "\n";

    }
    file.close();
    temp.close();
    remove("Students.csv");
    rename("Temp.csv", "Students.csv");
    cout << "Student has been deleted\n";
}

void Root::deleteBook() {
    system("clear");
    string title;
    cout << "Enter book's title you want to delete\n";
    getline(cin, title);
    ifstream file;
    ofstream temp;

    file.open("Books.csv", ios::in);
    temp.open("Temp.csv", ios::out);
    string row;
    string line, tempLine;
    while (getline(file, line)) {
        tempLine = line;
        row = tempLine.substr(0, tempLine.find(','));
        if (row == title) {
            continue;
        }
        temp << line << "\n";

    }
    file.close();
    temp.close();
    remove("Books.csv");
    rename("Temp.csv", "Books.csv");
    cout << "Book has been deleted\n";
}



