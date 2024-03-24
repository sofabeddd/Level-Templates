#pragma once

#include <Geode/Geode.hpp>

#include "../LevelTemplates/LevelTemplate.hpp"

using namespace geode::prelude;

class TemplateSelectorPopup : public Popup<> {
protected:

    bool setup() override;
    void onClose(CCObject* sender) override;

public:
    static TemplateSelectorPopup* create();

    void onImportTemplate(CCObject* sender);
    void onOpenFolder(CCObject* sender);
    void onReloadTemplates(CCObject* sender);
};
