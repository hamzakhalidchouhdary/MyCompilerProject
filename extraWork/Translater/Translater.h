using namespace std;
char Statmnt[300];
class Translater
{
    Tree *tree;
    void RPL_ATTR(LinkedList*);
    void RPL_ATTR_LIST(LinkedList*);
    void RPL_VAL(LinkedList*);
    void RPL_VAL_LIST(LinkedList*);
public:
    Translater(Tree*);
    ~Translater();
    char* STMT();
    void OPTR(char*);
    void READ(char*);
    void APPEND(char*);
    void APPEND_();
    void APPD_VAL();
    void APPD_VAL_LIST();
    void REPLACE(char*);
    void REMOVE(char*);
    void SCHEME(char*);
    void SCM_ATTR();
    void SCM_ATTR_TYPE();
    void SCM_ATTR_LIST();
    void VARCHAR();
    void R_ATTR();
    void R_ATTR_LIST();
    void READ_();
    void READ__();
    void READ___();
    void FILTER();
    void SORT();
    void EXP();
    void OR();
    void AND();
    void AND_();
    void EQULITY();
    void EQULITY_();
    void RELATION();
    void RELATION_();
    void ADDITIVE();
    void ADDITIVE_();
    void MULTIPLICATIVE();
    void MULTIPLICATIVE_();
    void UNARY();
    void FINAL();
    void DATATYPE();
    char* ID();
    void PUN(char*);
};
char* Translater::STMT()
{
    char data[50],first[50];
    strcpy(data,ID()); // read ID data
    PUN(".\0"); // read .
    OPTR(data); // call OPTR to process operation
    PUN(";\0"); // read ;
    return Statmnt;
}
void Translater::OPTR(char* table)
{
    tree->changeDir("OPTR\0"); // move to OPTR
    tree->moveToFirst(); // move to first node
    char data[50];
    strcpy(data,tree->readData());
    tree->previousDir();
    if(!strcmp(data,"READ\0"))
    {
        READ(table);
    }
    else if(!strcmp(data,"APPEND\0"))
    {
        APPEND(table);
    }
    else if(!strcmp(data,"REPLACE\0"))
    {
        REPLACE(table);
    }
    else if(!strcmp(data,"REMOVE\0"))
    {
        tree->changeDir(data);
        REMOVE(table);
    }
    else if(!strcmp(data,"SCHEME\0"))
    {
        SCHEME(table);
    }
    else
    {
        ;
    }
    tree->deleteCurDir();
}
void Translater::REPLACE(char* table)
{
    tree->changeDir("REPLACE\0");
//    tree->treverseCurDir();
    LinkedList rplAttr, rplVal;
    RPL_VAL(&rplVal);
//    rplVal.treavarseList();
    RPL_ATTR(&rplAttr);
//    rplAttr.treavarseList();
    char temp[50];
    strcpy(temp,"UPDATE \0");
    strcpy(Statmnt,temp);
    strcat(Statmnt,table);
    strcpy(temp," SET \0");
    strcat(Statmnt,temp);
    while(!rplAttr.isEnd())
    {
        strcpy(temp,rplAttr.getCurLexem());
        strcat(Statmnt,temp);
        strcpy(temp,"=\0");
        strcat(Statmnt,temp);
        strcpy(temp,rplVal.getCurLexem());
        strcat(Statmnt,temp);
        rplAttr.nextNode();
        rplVal.nextNode();
        if(!rplAttr.isEnd())
        {
            strcpy(temp,", \0");
            strcat(Statmnt,temp);
        }
    }
//    tree->treverseCurDir();
    FILTER();
    tree->deleteCurDir();
}
void Translater::RPL_VAL(LinkedList* TL)
{
    char temp[50];
    tree->changeDir("APPD_VAL\0");
//    tree->treverseCurDir();
    tree->moveToFirst();
//    tree->treverseCurDir();
    strcpy(temp,ID());
//    cout << temp << endl;
    tree->previousDir();
//    tree->treverseCurDir();
    TL->insertNode(temp,0);
    RPL_VAL_LIST(TL);
    tree->deleteCurDir();
//    tree->treverseCurDir();
}
void Translater::RPL_VAL_LIST(LinkedList* TL)
{
    char temp[50];
    tree->changeDir("APPD_VAL_LIST\0");
//    tree->treverseCurDir();
    strcpy(temp,ID());
//    cout << temp;
    if(strcmp(temp,"\0"))
    {
        RPL_VAL(TL);
    }
    tree->deleteCurDir();
//    tree->treverseCurDir();
}
void Translater::RPL_ATTR(LinkedList* TL)
{
    char temp[50];
    tree->changeDir("R_ATTR\0");
//    tree->treverseCurDir();
    strcpy(temp,ID());
    TL->insertNode(temp,0);
    RPL_ATTR_LIST(TL);
    tree->deleteCurDir();
//    tree->treverseCurDir();
}
void Translater::RPL_ATTR_LIST(LinkedList* TL)
{
    char temp[50];
    tree->changeDir("R_ATTR_LIST\0");
//    tree->treverseCurDir();
    strcpy(temp,ID());
//    cout << temp;
    if(strcmp(temp,"\0"))
    {
        strcpy(temp,ID());
        TL->insertNode(temp,0);
        RPL_ATTR_LIST(TL);
    }
    tree->deleteCurDir();
//    tree->treverseCurDir();
}
void Translater::APPEND(char* table)
{
    char temp[20];
    tree->changeDir("APPEND\0");
    ID(); // read append
    strcpy(temp,"INSERT INTO \0");
    strcpy(Statmnt,temp);
    strcat(Statmnt,table);
    APPEND_(); // expand attributes
    PUN("(\0"); // read (
    strcpy(temp," VALUES(\0");
    strcat(Statmnt,temp);
    APPD_VAL(); // expand values
    strcpy(temp,")\0");
    strcat(Statmnt,temp);
    PUN(")\0"); // read )
    tree->deleteCurDir();
}
void Translater::APPD_VAL()
{
    tree->changeDir("APPD_VAL\0");
    char temp[20];
    DATATYPE(); // read value
    APPD_VAL_LIST(); // expand value list
    tree->deleteCurDir();
}
void Translater::APPD_VAL_LIST()
{
    char temp[10];
    tree->changeDir("APPD_VAL_LIST\0");
    strcpy(temp,ID());
    if(strcmp(temp,"\0")) // list not null
    {
        strcat(Statmnt,temp);
        APPD_VAL();
    }
    tree->deleteCurDir();
}
void Translater::APPEND_()
{
    char temp[5];
    tree->changeDir("APPEND_\0");
    strcpy(temp,ID());
    if(strcmp(temp,"\0"))// attributes find
    {
        PUN("(\0");
        strcpy(temp,"(\0");
        strcat(Statmnt,temp);
        R_ATTR();
        PUN(")\0");
        strcpy(temp,")\0");
        strcat(Statmnt,temp);
    }
    tree->deleteCurDir();
}
void Translater::SCHEME(char* table)
{
    char temp[50];
    tree->changeDir("SCHEME\0");
//    tree->treverseCurDir();
    strcpy(temp,"CREATE TABLE \0");
    strcpy(Statmnt,temp); // append operation
    strcat(Statmnt,table); // append table name
    ID(); // read scheme
    strcpy(temp,ID());// read (
    strcat(Statmnt,temp); // append (
    SCM_ATTR(); // read attributes
    PUN(")\0"); // read )
    PUN(".\0"); // read .
    strcpy(temp, " PRIMARY KEY \0"); // Constraint
    strcat(Statmnt,temp); // append Constraint
    PUN("(\0");
    strcpy(temp,"(\0"); // read (
    strcat(Statmnt,temp); // append (
    strcpy(temp,ID()); // read id
    strcat(Statmnt,temp); // append id
    strcpy(temp,")\0"); // read )
    PUN(")\0");
    strcat(Statmnt,temp); // append )
    strcat(Statmnt,temp); // append )
    tree->deleteCurDir();
}
void Translater::SCM_ATTR()
{
    char temp[50];
    tree->changeDir("SCM_ATTR\0");
    strcpy(temp,ID()); // read attributes
    strcat(Statmnt,temp); // append attributes
    strcpy(temp," \0");
    strcat(Statmnt,temp); // append space
    SCM_ATTR_TYPE(); // expand attribute type
    SCM_ATTR_LIST(); // expand attribute list
    tree->deleteCurDir();
}
void Translater::SCM_ATTR_TYPE()
{
    char temp[50];
    tree->changeDir("SCM_ATTR_TYPE\0");
    tree->moveToFirst();
    strcpy(temp,tree->readData());
    tree->previousDir();
    if(strcmp(temp,"VARCHAR\0")) // not VARCHAR
    {
        if(!strcmp(temp,"num\0"))
        {
            strcpy(temp,"int\0");
        }
        strcat(Statmnt,temp);
    }
    else //VARCHAR
    {
        VARCHAR();
    }
    tree->deleteCurDir();
}
void Translater::VARCHAR()
{
    char temp[20];
    tree->changeDir("VARCHAR\0");
    strcpy(temp,ID()); // read varchar
    strcat(Statmnt,temp); // append varchar
    strcpy(temp,ID()); // read (
    strcat(Statmnt,temp); //append (
    strcpy(temp,ID()); // read num
    strcat(Statmnt,temp); // append num
    strcpy(temp,ID()); // read )
    strcat(Statmnt,temp); // append )
    tree->deleteCurDir();
}
void Translater::SCM_ATTR_LIST()
{
    char temp[20];
    tree->changeDir("SCM_ATTR_LIST\0");
    strcpy(temp,ID());
    if(strcmp(temp,"\0")) // not null (find ,)
    {
        strcat(Statmnt,temp); // append ,
        SCM_ATTR();
    }
    tree->deleteCurDir();
}
void Translater::REMOVE(char* table)
{
    char temp[10];
    strcpy(temp,"DELETE FROM \0");
    tree->changeDir("REMOVE\0");
    ID(); // read remove kw
    ID(); // read (
    strcpy(Statmnt,temp);
    strcat(Statmnt,table);
    strcpy(temp," WHERE \0");
    strcat(Statmnt,temp);
    EXP(); // expand EXP
    ID(); // read )
    tree->deleteCurDir();
}
void Translater::READ(char* table)
{
//    cout << "READ.." << endl;
    char OPR[50], SP[2], first[50],temp[15];
    strcpy(OPR,"SELECT\0");
    strcpy(SP," \0");
    strcpy(Statmnt,OPR); // copy operation to statement
    strcat(Statmnt,SP); // append space
    strcpy(temp,"FROM\0");
    tree->changeDir("READ\0");
    ID(); // read read node
    PUN("(\0"); // read (
    R_ATTR(); // read R_ATTR
    PUN(")\0"); // read )
    strcat(Statmnt,SP); // append space
    strcat(Statmnt,temp); // append FROM
    strcat(Statmnt,SP); //append space
    strcat(Statmnt,table); // append table name
    READ_(); // read READ_
//    tree->deleteCurDir(); // delete cur dir and move to root
    //cout << "READ" << endl;
}
void Translater::R_ATTR()
{
//    cout << "R_ATTR.." << endl;
    char para[50];
    tree->changeDir("R_ATTR\0");
//    tree->treverseCurDir();
    strcpy(para,ID()); // read parameters
    if(strcmp(para,"\0")) // parameters find
    {
        strcat(Statmnt,para);
        R_ATTR_LIST();
    }
    else // no parameters found
    {
        strcpy(para,"*\0");
        strcat(Statmnt,para);
    }
    tree->deleteCurDir();

}
void Translater::R_ATTR_LIST()
{
//    cout << "R_ATTR_LIST.." << endl;
    char para[50];
    tree->changeDir("R_ATTR_LIST\0");
    strcpy(para,ID());
    if(strcmp(para,"\0")) // parameters find
    {
//        tree->treverseCurDir();
        strcat(Statmnt,para); // append ,
        strcpy(para,ID()); // read parameters
        strcat(Statmnt,para);// append parameter
        R_ATTR_LIST(); // read next child dir
    }
    tree->deleteCurDir();
//    cout << "R_ATTR_LIST" << endl;

}
void Translater::READ_()
{
//    cout << "READ_\0" << endl;
    char first[50];
    tree->changeDir("READ_\0");
    strcpy(first,ID());
    if(strcmp(first,"\0")) // obtain first node
    {
//        tree->treverseCurDir();
        PUN(".\0");
        READ__(); // call READ__
    }
    tree->deleteCurDir(); // move to root
}
void Translater::READ__()
{
    char first[50];
    tree->changeDir("READ__\0");
    tree->moveToFirst();
    strcpy(first,tree->readData());
    tree->previousDir();
    if(!strcmp(first,"FILTER\0")) // first node is FILTER
    {
        FILTER(); // call filter
        READ___(); // call READ___
    }
    else // first node is sort
    {
        SORT(); // move to sort
    }
    tree->deleteCurDir();
}
void Translater::SORT()
{
    char data[50],temp[20];
    tree->changeDir("SORT\0");
    ID();
    PUN("(\0");
    strcpy(data,ID()); // read id
    strcpy(temp," ORDER BY \0"); // append sort operation
    strcat(Statmnt,temp); // append ORDER BY
    strcat(Statmnt,data); // append attribute
    PUN(",\0");
    strcpy(temp," \0"); // copy space
    strcat(Statmnt,temp); // append space
    strcpy(data,ID()); // read sort order
    strcat(Statmnt,data); // append sort order
    tree->deleteCurDir(); // move up
}
void Translater::READ___()
{
    char first[50];
    tree->changeDir("READ___\0");
    strcpy(first,ID());
    if(strcmp(first,"\0")) // READ___ found
    {
        PUN(".\0");
        SORT();
    }
    tree->deleteCurDir();
}

void Translater::FILTER()
{
    char temp[50];
    tree->changeDir("FILTER\0");
    //tree->treverseCurDir();
    strcpy(temp," WHERE \0");
    strcat(Statmnt,temp);
    ID(); // read filter
    PUN("(\0"); //read (
    EXP(); // read EXP
    PUN(")\0"); // read )
    tree->deleteCurDir();
}
void Translater::EXP()
{
    tree->changeDir("EXP\0");
//    tree->treverseCurDir();
    AND();
    OR();
    tree->deleteCurDir();
}
void Translater::OR()
{
    char first[50],temp[5];
    tree->changeDir("OR\0");
//    tree->treverseCurDir();
    strcpy(first,ID());
    if(strcmp(first,"\0")) // OR found
    {
        PUN("|\0");
        strcpy(temp," OR \0");
        strcat(Statmnt,temp);
        AND();
        OR();
    }
    tree->deleteCurDir();

}
void Translater::AND()
{
    char first[50];
    tree->changeDir("AND\0");
//    tree->treverseCurDir();
    EQULITY(); // call EQULITY
    AND_();
    tree->deleteCurDir();
}
void Translater::AND_()
{
    char temp[50];
    tree->changeDir("AND_\0");
//    tree->treverseCurDir();
    strcpy(temp,ID());
    if(strcmp(temp,"\0")) // & node found
    {
        PUN("&\0"); // delete & node
        strcpy(temp," AND \0");
        strcat(Statmnt,temp);// append AND in Statmnt
        AND(); // call AND
        AND_(); // call AND_
    }
    tree->deleteCurDir();
}
void Translater::EQULITY()
{
    tree->changeDir("EQULITY\0");
//    tree->treverseCurDir();
    RELATION(); // call RELATION
    EQULITY_(); //call EQULITY__
    tree->deleteCurDir();
}
void Translater::EQULITY_()
{
    char first[5];
    tree->changeDir("EQULITY_\0");
//    tree->treverseCurDir();
    strcpy(first,ID());
    if(strcmp(first,"\0")) // not null
    {
        if(!strcmp(first,"==\0")) // == obtain
        {
            strcpy(first,"=\0");
            strcat(Statmnt,first); // append =
        }
        else
        {
            strcpy(first,"!=\0");
            strcat(Statmnt,first); // append !=
        }
        EQULITY();
        EQULITY_();
    }
    tree->deleteCurDir();
}
void Translater::RELATION()
{
    char first[50],temp[5];
    tree->changeDir("RELATION\0");
//    tree->treverseCurDir();
    ADDITIVE(); // call ADD
    RELATION_();
    tree->deleteCurDir();

}
void Translater::RELATION_()
{
    char first[50];
    tree->changeDir("RELATION_\0");
//    tree->treverseCurDir();
    strcpy(first,ID());
    if(strcmp(first,"\0")) // not null
    {
        strcat(Statmnt,first);
        RELATION();
        RELATION_();
    }
    tree->deleteCurDir();
}
void Translater::ADDITIVE()
{
    tree->changeDir("ADDITIVE\0");
//    tree->treverseCurDir();
    MULTIPLICATIVE();
    ADDITIVE_();
    tree->deleteCurDir();
}
void Translater::ADDITIVE_()
{
    char first[50];
    tree->changeDir("ADDITIVE_\0");
//    tree->treverseCurDir();
    strcpy(first,ID());
    if(strcmp(first,"\0")) // not null
    {
        strcat(Statmnt,first);
        ADDITIVE();
        ADDITIVE_();
    }
    tree->deleteCurDir();
}
void Translater::MULTIPLICATIVE()
{
    tree->changeDir("MULTIPLICATIVE\0");
//    tree->treverseCurDir();
    UNARY();
    MULTIPLICATIVE_();
    tree->deleteCurDir();
}
void Translater::MULTIPLICATIVE_()
{
    char first[50];
    tree->changeDir("MULTIPLICATIVE_\0");
//    tree->treverseCurDir();
    strcpy(first,ID());
    if(strcmp(first,"\0")) // not null
    {
        strcat(Statmnt,first);
        MULTIPLICATIVE();
        MULTIPLICATIVE_();
    }
    tree->deleteCurDir();
}
void Translater::UNARY()
{
    char first[50];
    tree->changeDir("UNARY\0");
//    tree->treverseCurDir();
    tree->moveToFirst();
    strcpy(first,tree->readData());
    if(strcmp(first,"FINAL\0")) // if first is not FINAL
    {
        strcat(Statmnt,first);
    }
    FINAL();
    tree->deleteCurDir();
}
void Translater::FINAL()
{
    char first[50];
    tree->changeDir("FINAL\0");
//    tree->treverseCurDir();
    tree->moveToFirst();
    strcpy(first,tree->readData());
    tree->previousDir();
    if(!strcmp(first,"(\0")) // first node is (
    {
        EXP();
        PUN(")\0");
    }
    else if(!strcmp(first,"DATATYPE\0")) // first node is DATATYPE
    {
        DATATYPE();
    }
    else
    {
        strcat(Statmnt,first);
    }
    tree->deleteCurDir();
}
void Translater::DATATYPE()
{
    char first[50];
    tree->changeDir("DATATYPE\0");
//    tree->treverseCurDir();
    strcpy(first,ID());
    strcat(Statmnt,first);
    tree->deleteCurDir();
}
void Translater::PUN(char* p)
{
    tree->deleteDir(p);
}
char* Translater::ID()
{
    tree->moveToFirst();
    char data[50];
    strcpy(data,tree->readData());
    tree->deleteCurDir();
    return data;
}
Translater::Translater(Tree* t)
{
//    cout << "CONSTURCTOR..." << endl;
    tree = t;
//    cout << "CONSTURCTOR" << endl;
}
Translater::~Translater()
{
    tree->destroyTree();
}
