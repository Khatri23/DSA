#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using std::string,std::vector;
#ifndef Database
#define Database
//logic for handeling the user input.
class DATABASE{
protected:
  
    enum Columns_datatype {INT,STRING,LONG};
    string dbname;
    vector<string>column_name;
    std::map<string,Columns_datatype>mapType={{"INT",INT},{"STRING",STRING},{"LONG",LONG}}; // standard for logic on the basis of validation
    std::map<string,string>ColumnDatatype; // maaping the column name with respect to its datatype
    std::map<string,int>refsorting; //for sorting reference
    int column,n;
    string columnsData[3];
public:
    
    DATABASE(string dbname):column(3){this->dbname=dbname;}

    string DBName(){return dbname;}
    void CreateTable();
    void InputColumn();
    void Help()
    {
        showColumnNames(ColumnDatatype);
    }

    void Display();
    void option(int n)
    {
        this->n=n;
    }

private:
   
    void ColumnName();
    void showColumnNames(std::map<string,string>&temp);
    string InputColumnss(int index)
    {
         std::cout<<column_name[index]<<" : ";
        std::cin>>columnsData[index];
        std::transform(columnsData[index].begin(),columnsData[index].end(),columnsData[index].begin(),::toupper);
        std::cout<<std::endl;
        return columnsData[index];
    }
protected:
    bool CheckDatatype(string,string);

};
void DATABASE::CreateTable(){
    
    std::cout<<"\nNo of columns is "<<column<<std::endl;
    ColumnName();
}

void DATABASE:: showColumnNames(std::map<string,string>&temp)
{
    for(auto x:temp)
    {
        std::cout<<x.first<<"   "<<x.second<<std::endl;
    }
    
}
//for specifying the column name and the data type.
void DATABASE::ColumnName()
{
    string name;
    std::cout<<"-------------------------------------------------------"<<std::endl;
    std::cout<<" specify column name and datatype\n";
    std::cout<<"\tExisting Datatype"<<std::endl;
    std::cout<<"\tINT,    STRING , LONG  "<<std::endl;
    std::cout<<"-------------------------------------------------------"<<std::endl;
    for(int i=0;i<column;i++)
    {
        std::cout<<"Enter columnName :";
        std::cin>>name;
        std::transform(name.begin(),name.end(),name.begin(), ::toupper);
        column_name.push_back(name);
        if(ColumnDatatype.find(name)!=ColumnDatatype.end())
        {
            column_name.pop_back();
            std::cout<<"Column name can't be same"<<std::endl;
            i--;
        }
        else{
            std::cout<<"Enter Its dataType :";
            std::cin>>name;
            std::transform(name.begin(),name.end(),name.begin(), ::toupper);
            //if the data type doesn't found in the maptype
            if(mapType.find(name)==mapType.end())
            {
                std::cout<<"Invalid datatype for:: "<<column_name[i];
                column_name.pop_back();
                std::cout<< "  options are :: ";std::cout<<"  INT,  STRING , LONG"<<std::endl;
                i--;
            }
            // if data type found push the data type and the column name in the map columnDatatype aswell as refsorting.
            else
            {
                ColumnDatatype[column_name[i]]=name;
                refsorting[column_name[i]]=i;
            }
        }
       
       
    }
    std::cout<<"Successfully created column"<<std::endl;
    showColumnNames(ColumnDatatype);

}
//logic for user input.
void DATABASE::InputColumn()
{
    std::cout<<"\nInput the datas:\n";
  for(int i=0;i<column_name.size();i++)
  {
    string data;
    try{
       if(n==1)
       {
        data=InputColumnss(i);
        if(CheckDatatype(data,column_name[i])==false)
        throw(data);
       }
       else if(n==2)
       {
            string name;
            std::cout<<"Enter the column-name :";
            std::cin>>name;
            std::transform(name.begin(),name.end(),name.begin(),::toupper);
            while(refsorting.find(name)==refsorting.end())
            {
                std::cout<<"No such column specify columns are "<<column_name[0]<<','<<column_name[1]<<','<<column_name[2]<<std::endl;
                std::cout<<"Enter the column-name :";
                std::cin>>name;
                std::transform(name.begin(),name.end(),name.begin(),::toupper);
            }
            
            data=InputColumnss(refsorting[name]);
            if(CheckDatatype(data,name)==false)
            {
                i=refsorting[name];
                throw(data);
            }
            if(refsorting[name]==1)
            columnsData[0]=columnsData[2]="";
            else if(refsorting[name]==0)
            columnsData[1]=columnsData[2]="";
            else if(refsorting[name]==2)
            columnsData[0]=columnsData[1]="";
       }
        
    }
    catch(string value)
    {
        std::cout<<"Wrong datatype::\n";
        while(!CheckDatatype(data,column_name[i]))
        {
            std::cout<<"Datatype for "<<column_name[i]<<" is "<<ColumnDatatype[column_name[i]]<<std::endl;
            data=InputColumnss(i);
        }
    }
    if(n==2)
    break;
  }
  
    std::cout<<"Datas inserted successfully!"<<std::endl;
    
}
//logic for checking the user input according to the data type they specified during the program.
bool DATABASE::CheckDatatype(string data,string column)
{
  switch (mapType[ColumnDatatype[column]])
  {
    case INT:
        for(int i=0;i<data.length();i++)
        {
            if((data[i]>='0' && data[i]<='9') && data.length()<5)
            continue;
            else
                return false;
        }
        break;
    case STRING:
        for(int i=0;i<data.length();i++)
        {
            if(data[i]>='0' && data[i]<='9')
                return false;
            else
                continue;
        }
        break;
    case LONG:
        for(int i=0;i<data.length();i++)
        {
            if(data[i]>='0' && data[i]<='9')
            continue;
            else
                return false;
        }
        break;
  }
  return true;
}

void DATABASE::Display()
{
    std::cout<<" Database Operations::\n";
    std::cout<<"1.Default Insertion to the table"<<std::endl;
    std::cout<<"2.Insert into condition"<<std::endl;
    std::cout<<"3. Display the table...."<<std::endl;
    std::cout<<"4. searching the element..."<<std::endl;
    std::cout<<"5. Modify the data in the table"<<std::endl;
    std::cout<<"6. Delete a data from table.."<<std::endl;
    std::cout<<"99. to exit from the program."<<std::endl;
}


#endif