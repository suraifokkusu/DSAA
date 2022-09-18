#define _CRT_SECURE_NO_WARNINGS //эта штука нужна дя использования strtok, поскольку в новых релизах ее использование небезопасно
#include <iostream>
#include <string>
#include <fstream>

using namespace std; 
struct Company { //звено, из которого потом наращиваем массив
    string name; 
    string sphere;
    string directorFio; 
    int countOfEmployees;
};

void sort(Company* A, unsigned int n) //функция сортировки двоичными вставками, сюда передаем массив структур и размерность этого массива 
{
    /*
    Cортировка напоминает детскую игру "больше-меньше": после каждого сравнения обрабатываемая последовательность сокращается в два раза. 
    Сравниваем мы со средним элементом, и если он, к примеру, окажется меньше среднего, то все что больше - отсекаем, и работаем с оставшейся частью, находя новую середину. 
    
    Я приложил гифку в гите в корне папки этой лабораторной, посмотри, нагляднее будет
    */
    Company temp; //временная переменная
    int left; //границы
    int right;
    int sred;

    for (int i = 1; i < n; i++)
        if (A[i - 1].name > A[i].name) {
            temp = A[i]; //если предыдущий элемент больше, запоминаем текущий
            left = 0;
            right = i - 1;
            do {
                sred = (left + right) / 2; //середина
                if (A[sred].name < temp.name) left = sred + 1; //если элемент, который запомнили, больше середины - двигаем левую границу и наоборот
                else  right = sred - 1;
            } while (left <= right); //делаем это до тех пор, пока не найдем место для вставки 
            for (int j = i - 1; j >= left; j--)
                A[j + 1] = A[j]; //подтягиваем элементы "направо"
            A[left] = temp; //в освободившеееся место вставляем элемент 
        }
}
         
void mainDisplay() { //просто функция для вывода команд 
    cout << "---------------------------------------------------------------" << endl;
    cout << "1. Show list of companies" << endl;
    cout << "2. Sort list by name of company" << endl;
    cout << "3. Show sorted array" << endl;
    cout << "4. Clear the terminal" << endl;
    cout << "0. Exit" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "ENTER THE NUMBER OF OPERATION" << endl;
    cout << "-> ";
}

void titleDisplay() { //здесь заголовки того, что выводим
    cout << "---------------------------------------------------------------" << endl;
    cout << "NAME OF COMPANY\t\tSPHERE      \t\tDIRECTOR\t\tCOUNT OF EMPLOYEES" <<endl; 
    cout << "---------------------------------------------------------------" << endl<<endl;
}
const int SIZE = 20;  //размер задается здесь, в лабораторной указано минимум 20

int main()
{
    Company arrayOfCompanies[SIZE]; //массив структуры-звена, то есть в каждом элементе массива у нас будет то самое звено Company 
    ifstream file("db.txt"); //поток-файл, просто открываем файл txt

    if (!file) { //если не открылся - выходим из программы
        cout << "Error! File not open...\n";
        return 1;
    }

    // Дальше идет считывание с файла в массив структур  
    int count = 0; //это счетчик для того, чтобы обращаться по индексу массива и записывать в него 
    char tempStr[100]; //переменная для перегонки строк из файла в самом strtok 
    char separator[2] = "|"; //это разделитель по которому strtok понимает, что когда этот разделитель встретился, то это отдельное слово (см. файл txt, поймешь)


    char* temp = new char[50];//переменная для того, чтобы strtok закинул лексему tempStr туда
    /*
    Почему я так сделал? strtok работает с массивами типа char, а нам нужен string, так как он более удобный для сравнения непосредственно в функции сортировки
    Поэтому мы берем лексему и из char переводим ее в string. 

    Если вкратце? tempStr для работы strtok на получение лексемы, а temp для того, чтобы готовую лексему сделать из char в string
    */
    while (!file.eof()) { //пока не конец файла
        file.getline(tempStr, sizeof(tempStr)); //считываем строку(!) 

        strcpy(temp, strtok(tempStr, separator)); //здесь функция strtok обрабатывает ту строку, которую считали и "режет" ее пока не встретит разделитель, и записывает значение в temp
        arrayOfCompanies[count].name = string(temp); //здесь уже temp мы приводим к типу string и записываем в массив по полю, поскольку в файле мы изначально подразумеваем, что все прописано структурированно
        strcpy(temp, strtok(NULL, separator)); //здесь указатель NULL, поскольку это особенность работы strtok, условно, это говорит ему работать с уже порезанной строкой дальше
        arrayOfCompanies[count].sphere = string(temp);
        strcpy(temp, strtok(NULL, separator));
        arrayOfCompanies[count].directorFio = string(temp);
        arrayOfCompanies[count].countOfEmployees = atoi(strtok(NULL, separator)); //здесь из char в int (atoi)
        count++; //как только обработали строку, увеличиваем индекс и работаем дальше
    }
    delete[] temp; //удаление используемой памяти

    Company sortedArray[SIZE]; //отдельный массив, который будет сортирован, чтобы сохранить изначальный

    for (int i = 0; i < SIZE; i++)
        sortedArray[i] = arrayOfCompanies[i]; //здесь копирую изначальный в отсортированный


    int mainChooseOfUser;
    bool sorted = false; 
    while (true) {
        mainDisplay(); //каждый раз вывод команд 

        cin >> mainChooseOfUser; 

        switch (mainChooseOfUser) {
        case 0:
            return 0;
        case 1:
            titleDisplay(); //вывод изначального(!) массива, потому arrayOfCompanies
            for (int i = 0; i < SIZE; i++) {
                cout << arrayOfCompanies[i].name << "     \t\t"
                    << arrayOfCompanies[i].sphere << "      \t\t"
                    << arrayOfCompanies[i].directorFio << "\t\t\t"
                    << arrayOfCompanies[i].countOfEmployees << endl;
            }
            break;
        case 2:
            sort(sortedArray, SIZE); //сортируем ту самую копию изначального массива
            sorted = true; //сортировка прошла
            cout << "SUCCESS! SORT COMPLETE!" << endl;
            break;

        case 3:
            if (!sorted) cout << "WARNING: ARRAY DOESN'T SORTED!" << endl; //если сортировки не было, говорим об этом
            titleDisplay(); 
            for (int i = 0; i < SIZE; i++) {
                cout << sortedArray[i].name << "      \t\t" //здесь уже вывод sortedArray
                    << sortedArray[i].sphere << "      \t\t"
                    << sortedArray[i].directorFio << "\t\t\t"
                    << sortedArray[i].countOfEmployees << endl;
            }
            break;

        case 4:
            system("CLS"); //очистка терминала
            break;
        default:
            cout << "Unknown operation, try again" << endl;
            system("pause");
            break;
        }
    }
}
