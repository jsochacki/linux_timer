#pragma once

#include <vector>
#include <utility>  // for pair
#include <string>
#include <algorithm>
#include <cstdint>

//#include "sys/time.h"
#include <chrono>

namespace TestBed
{
   class abbp_timer
   {
      public:

      void clear_timers(void);
      void tick(std::string event_name);
      void tock(std::string event_name);
      void print_timer_point_to_point(void);
      void print_timer_cumulants(void);

      std::chrono::steady_clock sys_clock;
      int64_t get_delta(void);
      private:

      std::vector<std::pair<std::string, std::chrono::time_point<std::chrono::steady_clock>>> tick_times;
      std::vector<std::pair<std::string, std::chrono::time_point<std::chrono::steady_clock>>> tock_times;
      std::vector<std::pair<std::string, std::chrono::duration<int64_t, std::nano>>> event_durations;
      std::chrono::duration<int64_t, std::nano> time_delta;

      std::vector<std::pair<std::string, uint8_t>> event_vector;
   };
}
