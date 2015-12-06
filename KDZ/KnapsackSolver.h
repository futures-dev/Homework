//
// Created by Computer on 06.12.2015.
//

#include<string>
#include<fstream>
#include<vector>
#include <bits/stl_vector.h>

using namespace std;

class KnapsackSolver {
/*
 * Структуры и перечисления для решения задачи о рюкзаке
 */
public:
    /*
     * Структура, описывающая конкретную задачу о рюкзаке
     */
    struct Problem {
        /*
         * Максимальный допустимый вес рюкзака
         */
        int maxWeight;

        /*
         * Количество доступных предметов
         */
        int itemsNumber;

        /*
         * Веса предметов
         */
        int *itemsWeights;

        /*
         * Стоимость предметов
         */
        int *itemsCosts;


    };

    /*
     * Структура, описывающая результат решения задачи о рюкзаке
     */
    struct Solution {
        /*
         * Вес рюкзака
         */
        int weight;

        /*
         * Суммарная стоимость предметов в рюкзаке
         */
        int cost;

        /*
         * Номера предметов в рюкзаке
         */
        int *items;

        /*
         * Веса предметов. Нумерация по индексам массива items
         */
        int *weights;

        /*
         * Стоимость предметов. Нумерация по индексам массива items
         */
        int *costs;

        /*
         * Использованный метод
         */
        Method method;

        /*
         * Время расчета, нс
         */
        int time;
    };

    /*
     * Метод решения задачи о рюкзаке
     */
    enum Method {
        ITERATIVE, RECURSIVE, DYNAMIC, GREEDY, ALL
    };

/*
 * Параметры среды и переданные задачи о рюкзаке
 */
private:
    string _inputPath;
    string _outputPath;
    int _numberOfTests;
    vector<Problem> *_problems;
    vector<Solution> *_solutions;

/*
 * Конструктор и деструктор
 */
public:

    KnapsackSolver(string inputPath, string outputPath);

    virtual ~KnapsackSolver();

public:
/*
 * Путь к входному файлу
 */
    string &getInputPath() const {
        return _inputPath;
    }

    /*
     * Путь к выходному файлу
     */
    string &getOutputPath() const {
        return _outputPath;
    }

    /*
     * Количество конкретных задачи для решения
     */
    int getNumberOfTests() const {
        return _numberOfTests;
    }

    /*
     * Конкретные задачи о рюкзаке для решения
     */
    vector<Problem> *getProblems() const {
        return _problems;
    }

    /*
     * Результат решения задач
     */
    vector<Solution> *getSolutions() const {
        return _solutions;
    }

/*
 * Реализации методов решения задачи о рюкзаке
 */
private:
    /*
     * Решает задачу итерационным методом перебора с возвратом
     */
    static Solution solveIterative(Problem problem);

    /*
     * Решает задачу рекурсивным методом перебора с возвратом
     */
    static Solution solveRecursive(Problem problem);

    /*
     * Решает задачу методом динамического программирования
     */
    static Solution solveDynamic(Problem problem);

    /*
     * Решает задачу методом "жадного" алгоритма
     */
    static Solution solveGreedy(Problem problem);

/*
 * Методы для пользователя класса
 */
public:
    /*
     * Решает конкретную задачу о рюкзаке указанным методом
     * Возвращает экземпляр класса Solution
     */
    static Solution solve(Problem problem, Method method);

    /*
     * Производит решение доступных для экземпляра класса KnapsackSolver задач о рюкзаке
     * Инициализирует поле solutions
     */
    void solve(Method method);

};


#endif //KDZ_BAGPACKSOLVER_H
