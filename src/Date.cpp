//
// Created by Łukasz Kolarz on 06/01/2020.
//

#include "Date.h"
#include <vector>

int subDate(string date){

    vector<int> borrowed;
    while(date.find('.') != string::npos){
        borrowed.push_back(stoi(date.substr(0,date.find('.'))));
        date.erase(0, date.find('.') + 1);
    }

    time_t current;
    struct tm * data;
    char value[80];
    time (&current);
    data =localtime (&current);
    strftime(value,80,"%d.%m.%Y",data);
    string temp(value);
    temp += ".";
    vector<int> returned;
    while(temp.find('.') != string::npos){
        returned.push_back(stoi(temp.substr(0,temp.find('.'))));
        temp.erase(0, temp.find('.')+1);
    }


    return days(returned[0], returned[1], returned[2]) -
           days(borrowed[0], borrowed[1], borrowed[2]);

}


int days(int d, int m, int y) {
    m = (m + 9) % 12;
    y = y - m / 10;
    return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
}
