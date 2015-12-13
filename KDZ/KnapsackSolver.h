//
// Created by Computer on 06.12.2015.
//

#include<string>
#include<fstream>
#include<vector>

using namespace std;

class KnapsackSolver {
/*
 * Structs and enums for knapsack problem 
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
        friend bool operator==(const Item& lhs, const Item& rhs);

        friend bool operator!=(const Item& lhs, const Item& rhs);

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
        uint64_t time;
    };


/*
 * Параметры среды и переданные задачи о рюкзаке
 */
private:
    int _numberOfTests = 0;
    vector<Problem> _problems;
    vector<Solution> _solutions;
    int _currentProblem = 0;
/*
 * Конструктор и деструктор
 */
public:

    KnapsackSolver(vector<Problem> problems);

    virtual ~KnapsackSolver();

public:

    int getNumberOfTests() const;

    vector<Problem> getProblems() const;

    vector<Solution> getSolutions() const;

/*
 * Реализации методов решения задачи о рюкзаке
 */
private:
    /*
     * Решает задачу итерационным методом перебора с возвратом
     */
    void solveIterative();

    /*
     * Решает задачу рекурсивным методом перебора с возвратом
     */
    void solveRecursive();

    /*
     * Внешние переменные для рекурсивного алгоритма, чтобы не возвращать/передавать в качестве аргументов
     */
    vector<Item> *_solveRecursive_knapsack;
    vector<int> *_solveRecursive_bestKnapsack;
    int _solveRecursive_knapsackWeight, _solveRecursive_knapsackCost;
    int _solveRecursive_bestCost, _solveRecursive_bestSize;


    void _solveRecursive_grain(int currentItem);

    /*
     * Решает задачу методом динамического программирования
     */
    void solveDynamic();

    vector<Item> *_solveDynamic_items;
    vector<Item> *_solveDynamic_knapsack;
    int **_solveDynamic_matrix;

    void _solveDynamic_grain(int n, int m);
    /*
     * Решает задачу методом "жадного" алгоритма
     */
    void solveGreedy();


	void destroySolutions();


/*
 * Методы для пользователя класса
 */
public:
    /*
     * Решает конкретную задачу о рюкзаке указанным методом
     * Добавляет экземпляр класса Solution в _solutions
     */
    void solve(int problemNumber, Method method, int times);

	/*
     * Производит решение доступных для экземпляра класса KnapsackSolver задач о рюкзаке
     * Инициализирует поле solutions
     */
    void resolveAll(int times);

    static vector<Problem> *problemsFromFile(string inputPath);

	void solutionsToStream(ostream** streams,int streamNumber);
    
    static string methodToString(Method method);

};

