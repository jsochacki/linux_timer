#include "abbp_timer.hpp"

namespace TestBed
{
   void abbp_timer::clear_timers(void)
   {
      tick_times.clear();
      tock_times.clear();
      event_vector.clear();
   }

   void abbp_timer::tick(std::string event_name)
   {
      for(auto &string_time_point_pair : tick_times)
      {
         if(event_name.compare(string_time_point_pair.first))
         {
            string_time_point_pair.second = sys_clock.now();
            return;
         }
      }

      tick_times.push_back(std::make_pair(event_name, sys_clock.now()));
   }

   void abbp_timer::tock(std::string event_name)
   {
      for(auto &string_time_point_pair : tock_times)
      {
         if(event_name.compare(string_time_point_pair.first))
         {
            string_time_point_pair.second = sys_clock.now();
            return;
         }
      }

      tock_times.push_back(std::make_pair(event_name, sys_clock.now()));
   }

   void abbp_timer::print_timer_point_to_point(void)
   {

   }
}
