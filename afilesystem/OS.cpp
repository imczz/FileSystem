#include "OS.h"

void OS::login(UN id, string key) {

	switch (id)

	{

	case user0:

		if (key.compare("000000") == 0) user = 0;

		cout << "����Ա��¼�ɹ�" << endl;

		break;



	case user1:

		if (key.compare("111111") == 0) user = 1;

		cout << "�û�1��¼�ɹ�" << endl;

		break;



	case user2:

		if (key.compare("222222") == 0) user = 2;

		cout << "�û�2��¼�ɹ�" << endl;

		break;



	case user3:

		if (key.compare("333333") == 0) user = 3;

		cout << "�û�3��¼�ɹ�" << endl;

		break;



	case user4:

		if (key.compare("444444") == 0) user = 4;

		cout << "�û�4��¼�ɹ�" << endl;

		break;



	case user5:

		if (key.compare("555555") == 0) user = 5;

		cout << "�û�5��¼�ɹ�" << endl;

		break;



	case user6:

		if (key.compare("666666") == 0) user = 6;

		cout << "�û�6��¼�ɹ�" << endl;

		break;



	case user7:

		if (key.compare("777777") == 0) user = 7;

		cout << "�û�7��¼�ɹ�" << endl;

		break;



	case user8:

		if (key.compare("888888") == 0) user = 8;

		cout << "�û�8��¼�ɹ�" << endl;

		break;



	default:

		cout << "��¼ʧ��" << endl;

		break;

	}

}



void OS::logout() {

	user = -1;

	cout << "���˳�" << endl;

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
