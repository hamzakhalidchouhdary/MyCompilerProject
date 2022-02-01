#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

int main()
{
    ofstream file("ascii.txt");
    for(int i=0;i<128;i++)
    {
        file << (char)(i) << endl;
    }
    cout << "FILE CREATED";

    getch();
    return 0;
}
