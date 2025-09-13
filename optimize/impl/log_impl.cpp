#include <ctime>
#include <iostream>
#include <fstream>
#include <exception>
#include <cstring>
#include "test_driver.h"
#include "stopwatch11.h"

char* timetoa(char* buf, std::size_t bufsz) {
    if(buf == 0 || bufsz < 9) {  // invalid arguments
        return nullptr; 
    }

    time_t t = std::time(nullptr); // Get time from OS
    tm tm_ = *(std::localtime(&t)); // break time into hours, minutes, seconds
    std::size_t sz = std::strftime(buf, bufsz, "%c", &tm_); // format into buffer
    if(sz == 0) strcpy(buf, "XX:XX:XX");  // error
    return buf;
}

int test_log(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch (test_no) {
    default:
        return -1;
    case 0:
        return 3;
    
    case 1: {
        char buf[50];
        std::cout << timetoa(buf, sizeof(buf)) << std::endl;
    }
        break;

    case 2: {
        char buf[50];
        StopWatch sw("timetoa()");
        for(unsigned i=0; i < 1000*multiplier; ++i) {
            timetoa(buf, sizeof(buf));
        }
    }
        break;

    case 3: {
        char const file_name[] = "log_tester.txt";
        std::ofstream out(file_name);
        if(!out) {
            std::cout << "Can't open " << file_name << " for writting" << std::endl;
            return 0;
        }    

        {
            char buf[50];
            timetoa(buf, sizeof(buf));
            StopWatch sw("no timetoa()");
            for(unsigned i=0; i<1000 * multiplier; ++i) {
                out << buf << " Test log line test log line test log line\n";
            }
            out.flush();
        }

        out.seekp(0);
        {
            char buf[50];
            StopWatch sw("timetoa() per 10 lines");
            for(unsigned i=0; i<1000 * multiplier; ++i) {
                if(i%10 == 0) {
                    timetoa(buf, sizeof(buf));
                }
                out << buf << " Test log line test log line test log line\n";
            }
            out.flush();
        }

        out.seekp(0);
        {
            char buf[50];
            StopWatch sw("timetoa() per line");
            for(unsigned i=0; i<1000 * multiplier; ++i) {
                out << timetoa(buf, sizeof(buf)) <<  " Test log line test log line test log line\n";
            }
            out.flush();
        }

        std::remove(file_name);
    }
        break;
    }

    return rc ? 1: 0;
}