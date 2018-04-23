// variable time step: delta time-> (desired_frame_rate) / (actual_frame_rate) 
// this can cause massive movement spikes in motion which can affect collision detection

// semi-fixed time step
// is deterministic which is good for physics

// all update functions are passed delta time
// position * delta_time
// we think in terms of movement per second, instead of frame

uint64_t perf_count_frequency = SDL_GetPerformanceFrequency();

const int MAX_STEPS = 6;
const float DESIRED_FPS = 60.0f;
const float DESIRED_FRAME_TIME = 1000.0f / DESIRED_FPS;
const float MAX_DELTA_TIME = 1.0f;

float previous_ticks = SDL_GetCurrentTicks();

uint64_t last_counter = SDL_GetPerformanceCounter();
uint64_t last_cycle_counter = _rtdsc();
while (running) {
  float frame_time = SDL_GetTicks() - previous_ticks;
  previous_ticks = frame_time;
  float total_delta_time = frame_time / DESIRED_FRAME_TIME;
  
  // events
  
  int i = 0;
  while (total_delta_time > 0.0f && i < MAX_STEPS) {
    // updates
    float delta_time = min(total_delta_time, MAX_DELTA_TIME);
    total_delta_time -= delta_time;
    ++i;
  }
  
  uint64 EndCycleCount = _rdtsc();
  uint64 EndCounter = SDL_GetPerformanceCounter();
  uint64 CounterElapsed = EndCounter - LastCounter;
  uint64 CyclesElapsed = EndCycleCount - LastCycleCount;

  real64 MSPerFrame = (((1000.0f * (real64)CounterElapsed) / (real64)PerfCountFrequency));
  real64 FPS = (real64)PerfCountFrequency / (real64)CounterElapsed;
  real64 MCPF = ((real64)CyclesElapsed / (1000.0f * 1000.0f));

  printf("%.02fms/f, %.02f/s, %.02fmc/f\n", MSPerFrame, FPS, MCPF);

  LastCycleCount = EndCycleCount;
  LastCounter = EndCounter;
  
  // render
  
}
