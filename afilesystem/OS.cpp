#include "OS.h"

#include "BitOperate.h"
#include "windows.h"

//构造函数
OS::OS()
{
	FileSystem * fs = new FileSystem("D:\\disk.txt");
	fsList.push_back(fs);
}

OS::~OS()
{
	for (vector<FileSystem *>::iterator iter = fsList.begin(); iter != fsList.end(); iter++)
	{
		free(*iter);
	}
}

int OS::login(UN id, string key) {

	int result = 0;
	switch (id)

	{

	case user0:

		if (key.compare("000000") == 0) user = 0;

		cout << "管理员登录成功" << endl;
		result = 200;

		break;



	case user1:

		if (key.compare("111111") == 0) user = 1;

		cout << "用户1登录成功" << endl;
		result = 200;

		break;



	case user2:

		if (key.compare("222222") == 0) user = 2;

		cout << "用户2登录成功" << endl;
		result = 200;

		break;



	case user3:

		if (key.compare("333333") == 0) user = 3;

		cout << "用户3登录成功" << endl;
		result = 200;

		break;



	case user4:

		if (key.compare("444444") == 0) user = 4;

		cout << "用户4登录成功" << endl;
		result = 200;

		break;



	case user5:

		if (key.compare("555555") == 0) user = 5;

		cout << "用户5登录成功" << endl;
		result = 200;

		break;



	case user6:

		if (key.compare("666666") == 0) user = 6;

		cout << "用户6登录成功" << endl;
		result = 200;

		break;



	case user7:

		if (key.compare("777777") == 0) user = 7;

		cout << "用户7登录成功" << endl;
		result = 200;

		break;



	case user8:

		if (key.compare("888888") == 0) user = 8;

		cout << "用户8登录成功" << endl;
		result = 200;

		break;

	case unknown:

		cout << "登录失败" << endl;

		break;
	default:

		cout << "登录失败" << endl;

		break;

	}
	return result;
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

void OS::start()
{
	string username;
	string password;
	UN user;
	cout << "请输入用户名:" << endl;
	cin >> username;
	cout << "请输入密码:" << endl;
	cin >> password;
	if (username == "root")
	{
		user = user0;
	}
	else
	{
		if (username.size() == 5 && username.substr(0, 4) == "user")
		{
			switch (username[4])
			{
			case '0':
				user = user0;
				break;
			case '1':
				user = user1;
				break;
			case '2':
				user = user2;
				break;
			case '3':
				user = user3;
				break;
			case '4':
				user = user4;
				break;
			case '5':
				user = user5;
				break;
			case '6':
				user = user6;
				break;
			case '7':
				user = user7;
				break;
			case '8':
				user = user8;
				break;
			}
		}
		else
		{
			user = unknown;
		}
	}
	if (login(user, password) != 200)
	{
		system("pause");
		exit(0);
	}

	//fsList[0]->Initialize("D:\\disk.txt");
	if (!fsList[0]->IsInitalized)
	{
		cout << "初始化文件系统失败，按任意键退出程序" << endl;
		system("pause");
	}
	if (fsList[0]->superBlock.dataBlockNumber != 512)
	{
		cout << "系统第一次运行，请按任意键开始格式化虚拟文件系统VFS" << endl;
		system("pause");
		fsList[0]->format();
	}

	SystemOpenFileListItem sofli("", 0);
	openList.push_back(sofli);
	help();
	while (menu0());
	logout();
}

int OS::menu0()
{
	string operate;
	string args;
	int space = 0;
	int result;
	for (int i = 0; i < openList.size(); i++)
	{
		cout << openList[i].name << "/";
	}
	cout << ">";
	cin >> operate;
	if (operate == "exit") return 0;
	else if (operate == "ls") ls();
	else if (operate == "help") help();
	else if (operate == "format")
	{
		cout << "确定要格式化文件系统吗？[Y/N]" << endl;
		cin >> args;
		if (args == "Y" || args == "y")
		{
			fsList[0]->format();
			cout << "格式化完成" << endl;
			openList.clear();
			openList.push_back(SystemOpenFileListItem("", 0));
		}
	}
	else if (operate == "mkdir")
	{
		cin >> args;
		result = fsList[0]->mkdir(openList[openList.size() - 1].id, user, '0', args);
		if (result == 1)
		{
			cout << "目录" + args + "创建成功" << endl;
		}
		else if (result == -10)
		{
			cout << "存在同名文件或目录" << endl;
		}
	}
	else if (operate == "create")
	{
		cin >> args;
		result = fsList[0]->CreateAFile(openList[openList.size() - 1].id, user, '0', args);
		if (result == 1)
		{
			cout << "文件" + args + "创建成功" << endl;
		}
		else if (result == -10)
		{
			cout << "文件名重复" << endl;
		}
	}
	else if (operate == "delete")
	{
		cin >> args;
		result = fsList[0]->DeleteAFile(openList[openList.size() - 1].id, user, '0', args);
		if (result == 1)
		{
			cout << "文件" + args + "已经成功删除" << endl;
		}
		else if (result == -10)
		{
			cout << "文件名重复" << endl;
		}
	}
	else if (operate == "chdir")
	{
		cin >> args;
		if (args == ".." && openList.size() > 1) openList.pop_back();				//返回上级菜单
		else
		{
			result = fsList[0]->namei(openList[openList.size() - 1].id, args);
			
			if (result > 0)
			{
				if (fsList[0]->inodes[result].fileType == 1)
				{
					SystemOpenFileListItem sofli(args, result);
					openList.push_back(sofli);
					return 1;
				}
			}
			cout << "目录不存在" << endl;
		}
	}
	else if (operate == "read")
	{
		cin >> args;
		result = fsList[0]->namei(openList[openList.size() - 1].id, args);
		char fileBuffer[5120];
		if (result > 0)
		{
			if (fsList[0]->inodes[result].fileType == 0)
			{
				int length;
				SystemOpenFileListItem sofli(args, result);
				openList.push_back(sofli);
				cout << args + ":" << endl;
				fsList[0]->read(result, user, '0', length, fileBuffer);
				cout << fileBuffer << endl;
				openList.pop_back();
				return 1;
			}
			cout << "文件不存在" << endl;
		}
	}
	else if (operate == "write")
	{
		cin >> args;
		result = fsList[0]->namei(openList[openList.size() - 1].id, args);
		char fileBuffer[5120];
		if (result > 0)
		{
			if (fsList[0]->inodes[result].fileType == 0)
			{
				int length;
				SystemOpenFileListItem sofli(args, result);
				openList.push_back(sofli);
				cout << args + ":" << endl;
				cin >> fileBuffer;
				length = strlen(fileBuffer);
				fsList[0]->write(result, user, '0', length, fileBuffer);
				openList.pop_back();
				return 1;
			}
			cout << "文件不存在" << endl;
		}
	}
	else help();
	return 1;
}

void OS::outCurrentInode()
{
	
}

void OS::ls()
{
	Inode thisInode = fsList[0]->inodes[openList[openList.size() - 1].id];
	int folderNumber = 0, folderItemNumber = 0;
	char blockBuffer[512];
	char foderItem[16];
	FolderItem aFolderItem;

	if (thisInode.fileType == 1)
	{
		if (thisInode.state == 0 || thisInode.fileSize == 0)
		{
			cout << "空目录" << endl;
		}
		else
		{
			folderNumber = thisInode.fileSize / 16;
			for (int i = 0; i < thisInode.blockNumber; i++)
			{
				fsList[0]->ReadABlock(34 + thisInode.blocksIndex[i], blockBuffer);
				if (folderNumber >= 32) folderItemNumber = 32;
				else folderItemNumber = folderNumber;
				for ( int j = 0; j < folderItemNumber; j++)
				{
					BitOperate::bitCopy(foderItem, 0, blockBuffer, j * 128, 128);
					aFolderItem.LoadFromBuffer(foderItem);
					cout << aFolderItem.name << "[" << ((fsList[0]->inodes[aFolderItem.inode].fileType == 0) ? "文件" : "文件夹") << "]" << "\t";
				}
			}
			cout << endl;
		}
	}
}

void OS::help()
{
	cout << "================= 帮助 help ====================" << endl;
	cout << "help —— 帮助" << endl;
	cout << "ls —— 查看当前目录" << endl;
	cout << "mkdir [folder name] —— 创建文件夹" << endl;
	cout << "create [file name] —— 创建文件" << endl;
	cout << "delete [file name] —— 删除文件" << endl;
	cout << "chdir [folder name] —— 目录跳转" << endl;
	cout << "read [file name] —— 读取文件" << endl;
	cout << "write [file name] —— 写入文件" << endl;
	cout << "format —— 格式化文件系统" << endl;
	//cout << "close [file name] —— 关闭文件" << endl;
	cout << "exit —— 退出系统" << endl;
	cout << "================================================" << endl << endl;
}

SystemOpenFileListItem::SystemOpenFileListItem()
{
	id = -1;
	name = "";
}

SystemOpenFileListItem::SystemOpenFileListItem(string name, short id)
{
	this->name = name;
	this->id = id;
}

SystemOpenFileListItem::SystemOpenFileListItem(const SystemOpenFileListItem & sofli)
{
	name = sofli.name;
	id = sofli.id;
}
