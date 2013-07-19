#include "AudioSystem.h"

void Arc::AudioSystem::init( void )
{
    INFO(toString(), "Initializing");

    _rate      = 44100;
    _chunkSize = 1024;
    _channels  = 2;
    _format    = MIX_DEFAULT_FORMAT;

    if (Mix_OpenAudio(_rate, _format, _channels, _chunkSize))
    {
        ERRORF(toString(), "Unable to open audio (%s)", Mix_GetError());
        die();
    }

    INFO(toString(), "Complete");
}

void Arc::AudioSystem::term( void )
{
    Mix_CloseAudio();
}
