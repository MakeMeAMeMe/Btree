#include <chrono>
#include <iostream>
#include <random>
#include <ctime>

int main() {
    srand(time(NULL));
    double aux;
    aux = 0;
    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < 100000000; i++)
    {
        aux += ((double)rand()) / RAND_MAX;
    }
    std::cout << "aux: " << aux << std::endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
