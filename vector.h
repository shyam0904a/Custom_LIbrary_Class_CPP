#pragma once
#include<cstddef>

template<typename Vector>
class Vectoriterator{

public:
    using Valuetype = typename Vector::Valuetype;
    using Pointertype = Valuetype*;
    using Referencetype =Valuetype&;
public:
    Vectoriterator(Pointertype ptr):m_ptr(ptr){}    
    Vectoriterator& operator++()                                                //prefix operator increment  
    {
        m_ptr++;                                                                //increment operator and return the pointer
        return *this;
    }   
     Vectoriterator operator++(int)                                             //postfix operator increment 
    {
        Vectoriterator iterator= *this;                                         //create copy and increment
        ++(*this);
        return iterator;                                                        //return the copy
    }
    Vectoriterator& operator--()                                                //prefix operator  decrement 
    {
        m_ptr--;                                                                //increment operator and return the pointer
        return *this;
    }   
     Vectoriterator operator--(int)                                             //postfix operator decrement
    {
        Vectoriterator iterator= *this;                                         //create copy and increment
        --(*this);
        return iterator;                                                        //return the copy
    }
    Referencetype operator[](int index)                                         //index operator
    {
        return *(m_ptr+index);                                                  //return pointer to the index 
    }
    Referencetype operator*()                                                   //reference operator overload 
    {
        return *(m_ptr);                                                        //returns a pointer
    }
    Pointertype operator->()                                                    //arrow operator overload
    {
        return m_ptr;
    }
    bool operator==(const Vectoriterator& other) const                          //bool equal operator overload
    {
        return m_ptr==other.m_ptr;
    }
    bool operator!=(const Vectoriterator& other) const                          //bool not equal operator overload
    {
        return !(*this==other);
    }
private:
    Pointertype m_ptr;
};

template<typename t>
class Vector{
public:
    using Valuetype = t;                                                     //just a reference variable
    using Iterator = Vectoriterator<Vector<t>>;

private:
    t* m_data = nullptr;
    size_t m_size =0;
    size_t m_capacity =0;
private:
    void realloc(size_t newcapacity){                                       //reallocation base with size capacity 2
       
        t* newblock = (t*)::operator new(newcapacity *sizeof(t));           //create a heap allocated newblock for copying//
                                                                            
        if(newcapacity<m_size)                                              //check if downsizing the array,if so change the 
            m_size=newcapacity;                                             //m_size to be newcapacity

        for (size_t i=0;i<m_size;i++)                                       //copying the existing data to newblock//                                                 
            new(&newblock[i]) t(std::move(m_data[i]));
            

        for(size_t i=0;i<m_size;i++)
            m_data[i].~t();

        ::operator delete(m_data,m_capacity*sizeof(t));
        m_data = newblock;                                                   //delete the old block of memory//
        m_capacity=newcapacity;                                             //set new capacity 
    }

public:
    Vector()
    {   
        realloc(3);
    }
    ~Vector()
    {
        clear(); 
        delete[] m_data;    
    }
    void pushback(const t& value){
        if(m_size>=m_capacity)                                              //check if block is free,if not reallocate
            realloc(m_capacity * 2);                                          //m_capacity 2X
        m_data[m_size]=value;
        m_size++;
    }

    void pushback(t&& value){                                               //r-value reference move constructor 
        if(m_size>=m_capacity)                                             //instead of copy constructor
            realloc(m_capacity * 2);                                          
        m_data[m_size]=std::move(value);
        m_size++;
    }
    void popback(){                                                         //deleting vector items
        if(m_size<0){                                                       //size check 
            m_size--;                                                       //removing size/space
            m_data[m_size].~Vector();                                       //deleting reference to the data
        }
    }
    void clear(){                                                           //clearing the whole vector storage
        for(size_t i=0;i<m_size;i++)
            m_data[i].~t();
        m_size=0;
    }
    
    template<typename... Args>                                              //instead of constructing a vector
    t& emplaceback(Args&&...args)                                           //it,this function takes constrol and constructes
    {                                                                       //the required by it's own (moving) in this stack
        if(m_size >= m_capacity)                                            //frame instead of the main function stack frame.  
            realloc(m_capacity * 2);
        new(&m_data[m_size]) t(std::forward<Args>(args)...);
        return m_data[m_size++];
    }


    size_t size()const {return m_size;}                                          //size function to return size

    Iterator begin()                                                            //vector start
    {
        return Iterator(m_data);
    }
    Iterator end()                                                              //vecter end +1
    {
        return Iterator(m_data+m_size);
    }

    const t& operator[](size_t index) const                            //index operator const version
    {
            // if(index>=m_size)
            // {
            //     assert(index>=m_size);
            // }
        return m_data[index];
    }
    t& operator[](size_t index)                                        //index operator non-const version
    {
        return m_data[index];
    }
};