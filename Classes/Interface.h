#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocos2d;

TextField* newTextField(std::string);
Button* newButton(std::string);
Label* newLabel(std::string);
Vec2 center();
float centerWidth();
float centerHeight();