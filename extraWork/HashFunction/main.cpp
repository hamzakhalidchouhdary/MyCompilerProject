#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>

using namespace std;

class Hashing
{
    char HT[25][15];
    int hashCode(char*);
public:
    void intilizeHashTable();
    Hashing();
    bool isInTable(char*);
};
void Hashing::intilizeHashTable()
{
    /*00*/strcpy(HT[0],"scheme\0");//{'s','c','h','e','m','e','\0'};
    /*01*/strcpy(HT[1],"append\0");//{'a','p','p','e','n','d','\0'},
    /*02*/strcpy(HT[2],"\0");//{'\0'},
    /*03*/strcpy(HT[3],"\0");//{'\0'},
    /*04*/strcpy(HT[4],"filter\0");//{'f','i','l','t','e','r','\0'},
    /*05*/strcpy(HT[5],"remove\0");//{'r','e','m','o','v','e','\0'},
    /*06*/strcpy(HT[6],"\0");//{'\0'},
    /*07*/strcpy(HT[7],"read\0");//{'r','e','a','d','\0'},
    /*08*/strcpy(HT[8],"\0");//{'\0'},
    /*09*/strcpy(HT[9],"\0");//{'\0'},
    /*10*/strcpy(HT[10],"\0");//{'\0'},
    /*11*/strcpy(HT[11],"\0");//{'\0'},
    /*12*/strcpy(HT[12],"\0");//{'\0'},
    /*13*/strcpy(HT[13],"\0");//{'\0'},
    /*14*/strcpy(HT[14],"\0");//{'\0'},
    /*15*/strcpy(HT[15],"\0");//{'\0'},
    /*16*/strcpy(HT[16],"sort\0");//{'s','o','r','t','\0'},
    /*17*/strcpy(HT[17],"\0");//{'\0'},
    /*18*/strcpy(HT[18],"\0");//{'\0'},
    /*19*/strcpy(HT[19],"\0");//{'\0'},
    /*20*/strcpy(HT[20],"\0");//{'\0'},
    /*21*/strcpy(HT[21],"replace\0");//{'r','e','p','l','a','c','e','\0'},
    /*22*/strcpy(HT[22],"\0");//{'\0'},
    /*23*/strcpy(HT[23],"\0");//{'\0'},
    /*24*/strcpy(HT[24],"\0");//{'\0'}
}

Hashing::Hashing()
{
    intilizeHashTable();
}
int Hashing::hashCode(char str[])
{
    int sum = 0;
    for(int i=0;str[i];i++)
    {
        sum += (int)(str[i]);
    }
    return (sum/5)%25;
}
bool Hashing::isInTable(char str[])
{
    return !strcmp(HT[hashCode(str)],str);
}



int main()
{
    char word[15];
    cout << "Enter word : ";
    cin >> word;
    word[strlen(word)+1] = '\0';
    Hashing obj;
    if(obj.isInTable(word))
        cout << "KW";
    else
        cout << "ID";
    getch();
    return 0;
}
