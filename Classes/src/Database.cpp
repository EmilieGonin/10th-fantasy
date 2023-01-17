#include "Database.h"

Database::Database() {
	cpr::Response r = cpr::Get(cpr::Url{ "http://www.httpbin.org/get" }); //Testing only
	cocos2d::log(r.url.c_str()); //Testing only
}