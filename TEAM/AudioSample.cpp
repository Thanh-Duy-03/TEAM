#include "AudioSample.h"

AudioSample::AudioSample()
{
	this->name = L"";
	this->length = 0;
	this->volume = 1000;
	this->speed = 1000;
}

AudioSample::AudioSample(wstring name)
{
	this->name = L"";
	this->length = 0;
	this->volume = 1000;
	this->speed = 1000;
	Open(name);
}

AudioSample::AudioSample(const AudioSample& audio)
{
	this->name = audio.name;
	this->length = 0;
	this->volume = 1000;
	this->speed = 1000;
	Open(this->name);
}

AudioSample::~AudioSample()
{
	Close();
}

AudioSample& AudioSample::operator=(const AudioSample& audio)
{
	if (this == &audio)
		return *this;
	this->name = audio.name;
	this->length = 0;
	this->volume = 1000;
	this->speed = 1000;
	Open(this->name);
}

bool AudioSample::Open(wstring name)
{
	this->name = name;
	wstring cmd = L"open \"" + this->name + L"\" type mpegvideo alias " + this->name;
	if (mciSendString(cmd.c_str(), NULL, 0, NULL) != 0)
	{
		return false;
	}
	LPTSTR str = new TCHAR[256];
	cmd = L"status " + this->name + L" length";
	mciSendString(cmd.c_str(), str, 256, NULL);
	this->length = _wtoi(str);
	return true;
}

void AudioSample::Play()
{
	wstring cmd = L"play " + this->name;
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}

void AudioSample::PlayFrom(int pos)
{
	wstring cmd = L"play " + this->name + L" from " + to_wstring(pos);
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}

void AudioSample::PlayLoop()
{
	wstring cmd = L"play " + this->name + L" repeat";
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}

void AudioSample::Resume()
{
	wstring cmd = L"resume " + this->name;
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}

void AudioSample::Pause()
{
	wstring cmd = L"pause " + this->name;
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}

void AudioSample::Stop()
{
	wstring cmd = L"stop " + this->name;
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}

void AudioSample::Close()
{
	wstring cmd = L"close " + this->name;
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}

AudioMode AudioSample::GetMode()
{
	LPTSTR str = new TCHAR[256];
	wstring cmd = L"status " + this->name + L" mode";
	mciSendString(cmd.c_str(), str, 256, NULL);
	wstring mode = str;

	if (mode == L"paused")
	{
		return Paused;
	}
	if (mode == L"playing")
	{
		return Playing;
	}
	if (mode == L"stopped")
	{
		return Stopped;
	}
	return Not_ready;
}

int AudioSample::GetLength()
{
	return this->length;
}

int AudioSample::GetVolume()
{
	return this->volume;
}

int AudioSample::GetSpeed()
{
	return this->speed;
}

int AudioSample::GetPosition()
{
	LPTSTR str = new TCHAR[256];
	wstring cmd = L"status " + this->name + L" position";
	mciSendString(cmd.c_str(), str, 256, NULL);
	return _wtoi(str);
}

void AudioSample::SetVolume(int volume)
{
	if (volume < 0)
	{
		this->volume = 0;
	}
	else if (volume > 1000)
	{
		this->volume = 1000;
	}
	else
		this->volume = volume;
	wstring cmd = L"setaudio " + this->name + L" volume to " + to_wstring(this->volume);
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}

void AudioSample::SetSpeed(int speed)
{
	if (speed < 0)
	{
		this->speed = 0;
	}
	else if (this->speed > 2000)
	{
		this->speed = 2000;
	}
	this->speed = speed;
	wstring cmd = L"set " + this->name + L" speed " + to_wstring(this->speed);
	mciSendString(cmd.c_str(), NULL, 0, NULL);
}