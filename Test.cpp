//layout
#include<iostream>
#include"Database_logic.h"
void Display(DatabaseLanguage& obj,int &n)
{
    obj.Display();
    std::cout<<"Enter the option- ";
    std::cin>>n;
    obj.option(n);
}
int main()
{
    std::string data,column;
    string dbname;
    std::cout<<"\t\t---------Welcome to my database program First thing first---------"<<std::endl;
    std::cout<<" \t\t.....Its a sample project which can handel a basic sQL command in practice ......."<<std::endl<<std::endl;
    std::cout<<"Enter your database name: ";
    std::cin>>dbname;
    DatabaseLanguage obj(dbname);
    std::cout<<"\t-------------TO GET STARTED----------------"<<std::endl;
    obj.CreateTable();
    obj.SetFlag();
    int n=0;
    while(n!=99)
    {
         Display(obj,n);
       
        switch (n)
        {
            
            case 1:case 2:
                system("cls");
                obj.InputColumn();
                break;
            case 3:
                system("cls");
                obj.ShowTable();
                break;
            case 4:
                
                std::cout<<"Enter the column to look for -";
                std::cin>>column;
                std::cout<<"Enter the data to search -";
                std::cin>>data;
                obj.search(data,column);
                break;
            case 5:
                obj.Modify_table();
                break;
            case 6:
                obj.Delete();
                break;
        }
        
    }
    system("cls");
    std::cout<<"\t\t\t\t"<<dbname<<std::endl;
    obj.ShowTable();
    obj.Close();
    obj.~DatabaseLanguage();


    return 0;
}