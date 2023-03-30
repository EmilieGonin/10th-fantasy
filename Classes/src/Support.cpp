#include "Support.h"


Support::Support(db::support* mySupport)
{
	support = mySupport;
}

db::support* Support::getSupportStat() { return support; }