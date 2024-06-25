#ifndef Database_logic
#define Database_logic
#include<iostream>
#include<vector>
#include<map>
#include<iomanip>
#include<fstream>
#include"Database.h"
using std::string,std::vector;
//main logic for storing the data into the table and manipulating it as specified in the menu hub.
class DatabaseLanguage:virtual public DATABASE
{
private:
    int count=0;
    struct Node{
        string value1,value2,value3;
        Node*next;
        Node*prev;
    };
    Node*head;
    Node*tail;
    Node*temp;
    bool flag; //flag for sorting
    string name;
    
public:
    DatabaseLanguage(string dbname):DATABASE(dbname),head(new Node()),temp(head){
        this->dbname=dbname;
        head->next=NULL;
        head->prev=NULL;
    }
    //destructor for freeing up the memory created by linked list.
    ~DatabaseLanguage(){delete[]head;delete temp; delete tail;}
    void InputColumn();
    void SetFlag()
    {
        char c;
        std::cout<<"Are you want your data to be sorted or not"<<std::endl;
        std::cout<<"press Y/N :";
        std::cin>>c;
        if(std::toupper(c)=='Y')
        {
            flag=true;
            sortReference();
        }
        else
        flag=false;
    }
   void ShowTable();
    void search(string data,string column)
    {
        std::transform(column.begin(),column.end(),column.begin(),::_toupper);
        while(refsorting.find(column)==refsorting.end())
        {
            std::cout<<"Inappropriate column\n";
            std::cout<<"Enter the column-name :";
            std::cin>>column;
            std::transform(column.begin(),column.end(),column.begin(),::_toupper);
            std::cout<<"Enter data-";
            std::cin>>data;
            
        }
        if(head->next!=NULL){
            Node *current=current=search_ref(data,column);
            if(current!=NULL)
            {
                std::cout<<"The information is--"<<std::endl;
                std::cout<<column_name[0]<<std::setw(30-column_name[0].length())<<'|'<<column_name[1]<<std::setw(30-column_name[1].length())<<"|"<<column_name[2]<<std::endl;
                std::cout<<current->value1<<std::setw(30-current->value1.length())<<'|'<<current->value2<<std::setw(30-current->value2.length())<<'|'<<current->value3<<std::endl;
            }
            else
            std::cout<<"No any data on the database existed.."<<std::endl;
            current=NULL;
            delete current;
        }
        else
        std::cout<<"No data on the table."<<std::endl;
       
    }

    void Delete();
    int Size()
    {
        return count;
    }
    void Close();
    void Modify_table();
private:
    void EmptyField() //empty for input variable:: as data is taken input by an array of string which is reusable on every new data it is made empty
    {
        for(int i=0;i<3;i++)
        {
            columnsData[i]=" ";
        }
    }
    void InsertoLinkedlist(Node *current);
    void sort(Node *);
    void sortReference();
    //logic for searching and uses the help of map refsorting which is the reference for sorting and indexing for input at particular condition
    struct Node* search_ref(string data,string column)
    {
        
        Node *first=head->next;
        Node * last=tail;
        
        std::transform(data.begin(),data.end(),data.begin(),::toupper);
        switch(refsorting[column])
        {
            case 0:
                while(first!=last->next)
                {
                    if(first->value1==data)
                    return first;
                    else if(last->value1==data)
                    return last;
                    if(first==last)
                    break;
                    first=first->next;
                    last=last->prev;
                    
                }
                break;
            case 1:
               
                while(first!=last->next)
                {
                    
                    if(first->value2==data)
                    return first;
                    else if(last->value2==data)
                    return last;
                    if(first==last)
                    break;
                    first=first->next;
                    last=last->prev;
                    
                }
                break;

            case 2:
                 
                while(first!=last->next )
                {
                    
                    if(first->value3==data)
                    return first;
                    else if(last->value3==data)
                    return last;
                    if (first==last)
                    break;
                    first=first->next;
                    last=last->prev;
                    
                }
                break;
        }
        if(head->next->value1==data || head->next->value2==data || head->next->value3==data)
        {
            return head->next;
        }
        
        return NULL;
    }

    void Modify(string &data,string &column)
    {
        std::cout<<"Enter the column-name: ";
        std::cin>>column;
        std::transform(column.begin(),column.end(),column.begin(),::toupper);
        while(refsorting.find(column)==refsorting.end())
        {
            std::cout<<"Inappropriate column---"<<std::endl;
            std::cout<<"Enter the column-name: ";
            std::cin>>column;
             std::transform(column.begin(),column.end(),column.begin(),::toupper);
        }
        std::cout<<"Enter the data: ";
        std::cin>>data;
        std::transform(data.begin(),data.end(),data.begin(),::toupper);
        while(!CheckDatatype(data,column))
        {
            std::cout<<"illegal data--"<<std::endl;
            std::cout<<"Data type for "<<column<<" is "<<ColumnDatatype[column]<<std::endl;
            std::cout<<"Enter the data :";
            std::cin>>data;
            std::transform(data.begin(),data.end(),data.begin(),::toupper);
        }
    }

};

void DatabaseLanguage::InputColumn()
{
    DATABASE::InputColumn();
    Node* current=new Node();
    current->value1=columnsData[0];current->value2=columnsData[1];current->value3=columnsData[2];
    EmptyField();
    InsertoLinkedlist(current);
}
//implementation and insertion of data in a doubly linked list.
void DatabaseLanguage::InsertoLinkedlist(Node *current)
{
    if(flag==false || head->next==NULL)
    {
        
        temp->next=current;
        current->prev=temp;
        temp=current;
        current->next=NULL;
        tail=temp;
        ++count;
    }
    else
      sort(current);  
}
//sorting on the basic of the column specified.
void DatabaseLanguage::sort(Node* current)
{
    
    ++count;
    tail=temp;
    Node*compare=temp;
    temp=compare;

     switch(refsorting[name])
    {
        case 0:
           
            while(current->value1<compare->value1)
            {
                compare=compare->prev;
            }
            if(compare->next!=NULL)
            {
                compare->next->prev=current;
            }
            current->next=compare->next;
            current->prev=compare;
            compare->next=current;
            if(current->next==NULL)
            {
                temp=current;
            }
            break;
        case 1:
            while(current->value2<compare->value2)
            {
                compare=compare->prev;
            }
            if(compare->next!=NULL)
            {
                compare->next->prev=current;
            }
            current->next=compare->next;
            current->prev=compare;
            compare->next=current;
            if(current->next==NULL)
            {
                temp=current;
            }
            break;
        case 2:
            while(current->value3<compare->value3)
            {
                compare=compare->prev;
            }
            if(compare->next!=NULL)
            {
                compare->next->prev=current;
            }
            current->next=compare->next;
            current->prev=compare;
            compare->next=current;
            if(current->next==NULL)
            {
                temp=current;
            }
            break;

    }
    
}

void DatabaseLanguage::sortReference() //sort parameter logic
{
    std::cout<<"Reference column- ";
    std::cin>>name;
    std::transform(name.begin(),name.end(),name.begin(), ::toupper);
    while(refsorting.find(name)==refsorting.end())
    {
        std::cout<<"No such column created::"<<std::endl;
        std::cout<<"Enter appropriate column: ";
        std::cin>>name;
        std::transform(name.begin(),name.end(),name.begin(), ::toupper);
    }
    if(refsorting.find(name)!=refsorting.end())
    std::cout<<"column no "<<refsorting[name]+1<<" is the reference\n";

    
}
//traverser in a linked list.
void DatabaseLanguage::ShowTable()
{
    Node *current=head->next;
    std::cout<<std::endl;
    if(current==NULL)
    {
        std::cout<<"No data in the database"<<std::endl;
        return;
    }
    std::cout<<column_name[0]<<std::setw(30-column_name[0].length())<<'|'<<column_name[1]<<std::setw(30-column_name[1].length())<<'|'<<column_name[2]<<std::endl;
    while(current!=NULL)
    {
        std::cout<<current->value1<<std::setw(30-current->value1.length())<<'|'<<current->value2<<std::setw(30-current->value2.length())<<'|'<<current->value3<<std::endl;
        
        current=current->next;
        
    }
    current=NULL;
    delete current;
}
//deleting a node from a linked list which uses the logic of searching first for finding the data.
void DatabaseLanguage::Delete()
{
    string data,column;
    std::cout<<"Enter the column-";
    std::cin>>column;
    std::cout<<"Enter the data-";
    std::cin>>data;
    std::transform(column.begin(),column.end(),column.begin(),::_toupper);
        while(refsorting.find(column)==refsorting.end())
        {
            std::cout<<"Inappropriate column\n";
            std::cout<<"Enter the column-name :";
            std::cin>>column;
            std::transform(column.begin(),column.end(),column.begin(),::_toupper);
            std::cout<<"Enter data-";
            std::cin>>data;
            
        }
    Node *current=search_ref(data,column);
    
    if(head->next!=NULL)
    {
        if(current!=NULL)
        {
            Node* temp=current->prev;
            char ch;
            std::cout<<"The information is--"<<std::endl;
            std::cout<<column_name[0]<<std::setw(30-column_name[0].length())<<'|'<<column_name[1]<<std::setw(30-column_name[1].length())<<'|'<<column_name[2]<<std::endl;
            std::cout<<current->value1<<std::setw(30-current->value1.length())<<'|'<<current->value2<<std::setw(30-current->value2.length())<<'|'<<current->value3<<std::endl;
            std::cout<<"Are you sure you want to delete Y/N: ";
            std::cin>>ch;
            if(std::toupper(ch)=='Y')
            {
                if(current->next==NULL)
                {
                    current->prev->next=NULL;
                    this->temp=current->prev;
                }
                else{
                temp->next=current->next;
                current->next->prev=temp;
                }
                std::cout<<"Deleted successfully!!"<<std::endl;
                --count;
            }
            
        }
        else
        std::cout<<"No data found."<<std::endl;
    }
    else
    std::cout<<"Database empty"<<std::endl;
    current=NULL;
    delete current;
}
//modifying the value of the specified credential 
void DatabaseLanguage::Modify_table()
{
    std::string column,data;
    std::cout<<"\t\t-------SET-----"<<std::endl;
    Modify(data,column);
    std::cout<<"Condition:"<<std::endl;
    string column_ref,data_ref;
    Modify(data_ref,column_ref);
    struct Node* current=search_ref(data_ref,column_ref);
    if(head->next!=NULL)
    {
        if(current!=NULL)
        {
            switch(refsorting[column])
            {
                case 0:
                    current->value1=data;
                    break;
                case 1:
                    current->value2=data;
                    break;
                case 2:
                    current->value3=data;
            }
            system("cls");
            std::cout<<"Data modified successfully.\n";
        }
        else
        std::cout<<"No data existed.."<<std::endl;
    }
    else
    std::cout<<"No data in the database."<<std::endl;
    current=NULL;
    delete current;
}

void DatabaseLanguage::Close()
{
    char ch;
    std::cout<<"Are you want your data to write in a file Y/N -";
    std::cin>>ch;
    if(std::toupper(ch)=='Y')
    {
        std::string name;
        std::cout<<"Enter the name of the file -";
        std::cin>>name;
        std::ofstream fout(name+".txt");
        head=head->next;
        fout<<"                                                 "<<dbname<<std::endl;
        fout<<column_name[0]<<std::setw(30-column_name[0].length())<<'|'<<column_name[1]<<std::setw(30-column_name[1].length())<<'|'<<column_name[2]<<std::endl;
        while(head!=NULL)
        {
            fout<<head->value1<<std::setw(30-head->value1.length())<<'|'<<head->value2<<std::setw(30-head->value2.length())<<'|'<<head->value3<<std::endl;
            head=head->next;
        } 
        std::cout<<"The information have been saved in "<<name<<" file"<<std::endl;
    }
    else
    exit(0);
}

#endif