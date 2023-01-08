#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int task()
{
    string s;
    cout << "Enter a string (to exit the program press ENTER): ";
    getline(cin, s);
    if (s == "") return 0;
    string* words = new string[s.length()]; //массив строк
    int k = 0; //кол-во слов 

    for (int i = 0; i < s.length() + 1; i++) {
        if ((s[i] == ' ') || (s[i] == '\0')) {
            k++;
            continue;
        }
        words[k] += s[i];// делим на лексемы 
    }

    int* counters_letter = new int[k];
    for (int i = 0; i < k; i++) {
        counters_letter[i] = 0;
    }

    for (int i = 0; i < k; i++) { //подсчет символов в слове
        for (int j = 0; j < words[i].length(); j++) {
            if ((words[i][j] >= '0') && (words[i][j] <= '9')) {
                counters_letter[i]++;
            }
            else if (((words[i][j] >= 'A') && (words[i][j] <= 'Z')) || ((words[i][j] >= 'a') && (words[i][j] <= 'z'))) {
                counters_letter[i]++;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        cout << words[i] << ": "  << counters_letter[i] << " - letter" << "\n";
    } 


    int max_letter = counters_letter[0], min_letter = counters_letter[0];
    int id_minl = 0, id_maxl = 0;
    for (int i = 0; i < k; i++) {
        if (counters_letter[i] > max_letter) {
            max_letter = counters_letter[i];// макс колво цифр
            id_maxl = i;// айди этого слова
        }
        if (counters_letter[i] < min_letter) {
            min_letter = counters_letter[i];// мин колво букв
            id_minl = i;// индекс мин слова
        }
    }
    
    string temp = words[id_minl];
    words[id_minl] = words[id_maxl];
    words[id_maxl] = temp;  //меняем местами слова с макс и мин кол-вом символов 

    for (int i = 0; i < k; i++) cout << words[i] << " ";
    cout << "\n";
    task();
}

int main() {
    task();
    return 0;
}
