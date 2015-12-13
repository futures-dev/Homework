//
// Created by Computer on 06.12.2015.
//

#include<string>
#include<fstream>
#include<vector>

using namespace std;

class KnapsackSolver {
/*
 * Структуры и перечисления, необходимые для решения задачи о рюкзаке
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
        Solution(int weight, int cost, int itemsNumber, vector<Item> *items, const Method method, int problem,
                 int64_t time);

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
         * Номер задачи
         */
        int problem;

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

    /*
     * Настраивает экземпляр класса KnapsackSolver на конкретные задачи
     */
    KnapsackSolver(vector<Problem> problems);

    /*
     * Очищает память, выделенную под задачи и решения
     */
    virtual ~KnapsackSolver();

    /*
     * Публичные свойства
     */
public:

    /*
     * Возвращает количество
     */
    int getNumberOfTests() const;

    /*
     * Возвращает вектор задач, доступных экземпляру класса KnapsackSolver
     */
    vector<Problem> getProblems() const;

    /*
     * Возвращает вектор решений, произведенных экземпляром класса KnapsackSolver
     */
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

    /*
     * Гранула рекурсии для рекурсивного алгоритма перебора с возвратом
     */
    void _solveRecursive_grain(int currentItem);

    /*
     * Решает задачу методом динамического программирования
     */
    void solveDynamic();

    /*
     * Переменные для рекурсии динамического алгоритма, чтобы не возвращать/передавать в качестве аргументов
     */
    vector<Item> *_solveDynamic_items;
    vector<Item> *_solveDynamic_knapsack;
    int **_solveDynamic_matrix;

    /*
     * Гранула рекурсии динамического алгоритма
     */
    void _solveDynamic_grain(int n, int m);

    /*
     * Решает задачу методом "жадного" алгоритма
     */
    void solveGreedy();

    /*
     * Освобождает память, выделенную под решения задач
     */
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

    /*
     * Генерирует вектор конкретных задач из входного файла
     */
    static vector<Problem> *problemsFromFile(string inputPath);

    /*
     * Выводит результат решения задач в потоки
     */
	void solutionsToStream(ostream** streams,int streamNumber);

    /*
     * Возвращает строковое представление перечисления Method
     */
    static string methodToString(Method method);

};

