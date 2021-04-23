#pragma once

template<typename Type,size_t Size>
class ArrayIterator
{ 
public:
    using valuetype = Type;                                                                                   //Assignment for easy use
    using pointer =   Type*;
    using reference = Type&;
    using difference_type   = ptrdiff_t;
    
    ArrayIterator() noexcept:m_ptr(){}

    explicit ArrayIterator(pointer _prag,size_t m_offset=0) noexcept:m_ptr(_prag + m_offset){}

    reference operator*()                                                                                   //overload for operator *
    {
        return *m_ptr;                                                                                      //returns pointer to the data
    }
    pointer operator->()                                                                                   //overload for operator                                                                   
    {
        return m_ptr;                                                                                       //returns dereferenced value
    }
    ArrayIterator& operator++()                                                                            //pre increment operator overload
    {
        ++m_ptr;
        return *this;
    }
    ArrayIterator operator++(int)                                                                          //post-increment-creates a temporary
    {                                                                                                      //increment the value and return this
        ArrayIterator m_tmp = *this;            
        ++m_ptr;
        return *this;
    }
    ArrayIterator& operator--()                                                                            //pre-decrement operator overload
    {
        --m_ptr;
        return *this;
    }   
    ArrayIterator operator--(int)                                                                         //post-decrement operator
    {
        ArrayIterator m_tmp = *this;
        --m_ptr;
        return *this;
    }
    
    bool operator==(ArrayIterator& other)const                                                          //equalsto operator,returns true if other=this
    {
        return m_ptr=other.m_ptr;
    }
    bool operator!=(ArrayIterator& other)const                                                          //not-equalsto operator,returns ture if values are not equal
    {
        return !(*this==other);
    }
    bool operator<(ArrayIterator& other)const                                                           //less than
    {
        return m_ptr<other.m_ptr;
    }
    bool operator>(ArrayIterator& other)const                                                           //greater than
    {
        return other>*this;
    }
    bool operator<=(ArrayIterator& other)const                                                          //less than equal to
    {
        return !(other<*this);
    }
    bool operator>=(ArrayIterator& other)const                                                         //greater than equal to
    {
        return !(*this<other);
    }


private:
    pointer m_ptr;
    size_t m_size;
};

template<typename T,size_t S>
class Array
{
public:
    using value_type = T;                                                                   //refernces
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator = ArrayIterator<T,S>;
    
private:
    T m_data[S]; 

public:
    constexpr size_t Size() const                                    //Size function to retun the size of the array
    {
        return S;
    }

    constexpr size_t max_size() const noexcept                       //max size function
    {        
        return S;
    }

    T& operator[](size_t m_index)                                   //index operator
    {
        return m_data[m_index];
    }
    iterator begin()noexcept                                        //returns value at begining
    {
        return iterator(m_data,0);

    }
    iterator end()noexcept                                         //returns value at end
    {
        return iterator(m_data,S);
    }
    pointer unchecked_begin() const noexcept
    {
        return m_data;
    }
    pointer unchecked_end()const noexcept
    {
        return m_data+S;
    }
    bool isempty()const noexcept                                   //check if the array is empty
    {
        return false;
    }   
    reference at(size_type m_pos)                                 //Find elemet at given index
    {
        return m_data[m_pos];
    }
    reference front()noexcept                                   //same as begin
    {
        return m_data[0];
    }
    reference back()noexcept                                   //same as end
    {
        return m_data[S-1];
    }
    pointer data()noexcept                                     //data at current location
    {
        return m_data;
    }
    
};
       




