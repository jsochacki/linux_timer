#pragma once

#include <vector>
#include <utility>  // for pair
#include <string>
#include <cstdint>
#include <numeric>
#include <math.h>
#include <iostream>

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
      void timer_pre_print_prep(void);
      void print_timer_point_to_point(void);
      void print_timer_cumulants(void);

      private:

      bool ready_to_print;

      std::chrono::steady_clock sys_clock;

      std::vector<std::pair<std::string, std::vector<std::chrono::time_point<std::chrono::steady_clock>>>> tick_times;
      std::vector<std::pair<std::string, std::vector<std::chrono::time_point<std::chrono::steady_clock>>>> tock_times;

      std::vector<std::pair<std::string, std::vector<int64_t>>> durations_vector;
      std::vector<std::pair<std::string, uint32_t>> ticks_vector;
      std::vector<std::pair<std::string, uint32_t>> count_vector;

   };
}
