#ifndef Base64
#include<iostream>
#include<cmath>
#include<vector>
/*
    although it is not like hash generated like independent of the size of input it just
    give basic view about how data-base stored the hash of the password and when trying to 
    login the hashes are compared.

    simplification of ***Base64 encoding*** which is a encoding technique in web application.
*/
class EncodeMe{
    private:
        std::vector<std::string>array;
        std::vector<long>relatedDecimal;
        std::string result;
    public:
        EncodeMe(){}
        
        std::string Encode(std::string);
    private:
        std::string Encoder(std::string);
        std::string Encode();
        std::string convertToBinary(int value);
        long Binary(int value)
        {
            if(value==0)
            return 0;
            else
            return 10*Binary(value/2)+value%2;

        }
        long Decimal(int value,int count)
        {
            if(value==0)
            return 0;
            return (value%10)*pow(2,count)+Decimal(value/10,count+1);
        }


};
std::string EncodeMe::Encoder(std::string value)
{
    std::string temp="000000";
    std::string result="";
    for(int i=0;i<value.length();i++)
    {
        result+=convertToBinary(value[i]);
    }
    for(int i=0;i<result.length();i+=6)
    {
        array.push_back(result.substr(i,6));
    }
    if(array[array.size()-1].length()<6)
    {
        array[array.size()-1]+=temp.substr(0,6-array[array.size()-1].length());
    }
    for(auto x: array)
    {
        relatedDecimal.push_back(Decimal(std::stoi(x),0));
    }
    result =Encode();
    return result;
}
std::string EncodeMe::Encode()
{
    std::string result;
    for(auto x: relatedDecimal)
    {
        if(x<26)
        result.push_back(65+x);
        else if(x>=26 && x<52)
        result.push_back(71+x);
        else if(x>=52 && x<62)
        result.push_back(x-4);
        else
        result.push_back('=');
    }
    array.resize(0);
    relatedDecimal.resize(0);
    return result;
}

std::string EncodeMe::convertToBinary(int value)
{
    std::string result=std::to_string(Binary(value));
    for(int i=result.length();i<8;i++)
    {
        result='0'+result;
    }
    return result;
}

std::string EncodeMe::Encode(std::string value)
{  
    result=value; 
    result=Encoder(result);
    return this->result;
}

#endif