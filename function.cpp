#include "function.h"
#include <iostream>
#include <string>
using namespace std;

#define STACK_SIZE 15000
#define QUEUE_SIZE 30000

/*
1:accept
5:accept
*/

// STACK
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
    return _top < 0;
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
    // assert(_top <= (_capacity - 1)); // error if capacity explode

    if (_stack == NULL)
    {
        _stack = new T[_capacity];
    }
    _stack[++_top] = item; // add new item
}

template <class T>
void BaseStack<T>::pop()
{
    if (_top >= 0)
    {
        _top--;
    }
    else
    {
        delete[] _stack;
        _stack = NULL;
        _top = -1;
    }
}

// QUEUE
template <class T>
BaseQueue<T>::BaseQueue() : _front(0), _rear(0), _capacity(QUEUE_SIZE)
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
    return _rear == _front;
}

template <class T>
int BaseQueue<T>::size()
{
    return _rear - _front;
}

template <class T>
T &BaseQueue<T>::front()
{
    // assert(!empty()); // if empty print ERROR
    return _queue[(_front) % _capacity];
}

template <class T>
void BaseQueue<T>::push(const T &item)
{
    if (_queue == NULL)
    {
        _queue = new T[_capacity];
    }
    _queue[(_rear++) % _capacity] = item; // add new item
}

template <class T>
void BaseQueue<T>::pop()
{
    if (!empty())
    {
        _front++;
    }
    else
    {
        delete[] _queue;
        _queue = NULL;
        _rear = 0;
        _front = 0;
    }
}

BaseStack<string> pos_stack[100];
BaseQueue<string> Bullet_queue;
BaseStack<string> sb_stack[1];
BaseStack<string> inverse_stack[100];

void InitialzeStage(int W, int H)
{
    string enemy;

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> enemy;
            pos_stack[j].push(enemy);
        }
    }
}

// ShootNormal
void ShootNormal(int col, int W)
{
    int index = 0;

    if (col >= 0 & col < W)
    {
        while (pos_stack[col].top() == "_")
        {
            pos_stack[col].pop();
            index++;
        }

        // Enemy Type
        if (pos_stack[col].top() == "5")
        {
            pos_stack[col].pop(); // pop the enemy
            while (index >= 0)    // add _
            {
                pos_stack[col].push("_");
                index--;
            }

            for (int j = 0; j < W; j++)
            {
                if (j >= (col - 2) & j <= (col + 2))
                {
                    for (int i = 0; i < 3; i++) // add enemy 1 by kill 5
                    {
                        pos_stack[j].push("1");
                    }
                }
                else
                {
                    for (int i = 0; i < 3; i++) // add enemy _ by kill 5
                    {
                        pos_stack[j].push("_");
                    }
                }
            }
        }
        else if (pos_stack[col].top() != "1" & pos_stack[col].top() != "5")
        {
            /* Bullet Type:
            2: Shotgun bullet
            3: Penetration bullet
            4: Super bullet
            */
            Bullet_queue.push(pos_stack[col].top());
            pos_stack[col].pop();

            while (index >= 0) // add "_"
            {
                pos_stack[col].push("_");
                index--;
            }
        }
        else
        {
            pos_stack[col].pop();

            while (index >= 0) // add "_"
            {
                pos_stack[col].push("_");
                index--;
            }
        }
    }
}

void ShootSpecial(int col, int W)
{
    string top_1, top_2, sb_stack_top;
    int super_index = 0;
    int super_index_normal = 0;
    int pos_stack_size = pos_stack[col].size();

    if (!Bullet_queue.empty())
    {
        // Shotgun bullet
        if (Bullet_queue.front() == "2")
        {
            for (int i = col - 2; i < col + 3; i++)
            {
                if (i >= 0 & i <= W)
                {
                    ShootNormal(i, W);
                }
            }
            Bullet_queue.pop();
        }
        // Penetration bullet
        else if (Bullet_queue.front() == "3")
        {
            for (int i = 0; i < 3; i++)
            {
                ShootNormal(col, W);
            }
            Bullet_queue.pop();
        }
        // Super bullet
        else if (Bullet_queue.front() == "4")
        {
            while (true)
            {
                top_1 = pos_stack[col].top();
                sb_stack[0].push(top_1);
                pos_stack[col].pop();
                top_2 = pos_stack[col].top();
                super_index++;

                if (top_1 != top_2 & top_1 != "_" & top_2 != "_") // Shoot the same enemy
                {
                    break;
                }
                else if (sb_stack[0].size() == (pos_stack_size - 1))
                {
                    break;
                }
            }
            for (int i = 0; i < super_index; i++)
            {
                sb_stack_top = sb_stack[0].top();
                if (sb_stack_top != "_")
                {
                    super_index_normal++;
                }

                pos_stack[col].push(sb_stack_top);
                sb_stack[0].pop();
            }
            for (int i = 0; i < super_index_normal; i++)
            {
                ShootNormal(col, W);
            }
            Bullet_queue.pop();
        }
    }
}

void FrontRow(int W)
{
    for (int i = 0; i < W; i++)
    {
        while (pos_stack[i].top() == "_")
        {
            pos_stack[i].pop();
        }
    }
    int MaxLevel = 0;
    for (int j = 0; j < W; j++)
    {
        if (pos_stack[j].size() > MaxLevel)
        {
            MaxLevel = pos_stack[j].size();
        }
    }
    if (MaxLevel == 0)
    {
        cout << "FRONT_ROW, LEVEL:" << MaxLevel << endl;
    }
    else
    {
        for (int k = 0; k < W; k++)
        {
            while (pos_stack[k].size() < MaxLevel)
            {
                pos_stack[k].push("_");
            }
        }

        cout << "FRONT_ROW, LEVEL:" << MaxLevel << endl;
        for (int i = 0; i < W; i++)
        {
            cout << pos_stack[i].top();
            if (i < W - 1)
            {
                cout << " ";
            }
        }
        cout << "\n";
    }
}

void ShowResult(int W)
{
    int max_level = pos_stack[0].size();
    string inverse_enemy;

    for (int i = 0; i < max_level; i++)
    {
        for (int j = 0; j < W; j++)
        {
            inverse_enemy = pos_stack[j].top();
            inverse_stack[j].push(inverse_enemy);
            pos_stack[j].pop();
        }
    }
    /*
    for (int i = 0; i < 6; i++)
    {
        cout << inverse_stack[i].size() << endl;
    }
    */

    cout << "END_RESULT:"
         << "\n";
    for (int j = 0; j < max_level; j++)
    {
        for (int i = 0; i < W; i++)
        {
            // if (!inverse_stack[i].top()){ // for NA value "_"
            //     cout << "_";
            // }else{
            if (i == (W - 1))
            {
                cout << inverse_stack[i].top() << endl;
                inverse_stack[i].pop();
            }
            else
            {
                cout << inverse_stack[i].top() << " ";
                inverse_stack[i].pop();
            }
        }
    }
}

void deleteStage()
{
    while (!Bullet_queue.empty())
    {
        Bullet_queue.pop();
    }

    while (!sb_stack[0].empty())
    {
        sb_stack[0].pop();
    }

    for (int i = 0; i < 6; i++)
    {
        while (!pos_stack[i].empty())
        {
            pos_stack[i].pop();
            inverse_stack[i].pop();
        }
    }
}