#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>

using namespace std;

class FileManager{
    ifstream file;
    bool fileOpenFlag;
public:
    FileManager();
    FileManager(char[]);
    void openFile(char[]);
    void closeFile();
    void readLine(char[], char);
    void readLine(char[]);
    char* readLine(char);
    char* readLine();
    bool isOpen();
    bool fileEnd();
    ~FileManager();
};

FileManager::FileManager()
{
    ;
}
FileManager::FileManager(char addr[])
{
    openFile(addr);
}
bool FileManager::fileEnd()
{
//    cout << "CALL FILE END \n"; // break point statement
//    cout << "EOF" << file.eof()<< endl; // break point statement
    return file.eof();
}
void FileManager::openFile(char addr[])
{
    if(!isOpen())
    {
        file.open(addr);
        if(!isOpen())
            cout << "FILE NOT FOUND : " <<"\"" << addr << "\"" << endl;
    }
    else
        cout << "ALREADY OPEN A FILE" << endl;
}
void FileManager::readLine(char data[],char limit)
{
    if(isOpen() && !fileEnd())
    {
        char ch;
        int index = 0;
        do
        {
           file >> noskipws >> ch;
//           switch(ch)
//           {
//
//            case (char)(92):
//                file >> ch;
//                switch(ch)
//                {
//                case 'n':
//                   ch = (char)(10);
//                   break;
//                case 'r':
//                   ch = (char)(13);
//                   break;
//                case '0':
//                   ch = (char)(0);
//                   break;
//                }
//           default:
               data[index++] = ch;
//               break;
//           }

        }while(ch != limit && !fileEnd());
        data[index++] = '$';
        data[index++] = '\0';
    }
    else
    {
        strcpy(data,"EMPTY\0");
    }
}
void FileManager::readLine(char data[])
{
    string line;
    if(!getline(file,line))
        line.append("EMPTY\0");
    else
    {
        line.append("$\0");
        int i = 0;
        do
        {
//            switch(line[i])
//            {
//            case (char)(32):
//            case '\n':
//               break;
//            default:
                data[i] = line[i];
//                break;
//            }
            i++;
        }while(line[i] != '\0');
        data[i] = '\0';
    }
}
char* FileManager::readLine()
{
    static char data[200] = {'E','M','P','T','Y','\0'};
    readLine(data);
    return data;
}
char* FileManager::readLine(char limit)
{
    static char data[200] = {'E','M','P','T','Y','\0'};
    readLine(data,limit);
    return data;
}
void FileManager::closeFile()
{
    file.close();
}
bool FileManager::isOpen()
{
    return file.is_open();
}
FileManager::~FileManager()
{
    closeFile();
}
