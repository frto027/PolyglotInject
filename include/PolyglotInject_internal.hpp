#pragma once
#include "PolyglotInject.hpp"
#include "UnityEngine/TextAsset.hpp"
#include <memory>
#include <string_view>
#include <vector>
#include <set>

namespace PolyglotInject {
    class PendingTextAsset;
    extern std::vector<std::unique_ptr<PendingTextAsset>> pendingAssets;
    extern std::set<Language> pendingLanguages;

    extern bool assetsAlreadyInstalled;

    class PendingTextAsset{
    public:
        virtual std::optional<UnityW<UnityEngine::TextAsset>> getAsset() = 0;
        virtual ~PendingTextAsset(){}
    };

    class PendingTextAssetByReference : public PendingTextAsset{
    private:
        const uint8_t * text;
        const size_t size;
    public:
        PendingTextAssetByReference(const uint8_t * text, size_t size): text(text), size(size) {}
        std::optional<UnityW<UnityEngine::TextAsset>> getAsset() override {
            return UnityEngine::TextAsset::New_ctor(std::move(std::string_view((const char*)text, size)));
        }
    };
    class PendingTextAssetByValue : public PendingTextAsset{
    private:
        std::string_view text;
    public:
        PendingTextAssetByValue(const uint8_t * text, size_t size): text((const char*)text, size) {}
        std::optional<UnityW<UnityEngine::TextAsset>> getAsset() override {
            return UnityEngine::TextAsset::New_ctor(std::move(text));
        }
    };
    class PendingTextAssetByFileName : public PendingTextAsset{
    private:
        const char * path;
    public:
        PendingTextAssetByFileName(const char * path): path(path){}
        std::optional<UnityW<UnityEngine::TextAsset>> getAsset() override {
            FILE * file = fopen(path, "rb");
            if(!file)
                return {};
            auto file_size = std::filesystem::file_size(path);
            std::string buff(file_size, 0);
            size_t i=0;
            while(i<file_size){
                auto ret = fread(&buff.data()[i], 1, file_size - i, file);
                i += ret;
                if(ret == 0){
                    break;
                }
            }
            if(i != file_size || !feof(file)){
                fclose(file);
                return {};
            }
            fclose(file);
            return UnityEngine::TextAsset::New_ctor(std::move(buff));
        }
    };
}


