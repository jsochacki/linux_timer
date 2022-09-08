#include <iostream>
#include "abbp_timer.hpp"

int main()
{
   TestBed::abbp_timer local_timer;

   std::chrono::time_point<std::chrono::steady_clock> t_start = local_timer.sys_clock.now();

   //std::chrono::duration<rep, period>
   //std::chrono::time_point<std::chrono::steady_clock>;

   std::cout << "compiled" << std::endl;

   std::chrono::time_point<std::chrono::steady_clock> t_end = local_timer.sys_clock.now();

   double timedif = std::chrono::duration<double, std::milli>(t_end - t_start).count();
   int64_t timedifi = std::chrono::duration<int64_t, std::nano>(t_end - t_start).count();
   int64_t timedifi2 = std::chrono::nanoseconds(t_end - t_start).count();

   std::cout << "t_delta = " << timedif << std::endl;
   std::cout << "t_delta = " << timedifi << std::endl;
   std::cout << "t_delta = " << timedifi2 << std::endl;

   return 0;

}
