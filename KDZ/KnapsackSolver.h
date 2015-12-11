//
// Created by Computer on 06.12.2015.
//

#include<string>
#include<fstream>
#include<vector>

using namespace std;

class KnapsackSolver {
/*
 * Структуры и перечисления для решения задачи о рюкзаке
 */
public:
    /*
     * Метод решения задачи о рюкзаке
     */
    enum Method {
        ITERATIVE, RECURSIVE, DYNAMIC, GREEDY, ALL
    };

    /*
     * Структура, описывающая предмет
     */
    struct Item {
        Item() {
            /* Default initialization is senseless */
        };

        /*
         * Конструктор
         */
        Item(int number, int weight, int cost);

        /*
         * Начальный номер предмета
         */
        int number;

        /*
         * Вес предмета
         */
        int weight;

        /*
         * Стоимость предмета
         */
        int cost;
    };

    /*
     * Структура, описывающая конкретную задачу о рюкзаке
     */
    struct Problem {
        Problem() {
            /* Default initialization is senseless */
        };

        /*
         * Конструктор
         */
        Problem(int maxWeight, int itemsNumber, vector<Item> *items);

        /*
         * Деструктор отсутствует. Массив не создается конструктором Problem.
         * Освобождение памяти на ответственности создателя массива.
         */

/*
         * Максимальный допустимый вес рюкзака
         */
        int maxWeight;

        /*
         * Количество доступных предметов
         */
        int itemsNumber;

        /*
         * Доступные предметы
         */
        vector<Item> *items;


    };

    /*
     * Структура, описывающая результат решения задачи о рюкзаке
     */
    struct Solution {
        /*
         * Конструктор
         */
        Solution(int weight, int cost, int itemsNumber, vector<Item> *items, const Method method, int64_t time);

        Solution() {
            /* Default initialization is senseless */
        };

        /*
         * Деструктор отсутствует. Массив не создается конструктором Problem.
         * Освобождение памяти на ответственности создателя массива
         */

/*
         * Вес рюкзака
         */
        int weight;

        /*
         * Суммарная стоимость предметов в рюкзаке
         */
        int cost;

        /*
         * Количество предметов
         */
        int itemsNumber;

        /*
         * Доступные предметы
         */
        vector<Item> *items;

        /*
         * Использованный метод
         */
        Method method;

        /*
         * Время расчета, нс
         */
        int64_t time;
    };


/*
 * Параметры среды и переданные задачи о рюкзаке
 */
private:
    string _inputPath;
    string _outputPath;
    int _numberOfTests = 0;
    vector<Problem> *_problems = new vector<Problem>();
    vector<Solution> *_solutions = new vector<Solution>();

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
    string getInputPath() const {
        return _inputPath;
    }

    /*
     * Путь к выходному файлу
     */
    string getOutputPath() const {
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

