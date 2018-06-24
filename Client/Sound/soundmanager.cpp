#include "soundmanager.h"
#include <memory>
#include "generalSounds.h"

SoundManager::SoundManager()
{

}

void SoundManager::playSelectWorm()
{
    std::unique_ptr<generalSounds> sound(new generalSounds("../../sounds/YESSIR.WAV"));
    sound->play();
}
