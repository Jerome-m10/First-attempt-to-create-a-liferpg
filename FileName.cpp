#include<iostream>
#include<fstream>
#include<string>
using std::string;
using std::cout;
using std::cin;
using std::endl;
struct PlayData {
	int strength = 10;
	int stamina = 10;
	int intelligence = 10;
};
void DataSave(const PlayData& Data) { //const的用处即是将main函数操作得出的新PlayerData保护起来复制到file里，防止不当操作进行修改；&应用类型隐形绑定地址，也可用指针
	std::ofstream file;
	file.open("D:\\LIFE RPG\\BETA I\\playdata.txt");   //此处地址只是个人为了在电脑上调试数据所固定的

	file << Data.intelligence<<"\n";
	file << Data.stamina<<"\n";
	file << Data.strength<<"\n";
	file.close();
}
PlayData Dataload() {  //Playdata 用于传递回值
	PlayData data;
	std::ifstream file("D:\\LIFE RPG\\BETA I\\playdata.txt");
	if (file.is_open()) {                      //在读取方面，需要判断文件是否存在
		file >> data.intelligence;
		file >> data.stamina;
		file >> data.strength;
	}
	return data;
}
int OperateInt() {      //对智力进行操作，最简单的线性模型，暂无设计衰减上限模型
	int choice,times;
	cout << "你进天做了什么，做了几次" << endl;
	cout << "1,学习数学" << endl;
	cout << "2,学习数据结构" << endl;
	cout << "3,做项目" << endl;
	cin >> choice >> times;
	switch (choice) {
	case 1:
		return 5 * times;
	case 2:
		return 4 * times;
	case 3:
		return 3 * times;
	default:
		return 0;
	}

}
int OperateSta() {   //耐力
	int choice, times;
	cout << "你进天做了什么，做了几次" << endl;
	cout << "1,长跑1000m" << endl;
	cout << "2,速度耐力100*4" << endl;
	cout << "3,骑自行车3km" << endl;
	cin >> choice >> times;
	switch (choice) {
	case 1:
		return 5 * times;
	case 2:
		return 4 * times;
	case 3:
		return 3 * times;
	default:
		return 0;
	}

}
int OperateStr() {                 //力量
	int choice, times; 
	cout << "你进天做了什么，做了几次" << endl;
	cout << "1,健身房" << endl;
	cout << "2,俯卧撑100个" << endl;
	cout << "3,练腹肌" << endl;
	cin >> choice >> times;
	switch (choice) {
	case 1:
		return 5 * times;
	case 2:
		return 4 * times;
	case 3:
		return 3 * times;
	default:
		return 0;
	}

}
int main() {
	int a,timejudge=0;
	PlayData IniData;
	IniData = Dataload();
	cout << "您当前的智力，体力，力量数值分别为" << endl;
	cout << IniData.intelligence <<"  " << IniData.stamina <<"  " << IniData.strength << endl;
	while (1) {
		timejudge++;
		cout << "请输入你的操作" << endl;
		cout << "0:结束" << endl;
		cout << "1:进行智力训练" << endl;
		cout << "2:进行体力训练" << endl;
		cout << "3:进行力量训练" << endl;
		cin >> a;
		if (a == 0)
			if (timejudge == 1)
				return 0;
			else break;
		switch (a) {
		case 1:
			IniData.intelligence+=OperateInt();
			break;
		case 2:
			IniData.stamina += OperateSta();
			break;
		case 3:
			IniData.strength += OperateStr();
			break;
		default:
			cout << "错误操作" << endl;
			break;
		}

	}
	DataSave(IniData);
	return 0;
}
