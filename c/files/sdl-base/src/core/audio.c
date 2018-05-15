typedef struct {
	int pos;	
	void (*callback)(void*, uint8_t*, int);
} MusicDoctorWho;

IntPair* music_notes = NULL;
IntPair example_note = { 1, 10 }; // note identifier and frequency
BUF_PUSH(music_notes, example_note); 

static void callback(void* user_data, uint8_t* audio_buffer, int audio_buffer_size)
{
	int16_t* stream = (int16_t *)audio_buffer;	

	int music_time_pos = 0;
	int next_note_time = 0;
	float note_frequency = 0.0f;

	for (int16_t* stream_iter = stream; stream_iter != stream + audio_buffer_size / sizeof(*stream_iter); ++stream_iter) {
		if (music_time_pos >= next_note_time) {
			note_frequency = 440.0 * pow(); // get from music_note buffer list
			next_note_time += ;
		}

		*stream_iter = 0x7fff * sin(note_frequency * pos++ * 2 * MATH_PI / 48000);
		// 48000 to convert to seconds
	}
}

void music_doctor_who_create(MusicDoctorWho* music_doctor_who)
{
	music_doctor_who->pos = 0;
	music_doctor_who->callback = callback;
}


int main(void)
{
	MusicDoctorWho music_doctor_who = {0};

	music_doctor_who_create(&music_doctor_who);

	SDL_AudioSpec desired_audio = {
		.freq = 48000,
		.samples = 4096,
		.channels = 1,
		.format = AUDIO_S16LSB,
		.callback = music_doctor_who.callback;
		.userdata = NULL
	};	

	SDL_AudioSpec recieved_audio = {0};

	SDL_AudioDeviceID dev_id = SDL_OpenAudioSpec(NULL, 0, &desired_audio, &recieved_audio, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

	// play
	SDL_PauseAudio(0);
}
