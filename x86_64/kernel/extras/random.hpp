#include "../sources.hpp"

namespace System{
    
    void srand(unsigned int seed);
    int rand(void);
    int rand_in_range(int start, int end, int return_number_of_attempts);
    const char* random_pass_generator(int lenght, char* data);
}