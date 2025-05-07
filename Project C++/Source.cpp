#include "Header.h"
#include "AdminPanel.h"
#include "Users.h"


class LogIn {
public:
	string name;
	string phoneNumber;
	int age;
	string password;
	int balance;

	LogIn(string Name, string Number, int Age, string Password) {
		name = Name;
		phoneNumber = Number;
		age = Age;
		password = Password;
		balance = 30;
	}
	void BalanceControl(int Balance = 0) {
		this->balance += Balance;
	}
};

vector<LogIn> ReadFromFile(string filename = "Data.txt") {
	vector<LogIn> users;
	ifstream file(filename);
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string name, phone, AGE, balance, password;

		if (getline(ss, name, '#') &&
			getline(ss, phone, '#') &&
			getline(ss, AGE, '#') &&
			getline(ss, balance, '#') &&
			getline(ss, password, '#')) {
			int age = stoi(AGE);
			users.push_back(LogIn(name, phone, age, password));
		}
	}

	file.close();
	return users;
}

void ShowUsers(string filename = "Data.txt") {
	vector<LogIn> users = ReadFromFile(filename);

	for (const auto& user : users) {
		cout << "Name: " << user.name << endl;
		cout << "Age: " << user.age << endl;
		cout << "Number: " << user.phoneNumber << endl;
		cout << "Balance: " << user.balance << endl;
		cout << "passwoed: " << user.password << endl;
	}
}

int ControlSingIn(string name, string password) {
	string filename = "Data.txt";
	vector<LogIn> users = ReadFromFile(filename);

	for (const auto& user : users) {
		if ((user.name == name || user.phoneNumber == name) && user.password == password) {
			return 1;
		}
	}
	return 0;
}

int ControlSingUp(string name, string number) {
	string filename = "Data.txt";
	vector<LogIn> users = ReadFromFile(filename);

	for (const auto& user : users) {
		if (user.name == name || user.phoneNumber == number) {
			return 0;
		}
	}
	return 1;
}

int WriteToFile(LogIn newUser, string filename = "Data.txt") {
	vector<LogIn> users = ReadFromFile(filename);
	users.push_back(newUser);

	ofstream file(filename, ios::out);
	if (!file.is_open()) {
		return 0;
	}

	for (const auto& user : users) {
		file << user.name << "#" << user.phoneNumber << "#" << user.age << "#" << user.balance << "#" << user.password << "\n";
	}
	file.close();
	return 1;
}

void LogInUser(string name, string number, string password, int age) {
	bool valid = true;

	if (name.length() < 3) {
		cout << "\nAd minimum 3 herf olmalidir!" << endl;
		valid = false;
	}

	if (number.length() < 9 || number.length() > 10) {
		cout << "\nNomre 0123456789 ve ya 1234567890 formatinda olmalidir!" << endl;
		valid = false;
	}

	for (char c : number) {
		if (!isdigit(c)) {
			cout << "\nNomrede yalniz reqem olmalidir!" << endl;
			valid = false;
			break;
		}
	}

	if (password.length() < 6 || password.length() > 16) {
		cout << "\nSifre 6-16 simvol araliginda olmalidir!" << endl;
		valid = false;
	}

	if (age < 18) {
		cout << "\nYash 18-den boyuk olmalidir!" << endl;
		valid = false;
	}

	if (HasSharp(name) || HasSharp(password) || HasSharp(number)) {
		cout << "Ad ve ya sifrede '#' simvolu isdifade etmey olmaz!" << endl;
		return;
	}


	int n = ControlSingUp(name, number);

	if (valid) {
		if (n) {
			LogIn user(name, number, age, password);
			int n = WriteToFile(user);
			if (n == 0) {
				CLSconsol();
				PrintColor("\nGeydiyat ugursuz oldu!!", 41, 1);
			}
			else {
				CLSconsol();
				PrintColor("\nGeydiyat Ugurla tamamlandi", 44, 1);
			}
		}
		else {
			PrintColor("\nIsdifadeci adi ve ya telefon nomresi sistemde movcuddur!!", 41, 1);
		}
	}
}



int main() {

	while (true) {

		PrintMSG("Log In", 44);

		cout << "\n\n\n" << endl;
		PrintCanter("[1] Sing In");
		PrintCanter("[2] Sing Up");
		PrintCanter("[3] Exit");

		int index;
		PrintCanter("\nInput Index: ", 1);
		cin >> index;



		if (index == 3) {
			return 0;
		}
		else if (index == 1) {
			CLSconsol();
			PrintMSG("Sing In", 44);

			string name, password;


			cout << "Name or Phone: ";
			cin >> name;
			cout << "Password: ";
			cin >> password;

			if ((name == "admin" || name == "Admin") && (password == "admin" || password == "Admin")) {
				AdminMain();
			}
			else {
				int n = ControlSingIn(name, password);
				if (n == 1) {
					PrintColor("Hesab tapildi!", 44, 1);
					string filename = "Data.txt";
					vector<LogIn> users = ReadFromFile(filename);
					for (auto& user : users) {
						if (user.name == name || user.phoneNumber == name) {
							UserMain(user.name, user.phoneNumber, user.age, user.balance);
							break;
						}
					}

				}
				else {
					PrintColor("Hesab tapilmadi!", 41, 1);
				}
			}
		}
		else if (index == 2) {
			CLSconsol();
			PrintMSG("Sing Up", 44);

			string name, phoneNumber, password;
			int age;


			cout << "Name: ";
			cin >> name;
			cout << "Phone: ";
			cin >> phoneNumber;
			cout << "Age: ";
			cin >> age;
			cout << "Password: ";
			cin >> password;

			LogInUser(name, phoneNumber, password, age);

		}


		Sleep(3000);
		CLSconsol();

	}




	return 1;
}