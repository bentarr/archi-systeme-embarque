#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>
#include <csignal>
#include <cmath>
#include <unistd.h>

int main(void)
{
    for (int i = 0; i < 5; i++)
    {
        using std::chrono::system_clock;
        std::time_t tt = system_clock::to_time_t(system_clock::now());
        struct std::tm *ptm = std::localtime(&tt);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "test" << std::endl;
        std::cout << ptm << std::endl;
    }
}
