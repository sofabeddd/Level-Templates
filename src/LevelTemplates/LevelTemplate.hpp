#pragma once

#include <fstream>
#include <sstream>

#include <Geode/Geode.hpp>

class LevelTemplate {
public:
    explicit LevelTemplate(const GJGameLevel& level);
    explicit LevelTemplate(const ghc::filesystem::path& filepath);

    void save() const;
    void save(const std::string& filename) const;

    static ghc::filesystem::path getTemplatesFolder();

private:
    static std::string toValidFileName(const std::string& filename);

    gd::string m_name;
    gd::string m_levelString;
};
