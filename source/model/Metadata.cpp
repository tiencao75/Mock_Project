#include "Metadata.hpp"
#include "MediaFile.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/audioproperties.h>

namespace fs = std::filesystem;

// Implementation for Metadata class
std::map<std::string, std::string> Metadata::getData() const {
    return data;
}

std::string Metadata::getValue(const std::string& key) const {
    auto it = data.find(key);
    return (it != data.end()) ? it->second : "";
}

void Metadata::setData(const std::map<std::string, std::string>& data) {
    this->data = data;
}

void Metadata::setValue(const std::string& key, const std::string& value) {
    data[key] = value;
}

void Metadata::loadFromFile(const std::string& filePath) {
    if (!fs::exists(filePath)) {
        throw std::runtime_error("File not found: " + filePath);
    }

    TagLib::FileRef fileRef(filePath.c_str());
    if (fileRef.isNull() || !fileRef.tag() || !fileRef.audioProperties()) {
        throw std::runtime_error("Invalid media file: " + filePath);
    }

    TagLib::Tag* tag = fileRef.tag();
    TagLib::AudioProperties* audioProperties = fileRef.audioProperties();

    data["Title"] = tag->title().toCString();
    data["Artist"] = tag->artist().toCString();
    data["Album"] = tag->album().toCString();
    data["Year"] = std::to_string(tag->year());
    data["Track"] = std::to_string(tag->track());
    data["Genre"] = tag->genre().toCString();
    data["Duration"] = std::to_string(audioProperties->length());
    data["Bitrate"] = std::to_string(audioProperties->bitrate());
    data["SampleRate"] = std::to_string(audioProperties->sampleRate());
    data["Channels"] = std::to_string(audioProperties->channels());
}
void Metadata::loadFromMp4(const std::string &filePath)
{
    if (!fs::exists(filePath))
    {
        throw std::runtime_error("File not found: " + filePath);
    }

    AVFormatContext *formatContext = nullptr;

    if (avformat_open_input(&formatContext, filePath.c_str(), nullptr, nullptr) < 0)
    {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0)
    {
        avformat_close_input(&formatContext);
        throw std::runtime_error("Could not find stream info.");
    }

    if (formatContext->metadata)
    {
        AVDictionaryEntry *tag = nullptr;
        while ((tag = av_dict_get(formatContext->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
        {
            data[tag->key] = tag->value;
        }
    }

    avformat_close_input(&formatContext);
}

void Metadata::saveToFile(const std::string &filePath) const
{
    TagLib::FileRef fileRef(filePath.c_str());
    if (fileRef.isNull() || !fileRef.tag()) {
        throw std::runtime_error("Invalid media file: " + filePath);
    }

    TagLib::Tag* tag = fileRef.tag();

    if (data.find("Title") != data.end()) {
        tag->setTitle(TagLib::String(data.at("Title").c_str(), TagLib::String::UTF8));
    }
    if (data.find("Artist") != data.end()) {
        tag->setArtist(TagLib::String(data.at("Artist").c_str(), TagLib::String::UTF8));
    }
    if (data.find("Album") != data.end()) {
        tag->setAlbum(TagLib::String(data.at("Album").c_str(), TagLib::String::UTF8));
    }
    if (data.find("Year") != data.end()) {
        tag->setYear(std::stoi(data.at("Year")));
    }
    if (data.find("Track") != data.end()) {
        tag->setTrack(std::stoi(data.at("Track")));
    }
    if (data.find("Genre") != data.end()) {
        tag->setGenre(TagLib::String(data.at("Genre").c_str(), TagLib::String::UTF8));
    }

    if (!fileRef.save()) {
        throw std::runtime_error("Failed to save metadata to file: " + filePath);
    }
}
