#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define STACK_SIZE 10000
#define QUEUE_SIZE 300000

template <class T>
class BaseStack
{
public:
    // Constructor
    BaseStack();

    // Destructor
    ~BaseStack();

    // Check if the stack is empty
    bool empty();

    // Return the size of the stack
    int size();

    // Return the top element
    T &top();

    // Insert a new element at top
    void push(const T &item);

    // Delete one element from top
    void pop();

private:
    T *_stack;
    int _top;
    int _capacity;
};

template <class T>
class BaseQueue
{
public:
    // Constructor
    BaseQueue();

    // Destructor
    ~BaseQueue();

    // Check if the queue is empty
    bool empty();

    // Return the size of the queue
    int size();

    // Return the front element
    T &front();

    // Insert a new element at rear
    void push(const T &item);

    // Delete one element from front
    void pop();

private:
    T *_queue;
    int _front, _rear;
    int _capacity;
};

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
    assert(!empty()); // if empty print ERROR
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

// Test Stack & Queue
/*
int main()
{
    BaseStack<int> B;
    cout << B.empty() << endl;
    B.push(7);
    cout << B.empty() << endl;
    B.pop();
    cout << B.top() << endl;
    B.push(1);
    cout << B.top() << endl;
    B.pop();
    cout << B.top() << endl;
    cout << "answer: 1, 0, 6, 1, 6" << endl;

    BaseQueue<int> A;
    cout << A.empty() << endl;
    A.push(7);
    cout << A.empty() << endl;
    A.push(13);
    cout << A.front() << endl;
    A.push(9);
    cout << A.front() << endl;
    A.pop();
    cout << A.size() << endl;
    cout << A.front() << endl;
    cout << "answer: 1, 0, 7, 7, 2, 13" << endl;
}
*/

// Test read data
/*
int main()
{
    char buffer[256] = {0};
    string s;
    std::ifstream ifs("./13453_sampleIn.txt", std::ios::in);
    if (!ifs.is_open())
    {
        cout << "Failed to open file.\n";
    }
    else
    {
        while (ifs >> s)
        {
            cout << s << endl;
        }
        ifs.close();
    }
    ifs.close();
    return 0;
}
*/

int main()
{
    // char buffer[256] = {0};
    string s;
    std::ifstream ifs("./13453_sampleIn.txt", std::ios::in);
    if (!ifs.is_open())
    {
        cout << "Failed to open file.\n";
    }

    // Variable declaration
    int W, H, M, position;
    ifs >> W;
    ifs >> H;
    ifs >> M;

    string enemy, inverse_enemy, Bullet;

    cout << "W: " << W << ", H: " << H << ", M: " << M << endl;

    // Read enemy
    BaseStack<string> pos_stack[6];
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            ifs >> enemy;
            pos_stack[j].push(enemy);
        }
    }

    /* Test the data road
    for(int i = 0; i < W; i++){
        cout << pos_stack[i].top() << endl;
    }
    */

    // ShootNormal
    ifs >> Bullet;
    ifs >> position;
    cout << "Bullet: " << Bullet << ", position: " << position << endl;
    int index = 0;

    while (pos_stack[position].top() == "_")
    {
        pos_stack[position].pop();
        index++;
    }

    // Enemy Type
    BaseQueue<string> Bullet_queue;
    if (pos_stack[position].top() == "2") // Enemy 2
    {
        Bullet_queue.push("Shotgun");
    }
    else if (pos_stack[position].top() == "3") // Enemy 3
    {
        Bullet_queue.push("Penetration");
    }
    else if (pos_stack[position].top() == "4") // Enemy 4
    {
        Bullet_queue.push("Super");
    }
    else if (pos_stack[position].top() == "5") // Enemy 5
    {
        pos_stack[position].pop(); // pop the enemy

        /*
        for (int j = -2; j <= 2; j++)
        {
            if (((j + position) >= 0) && ((j + position) <= W))
            {
                for (int i = 0; i < 3; i++)// add enemy 1 by kill 5
                {
                    pos_stack[j].push("1");
                }

            }
        }
        */
        // aa
    }

    pos_stack[position].pop();

    while (index >= 0) // add "_"
    {
        pos_stack[position].push("_");
        index--;
    }

    for (int i = 0; i < W; i++)
    {
        cout << pos_stack[i].size() << endl;
    }
    for (int i = 0; i < W; i++)
    {
        cout << pos_stack[i].top() << endl;
    }

    cout << Bullet_queue.front() << endl;

    // pos_stack[position].pop(); // Enemy 1 // Pop the position have enemy

    // ShowResult (Consider without NA value (done))
    BaseStack<string> inverse_stack[6];
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            inverse_enemy = pos_stack[j].top();
            inverse_stack[j].push(inverse_enemy);
            pos_stack[j].pop();
        }
    }

    for (int j = 0; j < H; j++)
    {
        for (int i = 0; i < W; i++)
        {
            // if (!inverse_stack[i].top()){ // for NA value "_"
            //     cout << "_";
            // }else{
            cout << inverse_stack[i].top();
            inverse_stack[i].pop();
            //}
        }
        cout << "\n";
    }

    return 0;
}