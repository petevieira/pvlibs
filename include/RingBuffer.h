/**
 * \file RingBuffer.h
 * \brief Template class for RingBuffer
*/

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <iostream>
#include <stdio.h>

/**
 * \brief Templated RingBuffer class of user-defined size.
*/
template <typename T>
class RingBuffer
{
// Public member functions
public:

    /**
     * \brief Constructor:
     * pass in first item and static buffer size.
     * \param itemToBuffer First item of the buffer.
     * \param bufferSize Static size of buffer.
    */
    RingBuffer(const T& itemToBuffer, int bufferSize);

    /**
     * \brief Destructor
    */
    ~RingBuffer();

    /**
     * \brief Add an item of type T to the buffer
    */
    void add(const T& i);

    /**
     * \brief Get the previous item in the buffer
     * and set the head to it.
     * \return The previous item in the buffer.
    */
    T prev();

    /**
     * \brief Get the next item in the buffer
     * and set the head to it.
     * \return The next item in the buffer.
    */
    T next();

    /**
     * \brief Get the current item in the buffer.
     * \return The current item in the buffer.
    */
    T cur();

    /**
     * \brief Get the size of the buffer.
     * \return Size of the buffer.
    */
    int size();

    /**
     * \brief Whether or not the buffer is empty
     * \return True if empty, false if it contains any items.
    */
    bool isEmpty();

    /**
     * \brief Standard output stream operator
     * \return Reference to modified out stream.
    */
    friend std::ostream& operator<<(std::ostream& os, const RingBuffer& b)
    {
        os << "RingBuffer"
            << "\n\tBUF_SIZE = " << b.BUF_SIZE
            << "\n\tcount = " << b.count
            << "\n\thead  = " << b.head;

        for(int i=0; i<b.count; ++i)
            os << "\n\tdata[" << i+1 << "] = " << b.buffer[i];

        os << std::endl;
        return os;
    }

// Private member variables
private:

    T* buffer;                      // Array of items of type T
    unsigned int head;              // Current location in the buffer
    unsigned int count;             // Current number of items in the buffer
    const unsigned int BUF_SIZE;    // Static capacity of the buffer

};

template <typename T>
RingBuffer<T>::RingBuffer(const T& itemToBuffer, const int bufferSize) : BUF_SIZE(bufferSize)
{
    // Allocate memory for new buffer array of item of type T,
    // Initialize head and count and add item passed in by user.
    buffer = new T[BUF_SIZE];
    head = 0;
    count = 0;
    this->add(itemToBuffer);
}

template <typename T>
RingBuffer<T>::~RingBuffer()
{
    // Delete the buffer memory.
    delete buffer;
}

template <typename T>
void RingBuffer<T>::add(const T& itemToBuffer)
{
    // If buffer contains any items increment head,
    // add item to head and increment count.
    if(count > 0)
        head = (head+1) % BUF_SIZE;
    buffer[head] = itemToBuffer;
    if(count == head)
        count = std::min((count+1), BUF_SIZE);
}

template <typename T>
T RingBuffer<T>::prev()
{
    // Decrement head with wrap-around and return the previous item.
    head = head == 0 ? count - 1 : head - 1;
    return buffer[head];
}

template <typename T>
T RingBuffer<T>::next()
{
    // Increment head with wrap-around and return the next item.
    head = head == count - 1 ? 0 : head + 1;
    return buffer[head];
}

template <typename T>
T RingBuffer<T>::cur()
{
    // If the buffer is not empty return the item at the head.
    if(count > 0)
        return buffer[head];
}

template <typename T>
int RingBuffer<T>::size()
{
    // Return the static buffer size.
    return BUF_SIZE;
}

template <typename T>
bool RingBuffer<T>::isEmpty()
{
    // Return true if buffer contains any items.
    return (count > 0);
}

#endif // RINGBUFFER_H
