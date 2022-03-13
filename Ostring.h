#ifndef OSTRING_H
#define OSTRING_H

#include <iostream>
#include <cstring>
#include <exception>

//Own Namespace begin
namespace Own{

    //Exception class Begins
    class Exception:public std::exception{
        private:
            unsigned int m_errInd;
        public:
            Exception() = default;
            Exception(unsigned int errInd) noexcept: m_errInd(errInd){
            }
            const char* what()const throw();
    };

    template<class T>
    class dataPointer{
        public:
            T* m_ptr = nullptr;
            size_t m_size = 0;
            dataPointer() = default;
            dataPointer(size_t size){
                try{
                    if (size <= 0)
                        throw Exception(1);
                    else{
                        if (size > 1)
                            m_ptr = new T[size];
                        else
                            m_ptr = new T;
                        m_size = size;
                    }
                }
                catch(std::exception& e)
                {
                    std::cout<< "Error in Filename: " << __FILE__ << " on Line: "<< __LINE__<< "\n" << e.what() << std::endl;
                    exit(-1);
                }
            }
            ~dataPointer(){
                if (m_size == 1)
                    delete m_ptr;
                else
                    delete [] m_ptr;
                m_size = 0;
            }
    };


    //String class Begins
    class string{
        private:
            char * m_str = nullptr;
            size_t m_length = 0;
        public:
            //constructors
            string() = default;
            string(const char* str);
            string(const string& str);
            string(string&& str);

            //destructor
            ~string();

            //getter and setter
            size_t length()const ;
            const char* getStr()const;


            //data removal
            void clear();


            //operators
            string& operator=(const string& str);
            string& operator=(string && str);
            char operator[](size_t index);
            string& operator+=(const string& str);

            //functions
            string subStr(size_t s_index,size_t e_index,bool flag = false);
            bool insert(size_t index,const string& str);


            

            //friend functions
            friend string concat(const char* str1,const char* str2);
    };
    string operator+(const Own::string& str1,const Own::string& str2);


    Own::string concat(const char* str1,const char* str2){
        size_t strLen1 = std::strlen(str1);size_t strLen2 =  std::strlen(str2);
        Own::dataPointer<char> data(strLen1 + strLen2 + 1);
        std::memcpy(data.m_ptr,str1,strLen1 + 1 );
        std::memcpy(data.m_ptr + strLen1,str2,strLen2 + 1);
        return Own::string(data.m_ptr);
}
};
//Own Name space End


//Functions declerations
std::ostream& operator << (std::ostream & outPut, const Own::string& str);

//---------------------------------


#endif //OSTRING_H