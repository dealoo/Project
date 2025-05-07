#pragma once
#include"AdminPanel.h"


class User {
public:
	string name;
	string phone;
	float balance;
	int age;



	User(string Name, string Phone, int Age, float Balance)
	{ 
		this->name = Name;
		this->phone = Phone;
		this->age = Age;
		this->balance = Balance;
	}

	string GetName() {
		return name;
	}
	string GetPhone() {
		return phone;
	}
	int GetAge() {
		return age;
	}
	float GetBalance() {
		return balance;
	}
};



int UserMain(string name, string phone, int age, float balance) {
	User user(name, phone, age, balance);

	while (true) {
		CLSconsol();
		PrintMSG(name, 44);
		
		cout << "user:" << user.GetName() << "\n" << "Balance: "<< user.GetBalance()<< "\n\n\n";
		cout << "Menyu: " << endl;
		loadFromFile();
		showFood();

		cout << "\n\n\n" << endl;
		PrintColor("[1] Get Food\n", 44);
		PrintColor("[0] Exit\n", 44);
		cout << "\n\n" << endl;
		int n;
		cout << "Input Index: ";
		cin >> n;

		if (n == 1) {
			CLSconsol();
			PrintMSG("Sifaris", 44);

			cout << "user:" << user.GetName() << "\n" << "Balance: " << user.GetBalance() << "\n\n\n";
			cout << "Menyu: " << endl;
			showFood();
			
			try {
				int indeks;
				cout << "Indeks daxil et: ";
				cin >> indeks;

				Food food = getFoodByIndex(indeks);
				cout << "Ad: " << food.name << "\n";
				cout << "Qiymət: " << food.price << "\n";
				cout << "Tərkib: " << food.ings << "\n";

				if (user.balance >= food.price) {
					PrintColor("\nUgurla sifaris verildi\n", 44);
					user.balance -= food.price;
				}
				else {
					PrintColor("Balansda kifayet geder mebleg yoxdur!\n\n", 41);
					
				}
			}
			catch (const exception& e) {
				cout << "\n\nXəta baş verdi: " << e.what() << "\n\n";
			}

		}
		else if (n == 0) {
			return 0;
		}
		else {
			PrintColor("Index Error!", 41);
		}

		EnterExit();

	}



	return 0;
}