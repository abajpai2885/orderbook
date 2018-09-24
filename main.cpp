
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include "error_monitor.h"
#include "feed_handler.h"

int main(int argc, char **argv)
{
    JT::FeedHandler feed;
    std::string line;
    const std::string filename(argv[1]);
    std::ifstream infile(filename.c_str(), std::ios::in);

    decltype(std::chrono::high_resolution_clock::now()) start;
    decltype(start) end;
    uint64_t ticks = 0;
    int counter = 0;

    while (std::getline(infile, line)) {
        start = std::chrono::high_resolution_clock::now();
        feed.ProcessMessage(line);
        end = std::chrono::high_resolution_clock::now();

        ++counter;
#ifndef PROFILE
        if (counter % 10 == 0) {
            feed.PrintCurrentOrderBook(std::cout);
            //JT::ErrorMonitor::GetInstance().PrintStats();
        }
#endif
        ticks += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }



    feed.PrintCurrentOrderBook(std::cout);
    JT::ErrorMonitor::GetInstance().PrintStats();
    std::cout << "total time: " << ticks << " per msg:" << ticks/counter << " nanoseconds." << std::endl;
    return 0;
}
