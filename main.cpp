#include "rateLimiter/RateLimiter.hpp"
#include <iostream>
#include <future>
#include <ctime>
using namespace rateLimiter;
using namespace std::chrono_literals;

int main(){
    rate_limiter limit(1,5s);
    time_t t_start, t_finish;

    auto a = std::async(std::launch::async,[&](){
        int i=10;
        while(i>0) {

            time(&t_start);
            limit.acquire();
            std::cout << "A: Locked\n";
            time(&t_finish);
            std::cout << "Time elapsed = " << difftime(t_finish, t_start) << " seconds\n";
            i--;
        }

    });
//    auto b =std::async(std::launch::async,[&](){
//        int i=10;
//        while(i>0){
//
//            limit.acquire();
//            std::cout<<" B: Locked\n";
//            i--;
//        }
//
//    });
    a.wait();
//    b.wait();
    return 0;
}