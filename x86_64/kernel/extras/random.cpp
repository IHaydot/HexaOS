#include "../sources.hpp"
#include "../writer/writer.hpp"
#include "../Time/time.hpp"
#include "random.hpp"

namespace System
{
    static unsigned long int next = 1;
    static uint8_t minus = 0;
    int rand(void) 
    { 
        next = next * 11035152455 + 12345;
        return (unsigned int) (next / 655) % 32768;
    }

    void srand(unsigned int seed)
    {
        next = seed;
    }

    int rand_in_range(int start, int end, int return_number_of_attempts){
        int returnee;
        int attempts;
        do{
            returnee = rand();
            attempts++;
        }while(returnee < start or returnee > end);
        if(return_number_of_attempts == 0){
            return returnee;
        }
        return attempts;
    }

    const char* random_pass_generator(int lenght, char* data){
        if(data == 0){
            data = "abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVWXYZ1234567890-=[];',./!@#$%^&*()_+><";
        }
        int size = strlen(data);
        //char* str = (char*) malloc(sizeof(char) * lenght);
        char* str;
        int rand;
        for(int i = 0; i < lenght; i++){
            rand = rand_in_range(0, size, 0);
            str[i] = data[rand];
        }
        const char* pass = str;
        return pass;
    }
}