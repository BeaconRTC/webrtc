#pragma once

#include "modules/audio_device/include/audio_device.h"
#include "rtc_base/criticalsection.h"

class AudioTransportCallback : public webrtc::AudioTransport
{
public:
	AudioTransportCallback() = default;
	~AudioTransportCallback() = default;

	int32_t RecordedDataIsAvailable(const void* audioSamples,
		const size_t nSamples,
		const size_t nBytesPerSample,
		const size_t nChannels,
		const uint32_t samplesPerSec,
		const uint32_t totalDelayMS,
		const int32_t clockDrift,
		const uint32_t currentMicLevel,
		const bool keyPressed,
		uint32_t& newMicLevel) override;


	int32_t NeedMorePlayData(const size_t nSamples,
		const size_t nBytesPerSample,
		const size_t nChannels,
		const uint32_t samplesPerSec,
		void* audioSamples,
		size_t& nSamplesOut,
		int64_t* elapsed_time_ms,
		int64_t* ntp_time_ms) override;

	void PullRenderData(int bits_per_sample,
		int sample_rate,
		size_t number_of_channels,
		size_t number_of_frames,
		void* audio_data,
		int64_t* elapsed_time_ms,
		int64_t* ntp_time_ms) override;

private:

	typedef uint16_t Sample;
	// The value for the following constants have been derived by running VoE
	// using a real ADM. The constants correspond to 10ms of mono audio at 44kHz.
	static const size_t kNumberSamples = 480;
	static const size_t kNumberBytesPerSample = sizeof(Sample);


	rtc::CriticalSection _crit;
	char _rec_buffer[kNumberSamples * kNumberBytesPerSample];
	size_t _rec_buffer_bytes = 0;
};

