#include "_config.hpp"

#include "main.hpp"
#include "PolyglotInject.hpp"
#include "assets.hpp"
#include "cordl_internals/unity-utils.hpp"

#include "scotland2/shared/modloader.h"

#include "UnityEngine/TextAsset.hpp"

#include "BGLib/Polyglot/LocalizationImporter.hpp"
#include "BGLib/Polyglot/Localization.hpp"
#include "BGLib/Polyglot/LocalizationAsset.hpp"
#include "BGLib/Polyglot/LocalizationAsyncInstaller.hpp"
#include "BGLib/AppFlow/Initialization/AsyncInstaller.hpp"
#include "System/Collections/Generic/ICollection_1.hpp"
#include "System/Collections/Generic/List_1.hpp"
#include "System/Collections/Generic/IList_1.hpp"
#include <string_view>
#include "PolyglotInject_internal.hpp"
#include "StringResourceHelper.hpp"
// Stores the ID and version of our mod, and is sent to the modloader upon startup
static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be
// removed if those are in use
Configuration &getConfig() {
    static Configuration config(modInfo);
    return config;
}

// Called at the early stages of game loading
MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
    *info = modInfo.to_c();

    getConfig().Load();

    // File logging
    Paper::Logger::RegisterFileContextId(PaperLogger.tag);

    PaperLogger.info("Completed setup!");
}

MAKE_HOOK_MATCH(LocalizationInstallerHook, 
                &BGLib::Polyglot::LocalizationAsyncInstaller::LoadResourcesBeforeInstall, 
                void, 
                BGLib::Polyglot::LocalizationAsyncInstaller *self, 
                System::Collections::Generic::IList_1<UnityW<UnityEngine::TextAsset>> * assets, 
                BGLib::AppFlow::Initialization::AsyncInstaller::IInstallerRegistry* registry) {
    PaperLogger.debug("%s triggered!", name());
    for(auto & ptr : PolyglotInject::pendingAssets){
        auto asset = ptr->getAsset();
        if(asset.has_value()){
            assets->i___System__Collections__Generic__ICollection_1_T_()->Add(asset.value());
        }
    }

    for(auto & language : PolyglotInject::pendingLanguages){
        switch(language){
            #define CASE(x) \
                case PolyglotInject::L_##x: \
                    self->_mainPolyglotAsset->supportedLanguages->Add(BGLib::Polyglot::Language::x);\
                break;
            CASE(English)
            CASE(French)
            CASE(Spanish)
            CASE(German)
            CASE(Italian)
            CASE(Portuguese_Brazil)
            CASE(Portuguese)
            CASE(Russian)
            CASE(Greek)
            CASE(Turkish)
            CASE(Danish)
            CASE(Norwegian)
            CASE(Swedish)
            CASE(Dutch)
            CASE(Polish)
            CASE(Finnish)
            CASE(Japanese)
            CASE(Simplified_Chinese)
            CASE(Traditional_Chinese)
            CASE(Korean)
            CASE(Czech)
            CASE(Hungarian)
            CASE(Romanian)
            CASE(Thai)
            CASE(Bulgarian)
            CASE(Hebrew)
            CASE(Arabic)
            CASE(Bosnian)
            #undef CASE
        }
    }
    PolyglotInject::assetsAlreadyInstalled = true;
    PolyglotInject::pendingAssets.clear();
    PolyglotInject::pendingLanguages.clear();
    LocalizationInstallerHook(self, assets, registry);
}

// Called later on in the game loading - a good time to install function hooks
MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();

    PaperLogger.info("Installing hooks...");
    // Install our hooks
    INSTALL_HOOK(PaperLogger, LocalizationInstallerHook)
    PaperLogger.info("Installed all hooks!");


    ///////////////////////////
    // do some test here...
    ///////////////////////////

    PolyglotInject::AddGameLanguageBeforeInstall(PolyglotInject::L_Simplified_Chinese);
    PolyglotInject::AddTextBeforeInstall(polyglot_inject_csv::getData(), polyglot_inject_csv::getLength());

    PolyglotInject::StringResourceBuilder()
        .forLanguage(PolyglotInject::L_Simplified_Chinese)
        .p("KEY1", "VALUE1")
        .p("KEY2", "VALUE2")
        .submit(); 
    auto s = PolyglotInject::FormatKey("abc",2llu,3,4,6);
}