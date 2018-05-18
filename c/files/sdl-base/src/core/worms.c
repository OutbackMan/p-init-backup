// pixel level collisions
// wireframe for rotation purposes

// randomness with coherency
// as wraps around can have tesslation, i.e. smooth transitioning across
// ensure between 0 and 1 by dividing by sum of seed scaling factors
// perform a series of interpolations
// add series of octaves varying by frequency and amplitude
void perlin_noise_1d(
		const unsigned output_size, 
		float* seed_values, 
		const unsigned octaves_num, 
		float* output
)
{
	if (output_size == 0 || output_size & (output_size - 1) != 0) {
		return;		
	}

	// generate octave for each element
	for (size_t output_index = 0; output_index < output_size; ++output_index) {
		float noise_accumulator = 0.0f;
		float scale = 1.0f;
		float scale_accumulator = 0.0f;
		for (int octave_count = 0; octave_count < octaves_num; ++octave_count) {
			unsigned pitch = output_size >> octave_count; 

			// first is multiple of pitch
			int sample1_index = (output_index / pitch) * pitch;
			int sample2_index = (sample1_index + pitch) % output_size;

			// how far into the pitch are we
			// (first) gives number between 0 and pitch
			// (second) gives number between 0 and 1
			float pitch_blend = (float)(output_index - sample1_index) / (float)pitch;

			// y0 * (x1 - x) + y1 * (x - x0) / x1 - x0
			float sample_interpolated = (1.0f - pitch_blend) * seed_values[sample1_index] + pitch_blend * seed_values[sample2_index];

			noise_accumulator += sample_interpolated * scale;

			scale_accumulator += scale;
			scale /= 2.0f;
		}
		// ensure that it is [0, 1]
		output[output_index] = noise_accumulator / scale_accumulator;
	}
}

void create_map()
{
	float surface_heights[map_width];
	float noise_seeds[map_width];

	for (int i = 0; i < map_width; ++i) {
		noise_seeds[i] = rand() / RAND_MAX;		
	}
	noise_seeds[0] = 0.5f; // ensures that we start halfway 

	perlin_noise(noise_seeds, surface_heights);

	for (int x = 0; x < map_width; ++x) {
		for (int y = 0; y < map_height; ++y) {
			if (y >= surface[x] * map_height) {
				map[y * map_width + x] = LAND;	
			} else {
				map[y * map_width + x] = SKY;	
			}	
		}		
	}	

}

int main()
{
	// renderer size: 250, 160
	// coord size: 6, 6

	const int MAP_WIDTH = 1024;
	const int MAP_HEIGHT = 512;
	// 1 for land, 0 for no land
	int map[MAP_WIDTH * MAP_HEIGHT] = {0};
}
