#include "Interface.h"

TextField* newTextField(std::string string) {
	TextField* textField = TextField::create(string, "Arial", 30);
	textField->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::BEGAN) {
				cocos2d::log("began");
			}
		}
	);
	
	return textField;
}

Button* newButton(std::string string) {
	Button* button = Button::create();
	button->setTitleText(string);

	return button;
}

cocos2d::Vec2 center() {
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	return cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);
}

float centerWidth() {
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	return visibleSize.width / 2;
}

float centerHeight() {
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	return visibleSize.height / 2;
}