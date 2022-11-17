#pragma once
#include "Functions.h"

using namespace std;

enum AudioMode
{
    Not_ready,
    Paused,
    Playing,
    Stopped
};

class AudioSample
{
private:
    wstring name;
    int length;
    int volume;
    int speed;

public:
public:
    AudioSample();
    AudioSample(wstring name);
    AudioSample(const AudioSample &audio);
    ~AudioSample();
    AudioSample &operator=(const AudioSample &audio);
    bool Open(wstring name);
    void Play();
    void PlayFrom(int pos);
    void PlayLoop();
    void Resume();
    void Pause();
    void Stop();
    void Close();

    AudioMode GetMode();
    int GetLength();
    int GetVolume();
    int GetSpeed();
    int GetPosition();

    void SetVolume(int volume);
    void SetSpeed(int speed);
};
