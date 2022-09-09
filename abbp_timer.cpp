#include "abbp_timer.hpp"

namespace TestBed
{
   void abbp_timer::clear_timers(void)
   {
      tick_times.clear();
      tock_times.clear();
      durations_vector.clear();
      ticks_vector.clear();
      count_vector.clear();
      ready_to_print = false;
   }

   void abbp_timer::tick(std::string event_name)
   {
      for(auto &string_time_point_pair : tick_times)
      {
         if(event_name.compare(string_time_point_pair.first) == 0)
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
         if(event_name.compare(string_time_point_pair.first) == 0)
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

   void abbp_timer::timer_pre_print_prep(void)
   {
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
                  std::min(static_cast<uint32_t>(string_time_point_pair.second.size()),
                           static_cast<uint32_t>(ticks_vector[index++].second))));
      }

      index = 0;
      for(auto event : count_vector)
      {
         durations_vector.push_back(
               std::make_pair(
                  event.first,
                  std::vector<int64_t>(1,
                     std::chrono::duration<int64_t, std::nano>
                     (tock_times[index].second[0]
                    - tick_times[index].second[0]).count())));

         if(event.second < 1)
         {
            for(uint32_t count = 1; count < event.second; ++count)
            {
               durations_vector[index].second.push_back(
                  std::chrono::duration<int64_t, std::nano>
                     (tock_times[index].second[count]
                    - tick_times[index].second[count]).count());
            }
         }
         ++index;
      }
   }

   void abbp_timer::print_timer_point_to_point(void)
   {
      if(!ready_to_print)
      {
         this->timer_pre_print_prep();
         ready_to_print = true;
      }

      uint32_t index = 0;
      for(auto string_duration_pair : durations_vector)
      {
         uint64_t mean = (std::accumulate(
                            string_duration_pair.second.cbegin(),
                            string_duration_pair.second.cend(),
                            0))
                           / count_vector[index].second;
         std::cout << "Based on ["
            << count_vector[index++].second << "] measurements ["
            << string_duration_pair.first.c_str() << "] took ["
            << mean << "] us"
            << std::endl;
      }
   }

   void abbp_timer::print_timer_cumulants(void)
   {
      if(!ready_to_print)
      {
         this->timer_pre_print_prep();
         ready_to_print = true;
      }

      int64_t cumulative_values = 0;
      uint32_t index = 0;
      for(auto string_duration_pair : durations_vector)
      {
         uint64_t mean = (std::accumulate(
                            string_duration_pair.second.cbegin(),
                            string_duration_pair.second.cend(),
                            0))
                           / count_vector[index].second;
         cumulative_values += mean;
         std::cout << "Based on ["
            << count_vector[index++].second << "] measurements it took ["
            << cumulative_values << "] us to get to ["
            << string_duration_pair.first.c_str() << "]"
            << std::endl;
      }
   }

}
