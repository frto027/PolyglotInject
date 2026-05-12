#pragma once

#include "BGLib/Polyglot/Localization.hpp"
#include "beatsaber-hook/shared/utils/typedefs-string.hpp" // for ::StringW
#include <cstdint>
#include <string>

#ifdef POLYGLOT_INJECT_MAIN_MOD
#define POLYGLOT_INJECT_EXTERN __attribute__((visibility("default")))
#else
#define POLYGLOT_INJECT_EXTERN
#endif

namespace PolyglotInject {

    enum Language{
        L_English,
        L_French,
        L_Spanish,
        L_German,
        L_Italian,
        L_Portuguese_Brazil,
        L_Portuguese,
        L_Russian,
        L_Greek,
        L_Turkish,
        L_Danish,
        L_Norwegian,
        L_Swedish,
        L_Dutch,
        L_Polish,
        L_Finnish,
        L_Japanese,
        L_Simplified_Chinese,
        L_Traditional_Chinese,
        L_Korean,
        L_Czech,
        L_Hungarian,
        L_Romanian,
        L_Thai,
        L_Bulgarian,
        L_Hebrew,
        L_Arabic,
        L_Bosnian,
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