//#include "stdafx.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
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


void DNARepairer::readFile(string filename) {
    {
        ifstream file(filename, ios_base::in);

        if (!file) {
            throw std::invalid_argument("File could not be opened");
        }
        string line;
        getline(file, line);
        int linesNumber = atoi(line.c_str());
        int i = 0;
        Node<LinkedList<DNAElement>> *it = DNAStorage.getPreHead();
        while (getline(file, line)) {
            if (++i > linesNumber) {
                break;
            }
            Node<LinkedList<DNAElement>> *node = new Node<LinkedList<DNAElement>>;
            istringstream words(line);

            string word;

            while (words >> word) {
                DNAElement element;
                element.readString(word);
                node->value.addElementToEnd(element);
            }
            it->next = node;
            it = it->next;
        }
        if (i < linesNumber) {
            throw invalid_argument("Not enough strings in input");
        }
    }
    /*
        ifstream fin(filename);

        if (!fin) {
            cout << "File couldn't be opened :" << filename << endl;
            return;
        }

        string line;
        getline(fin, line); // для пропуск первой строчки с числом строк

        Node<LinkedList<DNAElement>> *it = DNAStorage.getPreHead();
        while (getline(fin, line)) {
            Node<LinkedList<DNAElement>> *pNewNode = new Node<LinkedList<DNAElement>>;
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
    */
}

LinkedList<LinkedList<DNAElement>> &DNARepairer::getDNAStorage(void) {
    return DNAStorage;
}

void DNARepairer::repairDNA(void) {
    int idNumber = 0;
    char ids['z' - 'a' + 1];
    for (int i = 0; i <= 'z' - 'a'; i++) {
        ids[i] = -1;
    }
    LinkedList<LinkedList<DNAElement>> DNAStorageNew;
    Node<LinkedList<DNAElement>> *dnaNode = DNAStorage.getPreHead();
    while (dnaNode->next) {
        dnaNode = dnaNode->next;
        Node<DNAElement> *before = dnaNode->value.getPreHead();
        Node<DNAElement> *last = before;
        char currentId;
        int currentNumber;
        while (last->next) {
            before = last;
            last = before->next;
            currentId = last->value.id[0];
            currentNumber = last->value.number;
            while (last->next && last->next->value.id[0] == currentId &&
                   last->next->value.number == (++currentNumber)) {
                last = last->next;
            }
            currentId -= 'a';
            int index = ids[currentId];
            if (index < 0) {
                ids[currentId] = index = idNumber;
                idNumber++;
                // addElementToEnd зачем-то принимает ссылку вместо объекта
                DNAStorageNew.addElementToEnd(*new DNA());
            }
            Node<DNAElement> *current = DNAStorageNew[index].getPreHead();
            while (current->next && (current->next->value.number < currentNumber)) {
                current = current->next;
            }
            DNAStorageNew[index].moveNodesAfter(current, before, last);
            last = before; // last.value should be nullptr, last is prehead
        }
    }
    Node<DNA> *prev = DNAStorage.getPreHead();
    Node<DNA> *last = DNAStorage.getPreHead();
    while (last->next) {
        prev = last;
        last = last->next;
    }
    Node<DNA> *lastNew = DNAStorageNew.getPreHead();
    while (lastNew->next) {
        lastNew = lastNew->next;
    }
    DNAStorage.moveNodesAfter(DNAStorage.getPreHead(), DNAStorageNew.getPreHead(), lastNew);
    DNAStorageNew.moveNodesAfter(DNAStorageNew.getPreHead(), prev, last);
    //delete DNAStorageNew;
}

void DNARepairer::printDNAStorage(void) {
    Node<LinkedList<DNAElement>> *dnaNode = DNAStorage.getPreHead();
    while (dnaNode->next) {
        dnaNode = dnaNode->next;
        Node<DNAElement> *elementNode = dnaNode->value.getPreHead();
        while (elementNode->next) {
            elementNode = elementNode->next;
            cout << elementNode->value.id << elementNode->value.number << ":" << elementNode->value.base << " ";
        }
        cout << endl;
    }
}
