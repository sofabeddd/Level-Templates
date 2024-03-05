
#include <Geode/Geode.hpp>
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/GameLevelManager.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

#include "LevelTemplates/LevelTemplate.hpp"

using namespace geode::prelude;

class $modify(TemplateEditLevelLayer, EditLevelLayer) {
public:
    void onSaveTemplate(CCObject* sender) {
        if (auto button = typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
            LevelTemplate(*m_level).save();
        }
    }

    bool init(GJGameLevel* p0)  {
        if (!EditLevelLayer::init(p0)) return false;

        auto folder_menu = getChildByID("folder-menu");

        auto label = CCLabelBMFont::create("Save Level Template", "bigFont-hd.fnt", 48.f, CCTextAlignment::kCCTextAlignmentCenter);
        auto sprite = CircleButtonSprite::create(label, CircleBaseColor::Blue, CircleBaseSize::Big);
        auto button = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(TemplateEditLevelLayer::onSaveTemplate));

        folder_menu->addChild(button, -1);
        folder_menu->updateLayout(true);

        button->setID("create-template-button"_spr);
        button->setPositionY(button->getPositionY() - 12.f);

        return true;
    }
};

class $modify(TemplateLevelBrowserLayer, LevelBrowserLayer) {
public:
    void onTemplateSelectMenu(CCObject* sender) {
        if (auto button = typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
            FLAlertLayer::create("Level Template", "// todo", "OK")->show();
        }
    }

    bool init(GJSearchObject* p0) {
        if (!LevelBrowserLayer::init(p0)) return false;

        if (getChildByID("new-level-menu")) {
            auto new_level_menu = getChildByID("new-level-menu");

            auto label = CCLabelBMFont::create("Select Template", "bigFont-hd.fnt", 48.f,
                                               CCTextAlignment::kCCTextAlignmentCenter);
            auto sprite = CircleButtonSprite::create(label, CircleBaseColor::Blue, CircleBaseSize::Big);
            auto button = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(TemplateLevelBrowserLayer::onTemplateSelectMenu));

            new_level_menu->getChildByID("switch-mode-button")->setZOrder(1);

            new_level_menu->addChild(button);
            new_level_menu->updateLayout(true);

            button->setID("select-template-button"_spr);
        }

        return true;
    }
};
