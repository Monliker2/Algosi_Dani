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
    int Size() { // 2
        return st.size();
    }

    void Push(int x) { // 1
        st.push(x);
    }

    int Top() { // 2
        return st.top();
    }

    void Pop() { // 1
        st.pop();
    }

    bool isEmpty() { // 2
        return st.empty();
    }
};

class Numbers : public MyStack {
public:
    int Get(int pos) { // 4 + 12n
        MyStack tmp;
        int ans;
        for (int i = 0; i != pos; ++i) { // 2 + ∑_1^n▒〖(1 + 5)〗 = 2 + 6n
            tmp.Push(Top()); // 4
            Pop(); // 1
        }
        ans = Top(); // 3
        while (!tmp.isEmpty()) { // 3 + ∑_1^n▒〖(3 + 5)〗  = 3 + 8n
            Push(tmp.Top()); // 4
            tmp.Pop(); // 1
        }
        return ans; // 1
    }

    void Set(int num, int pos) { // 8 + 14n
        MyStack tmp;
        for (int i = 0; i < pos; ++i) { // 2 + ∑_1^n▒〖(1 + 5)〗 = 2 + 6n
            tmp.Push(Top()); // 4
            Pop(); // 1
        }
        Pop(); // 1
        Push(num); // 2
        while (!tmp.isEmpty()) { // 3 + ∑_1^n▒〖(3 + 5)〗 = 3 + 8n
            Push(tmp.Top()); // 4
            tmp.Pop(); // 1
        }
    }


    void Swap(int pos1, int pos2) { // 32 + 52n
        int temp1 = Get(pos1); // 6 + 12n
        int temp2 = Get(pos2); // 6 + 12n
        Set(temp1, pos2); // 10 + 14n
        Set(temp2, pos1); // 10 + 14n
    }

    void Sort() { // 1 + 4n + 14n^2 + 24n^3
        int n = Size(); // 3
        bool swapped;
        do {
            swapped = false; // 1
            for (int i = 0; i < n - 1; i++) { // 3 + ∑_1^n▒〖(2 + 12 + 24n)〗 = 3 + 14n + 24n^2
                if (Get(i) > Get(i + 1)) { // 5 + 12n + 6 + 12n + 1 = 12 + 24n
                    Swap(i, i + 1); // 35 + 52n
                    swapped = true; // 1
                }
            }
        } while (swapped); // 1 + ∑_1^n▒〖(1 + 3 + 14n + 24n^2)〗 = 1 + 4n + 14n^2 + 24n^3
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