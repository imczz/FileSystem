#include "OS.h"

void OS::login(UN id, string key) {

	switch (id)

	{

	case user0:

		if (key.compare("000000") == 0) user = 0;

		cout << "管理员登录成功" << endl;

		break;



	case user1:

		if (key.compare("111111") == 0) user = 1;

		cout << "用户1登录成功" << endl;

		break;



	case user2:

		if (key.compare("222222") == 0) user = 2;

		cout << "用户2登录成功" << endl;

		break;



	case user3:

		if (key.compare("333333") == 0) user = 3;

		cout << "用户3登录成功" << endl;

		break;



	case user4:

		if (key.compare("444444") == 0) user = 4;

		cout << "用户4登录成功" << endl;

		break;



	case user5:

		if (key.compare("555555") == 0) user = 5;

		cout << "用户5登录成功" << endl;

		break;



	case user6:

		if (key.compare("666666") == 0) user = 6;

		cout << "用户6登录成功" << endl;

		break;



	case user7:

		if (key.compare("777777") == 0) user = 7;

		cout << "用户7登录成功" << endl;

		break;



	case user8:

		if (key.compare("888888") == 0) user = 8;

		cout << "用户8登录成功" << endl;

		break;



	default:

		cout << "登录失败" << endl;

		break;

	}

}



void OS::logout() {

	user = -1;

	cout << "已退出" << endl;

}



void OS::open(string fileName) {



}



void OS::close(string fileName) {



}



void OS::create(string fileName) {



}



void OS::read(string fileName) {



}



void OS::write(string fileName) {



}



void OS::mkdir() {



}



void OS::chdir() {



}



void OS::dir() {



}



void OS::format() {



}
