#include "randomSoundPlayer.h"
#include <assert.h>

using namespace SlidingTiles;

void RandomSoundPlayer::loadSounds(const json & jsonArray) {
    for (auto& element : jsonArray) {
        const std::string filename = "assets/" + element["File"].get<std::string>();
        sf::SoundBuffer sb{};
        sb.loadFromFile(filename);
        addSound(sb);
    }
}

void RandomSoundPlayer::addSound(const sf::SoundBuffer & soundBuffer) {
    sounds.push_back(soundBuffer);
}

void RandomSoundPlayer::playRandomSound() {
    assert(sounds.size() > 0 && "There are no sounds loaded. Was adSound(sf::SoundBuffer) called?");
    std::size_t index = rand() % sounds.size();
    sound.setBuffer(sounds.at(index));
    sound.play();
}