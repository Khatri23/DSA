#include<iostream>
#include"hash.h"
 std::string username,password;
void menu()
{
    std::cout<<"\n\n...................................................\n";
    std::cout<<"press 1. to register\n";
    std::cout<<"press 2. to login\n";
    std::cout<<"Press 3. to show the table\n";
    std::cout<<"Press 4. to exit out\n";
    std::cout<<"...................................................\n";

}
void Options(Hash &obj)
{
    std::string hash;
    int choice;
    std::cout<<"Your choice-";
    std::cin>>choice;
    switch(choice)
    {
        case 1:
            std::cout<<"Enter the user-name: ";
            std::cin>>username;
            password="";
            while(password.length()<6)
            {
                std::cout<<"Enter the new-password: ";
                std::cin>>password;
                if(password.length()<6)
                std::cout<<"short password length "<<password.length()<<" expected at least 6\n";
            }
            obj.Insert(username,password);
            break;
        case 2:
            std::cout<<"\nEnter the user-name: ";
            std::cin>>username;
            std::cout<<"Enter the password: ";
            std::cin>>password;
            if(obj.search(username,hash))
            {
                if(obj.Encode(password)==hash)
                {
                    std::cout<<"\n...................................................\n";
                    std::cout<<"Login successfull\n";
                    std::cout<<"You login as "<<username<<std::endl;
                    std::cout<<"Both hashes are matched "<<hash<<std::endl;
                    std::cout<<"\n...................................................\n";
                }
                else
                {
                    std::cout<<"\nPassword incorrect\n";
                    std::cout<<"Generated hash- "<<obj.Encode(password)<<std::endl;
                    std::cout<<"stored hash- "<<hash<<std::endl;
                }
            }
            else
                std::cout<<"User-name or password is incorrect"<<std::endl;
            break;
        case 3:
            obj.show();
            break;
        case 4:
            exit(0);
        default:
            std::cout<<"Invalid option\n";
            
    }
}
int main()
{

    Hash obj(7);//creating the table size of 7.
    std::cout<<"Register at least 2 unique users to demonstrate.\n Do not insert spaces.\n";
    int count=0;
    while(count<2)
    {
        std::cout<<"Enter the user-name: ";
        std::cin>>username;
        password=" ";
        while(password.length()<6)
        {
            std::cout<<"Enter the new-password: ";
            std::cin>>password;
            if(password.length()<6)
            std::cout<<"short password length "<<password.length()<<" expected at least 6\n";
        }
        obj.Insert(username,password);//insert key as username and value as password.
        
        count++;
    }
    while(true)
    {
        menu();
        Options(obj);
    }

    return 0;
}