#include <fstream>
#include <sstream>

#include <Geode/Geode.hpp>
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/GameLevelManager.hpp>

using namespace geode::prelude;

class LevelTemplate {
public:
    gd::string m_name;
    gd::string m_levelString;

    static LevelTemplate create(const gd::string& template_name, const GJGameLevel& level) {
        return LevelTemplate {
            template_name,
            level.m_levelString
        };
    }

    static LevelTemplate create(const ghc::filesystem::path& filepath) {
        std::ifstream input_file(filepath);

        if (!input_file.is_open()) {
            log::error("failed to open level template file \"{}\"", filepath.string());
            return LevelTemplate {};
        }

        matjson::Value level_template = matjson::parse(static_cast<std::stringstream&>((std::stringstream&) (std::stringstream() << input_file.rdbuf())).str());

        return LevelTemplate {
            level_template.get<gd::string>("name"),
            level_template.get<gd::string>("level_string"),
        };
    }

    void save() {
        save(m_name);
    }

    void save(const std::string& filename) {
        auto save_directory = dirs::getModsSaveDir().string().append("/sofabeddd.level_templates/templates/");

        if (std::filesystem::create_directory(save_directory) || std::filesystem::exists(save_directory)) {
            std::ofstream template_file(save_directory.append(LevelTemplate::toValidFileName(filename)).append(".leveltemplate").c_str());

            template_file << "{\n\t\"name\": \"" << m_name.c_str() << "\",\n\t\"level_string\":\"" << m_levelString.c_str() << "\"\n}" << std::endl;
            template_file.close();

            FLAlertLayer::create("Template Created", "Created new level template <cc>\"" + filename + "\"</c>", "OK")->show();
        }

        else {
            log::error("Failed to create new level template.");

            FLAlertLayer::create("ERROR", "Failed to create a new level template.", "OK")->show();
        }
    }

private:
    static std::string toValidFileName(const std::string& filename) {
        std::string result;

        for (char ch : filename) {
            if (std::isalnum(ch)) {
                result += std::tolower(ch);
            }

            else if (ch == ' ') {
                result += '_';
            }
        }

        return result;
    }
};

class $modify(TemplateEditor, EditLevelLayer) {
public:
    void onTemplate(CCObject* sender) {
        if (auto button = typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
            LevelTemplate::create(m_level->m_levelName, *m_level).save();
        }
    }

    bool init(GJGameLevel* p0)  {
        if (!EditLevelLayer::init(p0)) return false;

        auto folder_menu = getChildByID("folder-menu");
        auto sprite = CircleButtonSprite::create(nullptr, CircleBaseColor::Blue);
        auto button = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(TemplateEditor::onTemplate));

        folder_menu->addChild(button, -1);
        folder_menu->updateLayout(true);

        button->setID("sofabeddd.level_templates/create-template-button");
        button->setPositionY(button->getPositionY() - 12.f);

        return true;
    }
};

class $modify(LevelTemplateManager, GameLevelManager) {
public:
    GJGameLevel* createNewLevel(const LevelTemplate& level_template) {

    }

    GJGameLevel* createNewLevel() {
        auto level = GameLevelManager::createNewLevel();

        return level;
    }
};
