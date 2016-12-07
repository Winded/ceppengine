#include "audioimporter.h"
#include "../audioclip.h"
#include <istream>

namespace cepp {

AudioImporter::AudioImporter()
{

}

bool AudioImporter::canLoadExtension(const std::string &extension) const
{
    return extension == ".wav";
}

std::vector<Asset *> AudioImporter::import(std::istream &stream) const
{
    std::vector<Asset*> assets;

    if(stream.eof() || stream.fail())
        return assets;

    char signature[4];
    stream.read(signature, 4);
    if(!strcmp(signature, "RIFF")) {
        fprintf(stderr, "AudioImporter: Specified stream is not a wave file");
        return assets;
    }

    int riff_chunk_size;
    stream.read((char*)&riff_chunk_size, sizeof(riff_chunk_size));

    char format[4];
    stream.read(format, 4);
    if(!strcmp(format, "WAVE")) {
        fprintf(stderr, "AudioImporter: Specified stream is not a wave file");
        return assets;
    }

    char format_signature[4];
    stream.read(format_signature, 4);
    if(!strcmp(format_signature, "fmt ")) {
        fprintf(stderr, "AudioImporter: Specified wave file is not supported");
        return assets;
    }

    int format_chunk_size, sample_rate, byte_rate;
    short audio_format, num_channels, block_align, bits_per_sample;

    stream.read((char*)&format_chunk_size, sizeof(format_chunk_size));
    stream.read((char*)&audio_format, sizeof(audio_format));
    stream.read((char*)&num_channels, sizeof(num_channels));
    stream.read((char*)&sample_rate, sizeof(sample_rate));
    stream.read((char*)&byte_rate, sizeof(byte_rate));
    stream.read((char*)&block_align, sizeof(block_align));
    stream.read((char*)&bits_per_sample, sizeof(bits_per_sample));

    char data_signature[4];
    stream.read(data_signature, 4);
    if(!strcmp(data_signature, "data")) {
        fprintf(stderr, "AudioImporter: Specified wave file is not supported");
        return assets;
    }

    int data_chunk_size;
    stream.read((char*)&data_chunk_size, sizeof(data_chunk_size));

    char *data = new char[data_chunk_size];
    stream.read(data, data_chunk_size);

    AudioClip *clip = new AudioClip((void*)data, data_chunk_size, num_channels, bits_per_sample, sample_rate);
    assets.push_back(clip);

    return assets;
}

} // namespace cepp
