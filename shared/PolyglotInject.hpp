#pragma once

#include "BGLib/Polyglot/Localization.hpp"
#include "beatsaber-hook/shared/utils/typedefs-string.hpp"
#include <cstdint>
#include <string>

#ifdef POLYGLOT_INJECT_MAIN_MOD
#define POLYGLOT_INJECT_EXTERN __attribute__((visibility("default")))
#else
#define POLYGLOT_INJECT_EXTERN
#endif

namespace PolyglotInject {

    enum Language{
        LANG_English,
        LANG_French,
        LANG_Spanish,
        LANG_German,
        LANG_Italian,
        LANG_Portuguese_Brazil,
        LANG_Portuguese,
        LANG_Russian,
        LANG_Greek,
        LANG_Turkish,
        LANG_Danish,
        LANG_Norwegian,
        LANG_Swedish,
        LANG_Dutch,
        LANG_Polish,
        LANG_Finnish,
        LANG_Japanese,
        LANG_Simplified_Chinese,
        LANG_Traditional_Chinese,
        LANG_Korean,
        LANG_Czech,
        LANG_Hungarian,
        LANG_Romanian,
        LANG_Thai,
        LANG_Bulgarian,
        LANG_Hebrew,
        LANG_Arabic,
        LANG_Bosnian,
    };

    // it's okay to add one language multiple times.
    POLYGLOT_INJECT_EXTERN void AddGameLanguageBeforeInstall(Language language);

    // You need add a .csv file, polyglot will read it.
    // if arg byReference == false, the mod will do memcpy with your text.
    POLYGLOT_INJECT_EXTERN void AddTextBeforeInstall(const uint8_t * text, size_t size, bool byReference = false);
    // the mod saves the path and load it when needed.
    POLYGLOT_INJECT_EXTERN void AddFileBeforeInstall(const char * path);

    inline ::StringW Get(::StringW key){
        return BGLib::Polyglot::Localization::Get(key);
    }
    inline std::string GetStr(::StringW key){
        return il2cpp_utils::detail::to_string(Get(key));
    }

}