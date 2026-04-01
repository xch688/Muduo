#include "sylar/log.h"

class LidarParser {
public:
    LidarParser() { SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "LidarParser..."; }
    ~LidarParser() { SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "~LidarParser..."; }
    void printMsg() { SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "hello world..."; }
};

thread_local LidarParser parser;

void threadFunc()
{
    parser.printMsg();
}

int main(int argc, char** argv)
{
    parser.printMsg();
    std::thread t1(threadFunc);
    t1.join();

    return 0;
}