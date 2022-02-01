#include "../resourseFiles/Tree.h"
class Grammer{
    LinkedList *LL;
    char nodeName[50];
    Tree* tree;
public:
    Grammer();
    Grammer(LinkedList*);
    ~Grammer();
    bool readList(LinkedList*);
    Tree* STMT(void);
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
    bool VARCHAR(void);
    bool SCM_ATTR_LIST(void);
    bool EXP(void);
    bool OR(void);
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
    bool FINAL(void);
    bool terminal(char*);
    bool terminal(int);
};
Grammer::Grammer(LinkedList *arg)
{
    readList(arg);
    strcpy(nodeName,"STMT\0");
    tree = new Tree(nodeName);
}
Grammer::Grammer()
{
    strcpy(nodeName,"STMT");
    tree = new Tree(nodeName);
}
Grammer::~Grammer()
{
    this->LL->deleteList();
    delete tree;
}
bool Grammer::readList(LinkedList *arg)
{
    this->LL = arg;
}
 Tree* Grammer::STMT(void)
 {
     tree->destroyTree();
     if(terminal(id) && terminal(".\0") && OPTR() && terminal(";\0"))
     {
         return tree;
     }
     else
     {
         tree->deleteCurDir();
         return NULL;
     }

 }
 bool Grammer::OPTR(void)
 {
     strcpy(nodeName,"OPTR\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
     if(READ() || APPEND() || REPLACE() || REMOVE() || SCHEME() )
     {
         tree->previousDir();
         return 1;
     }
     else
     {
        tree->deleteCurDir();
        return 0;
     }
 }
 bool Grammer::READ(void)
 {
     strcpy(nodeName,"READ\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
     if(terminal("read\0") && terminal("(\0") && R_ATTR() && terminal(")\0") && READ_() )
     {
         tree->previousDir();
         return 1;
     }
     else
     {
        tree->deleteCurDir();
        return 0;
     }
 }
 bool Grammer::R_ATTR(void)
 {
     strcpy(nodeName,"R_ATTR\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
     if(terminal(id))
     {
         if( R_ATTR_LIST())
         {
             tree->previousDir();
         return 1;
         }
         else
         {
             tree->deleteCurDir();
             return 0;
         }
     }

     else
     {
        terminal("\0");
        tree->previousDir();
        return 1;
     }
 }
 bool Grammer::R_ATTR_LIST(void)
 {
     strcpy(nodeName,"R_ATTR_LIST\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
     if(terminal(",\0"))
     {
         if(terminal(id) && R_ATTR_LIST())
         {
             tree->previousDir();
             return 1;
         }

         else
        {
            tree->deleteCurDir();
            return 0;
        }
     }
     else
     {
        terminal("\0");
        tree->previousDir();
        return 1;
     }

 }
 bool Grammer::READ_(void)
 {
     strcpy(nodeName,"READ_\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
     if(terminal(".\0"))
        if(READ__())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
     else
     {
         terminal("\0");
         tree->previousDir();
         return 1;
     }

 }
 bool Grammer::READ__(void)
 {
     strcpy(nodeName,"READ__\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
     if(FILTER() && READ___())
     {
         tree->previousDir();
         return 1;
     }
     else if(SORT())
     {
         tree->previousDir();
         return 1;
     }

     else
     {
         tree->deleteCurDir();
         return 0;
     }

 }
 bool Grammer::READ___(void)
 {
     strcpy(nodeName,"READ___\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
     if(terminal(".\0"))
        if(SORT())
        {
            tree->previousDir();
            return 1;
        }

        else
        {
            tree->deleteCurDir();
            return 0;
        }

    else
    {
        terminal("\0");
        tree->previousDir();
        return 1;
    }

 }
 bool Grammer::FILTER(void)
 {
     strcpy(nodeName,"FILTER\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
     if(terminal("filter\0") && terminal("(\0") && EXP() && terminal(")\0"))
     {
         tree->previousDir();
         return 1;
     }
     else
     {
         tree->deleteCurDir();
         return 0;
     }

 }
bool Grammer::SORT(void)
{
    strcpy(nodeName,"SORT\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("sort\0") && terminal("(\0") && terminal(id) && terminal(",\0") && terminal(kw) && terminal(")\0"))
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }

}
bool Grammer::APPEND(void)
{
    strcpy(nodeName,"APPEND\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("append\0") && terminal("(\0") && APPD_VAL() && terminal(")\0") && APPEND_() )
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }

}
bool Grammer::APPEND_(void)
{
    strcpy(nodeName,"APPEND_\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal(".\0"))
    {
        if(terminal("(\0") && R_ATTR() && terminal(")\0"))
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else
    {
        terminal("\0");
        tree->previousDir();
        return  1;
    }

}
bool Grammer::APPD_VAL(void)
{
    strcpy(nodeName,"APPD_VAL\0");
    tree->addChild(nodeName);
    tree->changeDir(nodeName);
    if(DATATYPE() && APPD_VAL_LIST())
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::APPD_VAL_LIST(void)
{
    strcpy(nodeName,"APPD_VAL_LIST\0");
    tree->addChild(nodeName);
    tree->changeDir(nodeName);
    if(terminal(",\0"))
    {
        if(APPD_VAL())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else
    {
        terminal("\0");
        tree->previousDir();
        return 1;
    }

}
bool Grammer::REPLACE(void)
{
    strcpy(nodeName,"REPLACE\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("replace\0") && terminal("(\0") && R_ATTR() && terminal(")\0") && terminal(".\0")
       && terminal("(\0") && APPD_VAL() && terminal(")\0") && terminal(".\0") && FILTER() )
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::DATATYPE(void)
{
    strcpy(nodeName,"DATATYPE\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal(num) || terminal(str))
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::REMOVE(void)
{
    strcpy(nodeName,"REMOVE\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("remove\0") && terminal("(\0") && EXP() && terminal(")\0"))
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }

}
bool Grammer::SCHEME(void)
{
    strcpy(nodeName,"SCHEME\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("scheme\0") && terminal("(\0") && SCM_ATTR() && terminal(")\0") && terminal(".\0")
       && terminal("(\0") && terminal(id) && terminal(")\0"))
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::SCM_ATTR(void)
{
    strcpy(nodeName,"SCM_ATTR\0");
    tree->addChild(nodeName);
    tree->changeDir(nodeName);
    if(terminal(id) && SCM_ATTR_TYPE() && SCM_ATTR_LIST())
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::SCM_ATTR_TYPE(void)
{
    strcpy(nodeName,"SCM_ATTR_TYPE\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("num\0") || terminal("datetime\0") || VARCHAR() )
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }

}
bool Grammer::VARCHAR(void)
{
    strcpy(nodeName,"VARCHAR\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("varchar\0") && terminal("(\0") && terminal(num) && terminal(")\0"))
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::SCM_ATTR_LIST(void)
{
    strcpy(nodeName,"SCM_ATTR_LIST\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal(",\0"))
        if(SCM_ATTR())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    else
    {
        terminal("\0");
        tree->previousDir();
        return 1;
    }

}
bool Grammer::EXP(void)
{
    //if((terminal(id) && terminal("=\0") && EXP() )|| OR())
    strcpy(nodeName,"EXP\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(AND() && OR())
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }

}
bool Grammer::OR(void)
{
    strcpy(nodeName,"OR\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("|\0"))
    {
        if(AND() && OR())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else
    {
        terminal("\0");
        tree->previousDir();
        return 1;
    }

}
bool Grammer::AND(void)
{
    strcpy(nodeName,"AND\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(EQULITY() && AND_())
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::AND_(void)
{
    strcpy(nodeName,"AND_\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("&\0"))
    {
        if(AND() && AND_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else
    {
        terminal("\0");
        tree->previousDir();
        return 1;
    }
}
bool Grammer::EQULITY(void)
{
    strcpy(nodeName,"EQULITY\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(RELATION() && EQULITY_())
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::EQULITY_(void)
{
    strcpy(nodeName,"EQULITY_\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("!=\0") )
    {
        if(EQULITY() && EQULITY_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else if(terminal("==\0"))
    {
        if(EQULITY() && EQULITY_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else
    {
        terminal("\0");
        tree->previousDir();
        return 1;
    }

}
bool Grammer::RELATION(void)
{
    strcpy(nodeName,"RELATION\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(ADDITIVE() && RELATION_())
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::RELATION_(void)
{
    strcpy(nodeName,"RELATION_\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("<\0"))
    {
        if(RELATION() && RELATION_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else if(terminal(">\0"))
    {
        if(RELATION() && RELATION_())
        {
            tree->previousDir();
            return 1;
        }

        else
        {
            tree->deleteCurDir();
            return 0;
        }

    }
    else if(terminal("<=\0"))
    {
        if(RELATION() && RELATION_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else if(terminal(">=\0"))
    {
        if(RELATION() && RELATION_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else
    {
        terminal("\0");
        tree->previousDir();
        return 1;
    }

}
bool Grammer::ADDITIVE(void)
{
    strcpy(nodeName,"ADDITIVE\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(MULTIPLICATIVE() && ADDITIVE_())
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::ADDITIVE_(void)
{
    strcpy(nodeName,"ADDITIVE_\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("+\0"))
    {
        if(ADDITIVE() && ADDITIVE_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else if(terminal("-\0"))
    {
        if(ADDITIVE() && ADDITIVE_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else
    {
        terminal("\0");
        tree->previousDir();
        return 1;
    }
}
bool Grammer::MULTIPLICATIVE(void)
{
    strcpy(nodeName,"MULTIPLICATIVE\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(UNARY() && MULTIPLICATIVE_())
    {
        tree->previousDir();
        return 1;
    }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::MULTIPLICATIVE_(void)
{
    strcpy(nodeName,"MULTIPLICATIVE_\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("*\0"))
    {
        if(MULTIPLICATIVE() && MULTIPLICATIVE_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else if(terminal("/\0"))
    {
        if(MULTIPLICATIVE() && MULTIPLICATIVE_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else if(terminal("%\0"))
    {
        if(MULTIPLICATIVE() && MULTIPLICATIVE_())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else
    {
        terminal("\0");
        tree->previousDir();
        return 1;
    }
}
bool Grammer::UNARY(void)
{
    strcpy(nodeName,"UNARY\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal("!\0"))
    {
        if(FINAL())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else if(terminal("++\0"))
    {
        if(FINAL())
        {
            tree->previousDir();
            return 1;
        }

        else
        {
            tree->deleteCurDir();
            return 0;
        }

    }
    else if(terminal("--\0"))
    {
        if(FINAL())
        {
            tree->previousDir();
            return 1;
        }

        else
        {
            tree->deleteCurDir();
            return 0;
        }
    }
    else
    {
        if(FINAL())
        {
            tree->previousDir();
            return 1;
        }
        else
        {
            tree->deleteCurDir();
            return 0;
        }

    }
}
bool Grammer::FINAL(void)
{
    strcpy(nodeName,"FINAL\0");
     tree->addChild(nodeName);
     tree->changeDir(nodeName);
    if(terminal(id)
       ||DATATYPE()
       || (terminal("(\0") && EXP() && terminal(")\0")))
       {
           tree->previousDir();
           return 1;
       }
    else
    {
        tree->deleteCurDir();
        return 0;
    }
}
bool Grammer::terminal(char str[])
{
    if(!strcmp(str,"\0"))
    {
       tree->addChild("\0");
       return 1;
    }
    if(!this->LL->isEnd())
    {
        if(!strcmp(this->LL->getCurLexem(),str))
        {
            tree->addChild(LL->getCurLexem());
            this->LL->nextNode();
            return 1;
        }
        else
        {
            return 0;
        }

    }
    else
    {
//        cout << "(END)";
        return 0;
    }

}
bool Grammer::terminal(int tokEnum)
{
    //cout << "t2";
    if(!this->LL->isEnd())
    {
        //cout << "<" << tokEnum << "," << this->LL.getCurLexUnit() << ">";
        if(this->LL->getCurLexUnit() == tokEnum)
        {
            if(tokEnum == str)
            {
                char temp[50];
                strcpy(temp,"'\0");
                strcat(temp,LL->getCurLexem());
                strcat(temp,"'\0");
                tree->addChild(temp);
            }
            else
            {
                tree->addChild(LL->getCurLexem());
            }

            this->LL->nextNode();
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
//        cout << "(END)";
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
