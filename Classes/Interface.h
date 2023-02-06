#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

TextField* newTextField(std::string);
Button* newButton(std::string string);
cocos2d::Vec2 center();
float centerWidth();
float centerHeight();