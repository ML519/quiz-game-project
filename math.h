#include <stdlib.h>
#include <random>
#include <chrono>
namespace Math {
    int RandomInt(int min, int max)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(min, max);

        int result = distribution(generator);
        return result;
    }
};
