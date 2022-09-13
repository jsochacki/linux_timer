#include <iostream>
#include "linux_timer.hpp"

int main()
{
   TestBed::linux_timer local_timer;
   local_timer.clear_timers();

   local_timer.tick("print statement 1");

   std::cout << "compiled" << std::endl;

   local_timer.tock("print statement 1");

   local_timer.tick("print statement 1");
   local_timer.tick("print statement 2");
   local_timer.tock("print statement 2");
   local_timer.tock("print statement 1");
   local_timer.tick("print statement 2");
   local_timer.tock("print statement 2");

   local_timer.print_timer_all_point_to_point();
   local_timer.print_timer_point_to_point();
   local_timer.print_timer_point_to_point();
   local_timer.print_timer_cumulants();
   local_timer.clear_timers();
   local_timer.print_timer_point_to_point();

   /*
   std::chrono::time_point<std::chrono::steady_clock> t_start = local_timer.sys_clock.now();

   std::chrono::time_point<std::chrono::steady_clock> t_end = local_timer.sys_clock.now();

   double timedif = std::chrono::duration<double, std::milli>(t_end - t_start).count();
   int64_t timedifi = std::chrono::duration<int64_t, std::nano>(t_end - t_start).count();
   int64_t timedifi2 = std::chrono::nanoseconds(t_end - t_start).count();

   std::cout << "t_delta = " << timedif << std::endl;
   std::cout << "t_delta = " << timedifi << std::endl;
   std::cout << "t_delta = " << timedifi2 << std::endl;
*/

   return 0;

}
