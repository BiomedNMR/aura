#ifndef AURA_MISC_PROFILE_HPP
#define AURA_MISC_PROFILE_HPP

#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <thread>
#include <mutex>

#include <aura/misc/now.hpp>
#include <aura/error.hpp>


#define AURA_PROFILE_FUNCTION(sinktype, sink) \
  aura::profile::scope<sinktype> \
    aura_profile_function_scope__ (sink, __func__); \
  /**/

namespace aura {

namespace profile {

/**
 * entry in a profile holding function name, 
 * thread id timestamp and start/stop flag
 */
struct entry { 
  entry(const char * name, std::thread::id thread_id, 
    double timestamp, bool start) : 
    name(name), thread_id(std::hash<std::thread::id>()(thread_id)), 
    timestamp(timestamp), start(start) 
  {}

  const char * name;
  std::size_t thread_id;
  double timestamp;
  bool start;
};

/**
 * file sink to log profile to file
 */
struct file_sink {
  FILE * file;
  void record(const entry & e) {}
};

/** 
 * memory sink to store profile in memory
 */
struct memory_sink {
  /// vector to store profile
  std::vector<entry> data;
  
  /// record profile data
  void record(const entry & e) { 
    std::lock_guard<std::mutex> guard(mtx_);
    data.push_back(e); 
  }
  
  /// dump profile data to file
  void dump(const char * filename) {
    FILE * f = fopen(filename, "w");
    if(f == NULL) {
      AURA_ERROR("Unable to open file.");
    }
    std::lock_guard<std::mutex> guard(mtx_);
    for(std::size_t i=0; i<data.size(); i++) {
      fprintf(f, "%s, %ld, %.17g %d\n", 
        data[i].name, data[i].thread_id, 
        data[i].timestamp, data[i].start);
    }
    if(0 != fclose(f)) {
      AURA_ERROR("Unable to close file.");
    }
  }

  private:
    std::mutex mtx_;
};

/**
 * record a profiler starting event
 */
template <typename sink>
void start(sink & s, const char * name) {
  s.record(entry(name, std::this_thread::get_id(), 
    aura::now(), true));  
}

/**
 * record a profiler stopping event
 */
template <typename sink>
void stop(sink & s, const char * name) {
  s.record(entry(name, std::this_thread::get_id(), 
    aura::now(), false));  
}

/**
 * profile a scope
 */
template <typename sink>
struct scope {
  scope(sink & s, const char * name) : name_(name), sink_(s) {
    start(sink_, name_);  
  }
  ~scope() {
    stop(sink_, name_);  
  }
  const char * name_;
  sink & sink_;
};


} // namespace profile

} // namespace aura

#endif // AURA_MISC_PROFILE_HPP
