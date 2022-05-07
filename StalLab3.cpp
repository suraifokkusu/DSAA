
#include <iostream>
#include <list>
#include <stdio.h>

using namespace std; 
struct Student {   //Структура, являющаяся звеном списка
    string firstName, secondName, thirdname; 
    string group; 
    string event;
    string day, month, year;   //либо делать динамическую матрицу по числу n студентов в списке, размерностью [n][3]; 
    Student *next=nullptr, *prev=nullptr; //Указатели на адреса следующего и предыдущего элементов списка

};
class ListOfStudents {
public:
    Student* head, * tail; //Указатели на адреса начала списка и его конца
      // Количество элементов
    int Count=0;
    ListOfStudents() : head(NULL), tail(NULL) {}; 
    ~ListOfStudents(); //Инициализируем адреса как пустые
    // ПРОТОТИПЫ ФУНКЦИЙ 
    void AddStudent(Student* student); 
    int DeleteStudent(int indexOfDeleteStudent);
    int LengthOfList();
    int FindStudent(string firstName, string secondName);
    void ShowListOfStudents(); 
    void ShowStudent(int indexOfStudent);
};
enum GROUPS {
    PO_71,
    PM_71,
    F_71,
    KB_71
};
enum EVENTS {
    PERVOKURSNIK,
    STUDVESNA,
    ARTKAMPUS
};

ListOfStudents::~ListOfStudents()                           //Деструктор
{
    while (head)                       //Пока по адресу на начало списка что-то есть
    {
        tail = head->next;             //Резервная копия адреса следующего звена списка
        delete head;                   //Очистка памяти от первого звена
        head = tail;                   //Смена адреса начала на адрес следующего элемента
    }
}
void ListOfStudents::AddStudent(Student* student) {
    Student* temp = new Student;               //Выделение памяти под новый элемент структуры
    temp->next = NULL;                   //Указываем, что изначально по следующему адресу пусто


    temp->firstName = student->firstName;                         //Записываем значения в структуру
    temp->secondName = student->secondName;
    temp->thirdname = student->thirdname;
    temp->group = student->group;
    temp->event = student->event;
    temp->day = student->day;
    temp->month = student->month;
    temp->year = student->year;

    temp->prev = tail; 

    // Если элементы есть?
    if (tail != NULL)
        tail->next = temp;

    // Если элемент первый, то он одновременно и голова и хвост
    if (Count == 0)
        head = tail = temp;
    else
        // иначе новый элемент - хвостовой
        tail = temp;

    Count++;
}
int ListOfStudents::DeleteStudent(int indexDeletionOfStudent) {
    
    if (indexDeletionOfStudent == -1)
        return -1; 
    //Счетчик
    int i = 1;

    Student* del = head;

    while(i <indexDeletionOfStudent)
    {
        // Доходим до элемента, 
        // который удаляется
        del = del->next;
        i++;
    }

    // Доходим до элемента, 
    // который предшествует удаляемому
    Student* PrevDel = del->prev;
    // Доходим до элемента, который следует за удаляемым
    Student* AfterDel = del->next;

    // Если удаляем не голову
    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    // Если удаляем не хвост
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    // Удаляются крайние?
    if (indexDeletionOfStudent == 0)
        head = AfterDel;
    if (indexDeletionOfStudent == Count)
        tail = PrevDel;

    // Удаление элемента
    delete del;

    Count--;
    return 0; 
}
int  ListOfStudents::LengthOfList() {
    return Count; 
}
int  ListOfStudents::FindStudent(string firstName, string secondName) {
    Student* temp = head;
    bool studentNotFind = true;
    int indexOfStudent = 0;
    for (int i = 0; i < Count; i++) {
        if (firstName == temp->firstName && secondName == temp->secondName)
            return i;
        temp = temp->next;
    }
    return -1;

}
void ListOfStudents::ShowListOfStudents() {
   
    if (Count != NULL)

    {
        Student* temp = head;
        int _count = 0;

        cout << "---------------------------------------------------------------" << endl;
        cout << "FULL NAME\t\tGROUP\tEVENT\t\tDATE OF EVENT" << endl;
        cout << "---------------------------------------------------------------" << endl;

        while (temp != NULL) {
            _count++;
            ShowStudent(_count);
            temp = temp->next;
        }
    }
        
    else
        cout << "List is empty!" << endl;
}
void ListOfStudents::ShowStudent(int indexOfStudent) {
    if (indexOfStudent<1 ||indexOfStudent>Count) {
        cout << "Incorrect position" << endl;
        return;
    }
    Student* temp = head;
    int _count =1;
    while (_count<indexOfStudent) {
        temp = temp->next; 
        _count++;
        }
    cout << temp->firstName << " " << temp->secondName << " " << temp->thirdname;  //ФИО 
    cout << "\t" << temp->group;
    cout << "\t" << temp->event;
    cout << "\t";
        cout << temp->day << "."<<temp->month<<"." << temp->year;
    cout << endl;
}

void mainDisplay() {
    cout << "---------------------------------------------------------------" << endl;
    cout << "1. Add student in list of events." << endl;
    cout << "2. Delete student in list of events by name." << endl;
    cout << "3. Show count of students in list." << endl;
    cout << "4. Find a student by name." << endl;
    cout << "5. Show list." << endl;
    cout << "0. Exit" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "ENTER THE NUMBER OF OPERATION" << endl;
    cout << "-> ";
}
void groupDisplay() {
    cout << "\t1. PO-71 " << endl;
    cout << "\t2. PM-71" << endl;
    cout << "\t3. F-71" << endl;
    cout << "\t4. KB-71" << endl;
    cout << "\tENTER THE NUMBER OF OPERATION"<<endl; 
    cout << "\t-> ";
}
void eventDisplay() {
    cout << "\t1. PERVOKURSNIK" << endl;
    cout << "\t2. STUDVESNA" << endl;
    cout << "\t3. ARTKAMPUS" << endl;
    cout << "\tENTER THE NUMBER OF OPERATION" << endl;
    cout << "\t-> ";
}


inline const char* toStringEvent(EVENTS events)
{
    switch (events)
    {
    case PERVOKURSNIK:   return "PERVOKURSNIK";
    case  STUDVESNA:   return " STUDVESNA";
    case ARTKAMPUS: return "ARTKAMPUS";
    default:      return "[Unknown event]";
    }
}
inline const char* toStringGroup(GROUPS groups)
{
    switch (groups)
    {
    case PO_71:   return "PO_71";
    case  PM_71:   return "PM_71";
    case F_71: return "F_71";
    case KB_71: return "KB_71";
    default:      return "[Unknown group]";
    }
}

int main()
{
    ListOfStudents listOfStudents;

    int mainChooseOfUser, groupChooseOfUser, eventChooseOfUser;
    string firstName, secondName, thirdName, group = "", event = "", day, month, year;
    Student* newStudent;
    int indexOfDeletionStudent = -1, indexOfFindedStudent = -1;

    while (true) {
        mainDisplay();

        cin >> mainChooseOfUser;

        switch (mainChooseOfUser) {
        case 0:
            return 0;
        case 1:

            cout << "Enter the first name of student: ";
            cin >> firstName;
            cout << "Enter the second name of student: ";
            cin >> secondName;
            cout << "Enter the third name of student: ";
            cin >> thirdName;
            cout << "Сhoose group of student: " << endl;
            groupDisplay();
            cin >> groupChooseOfUser;
            switch (groupChooseOfUser)
            {
            case 1:
                group = toStringGroup(PO_71);
                break;
            case 2:
                group = toStringGroup(PM_71);
                break;
            case 3:
                group = toStringGroup(F_71);
                break;
            case 4:
                group = toStringGroup(KB_71);
                break;
            default:
                cout << "Unknown operation, group will be null" << endl;
                group = "NULL"; 
                break;
            }
            cout << "Сhoose event of student: " << endl;
            eventDisplay();
            cin >> eventChooseOfUser;
            switch (eventChooseOfUser)
            {
            case 1:
                event = toStringEvent(PERVOKURSNIK);
                break;
            case 2:
                event = toStringEvent(STUDVESNA);
                break;
            case 3:
                event = toStringEvent(ARTKAMPUS);
                break;
            default:
                cout << "Unknown operation, event will be null" << endl;
                event = "NULL";
                break;
            }

            cout << "Enter the date of event (example: 01.12.2000): ";
            cin >> day >> month >> year; 
           
            newStudent = new Student{ firstName, secondName, thirdName, group, event, day, month, year};
            listOfStudents.AddStudent(newStudent);
            //delete data; 
            cout << "SUCCESS!" << endl;
            system("pause");
            system("CLS");
            break;
        case 2:
            cout << "Enter the first name of deletion student: ";
            cin >> firstName;
            cout << "Enter the second name of deletion student: ";
            cin >> secondName;
            indexOfDeletionStudent = listOfStudents.FindStudent(firstName, secondName);
            if (indexOfDeletionStudent != -1) {
                listOfStudents.DeleteStudent(indexOfDeletionStudent);
                cout << "SUCCESS!" << endl;
            }
          else
              cout << "[Student not founded]" << endl;
            system("pause");
            system("CLS");
            break;
        case 3:
            cout << "Count of students: " << listOfStudents.LengthOfList() << endl;
            system("pause");
            system("CLS");
            break;
        case 4:
            cout << "Enter the first name of student for search: ";
            cin >> firstName;
            cout << "Enter the second name of student for search: ";
            cin >> secondName;
            indexOfFindedStudent = listOfStudents.FindStudent(firstName, secondName);
            if (indexOfFindedStudent != -1) {
                listOfStudents.ShowStudent(indexOfFindedStudent);
            cout << "SUCCESS!" << endl;
            }
            else
            cout << "[Student not founded]" << endl;
            system("pause");
            system("CLS");
            break;

        case 5:
            listOfStudents.ShowListOfStudents();
            system("pause");
            system("CLS");
            break;
        default:
            cout << "Unknown operation, try again" << endl;
            system("pause");
            system("CLS");
            break;
        }
    }
}
