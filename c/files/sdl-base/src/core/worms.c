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

void create_map(int map, unsigned map_width, unsigned map_height)
{
	float perlin_noise_seeds[map_width];
	perlin_noise_seeds[0] = 0.5f;
	for (int i = 0; i < map_width; ++i) {
		perlin_noise_seeds[i] = (float)rand() / (float)RAND_MAX;		
	}

	float map_heights[map_width];
	perlin_noise(map_width, perlin_noise_seeds, 8, 2.0f, map_heights);

	for (int map_x = 0; map_x < map_width; ++map_x) {
		for (int map_y = 0; map_y < map_height; ++map_y) {
			if (map_y >= map_heights[map_x] * map_height) {
				map[map_y * map_width + map_x] = LAND; // 1
			} else {
				map[map_y * map_width + map_x] = SKY; // 0
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
	int map[MAP_WIDTH * MAP_HEIGHT];
	create_map(map, MAP_WIDTH, MAP_HEIGHT);

}
