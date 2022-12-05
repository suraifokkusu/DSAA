#include <iostream>
using namespace std;

struct Node {
    int num;
    string mark;
    string nameDriver; 
    Node* next;

    Node(int _num, string _mark, string _nameDriver) : num(_num), mark(_mark), nameDriver(_nameDriver),  next(nullptr) {} //конструктор
};

struct list {
    Node* head;
    Node* last;
    int countOfNode = 0; 

    list() : head(nullptr), last(nullptr) {}

    bool is_empty() {
        return head == nullptr;
    }

    void push_back(int _num, string _mark, string _nameDriver) {
        Node* p = new Node(_num, _mark, _nameDriver);
        if (is_empty()) {
            head = p;
            last = p;
            countOfNode = 1; 
            return;
        }
        //cout << countOfNode;
        countOfNode += 1;
        last->next = p;
        last = p;
    }

    void printTitle() {

        cout << "------------------------------------------------------" << endl;
        cout << "COUNT\tCAR NUM\t\tMARK\tNAME_DRIVER" << endl;
        cout << "------------------------------------------------------" << endl;
    }
    void print() {
        if (is_empty()) return;
        Node* p = head;
        int count = 1; 
        printTitle(); 
        while (p) {
            cout << count<< ".\t"
                 <<  p->num 
                 << "\t\t" << p->mark
                 << "\t" << p->nameDriver
                 <<endl;
            p = p->next;
            count++; 
        }
        cout << endl;
    }

    Node* find(int _num) {
        Node* p = head;
        while (p && p->num != _num) p = p->next;
        return (p && p->num == _num) ? p : nullptr;
    }

    void remove_first() {
        if (is_empty()) return;
        Node* p = head;
        head = p->next;
        delete p;
        countOfNode -= 1;
    }

    void remove_last() {
        if (is_empty()) return;
        if (head == last) {
            remove_first();
            return;
        }
        Node* p = head;
        while (p->next != last) p = p->next;
        p->next = nullptr;
        delete last;
        last = p;
        countOfNode -= 1;
    }

    void remove(int _num) {
        if (is_empty()) return;
        if (head->num == _num) {
            remove_first();
            return;
        }
        else if (last->num == _num) {
            remove_last();
            return;
        }
        Node* slow = head;
        Node* fast = head->next;
        while (fast && fast->num != _num) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            cout << "this element does not exist" << endl;
            return;
        }
        slow->next = fast->next;
        delete fast;
        countOfNode -= 1; 
    }

    Node* operator[] (const int index) {
        if (is_empty()) return nullptr;
        Node* p = head;
        for (int i = 0; i < index; i++) {
            p = p->next;
            if (!p) return nullptr;
        }
        return p;
    }
};

void mainDisplay() {
    cout << "------------------------------------------------------" << endl;
    cout << "1. Add car mark, car num, nameDriver" << endl;
    cout << "2. Delete car by number" << endl;
    cout << "3. Show count of cars" << endl;
    cout << "4. Find a car by num." << endl;
    cout << "5. Show list." << endl;
    cout << "6. Clear the terminal." << endl;
    cout << "0. Exit" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "ENTER THE NUMBER OF OPERATION" << endl;
    cout << "-> ";
}

int main()
{
    list l;
    while (true) {
        mainDisplay();
        int mainChooseOfUser;
        cin >> mainChooseOfUser;
        string _mark, _nameDriver;
        int _num; 
        int numDel, numFind; 
        switch (mainChooseOfUser) {
        case 0:
            return 0;
        case 1:
            cout << "enter num car: ";  cin >> _num; cout << endl;
            cout << "enter mark car: ";  cin >> _mark; cout << endl;
            cout << "enter nameDriver car: ";  cin >> _nameDriver; cout << endl;
            l.push_back(_num, _mark, _nameDriver);
            cout << "SUCCESS!" << endl;
            system("pause");
            break;
        case 2:
            cout << "enter numDel: "; cin >> numDel; 
            l.remove(numDel); 
            system("pause");
            break;
        case 3:
            if (l.countOfNode == 0) cout << "list empty!\n";
            else
                cout << "count: " << l.countOfNode <<endl;
            break;
        case 4:
            cout << "enter findNum car: ";  cin >> numFind; cout << endl;
            if (l.find(numFind) != nullptr)
                cout << "find car" << endl
                << "num: " << l.find(numFind)->num << endl
                << "mark: " << l.find(numFind)->mark << endl
                << "nameDriver: " << l.find(numFind)->nameDriver << endl; 
            else
                cout << "car not finded" << endl;

            system("pause");
            break;

        case 5:
            l.print(); 
            system("pause");
            break;
        case 6:
            system("CLS");
            break;
        default:
            cout << "unknown operation, try again" << endl;
            system("pause");
            break;
        }
    }
}