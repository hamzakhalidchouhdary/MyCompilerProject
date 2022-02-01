#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>

using namespace std;

class FileManager{
    ifstream file;
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
    bool isEnd();
    ~FileManager();
};

FileManager::FileManager()
{
//    file = '\0';
}
FileManager::FileManager(char addr[])
{
    openFile(addr);
}
bool FileManager::isEnd()
{
    return file.eof();
}
void FileManager::openFile(char addr[])
{
    if(!isOpen())
    {
        file.open(addr);
        if(!isOpen())
            cout << "FILE NO FOUND : " << addr << endl;
    }
    else
        cout << "ALREADY OPEN A FILE" << endl;
}
void FileManager::readLine(char data[],char limit)
{
    if(isOpen() && !isEnd())
    {
        char ch;
        int index = 0;
        do
        {
           file >> noskipws >> ch;
//           cout << ch;
//           switch(ch)
//           {
//
//            case (char)(92):
//                file >> noskipws >> ch;
//                switch(ch)
//                {
//                case 'n':
//                   ch = (char)(10);
//                   break;
//                case 'r':
//                   ch = (char)(13);
//                   break;
//                default:
//                    break;
//                }
//            case '\n':
//                data[index++] = (char)(10);
//                break;
//            case '\r':
//                data[index++] = (char)(13);
//                break;
//            case (char)(32):
//                data[index++] = (char)(32);
//                break;
//           default:
               data[index++] = ch;
//               break;
//           }

        }while(ch != limit && !isEnd());
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
        strcpy(data,"EMPTY\0");
    else
    {
        //getline(file,line);
        line.append("$\0");
        int i = 0,j=0;
        while(line[i] != '\0')
        {
//            switch(line[i])
//            {
//            case (char)(32):
//                data[j++] = (char)(32);
//                break;
//            case '\n':
//                data[j++] = (char)(10);
//               break;
//            default:
                data[j++] = line[i];
//                break;
//            }
            i++;
        }
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
int main()
{
    char data[200] = {'E','M','P','T','Y','\0'};
    char addr[100];
    strcpy(addr,"../../dataFiles/data.txt");
    FileManager file;
    file.openFile(addr);
    //cout << data << endl;
    file.readLine(data);
    cout << data;
    //strcpy(data,file.readLine());
    //cout << data;

    getch();
    return 0;
}
