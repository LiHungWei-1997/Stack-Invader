#include "function.h"
#include <iostream>
#include <string>
using namespace std;

#define STACK_SIZE 200000
#define QUEUE_SIZE 200000

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

BaseStack<char> pos_stack[STACK_SIZE];
BaseQueue<char> Bullet_queue;
BaseStack<char> sb_stack[1];
BaseStack<char> inverse_stack[STACK_SIZE];

void InitialzeStage(int W, int H)
{
    char enemy;

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

        while (true) // check (not necessary)
        {
            int index_deletenull = 0;
            for (int i = 0; i < W; i++)
            {
                if (pos_stack[i].top() == '_')
                {
                    index_deletenull++;
                }
            }
            if (index_deletenull == W) // if the last row all null, delete
            {
                for (int i = 0; i < W; i++)
                {
                    pos_stack[i].pop();
                }
            }
            else
            {
                break;
            }
        }

        while (pos_stack[col].top() == '_')
        {
            pos_stack[col].pop();
            index++;
        }

        // Enemy Type
        if (pos_stack[col].top() == '5')
        {
            pos_stack[col].pop(); // pop the enemy

            // Clear all '_' on each stack
            for (int i = 0; i < W; i++)
            {
                while (pos_stack[i].top() == '_')
                {
                    pos_stack[i].pop();
                }
            }

            int max_level = 0; // record max level on needed column
            for (int i = 0; i < W; i++)
            {
                if (i >= (col - 2) & i <= (col + 2))
                {
                    if (pos_stack[i].size() > max_level)
                    {
                        max_level = pos_stack[i].size();
                    }
                }
            }
            for (int i = 0; i < W; i++) // add '_' on needed column to match max level
            {
                if (i >= (col - 2) & i <= (col + 2))
                {
                    while (pos_stack[i].size() < max_level)
                    {
                        pos_stack[i].push('_');
                    }
                }
            }
            for (int i = 0; i < W; i++) // add 1 on needed column by enemy 5
            {
                if (i >= (col - 2) & i <= (col + 2))
                {
                    for (int j = 0; j < 3; j++)
                    {
                        pos_stack[i].push('1');
                    }
                }
            }
            // rebuild the enemy on all column
            int max_level2 = 0;
            for (int i = 0; i < W; i++)
            {
                if (pos_stack[i].size() > max_level2)
                {
                    max_level2 = pos_stack[i].size();
                }
            }
            for (int i = 0; i < W; i++) // add '_' to match max level
            {
                while (pos_stack[i].size() < max_level2)
                {
                    pos_stack[i].push('_');
                }
            }
        }
        /* Bullet Type:
        2: Shotgun bullet
        3: Penetration bullet
        4: Super bullet
        */
        else if (pos_stack[col].top() == '2')
        {
            Bullet_queue.push(pos_stack[col].top());
            pos_stack[col].pop();

            while (index >= 0) // add "_"
            {
                pos_stack[col].push('_');
                index--;
            }
        }
        else if (pos_stack[col].top() == '3')
        {
            Bullet_queue.push(pos_stack[col].top());
            pos_stack[col].pop();

            while (index >= 0) // add "_"
            {
                pos_stack[col].push('_');
                index--;
            }
        }
        else if (pos_stack[col].top() == '4')
        {
            Bullet_queue.push(pos_stack[col].top());
            pos_stack[col].pop();

            while (index >= 0) // add "_"
            {
                pos_stack[col].push('_');
                index--;
            }
        }
        else if (pos_stack[col].top() == '1')
        {
            pos_stack[col].pop();

            while (index >= 0) // add "_"
            {
                pos_stack[col].push('_');
                index--;
            }
        }
        else
        {
            ;
        }
        // rebuild the enemy on all column
        int max_level3 = 0;
        for (int i = 0; i < W; i++)
        {
            if (pos_stack[i].size() > max_level3)
            {
                max_level3 = pos_stack[i].size();
            }
        }
        for (int i = 0; i < W; i++) // add '_' to match max level
        {
            while (pos_stack[i].size() < max_level3)
            {
                pos_stack[i].push('_');
            }
        }
    }
}

void ShootSpecial(int col, int W)
{
    char sb_stack_top;

    if (!Bullet_queue.empty() & (col >= 0) & (col < W))
    {
        // Shotgun bullet
        if (Bullet_queue.front() == '2')
        {
            for (int i = col - 2; i < col + 3; i++)
            {
                if (i >= 0 & i < W)
                {
                    ShootNormal(i, W);
                }
            }
            Bullet_queue.pop();
        }
        // Penetration bullet
        else if (Bullet_queue.front() == '3')
        {
            for (int i = 0; i < 3; i++)
            {
                ShootNormal(col, W);
            }
            Bullet_queue.pop();
        }
        // Super bullet
        else if (Bullet_queue.front() == '4')
        {
            int index1 = 0;
            int index2 = 0;
            int index3 = 0;

            while (pos_stack[col].top() == '_') // record the top enemy
            {
                pos_stack[col].pop();
                index1++;
                if (pos_stack[col].empty())
                {
                    break;
                }
            }
            sb_stack_top = pos_stack[col].top();

            for (int i = 0; i < index1; i++) // recover the stack
            {
                pos_stack[col].push('_');
                index1--;
            }

            if (sb_stack_top == '5') // special condition(enemy 5)
            {
                ShootNormal(col, W);
            }
            else
            {
                while (pos_stack[col].top() == sb_stack_top or pos_stack[col].top() == '_')
                {
                    sb_stack[0].push(pos_stack[col].top()); // for recover the stack
                    pos_stack[col].pop();
                    index2++;
                }
                for (int i = 0; i < index2; i++)
                {
                    sb_stack_top = sb_stack[0].top();
                    if (sb_stack_top != '_')
                    {
                        index3++; // compute NormalShoot times
                    }
                    pos_stack[col].push(sb_stack_top);
                    sb_stack[0].pop();
                }
                for (int i = 0; i < index3; i++)
                {
                    ShootNormal(col, W);
                }
            }
            Bullet_queue.pop();
        }
    }
}

void FrontRow(int W)
{
    for (int i = 0; i < W; i++)
    {
        while (pos_stack[i].top() == '_')
        {
            pos_stack[i].pop();
        }
    }
    int stack_max_size = 0;
    for (int i = 0; i < W; i++)
    {
        if (pos_stack[i].size() > stack_max_size)
        {
            stack_max_size = pos_stack[i].size();
        }
    }
    for (int j = 1; j < W; j++)
    {
        if (pos_stack[j].size() > stack_max_size)
        {
            stack_max_size = pos_stack[j].size();
        }
    }
    if (stack_max_size == 0)
    {
        cout << "FRONT_ROW, LEVEL:" << stack_max_size << endl;
    }
    else
    {
        for (int k = 0; k < W; k++)
        {
            while (pos_stack[k].size() < stack_max_size)
            {
                pos_stack[k].push('_');
            }
        }

        cout << "FRONT_ROW, LEVEL:" << stack_max_size << endl;
        for (int i = 0; i < W; i++)
        {
            cout << pos_stack[i].top();
            if (i < W - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void ShowResult(int W)
{
    char inverse_enemy;

    while (true)
    {
        int index_deletenull = 0;
        for (int i = 0; i < W; i++)
        {
            if (pos_stack[i].top() == '_')
            {
                index_deletenull++;
            }
        }
        if (index_deletenull == W) // if the last row all null, delete
        {
            for (int i = 0; i < W; i++)
            {
                pos_stack[i].pop();
            }
        }
        else
        {
            break;
        }
    }

    int max_level = pos_stack[0].size();

    for (int i = 0; i < max_level; i++)
    {
        for (int j = 0; j < W; j++)
        {
            inverse_enemy = pos_stack[j].top();
            inverse_stack[j].push(inverse_enemy);
            pos_stack[j].pop();
        }
    }

    cout << "END_RESULT:" << endl;
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