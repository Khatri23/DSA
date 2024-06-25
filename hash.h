#ifndef hash
#include<iostream>
#include<iomanip>
#include"Base64.h"
using std::string;
/*
simple hashing concept.
using the linear probing as a hash resolution technique.
objective:: to show the login crediental and the simple view of hash based authentication.
*/
class Hash:public EncodeMe{
    private:
        struct Map{
            string key;
            string value;
        };
        int size;
        struct Map ** hashtable; // table to store the addresses of the datas.
    public:
        Hash(int size):EncodeMe(){//constructor that set up the table for me consisting the nullptr.
            this->size=size;
            hashtable=new Map*[size];
            for(int i=0;i<size;i++)
            hashtable[i]=nullptr;    
        }

        void show()
        {
            std::cout<<"Username"<<std::setw(7)<<"|"<<std::setw(15)<<"Password_Hash"<<std::endl;
            for(int i=0;i<size;i++)
            {
                if(hashtable[i]!=NULL)
                {
                    std::cout<<hashtable[i]->key<<std::setw(15-hashtable[i]->key.length())<<"|"<<std::setw(14) <<hashtable[i]->value<<std::endl;
                }
            }
        }
        void Insert(string key,string value)
        {
            //index is generated based on my username.
            int index=hashfunction(key);
            struct Map *current=new Map();
            current->key=key;
            current->value=Encode(value);
            if(hashtable[index]==nullptr)
            {
                hashtable[index]=current;
            }
            else {
                int count=index;
                do{
                    if(hashtable[count]->key==key)
                    {
                        std::cout<<"Username already existed! \n";
                        return;
                    }
                    count=(count+1)%size;
                }while(count!=index && hashtable[count]!=nullptr);
                if(index==count)
                {
                    std::cout<<"Table full\n";
                    delete current;
                    exit(0);
                }
                else
                hashtable[count]=current;
            } 
        }

        bool search(string value,string &hash)
        {
            int key=hashfunction(value);
            int index=key;
            bool isvalue=false;
            do{
                if(hashtable[index]->key==value)
                {
                    hash=hashtable[index]->value;
                    return true;                    
                }
                index=(index+1)%size;
            }while(index!=key && hashtable[index]!=nullptr );
            hash=" ";
            return false;
        }
        void Remove(string value)
        {
            int key=hashfunction(value);
            int index=key;
             bool isvalue=false;
            do{
                if(hashtable[index]->key==value)
                {
                    hashtable[index]=nullptr;
                    isvalue=true;
                }
                index=(index+1)%size;
            }while(index!=key && hashtable[index]!=nullptr);
            if(isvalue==false)
            {
                std::cout<<"--------successfully removed------"<<std::endl;
            }
        }
        
    private:
    //simple hash function.
        int hashfunction(string key)
        {
            std::string temp;
            for(int i=0;i<key.length();i++)
            {
                int index=key[i];
                temp=temp+std::to_string(index);
            }
            //own technique for generating index for my hash table.
            return (abs(temp[0]-'0'+temp[temp.length()-1]-'0'-temp[temp.length()/2]-'0'))%size;
        }
        
};


#endif