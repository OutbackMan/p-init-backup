// variable time step: delta time-> (desired_frame_rate) / (actual_frame_rate) 
// this can cause massive movement spikes in motion which can affect collision detection

// semi-fixed time step
// is deterministic which is good for physics

// all update functions are passed delta time
// position * delta_time
// we think in terms of movement per second, instead of frame

const int MAX_STEPS = 6;
const float DESIRED_FPS = 60.0f;
const float DESIRED_FRAME_TIME = 1000.0f / DESIRED_FPS;
const float MAX_DELTA_TIME = 1.0f;

float previous_ticks = SDL_GetCurrentTicks();

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
  
  // render
  
}
