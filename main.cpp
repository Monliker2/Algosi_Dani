#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

class MyStack {
private:
    stack<int> st;

public:
    int Size() {
        return st.size();
    }

    void Push(int x) {
        st.push(x);
    }

    int Top() {
        return st.top();
    }

    void Pop() {
        st.pop();
    }

    bool isEmpty() {
        return st.empty();
    }
};

class Numbers : public MyStack {
public:
    int Get(int pos) {
        stack<int> tmp;
        int ans;
        for (int i = 0; i != pos; ++i) {
            tmp.push(Top());
            Pop();
        }
        ans = Top();
        while (!tmp.empty()) {
            Push(tmp.top());
            tmp.pop();
        }
        return ans;
    }

    void Set(int num, int pos) {
        stack<int> tmp;
        for (int i = 0; i < pos; ++i) {
            tmp.push(Top());
            Pop();
        }
        Pop();
        Push(num);
        while (!tmp.empty()) {
            Push(tmp.top());
            tmp.pop();
        }
    }


    void Swap(int pos1, int pos2) {
        int temp1 = Get(pos1);
        int temp2 = Get(pos2);
        Set(temp1, pos2);
        Set(temp2, pos1);
    }

    void BubbleSort() {
        int n = Size();
        bool swapped;
        do {
            swapped = false;
            for (int i = 0; i < n - 1; i++) {
                if (Get(i) > Get(i + 1)) {
                    Swap(i, i + 1);
                    swapped = true;
                }
            }
        } while (swapped);
    }

    void Sort() {
        BubbleSort();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Numbers stack;
    srand(time(0));

    cout << "Несортированный стек: ";
    for (int i = 0; i != 20; ++i) {
        int temp = rand() % 1000;
        stack.Push(temp);
        cout << temp << " ";
    }
    cout << "\n";

    stack.Sort();

    cout << "Отсортированный стек: ";
    for (int i = 0; i != 20; ++i) {
        cout << stack.Get(i) << " ";
    }
    cout << "\n";


    int key[1000];
    for (int i = 0; i != 1000; ++i) {
        key[i] = rand() % 1000;
    }
    //int n = 100;
    for(int n = 100; n<=1000; n+=100){

        Numbers stack1;

        for (int i = 0; i != n; ++i) {
            stack1.Push(key[i]);
        }
        cout << "\n";

        typedef std::chrono::high_resolution_clock Time;
        typedef std::chrono::milliseconds ms;

        auto t0 = Time::now();
        stack1.Sort();
        auto t1 = Time::now();

        ms time = std::chrono::duration_cast<ms>(t1 - t0);

        cout << "Sorting " << n << " elements take: " << time.count() << " ms";

    }

    return 0;
}