#include "TemplateSelectorPopup.hpp"
#include "../LevelTemplates/TemplateSelectorList.hpp"

bool TemplateSelectorPopup::setup() {

    setID("TemplateSelectLayer");
    setTitle("Select Level Template");

    auto folder_button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("gj_folderBtn_001.png"),
            this,
            menu_selector(TemplateSelectorPopup::onOpenFolder)
    );

    auto import_button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Import Template"),
            this,
            menu_selector(TemplateSelectorPopup::onImportTemplate)
    );

    auto border = GJCommentListLayer::create(nullptr, "", ccColor4B { 191, 114, 62, 255}, 340.f, 200.f, false);

    auto template_array = CCArray::create();
    template_array->addObject(CCNode::create());
    template_array->addObject(CCNode::create());
    template_array->addObject(CCNode::create());

    auto level_template_list = CustomListView::create(template_array, BoomListType::Default, 200.f, 340.f);

    m_buttonMenu->addChild(folder_button);
    m_buttonMenu->addChild(import_button);
    m_buttonMenu->addChild(border);
    border->addChild(level_template_list);

    m_closeBtn->setPosition(CCPoint { 12.f, 268.f });
    typeinfo_cast<CCSprite*>(m_closeBtn->getChildren()->objectAtIndex(0))->setScale(1.f);

    m_title->setPositionX(m_title->getPositionX() + 20.f);

    m_bgSprite->setID("background");
    folder_button->setID("folder-button"_spr);
    import_button->setID("import-button"_spr);
    // border->setID("border"_spr);
    // level_template_list->setID("level-template-list"_spr);


    border->setAnchorPoint(CCPoint { 0.5f, 0.5f });
    border->setPosition(CCPoint { 70.f, 40.f });

    folder_button->setPosition(CCPoint { 35.f, 140.f});
    import_button->setPosition(CCPoint { m_buttonMenu->boundingBox().getMidX() + 20.f, 8.f});
    level_template_list->setAnchorPoint(CCPoint { 0.5f, 0.5f });

    return true;
}

void TemplateSelectorPopup::onClose(CCObject* sender) {
    Popup::onClose(sender);
}

TemplateSelectorPopup *TemplateSelectorPopup::create() {
    auto template_selector_layer = new TemplateSelectorPopup;
    if (template_selector_layer->initAnchored(440.f, 280.f)) {
        template_selector_layer->autorelease();

        return template_selector_layer;
    }

    CC_SAFE_DELETE(template_selector_layer);
    return nullptr;
}

void TemplateSelectorPopup::onOpenFolder(CCObject *sender) {
    if (typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
        utils::file::openFolder(LevelTemplate::getTemplatesFolder());
    }
}

void TemplateSelectorPopup::onReloadTemplates(CCObject *sender) {
    return;
}

void TemplateSelectorPopup::onImportTemplate(CCObject *sender) {
    if (typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
        std::vector<file::FilePickOptions::Filter> filter;
        filter.push_back(file::FilePickOptions::Filter {"", std::unordered_set<std::string> { "*.leveltemplate" } });

        const file::FilePickOptions file_pick_options {
                "",
                filter
        };

        file::pickFile(file::PickMode::OpenFile, file_pick_options, [](ghc::filesystem::path file) {});
    }
}
