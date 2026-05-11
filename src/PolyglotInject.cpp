#define POLYGLOT_INJECT_MAIN_MOD
#include "PolyglotInject.hpp"

#include "PolyglotInject_internal.hpp"
#include "beatsaber-hook/shared/utils/utils-functions.h"
#include <memory>
#include <vector>


std::vector<std::unique_ptr<PolyglotInject::PendingTextAsset>> PolyglotInject::pendingAssets;
std::set<PolyglotInject::Language> PolyglotInject::pendingLanguages;

bool PolyglotInject::assetsAlreadyInstalled = false;

void ReportInstallTimingBug(const char * functionName, const char * file, int line){
    // PaperLogger.error("PolyglotInject::{} should only be called before game initialize.", functionName);
    safeAbortMsg(functionName, file, line, "PolyglotInject::{} should only be called before game initialize.", functionName);
}

void PolyglotInject::AddGameLanguageBeforeInstall(Language language){
    if(assetsAlreadyInstalled){
        ReportInstallTimingBug(__FUNCTION__, __FILE__, __LINE__);
        return;
    }
    pendingLanguages.insert(language);
}

void PolyglotInject::AddTextBeforeInstall(const uint8_t * text, size_t size, bool byReference){
    if(assetsAlreadyInstalled){
        ReportInstallTimingBug(__FUNCTION__, __FILE__, __LINE__);
        return;
    }
    if(byReference)
        pendingAssets.emplace_back(new PolyglotInject::PendingTextAssetByReference(text, size));
    else
        pendingAssets.emplace_back(new PolyglotInject::PendingTextAssetByValue(text, size));
}
void PolyglotInject::AddFileBeforeInstall(const char * path){
    if(assetsAlreadyInstalled){
        ReportInstallTimingBug(__FUNCTION__, __FILE__, __LINE__);
        return;
    }
    pendingAssets.emplace_back(new PolyglotInject::PendingTextAssetByFileName(path));
}
