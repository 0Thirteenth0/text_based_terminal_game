#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sstream>
#include <cmath>
#include <sys/ioctl.h>
#include <vector>
#include <filesystem>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fcntl.h>
#include "utility.hpp"

int main(int argc, char **argv) {
    while (!kbhit())
    {
        /* code */
    }
    std::cout << "get character: " << getchar() << std::endl;
    
}