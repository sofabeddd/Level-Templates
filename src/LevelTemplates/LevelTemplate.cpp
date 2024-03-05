#include "LevelTemplate.hpp"

using namespace geode::prelude;

LevelTemplate::LevelTemplate(const GJGameLevel& level) :
    m_name(level.m_levelName),
    m_levelString(level.m_levelString) {}

LevelTemplate::LevelTemplate(const ghc::filesystem::path &filepath) {
    std::ifstream input_file(filepath);

    if (!input_file.is_open()) {
        log::error("Failed to open file: \"{}\"", filepath.string());
        return;
    }

    matjson::Value level_template = matjson::parse(static_cast<std::stringstream&>((std::stringstream&) (std::stringstream() << input_file.rdbuf())).str());

    m_name = level_template.get<gd::string>("name");
    m_levelString = level_template.get<gd::string>("level_string");
}

void LevelTemplate::save() const {
    save(m_name);
}

void LevelTemplate::save(const std::string& filename) const {
    auto save_directory = LevelTemplate::getTemplatesFolder();

//    // will implement when i figure out how the hell to use this
//    matjson::Object template_json;
//
//    template_json["name"] = m_name.c_str();
//    template_json["level_string"] = m_levelString.c_str();

    std::ofstream template_file(save_directory / LevelTemplate::toValidFileName(filename));

    if (!template_file.is_open()) {
        log::error("Failed to open file: \"{}\"", LevelTemplate::toValidFileName(filename));

        FLAlertLayer::create("ERROR", "Failed to create a new level template.", "OK")->show();
        return;
    }

    template_file << "{\n\t\"name\": \"" << m_name.c_str() << "\",\n\t\"level_string\":\"" << m_levelString.c_str() << "\"\n}" << std::endl;
    template_file.close();

    FLAlertLayer::create("Template Created", "Created new level template: \n<cb>\"" + filename + "\"</c>", "OK")->show();
}

ghc::filesystem::path LevelTemplate::getTemplatesFolder() {
    auto template_directory = dirs::getModsSaveDir() / Mod::get()->getID() / "templates";
    std::filesystem::create_directory(template_directory.string());

    if (std::filesystem::exists(template_directory.string())) {
        return template_directory;
    }

    log::error("Failed to open folder: \"{}\"", template_directory.string());
    return ghc::filesystem::path {};
}

std::string LevelTemplate::toValidFileName(const std::string& filename) {
    std::string result;

    for (char ch : filename) {
        if (std::isalnum(ch)) {
            result += std::tolower(ch);
        }

        else if (ch == ' ') {
            result += '_';
        }
    }

    return result + ".leveltemplate";
}