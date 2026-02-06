#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"json.hpp"
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using json = nlohmann::json;  //简写一下
struct Task {                          //用于用户自己添加事项
	string name;
	int ValueToAdd;
	string category;
	int ncategory;
};
vector<Task> intelligence;
vector<Task> stamina;
vector<Task> strength;
struct PlayData {
	int strength = 10;
	int stamina = 10;
	int intelligence = 10;
};
void DataSave(const PlayData& Data) { //const的用处即是将main函数操作得出的新PlayerData保护起来复制到file里，防止不当操作进行修改；&应用类型隐形绑定地址，也可用指针
	std::ofstream file;
	file.open("D:\\LIFE RPG\\BETA I\\playdata.txt");

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
int OperateInt() {
	int choice,times;
	int i=0,add;
	for (auto it = intelligence.begin(); it != intelligence.end(); it++) {
		cout << ++i << "," << it->name << endl;
	}
	cin >> choice >> times;
	add = intelligence[choice - 1].ValueToAdd * times;
	return add;
}
int OperateSta() {
	int choice, times;
	int i = 0, add;
	for (auto it = stamina.begin(); it != stamina.end(); it++) {
		cout << ++i << "," << it->name << endl;
	}
	cin >> choice >> times;
	add = stamina[choice - 1].ValueToAdd * times;
	return add;
}
int OperateStr() {
	int choice, times;
	int i = 0, add;
	for (auto it = strength.begin(); it != strength.end(); it++) {
		cout << ++i << "," << it->name << endl;
	}
	cin >> choice >> times;
	add = strength[choice - 1].ValueToAdd * times;
	return add;

}
void CreateNewTask() {    //创建新的任务
	Task newtask;
	cout << "请分别输入任务名字，能力增长，类别，类别代号" << endl;
	cin >> newtask.name >> newtask.ValueToAdd >> newtask.category >> newtask.ncategory;
	switch (newtask.ncategory) {    //按照任务的类型分类
	case 1:
		intelligence.push_back(newtask);
		break;
	case 2:
		stamina.push_back(newtask);
		break;
	case 3:
		strength.push_back(newtask);
		break;
	default:
		cout << "错误的结果" << endl;
	}
}
void TaskSave() {
	json j = json::array();
	for (const auto& t : intelligence) {    //这种只读的用法有的时候还是不熟练，（declaration:range）
		j.push_back({                        
			{"name",t.name},
			{"ValueToAdd",t.ValueToAdd},
			{"category",t.category},
			{"ncategory",t.ncategory}
			});
	}
	for (const auto& t : stamina) {
		j.push_back({
			{"name",t.name},
			{"ValueToAdd",t.ValueToAdd},
			{"category",t.category},
			{"ncategory",t.ncategory}
			});
	}
	for (const auto& t : strength) {
		j.push_back({
			{"name",t.name},
			{"ValueToAdd",t.ValueToAdd},
			{"category",t.category},
			{"ncategory",t.ncategory}
			});
	}
	std::ofstream file("D:\\LIFE RPG\\BETA I\\tasks.json");
	file << j.dump(4);        //以字符串输出到文件
}
void DownloadTask() {
	std::ifstream file("D:\\LIFE RPG\\BETA I\\tasks.json");
	if (!file.is_open()) {
		std::cerr << "警告：未找到tasks.json文件，将创建新的任务列表" << std::endl;
		return;
	}

	json j;
	file >> j;
	for (const auto& jsonTask : j) {
		Task comtemporary;
		comtemporary.category = jsonTask["category"];
		comtemporary.ncategory = jsonTask["ncategory"];
		comtemporary.name = jsonTask["name"];
		comtemporary.ValueToAdd = jsonTask["ValueToAdd"];
		switch (comtemporary.ncategory) {    //按照任务的类型分类
		case 1:
			intelligence.push_back(comtemporary);
			break;
		case 2:
			stamina.push_back(comtemporary);
			break;
		case 3:
			strength.push_back(comtemporary);
			break;
		default:
			cout << "错误的结果" << endl;
		}
	}

}
int main() {
	int a,timejudge=0;
	DownloadTask();   //加载任务数据
	PlayData IniData;
	IniData = Dataload();
	cout << "您当前数值为" << endl;
	cout << IniData.intelligence <<"  " << IniData.stamina <<"  " << IniData.strength << endl;
	while (1) {
		timejudge++;
		cout << "请输入你的操作" << endl;
		cout << "0:结束" << endl;
		cout << "1:进行智力训练" << endl;
		cout << "2:进行体力训练" << endl;
		cout << "3:进行力量训练" << endl;
		cout << "4:加入新任务" << endl;
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
		case 4:
			CreateNewTask();
			break;
		default:
			cout << "错误操作" << endl;
			break;
		}

	}
	DataSave(IniData);
	TaskSave();
	return 0;
}
