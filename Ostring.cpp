#include "Ostring.h"


//String Ostream output function
std::ostream& operator << (std::ostream & outPut, const Own::string& str) 
{
    const char* tmpStr = str.getStr();
    if (tmpStr)
        outPut << tmpStr;
    return outPut;
}
//Exception class methods
const char* Own::Exception::what()const throw(){
    const char* message;
    switch(this->m_errInd){
        case 0: message = "IndexError: The index is out of range.";break;
        case 1: message = "BadAllocation: The allocation size is invalid.";break;
    }
    return message;
}



//String class friend functions


//Own function call
Own::string operator+(const Own::string& str1,const Own::string& str2){
    size_t strLen1 = str1.length();size_t strLen2 =  str2.length();
    Own::dataPointer<char> data(strLen1 + strLen2 + 1);
    std::memcpy(data.m_ptr,str1.getStr(),strLen1 + 1 );
    std::memcpy(data.m_ptr + strLen1,str2.getStr(),strLen2 + 1 );
    return Own::string(data.m_ptr);
}


//String class members and methods
//constructors
Own::string::string(const char* str){
    this->m_length = std::strlen(str);
    this->m_str = new char[this->m_length + 1];
    std::memcpy(this->m_str,str,this->m_length + 1);
}
Own::string::string(const Own::string& str){
    this->m_length = str.m_length;
    this->m_str = new char[this->m_length + 1];
    std::memcpy(this->m_str,str.m_str,this->m_length + 1);
}
Own::string::string(Own::string&& str){
    this->m_length = std::move(str.m_length);
    this->m_str = std::move(str.m_str);
    str.m_str = nullptr;
    str.m_length = 0;
    str.clear();
}

//destructor
Own::string::~string(){
    this->clear();
}

//String Methods

Own::string Own::string::subStr(size_t s_index,size_t e_index,bool flag){
    try{
        if(e_index > s_index && s_index >= this->m_length && e_index >= this->m_length )
            throw Own::Exception(0);
        else{
            if (!flag){
                size_t length = e_index - s_index + 1;
                Own::dataPointer<char> data(length);
                data.m_ptr[length] = 0;
                std::memcpy(data.m_ptr,this->m_str + s_index, length);
                return Own::string(data.m_ptr);
            }
            else {
                if((s_index + e_index) >= this->m_length )
                    throw Own::Exception(0);
                else{
                    Own::dataPointer<char> data(e_index);
                    data.m_ptr[e_index] = 0;
                    std::memcpy(data.m_ptr,this->m_str + s_index, e_index);
                    return Own::string(data.m_ptr);
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout<< "Error in Filename: " << __FILE__ << " on Line: "<< __LINE__<< "\n" << e.what() << std::endl;
        exit(-1);
    }

}

void Own::string::clear(){
    if (this->m_str){
        delete [] this->m_str;
        this->m_str = nullptr;
        this->m_length = 0;
    }
}

//Getter and setter methods
const char* Own::string::getStr() const
{
    return this->m_str;
}
size_t Own::string::length()const {
    return this->m_length;
}


//String Operators methods
Own::string& Own::string::operator=(const Own::string& str){
    if(this != &str){
        this->m_length = str.m_length;
        this->m_str = new char[this->m_length + 1];
        std::memcpy(this->m_str,str.m_str,this->m_length);
    }
    return *this;

}
Own::string& Own::string::operator=(Own::string && str){
    if(this != &str){
        this->m_length = std::move(str.m_length);
        this->m_str = std::move(str.m_str);
        str.m_str = nullptr;
        str.m_length = 0;
        str.clear();
    }
    return *this;
}
char Own::string::operator[](size_t index){
    try{
        if (index >= this->m_length)
            throw Own::Exception(0);
        else
            return *(this->m_str + index);
    }
    catch (std::exception& e)
    {
        std::cout<< "Error in Filename: " << __FILE__ << " on Line: "<< __LINE__<< "\n" << e.what() << std::endl;
        exit(-1);
    }
}
Own::string& Own::string::operator+=(const Own::string& str){
    if (this != &str)
    {
        size_t strLen1 = this->m_length; size_t strLen2 = str.m_length;
        char* data = new char[strLen1 + strLen2 + 1];
        std::memcpy(data,this->m_str,strLen1 + 1);
        std::memcpy(data + strLen1, str.getStr(),strLen2 + 1);
        this->m_str = std::move(data);
        this->m_length = strLen1 + strLen2;
    }
    return *this;
}

bool Own::string::insert(size_t index,const Own::string& str){
    if (index < 0 || index >= this->m_length)
        return false;
    else{
        if (index == 0){
            Own::string st = Own::concat(str.m_str,this->m_str);
            this->m_str = std::move(st.m_str);
            this->m_length = st.m_length;
            st.clear();
        }
        else if(index == this->m_length - 1){
            Own::string st = Own::concat(this->m_str,str.m_str);
            this->m_str = std::move(st.m_str);
            this->m_length = st.m_length;
            st.clear();
        }
        else{
            size_t length = this->m_length + str.m_length;
            char* data = new char[length + 1];
            std::memcpy(data,this->m_str,index);
            std::memcpy(data + index, str.m_str,str.m_length);
            std::memcpy(data + index + str.m_length, this->m_str + index,this->m_length - index + 1);
            this->m_str = std::move(data);
            this->m_length = length;
        }
        std::cout << "Hello world\n";
        return true;
    }
}

bool Own::string::operator==(const Own::string& str){
    if (this->m_length == str.m_length && std::strcmp(this->m_str,str.m_str) >= 0)
        return true;
    else
        return false;
}





