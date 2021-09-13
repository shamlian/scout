#define CIRCULAR_BUFFER_DEBUG
#include <CircularBuffer.h>
#include <Keypad.h>

#ifndef KeyBuffer_h
#define KeyBuffer_h

#include "Arduino.h"

#define BUFFER_MAX 6

class KeyBuffer {
  public:
    KeyBuffer();
    bool isEmpty();
    char getFirst();
    char getNth(int n);
    void print();
    void printBuffer();
    void populate();
    int  size();
  private:
    CircularBuffer<int, BUFFER_MAX> _buffer;
    bool isInBuffer(int c);
    bool removeFromBuffer(int c);
};

#endif
