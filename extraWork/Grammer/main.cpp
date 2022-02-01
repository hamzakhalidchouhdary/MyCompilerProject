#include <iostream>
#include <conio.h>


using namespace std;

enum lexicalUnits{id=0,kw,n,num,pun,str,err,op};

#include "../../resourseFiles/LinkedList.h"

LinkedList LL;

class Grammer{
public:
    Grammer();
    ~Grammer();
    bool STMT(void);
    bool OPTR(void);
    bool READ(void);
    bool READ_(void);
    bool READ__(void);
    bool READ___(void);
    bool R_ATTR(void);
    bool R_ATTR_LIST(void);
    bool FILTER(void);
    bool SORT(void);
    bool APPEND(void);
    bool APPEND_(void);
    bool APPD_VAL(void);
    bool APPD_VAL_LIST(void);
    bool REPLACE(void);
    bool DATATYPE(void);
    bool REMOVE(void);
    bool SCHEME(void);
    bool SCM_ATTR(void);
    bool SCM_ATTR_TYPE(void);
    bool SCM_ATTR_LIST(void);
    bool EXP(void);
    bool OR(void);
    bool OR_(void);
    bool AND(void);
    bool AND_(void);
    bool EQULITY(void);
    bool EQULITY_(void);
    bool RELATION(void);
    bool RELATION_(void);
    bool ADDITIVE(void);
    bool ADDITIVE_(void);
    bool MULTIPLICATIVE(void);
    bool MULTIPLICATIVE_(void);
    bool UNARY(void);
    bool UNARY_(void);
    bool FINAL(void);
    bool terminal(char*);
    bool terminal(int);
};
Grammer::Grammer()
{
    ;
}
Grammer::~Grammer()
{
    ;
}
 bool Grammer::STMT(void)
 {
     if(terminal(id) && terminal(".\0") && OPTR() && terminal(";\0"))
        return 1;
     else
        return 0;
 }
 bool Grammer::OPTR(void)
 {
     if(READ() || APPEND() || REPLACE() || REMOVE() || SCHEME())
        return 1;
     else
        return 0;
 }
 bool Grammer::READ(void)
 {
     if(terminal("read\0") && terminal("(\0") && R_ATTR() && terminal(")\0") && READ_() )
        return 1;
     else
        return 0;
 }
 bool Grammer::R_ATTR(void)
 {
     if(terminal(id) && R_ATTR_LIST())
        return 1;
     else
        return 0;
 }
 bool Grammer::R_ATTR_LIST(void)
 {
     if(terminal(",\0"))
     {
         if(R_ATTR())
            return 1;
         else
            return 0;
     }
     else
        return 1;
 }
 bool Grammer::READ_(void)
 {
     if(terminal(".\0"))
        if(READ__())
            return 1;
        else
            return 0;
     else
        return 1;
 }
 bool Grammer::READ__(void)
 {
     if(FILTER() && READ___())
        return 1;
     else if(SORT())
        return 1;
     else
        return 0;
 }
 bool Grammer::READ___(void)
 {
     if(terminal(".\0"))
        if(SORT())
            return 1;
        else
            return 0;
    else
        return 1;
 }
 bool Grammer::FILTER(void)
 {
     if(terminal("filter\0") && terminal("(\0") && EXP() && terminal(")\0"))
        return 1;
     else
        return 0;
 }
bool Grammer::SORT(void)
{
    if(terminal("sort\0") && terminal("(\0") && terminal(id) && terminal(",\0") && terminal(kw) && terminal(")\0"))
        return 1;
    else
        return 0;
}
bool Grammer::APPEND(void)
{
    if(terminal("append\0") && terminal("(\0") && APPD_VAL() && terminal(")\0") && APPEND_() )
        return 1;
    else
        return 0;
}
bool Grammer::APPEND_(void)
{
    if(terminal(".\0"))
    {
        if(terminal("(\0") && R_ATTR() && terminal(")\0"))
            return 1;
        else
            return 0;
    }
    else
        return  1;
}
bool Grammer::APPD_VAL(void)
{
    if(DATATYPE() && APPD_VAL_LIST())
        return 1;
    else
        return 0;
}
bool Grammer::APPD_VAL_LIST(void)
{
    if(terminal(",\0"))
    {
        if(APPD_VAL())
            return 1;
        else
            return 0;
    }
    else
        return 1;
}
bool Grammer::REPLACE(void)
{
    if(terminal("replace\0") && terminal("(\0") && APPD_VAL() && terminal(")\0") && terminal(".\0")
       && terminal("(\0") && R_ATTR() && terminal(")\0") && terminal(".\0") && FILTER() )
        return 1;
    else
        return 0;
}
bool Grammer::DATATYPE(void)
{
    if(terminal(num) || terminal(str))
        return 1;
    else
        return 0;
}
bool Grammer::REMOVE(void)
{
    if(terminal("remove\0") && terminal("(\0") && EXP() && terminal(")\0"))
        return 1;
    else
        return 0;
}
bool Grammer::SCHEME(void)
{
    if(terminal("scheme\0") && terminal("(\0") && SCM_ATTR() && terminal(")\0") && terminal(".\0")
       && terminal("(\0") && terminal(id) && terminal(")\0"))
        return 1;
    else
        return 0;
}
bool Grammer::SCM_ATTR(void)
{
    if(terminal(id) && SCM_ATTR_TYPE() && SCM_ATTR_LIST())
        return 1;
    else
        return 0;
}
bool Grammer::SCM_ATTR_TYPE(void)
{
    if(terminal("num\0") || terminal("str\0") )
        return 1;
    else
        return 0;
}
bool Grammer::SCM_ATTR_LIST(void)
{
    if(terminal(",\0"))
        if(SCM_ATTR())
            return 1;
        else
            return 0;
    else
        return 1;
}
bool Grammer::EXP(void)
{
    //if((terminal(id) && terminal("=\0") && EXP() )|| OR())
    if(AND() && OR_())
        return 1;
    else
        return 0;
}
bool Grammer::OR(void)
{
    if(AND() && OR_())
       return 1;
    else
        return 0;
}
bool Grammer::OR_(void)
{
    if(terminal("|\0"))
    {
        if(AND() && OR_())
            return 1;
        else
            return 0;
    }
    else
        return 1;
}
bool Grammer::AND(void)
{
    if(EQULITY() && AND_())
        return 1;
    else
        return 0;
}
bool Grammer::AND_(void)
{
    if(terminal("&\0"))
    {
        if(AND() && AND_())
            return 1;
        else
            return 0;
    }
    else
        return 1;
}
bool Grammer::EQULITY(void)
{
    if(RELATION() && EQULITY_())
        return 1;
    else
        return 0;
}
bool Grammer::EQULITY_(void)
{
    if(terminal("!=\0") )
    {
        if(EQULITY() && EQULITY_())
            return 1;
        else
            return 0;
    }
    else if(terminal("==\0"))
    {
        if(EQULITY() && EQULITY_())
            return 1;
        else
            return 0;
    }
    else
        return 1;
}
bool Grammer::RELATION(void)
{
    if(ADDITIVE() && RELATION_())
        return 1;
    else
        return 0;
}
bool Grammer::RELATION_(void)
{
    if(terminal("<\0"))
    {
        if(RELATION() && RELATION_())
            return 1;
        else
            return 0;
    }
    else if(terminal(">\0"))
    {
        if(RELATION() && RELATION_())
            return 1;
        else
            return 0;
    }
    else if(terminal("<=\0"))
    {
        if(RELATION() && RELATION_())
            return 1;
        else
            return 0;
    }
    else if(terminal(">=\0"))
    {
        if(RELATION() && RELATION_())
            return 1;
        else
            return 0;
    }
    else
        return 1;
}
bool Grammer::ADDITIVE(void)
{
    if(MULTIPLICATIVE() && ADDITIVE_())
        return 1;
    else
        return 0;
}
bool Grammer::ADDITIVE_(void)
{
    if(terminal("+\0"))
    {
        if(ADDITIVE() && ADDITIVE_())
            return 1;
        else
            return 0;
    }
    else if(terminal("-\0"))
    {
        if(ADDITIVE() && ADDITIVE_())
            return 1;
        else
            return 0;
    }
    else
        return 1;
}
bool Grammer::MULTIPLICATIVE(void)
{
    if(UNARY() && MULTIPLICATIVE_())
        return 1;
    else
        return 0;
}
bool Grammer::MULTIPLICATIVE_(void)
{
    if(terminal("*\0"))
    {
        if(MULTIPLICATIVE() && MULTIPLICATIVE_())
            return 1;
        else
            return 0;
    }
    else if(terminal("/\0"))
    {
        if(MULTIPLICATIVE() && MULTIPLICATIVE_())
            return 1;
        else
            return 0;
    }
    else if(terminal("%\0"))
    {
        if(MULTIPLICATIVE() && MULTIPLICATIVE_())
            return 1;
        else
            return 0;
    }
    else
        return 1;
}
bool Grammer::UNARY(void)
{
    if(FINAL() && UNARY_())
        return 1;
    else
        return 0;
}
bool Grammer::UNARY_(void)
{
    if(terminal("!\0"))
    {
        if(UNARY() && UNARY_())
            return 1;
        else
            return 0;
    }
    else if(terminal("++\0"))
    {
        if(UNARY() && UNARY_())
            return 1;
        else
            return 0;
    }
    else if(terminal("--\0"))
    {
        if(UNARY() && UNARY_())
            return 1;
        else
            return 0;
    }
    else
        return 1;
}
bool Grammer::FINAL(void)
{
    if(terminal(id)
       ||DATATYPE()
       || (terminal("(\0") && EXP() && terminal(")\0")))
           return 1;
    else
        return 0;
}
bool Grammer::terminal(char str[])
{
    //cout ;
    //if(LL.head != NULL)
    if(!strcmp(str,"\0"))
    {
       //LL.head = LL.head->link;
       cout << "(NULL)";
       return 1;
    }
    if(!LL.isEnd())
    {
        cout << "<" << str << "," << LL.getCurLexem() << ">";
        if(!strcmp(LL.getCurLexem(),str))
        {
           LL.nextNode();
           return 1;
        }
        else
        {
            //cout << endl << "EXPECTED " << str;
            return 0;
        }

    }
    else
    {
        cout << "(END)";
        return 0;
    }

}
bool Grammer::terminal(int tokEnum)
{
    //cout << "t2";
    if(!LL.isEnd())
    {
        cout << "<" << tokEnum << "," << LL.getCurLexUnit() << ">";
        if(LL.getCurLexUnit() == tokEnum)
        {
            LL.nextNode();
            return 1;
        }
        else
        {
            //cout << "EXPECT " << tokEnum << " BEFORE " << LL.head->lexem;
            return 0;
        }
    }
    else
    {
        cout << "(END)";
        return 0;
    }
    /*
        switch(LL.head->lexicalUnit)
        {
        case id:
        case num:
        case kw:
        case str:
            LL.head = LL.head->link;
            return 1;
        default:
            cout << "EXPECT ID BEFORE " << LL.head->lexem;
            return 0;
        }
        */


}

int main()
{
//    LL.insertNode("table\0",id);
//    LL.insertNode(".\0",pun);
//    LL.insertNode("scheme\0",kw);
//    LL.insertNode("(\0",pun);
//    LL.insertNode("id\0",id);
//    LL.insertNode("num\0",kw);
//    LL.insertNode(",\0",pun);
//    LL.insertNode("userName\0",id);
//    LL.insertNode("str\0",kw);
//    LL.insertNode(")\0",pun);
//    LL.insertNode(".\0",pun);
//    LL.insertNode("(\0",pun);
//    LL.insertNode("id\0",id);
//    LL.insertNode(")\0",pun);
//    LL.insertNode(";\0",pun);

    LL.insertNode("table\0",id);
    LL.insertNode(".\0",pun);
    LL.insertNode("remove\0",kw);
    LL.insertNode("(\0",pun);
    LL.insertNode("id\0",id);
  //  LL.insertNode("==\0",op);
    LL.insertNode("50\0",num);
    LL.insertNode(")\0",pun);
    LL.insertNode(";\0",pun);



    LL.treavarseList();
    cout << endl;
    Grammer syn;
    if(syn.STMT())
        cout << endl << "NO ERROR";
    else
        cout << endl<< "INVALID SYNTAX";



    getch();
    return 0;
}
//cout << "INPUT : ";
    //LL.treavarseList();
    //cout << endl << "OUTPUT : ";
//    Grammer syn;
//    if(syn.STMT())
//        cout << "SUCCESSED";
//    else
//        cout << "FAILED";
//    char str[3];
//    str[0] = '\0';
//    cout << !strcmp(str,"\0");
/*
LL.insertNode("table\0",id);
    LL.insertNode(".\0",pun);
    LL.insertNode("remove\0",kw);
    LL.insertNode("(\0",pun);
    LL.insertNode("id\0",id);
    LL.insertNode("==\0",op);
    LL.insertNode("50\0",num);
    LL.insertNode(")\0",pun);
    LL.insertNode(";\0",pun);
*/
/*
LL.insertNode("table\0",id);
    LL.insertNode(".\0",pun);
    LL.insertNode("read\0",kw);
    LL.insertNode("(\0",pun);
    LL.insertNode("id\0",id);
    LL.insertNode(",\0",pun);
    LL.insertNode("user_name\0",id);
    LL.insertNode(",\0",pun);
    LL.insertNode("DOB\0",id);
    LL.insertNode(")\0",pun);
    LL.insertNode(".\0",pun);
    LL.insertNode("filter\0",kw);
    LL.insertNode("(\0",pun);
    LL.insertNode("id\0",id);
    LL.insertNode("<\0",op);
    LL.insertNode("50\0",num);
    LL.insertNode(")\0",pun);
    LL.insertNode(".\0",pun);
    LL.insertNode("sort\0",kw);
    LL.insertNode("(\0",pun);
    LL.insertNode("id\0",id);
    LL.insertNode(",\0",pun);
    LL.insertNode("asc\0",kw);
    LL.insertNode(")\0",pun);
    LL.insertNode(";\0",pun);

*/
/*
LL.insertNode("table\0",id);
    LL.insertNode(".\0",pun);
    LL.insertNode("replace\0",kw);
    LL.insertNode("(\0",pun);
    LL.insertNode("3\0",num);
    LL.insertNode(",\0",pun);
    LL.insertNode("name\0",str);
    LL.insertNode(",\0",pun);
    LL.insertNode("13-Jan-1987\0",str);
    LL.insertNode(")\0",pun);
    LL.insertNode(".\0",pun);
    LL.insertNode("(\0",pun);
    LL.insertNode("id\0",id);
    LL.insertNode(",\0",pun);
    LL.insertNode("userName\0",id);
    LL.insertNode(",\0",pun);
    LL.insertNode("DOB\0",id);
    LL.insertNode(")\0",pun);
    LL.insertNode(".\0",pun);
    LL.insertNode("filter\0",kw);
    LL.insertNode("(\0",pun);
    LL.insertNode("id\0",id);
    LL.insertNode("<\0",op);
    LL.insertNode("50\0",num);
    LL.insertNode(")\0",pun);
    LL.insertNode(";\0",pun);
*/
/*
LL.insertNode("a\0",id);
    LL.insertNode("+\0",op);
    LL.insertNode("b\0",id);
    LL.insertNode("%\0",op);
    LL.insertNode("c\0",id);
    LL.insertNode("&\0",op);
    LL.insertNode("d\0",id);
    LL.insertNode("|\0",op);
    LL.insertNode("f\0",id);
    LL.insertNode("*\0",op);
    LL.insertNode("e\0",id);
*/
/*

*/
