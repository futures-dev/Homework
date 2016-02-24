//#include "stdafx.h"

#include <fstream>
#include <sstream>
#include "DNARepairer.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//  Очень важно!!
//  Этот файл является лишь примером-подсказкой, который
//  показывает как обращаться со списком имея доступ лишь
//  к pPreHead.
//  Вы должны опираясь на его реализовать свое правильное решение.
//  Например в методе readFile не проверяется формат и не
//  возбуждаются исключения, а repairDNA делает вообще
//  неизвестно что!!!
//  Кроме того этот пример будет работать только если у вас
//  правильно реализован LinkedList.h

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



typedef LinkedList<DNAElement> DNA;
// Класс DNA представляет список узлов, которые содержат DNAElement объекты
// Узел не то же самое, что значение!

typedef Node<DNAElement> NodeDNA;
// Класс NodeDNA представляет один узел, который содержат DNAElement
// Список DNA состоит из NodeDNA

void DNARepairer::repairDNA() {
    // Начало примера
    // ВАЖНО! Все содержимое этого метода всего лишь пример.
    // Удалите его и перепишите функцию repairDNA заново.

    Node<DNA> *it = DNAStorage.getPreHead();
    Node<DNA> *it1 = nullptr;
    Node<DNA> *it2 = nullptr;

    //Сохраняем указатель на первый узел с ДНК в it1
    it = it->next;
    it1 = it;

    //Сохраняем указатель на второй узел с ДНК в it2
    it = it->next;
    it2 = it;

    //Ищем элемент с id="a" во втором ДНК
    Node<DNAElement> *it3 = it2->value.getPreHead();
    while (it3->next != nullptr &&
           it3->next->value.id != "a") {
        it3 = it3->next;
    }

    //Перемещение одного элемента из второго списка в первый
    it1->value.moveNodeAfter(
            it1->value.getPreHead(),
            it3
    );
    // Конец примера

    //Write your code here...
}

void DNARepairer::printDNAStorage() {
    Node<DNA> *it1 = DNAStorage.getPreHead();
    while (it1->next != nullptr) {
        it1 = it1->next;
        //итерация по списку хранилища

        NodeDNA *it2 = it1->value.getPreHead();
        while (it2->next != nullptr) {
            it2 = it2->next;
            //итерация по списку ДНК

            cout << it2->value.id << "" << it2->value.number << ":";
            cout << it2->value.base << "  ";
        }
        cout << endl;
    }
}

void DNARepairer::readFile(string filename) {
    ifstream fin(filename);

    if (!fin) {
        cout << "File couldn't be opened :" << filename << endl;
        return;
    }

    string line;
    getline(fin, line); // для пропуск первой строчки с числом строк

    Node<DNA> *it = DNAStorage.getPreHead();
    while (getline(fin, line)) {
        Node<DNA> *pNewNode = new Node<DNA>;
        // Создаем узел ДНК на куче

        istringstream istr(line);
        //Создаем строковый поток для разбора

        string strTmp;

        while (istr >> strTmp) // разбиваем поток на слова
        {
            DNAElement tmpDNAElement;

            tmpDNAElement.readString(strTmp); // каждое слово читаем в DNAElement

            pNewNode->value.addElementToEnd(tmpDNAElement);
            // добавляем полученный DNAElement в ДНК
        }
        it->next = pNewNode;
        it = it->next;
        //сохраняем ДНК в хранилище
    }
}
