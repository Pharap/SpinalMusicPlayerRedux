
#define PROJ_HIRES              0            //1 = high resolution (220x176) , 0 = low resolution fast mode (110x88)
#define PROJ_SOUND_BUFFERED     1
#define PROJ_ENABLE_SOUND       1     // 0 = all sound functions disabled
#define PROJ_AUD_FREQ           44100
#define PROJ_STREAMING_MUSIC    1

#define PROJ_STREAM_TO_DAC      1       // 1 use DAC for stream, 0 = use PWM for stream
#define PROJ_USE_PWM            0       // 1 use PWM, 0 do not use PWM
#define PROJ_GBSOUND            0       // 1 = use Gamebuino-compatible sound interrupt (choose this or the one below)
#define PROJ_ENABLE_SYNTH       0       // 1 = use Rboy-compatible sound interrupt
#define PROJ_GAMEBUINO          0       // 1 if you are making a Gamebuino-based graphics mode (84x48)
