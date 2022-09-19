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
    cout << "3. Read text" << endl;
    cout << "4. Clear the terminal" << endl;
    cout << "0. Exit" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "ENTER THE NUMBER OF OPERATION" << endl;
    cout << "-> ";
}

int readText(Text* text, char* textStr, int count=0) { //по умолчанию количество лексем 0, чтобы считал с самого начала

    char separator[2] = " "; //это разделитель по которому strtok понимает, что когда этот разделитель встретился, то это отдельное слово (см. файл txt, поймешь)

    char* temp = new char[50];//переменная для того, чтобы strtok закинул лексему tempStr туда
    temp = textStr; 



   strtok(temp, separator); //здесь функция strtok обрабатывает ту строку, которую считали и "режет" ее пока не встретит разделитель, и записывает значение в temp
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
 
    delete[] temp; //удаление используемой памяти
    return count; 
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
    Text sortedText[SIZE]; //олтдельный массив для вывода результата, чт обы не терять изначальный массив, в который мы считаем данные с текста
    int count = 0; //это счетчик для того, чтобы обращаться по индексу массива и записывать в него 
    bool textExist = false; //изначально массив пустой
    char strUser[100] = "H1! 1m 4lb3rt 1 n33d sl33p";
    
    int mainChooseOfUser;
    while (true) {
        mainDisplay(); //каждый раз вывод команд 

        cin >> mainChooseOfUser;

        switch (mainChooseOfUser) {
        case 0:
            return 0;
        case 1:
            if (!textExist) { cout << "Array empty!\n"; break; } //если строчку еще не считали - выходим
            showResult(sortedText, count); //тут передаем тот масмсив с которым будем работать
            break;
        case 2:
            if (!textExist) { cout << "Array empty!\n"; break; } //если строчку еще не считали - выходим
            showText(text, count); //тут передаем массив работающий с файлом
            break;
        case 3:
            count = readText(text, strUser);
            textExist = true; 
            if (count == -1) return 1;;
            for (int index = 0; index < count; index++) //копирование массива который содержит данные файла в тот с которым будем работать
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