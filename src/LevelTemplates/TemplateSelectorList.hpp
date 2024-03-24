#pragma once

#include <Geode/Geode.hpp>

#include "LevelTemplateCell.hpp"

using namespace geode::prelude;

enum TemplateListView {
    Compact = 40,
    Cozy = 66
};

class TemplateSelectorList : public CustomListView {
protected:
    CCArray* m_levelTemplates;

    void updateTemplateList();

public:

    void setListView(TemplateListView list_view);
    void addTemplate(LevelTemplateCell* level_template);
    void deleteTemplate();
};