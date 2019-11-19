#include <iostream>
#include "src/Student.h"
#include "src/Book.h"

#include <ctime>
#include <string>


std::string sprawdz_godzine()
{
    time_t czas;
    struct tm * data;
    char godzina[80];
    time (&czas);
    data =localtime (&czas);
    strftime (godzina,80,"%d.%m.%Y, %H:%M",data);
    return godzina;
}




int main() {

    //Book ksiazka("Pan Samochodzik i Templariusze", "200", 250);
    //Book ksiega("Wladca Pierscieni");
    //ksiega.setTime();
   // ksiega.setAvailable(true);
   // ksiega.setReservation(false);
    //ksiega.changesUpload();




    //Student pierwszy("2137");
    //pierwszy.display();

   //cout << g(1,11,96) - g(28,10,96);
    Student osoba("234");
    //osoba.borrow();
    osoba.giveBack();
    //cout <<  subDate("1.8.2019.");


    return 0;
}
