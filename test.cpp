#include "function.h"
#include <iostream>
#include <string>
using namespace std;

#define STACK_SIZE 10000
#define QUEUE_SIZE 300000

template <class T>
BaseStack<T>::BaseStack() : _top(-1), _capacity(STACK_SIZE)
{
    _stack = NULL;
}

template <class T>
BaseStack<T>::~BaseStack()
{
    if (_stack != NULL)
        delete[] _stack; // delete pointer
}

template <class T>
bool BaseStack<T>::empty()
{
    if (top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
    // return (_top == -1);
}

template <class T>
int BaseStack<T>::size()
{
    return _top + 1;
}

template <class T>
T &BaseStack<T>::top()
{
    return _stack[_top];
}

template <class T>
void BaseStack<T>::push(const T &item)
{
    if (_stack == NULL)
        _stack = new T[_capacity]; // allow new one
    _stack[++_top] = item;
}

template <class T>
void BaseStack<T>::pop()
{
    if (_top >= 0)
        _top--;
    else
    {
        delete[] _stack;
        _stack = NULL;
    }
}

template <class T>
BaseQueue<T>::BaseQueue() : _rear(0), _front(0), _capacity(QUEUE_SIZE)
{
    _queue = NULL;
}

template <class T>
BaseQueue<T>::~BaseQueue()
{
    if (_queue != NULL)
        delete[] _queue; // delete pointer
}

template <class T>
bool BaseQueue<T>::empty()
{
    if (front == rear)
    {
        return true;
    }
    else
    {
        return false;
    }
    // return (_rear == _front);
}

template <class T>
int BaseQueue<T>::size()
{
    return _rear - _front;
}

template <class T>
T &BaseQueue<T>::front()
{
    return _queue[(_front) % _capacity];
}

template <class T>
void BaseQueue<T>::push(const T &item)
{
    if (_queue == NULL)
        _queue = new T[_capacity]();
    _queue[(_rear++) % _capacity] = item;
}

template <class T>
void BaseQueue<T>::pop()
{
    if (!empty())
        _front++; // front add one
    else
    {
        delete[] _queue;
        _queue = NULL;
        _rear = 0;
        _front = 0;
    }
}

BaseStack<int> *Hstack = NULL;
BaseQueue<int> Q;

void InitialzeStage(int W, int H)
{
    cin >> W >> H;
    int index = 0;
    int a;
    if (Hstack = NULL)
        Hstack = new BaseStack<int>[H];
    for (i = 0; i < H; i++)
    {
        for (j = 0; j < W; j++)
        {
            cin >> a;
            Hstack[index + i].push(a)
        }
    }
}

void ShootNormal()
{
}