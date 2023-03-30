#pragma once
#include <vector>
#include <cocos2d.h>
#include <Database.h>
class Support
{
protected:
	db::support* support;
public:
	Support(db::support*);
	db::support* getSupportStat();
};