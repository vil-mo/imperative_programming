// структура, в которой хранится разложение на простые множители
typedef struct Factors {
    int k;          // сколько различных простых в разложении
    int primes[32]; // различные простые в порядке возрастания
    int powers[32]; // в какие степени надо эти простые возводить
} Factors;

// функция, которая находит разложение числа X и записывает его в структуру res
void Factorize(int X, Factors *res) {
    res->k = 0;

    for (int p = 2; p * p <= X; p++) {
        if (X % p == 0) {
            res->powers[res->k] = 0;
            res->primes[res->k] = p;

            do {
                X /= p;
                res->powers[res->k] += 1;
            } while (X % p == 0);

            res->k += 1;
        }
    }

    if (X != 1) {
        res->powers[res->k] = 1;
        res->primes[res->k] = X;
        res->k += 1;
    }
}
