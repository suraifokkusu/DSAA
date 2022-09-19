#define _CRT_SECURE_NO_WARNINGS //эта штука нужна для использования strtok, поскольку в новых релизах ее использование небезопасно
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm> //см. 98 строку
using namespace std;
struct Text { //звено, из которого потом наращиваем массив
    string lexem;
    int countOfLetter; 
    int countOfDigit = 0; //по умолчанию цифр в слове нет
}; //лексема + кол-во букв и цифр в ней

void mainDisplay() { //просто функция для вывода команд 
    cout << "----------------------------------------------" << endl;
    
    cout << "1. Show result" << endl;
    cout << "2. Show text" << endl;
    cout << "3. Add the word in the text" << endl;
    cout << "4. Clear the terminal" << endl;
    cout << "0. Exit" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "ENTER THE NUMBER OF OPERATION" << endl;
    cout << "-> ";
}

int readFile(Text* text, int count = 0) { //по умолчанию количество лексем 0, чтобы считал с самого начала
    ifstream file("db.txt"); //поток-файл, просто открываем файл txt

    if (!file) { //если не открылся - выходим из программы
        cout << "Error! File not open...\n";
        return -1;
    }

    char tempStr[100]; //переменная для перегонки строк из файла в самом strtok 
    char separator[2] = " "; //это разделитель по которому strtok понимает, что когда этот разделитель встретился, то это отдельное слово (см. файл txt, поймешь)

    char* temp = new char[50];//переменная для того, чтобы strtok закинул лексему tempStr туда

    while (!file.eof()) { //пока не конец файла
        file.getline(tempStr, sizeof(tempStr)); //считываем строку(!) 

        strcpy(temp, strtok(tempStr, separator)); //здесь функция strtok обрабатывает ту строку, которую считали и "режет" ее пока не встретит разделитель, и записывает значение в temp
        //это особенность работы в strtok, ему нужен именно указатель, поэтому и используем указатель на символ temp

        while (temp != NULL) {
            text[count].lexem = string(temp); 
            text[count].countOfLetter = strlen(temp); //длина лексемы
            for (int i = 0; i <= text[count].countOfLetter; i++) //если находит цифру в слове, то увеличивает счетчик цифр в этом слове
                if (isdigit(int(temp[i])))
                    text[count].countOfDigit++;
            temp = strtok(NULL, separator);
            count++; //как только обработали лексему, увеличиваем индекс и работаем дальше
        }
    }
    delete[] temp; //удаление используемой памяти
    return count; 
}
int writeFile() {
    ofstream file; 
    file.open("db.txt", ios_base::app); //запись в конец файла
    string strOfUser; 
    cout << "Enter the string: "; 
    cin >> strOfUser; 
    file << " " << strOfUser; //записываем то что ввели в конец файла через пробел
    file.close();
    return 0;
}
void showText(Text* text, int count) {
    for (int indexLexem = 0; indexLexem < count; indexLexem++) {
        cout << text[indexLexem].lexem << endl; //вывод всех лексем
    }
}
void showResult(Text* text, int count) {
    int indexOfMaxDigitWord = 0;
    int indexOfMinLetterWord = 0;
    int countOfDigit = text[0].countOfDigit;
    int countOfLetter = text[0].countOfLetter;

    for (int index = 0; index < count; index++) { //находим лексему с максимальным количеством цифр + с минимальным количеством букв
        if (text[index].countOfDigit > countOfDigit) {
            countOfDigit = text[index].countOfDigit;
            indexOfMaxDigitWord = index;
        }

        if (text[index].countOfLetter < countOfLetter) {
            countOfLetter = text[index].countOfLetter;
            indexOfMinLetterWord = index;
        }
    }

        Text temp = text[indexOfMaxDigitWord]; //перетаскиваем звено с максимальным количеством цифр в начало
        for (int index = indexOfMaxDigitWord; index > 0; index--) 
            text[index] = text[index - 1];
        text[0] = temp;
        
 
       //меняем регистр на верхний у той строки где меньше букв, используя библиотеку algorithm
    transform(text[indexOfMinLetterWord].lexem.begin(), text[indexOfMinLetterWord].lexem.end(), text[indexOfMinLetterWord].lexem.begin(), ::toupper); 

    for (int index = 0; index < count; index++) {
        cout << text[index].lexem << " - " << text[index].countOfDigit << " digits";
        if (index == indexOfMinLetterWord)
            cout << " (MIN WORD)"; 
        cout << endl; 
    }
}


const int SIZE = 200; //изначальная размерность массива

int main()
{
    Text text[SIZE]; //массив структуры-звена, то есть в каждом элементе массива у нас будет то самое звено Text 
    Text sortedText[SIZE]; //олтдельныйц массив для вывода результата, чт обы не терять изначальный массив, в который мы считаем данные с файла
    int count = 0; //это счетчик для того, чтобы обращаться по индексу массива и записывать в него 
    count = readFile(text); //после считывания вернет количество элементов
    if (count == -1) return 1; //если вернет -1 выход из программы, поскольку не открыл файл 

    for (int index = 0; index < count; index++) //копирование массива который содержит данные файла в тот с которым будем работать
        sortedText[index] = text[index];
    


    int mainChooseOfUser;
    while (true) {
        mainDisplay(); //каждый раз вывод команд 

        cin >> mainChooseOfUser;

        switch (mainChooseOfUser) {
        case 0:
            return 0;
        case 1:
            showResult(sortedText, count); //тут передаем тот масмсив с которым будем работать
            break;
        case 2:
            showText(text, count); //тут передаем массив работаюзий с файлом
            break;
        case 3: 
            writeFile();
            count = readFile(text); //см. 115 строку
            if (count == -1) return 1;
            for (int index = 0; index < count; index++)
                sortedText[index] = text[index];
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