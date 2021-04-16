#pragma once

template<typename t>
class vector{

private:
    t* m_data = nullptr;
    size_t m_size =0;
    size_t m_capacity =0;
private:
    void realloc(size_t newcapacity){                                       //reallocation base with size capacity 2
       
        if(newcapacity<m_size)                                              //check if downsizing the array,if so change the 
            m_size=newcapacity;                                             //m_size to be newcapacity

        t* newblock = (*t)::operator new(newcapacity*sizeof(t));                                 //create a heap allocated newblock for copying//
                                                                            //with base size of 3//
        for (size_t i=0;i<m_size;i++)                                       //copying the existing data to newblock//                                                 
            newblock[i]=std::move(m_data[i]);

        for(size_t i=0;i<m_size;i++)
            m_data[i].~vector();
        ::operator delete(m_data,m_capacity*sizeof(t));
        m_data = newblock;                                                   //delete the old block of memory//
        m_capacity=newcapacity;                                             //set new capacity 
    }

public:
    vector()
    {   
        realloc(3);
    }
    ~vector()
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
            m_data[m_size].~vector();                                       //deleting reference to the data
        }
    }
    void clear(){                                                           //clearing the whole vector storage
        for(size_t i=0;i<m_size;i++)
            m_data[i].~vector();
        m_size=o;
    }
    
    template<typename... Args>                                              //instead of constructing a vector
    t& emplaceback(Args&&...args)                                           //it,this function takes constrol and constructes
    {                                                                       //the required by it's own (moving) in this stack
        if(m_size >= m_capacity)                                            //frame instead of the main function stack frame.  
            realloc(m_capacity * 2);
        new(m_data[m_size])t(std::forward<Args>(args)...);
        retun m_data[m_size++];
    }


    size_t size()const {return m_size;}                                          //size function to return size

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