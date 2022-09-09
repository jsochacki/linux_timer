#include "abbp_timer.hpp"

namespace TestBed
{
   void abbp_timer::clear_timers(void)
   {
      tick_times.clear();
      tock_times.clear();
   }

   void abbp_timer::tick(std::string event_name)
   {
      for(auto &string_time_point_pair : tick_times)
      {
         if(event_name.compare(string_time_point_pair.first))
         {
            string_time_point_pair.second.push_back(sys_clock.now());
            return;
         }
      }

      tick_times.push_back(
            std::make_pair(event_name,
                           std::vector<std::chrono::time_point<
                           std::chrono::steady_clock>>(1, sys_clock.now())));
   }

   void abbp_timer::tock(std::string event_name)
   {
      for(auto &string_time_point_pair : tock_times)
      {
         if(event_name.compare(string_time_point_pair.first))
         {
            string_time_point_pair.second.push_back(sys_clock.now());
            return;
         }
      }

      tock_times.push_back(
            std::make_pair(event_name,
                           std::vector<std::chrono::time_point<
                           std::chrono::steady_clock>>(1, sys_clock.now())));
   }

   void abbp_timer::print_timer_point_to_point(void)
   {
      std::vector<std::pair<std::string,
         std::vector<std::chrono::duration<int64_t, std::nano>>>> durations_vector;
      std::vector<std::pair<std::string, uint32_t>> ticks_vector;
      std::vector<std::pair<std::string, uint32_t>> count_vector;

      for(auto string_time_point_pair : tick_times)
      {
         ticks_vector.push_back(
               std::make_pair(
                  string_time_point_pair.first, string_time_point_pair.second.size()));
      }

      uint32_t index = 0;
      for(auto string_time_point_pair : tock_times)
      {
         count_vector.push_back(
               std::make_pair(
                  string_time_point_pair.first,
                  std::min(string_time_point_pair.second, ticks_vector[index++].second)));
      }

      index = 0;
      for(auto event : count_vector)
      {
         durations_vector.push_back(
               std::make_pair(
                  event.first,
                  std::vector<std::chrono::duration<int64_t, std::nano>>(1,
                     tock_vector[index].second[count]
                   - tick_vector[index].second[count])));

         if(event.second < 1)
         {
            for(uint32_t count = 1; count < event.second; ++count)
            {
               durations_vector.push_back(
                     std::make_pair(
                        event.first,
                        durations_vector[index].second.push_back(
                           tock_vector[index].second[count]
                         - tick_vector[index].second[count])));
            }
         }
         ++index;
      }

      index = 0;
      for(auto string_duration_pair : durations_vector)
      {
         uint64_t mean = (std::accumulate(
                            string_duration_pair.second.cbegin(),
                            string_duration_pair.second.cend(),
                            0))
                           / count_vector[index++].second;
         std::cout << string_durations_pair.first.c_str() << " took "
            << mean << " us" << std::endl;
      }
   }

   /*
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
   */

}
