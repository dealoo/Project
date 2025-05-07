#pragma once
#include "Header.h"
#include <string>


#pragma region Ingredients

class Ingredients {
public:
	string IgName;
	int IgWeight;
	double IgPrice;

	Ingredients(string name, int weight, double price) {
		this->IgName = name;
		this->IgWeight = weight;
		this->IgPrice = price;
	}
	void Edit(string name, int weight, double price) {
		this->IgName = name;
		this->IgWeight = weight;
		this->IgPrice = price;
	}
	int GetWeight() {
		return this->IgWeight;
	}

	double GetPrice() {
		return this->IgPrice;
	}
};

//Fayildan Ingredient leri oxuma <vector formatinda>
vector<Ingredients> ReadIngredients(string filename = "Ig.txt") {
	vector<Ingredients> ingredients;
	ifstream file(filename);
	string line;

	while (getline(file, line)) {
		stringstream n(line);
		string name, weightStr, priceStr;

		if (getline(n, name, '#') && getline(n, weightStr, '#') && getline(n, priceStr, '#')) {
			int weight = stoi(weightStr);
			double price = stod(priceStr);
			ingredients.push_back(Ingredients(name, weight, price));
		}
	}
	file.close();
	return ingredients;
}

//Fayli write modunda acarag yazma 
int WriteAllIngredients(vector<Ingredients> ingredients, string filename = "Ig.txt") {
	ofstream file(filename, ios::out);
	if (!file.is_open()) return 0;

	for (const auto& ig : ingredients) {
		file << ig.IgName << "#" << ig.IgWeight << "#" << ig.IgPrice << "\n";
	}

	file.close();
	return 1;
}

//Liste yeni Ingredient elave eleme
int AddIngredients(vector<Ingredients>& ingredients, string name, int weight, double price) {
	bool n = true;

	for (auto& ig : ingredients) {
		if (ig.IgName == name) {
			ig.IgWeight += weight;
			ig.IgPrice = price;
			n = false;
			break;
		}
	}
	if (n) {
		ingredients.push_back(Ingredients(name, weight, price));
		return 0;
	}
	return 1;
}

//Ingredient de duzelis etme ceki & ad
int EditIngredients(vector<Ingredients>& ingredients, string oldName, string newName, int newWeight, double newPrice) {
	for (auto& ig : ingredients) {
		if (ig.IgName == oldName) {
			ig.IgName = newName;
			ig.IgWeight = newWeight;
			ig.IgPrice = newPrice;
			return 1;
		}
	}
	return 0;
}

//Ingredient silme 
int DeleteIngredient(vector<Ingredients>& ingredients, string name) {
	for (int i = 0; i < ingredients.size(); i++) {
		if (ingredients[i].IgName == name) {
			ingredients.erase(ingredients.begin() + i);
			return 1;
		}
	}
	return 0;
}

// butun Ingredient leri ekrana cedvel seklinde cixarma
void ShowIngredients(vector<Ingredients> ingredients, string filename = "Ig.txt") {
	int n = 0;
	cout << "-------------------------------------------------------------" << endl;
	cout << setw(5) << "No" << setw(20) << "Name" << setw(15) << "Weight(g)" << setw(15) << "Price($)" << endl;
	cout << "-------------------------------------------------------------" << endl;
	for (const auto& ig : ingredients) {
		cout << setw(5) << n + 1;
		cout << setw(20) << ig.IgName;
		cout << setw(15) << ig.IgWeight;
		cout << setw(15) << fixed << setprecision(2) << ig.IgPrice << endl;
		n++;
	}
	cout << "-------------------------------------------------------------" << endl;
}

#pragma endregion

#pragma region Menyu
struct Food {
    string name;
    float price;
    string ings;
};

vector<Food> menyu;

Food getFoodByIndex(int index) {
	if (index > 0 && index - 1 < menyu.size()) {
		return menyu[index - 1];
	}
	else {
		throw out_of_range("Index duzgun deyil!");
	}
}

void loadFromFile() {
	ifstream file("menyu.txt");
	if (!file.is_open()) {
		PrintColor("Fayli acmag mumkun olmadi!", 41);
		return;
	}
	menyu.clear(); 
	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		Food f;
		string priceStr;

		getline(ss, f.name, ';');
		getline(ss, priceStr, ';');
		getline(ss, f.ings);

		f.price = stof(priceStr);

		menyu.push_back(f);
	}

	file.close();
	cout << "Menyu fayldan yükləndi!\n";
}

void saveToFile() {
	ofstream file("menyu.txt"); 

	for (const Food& f : menyu) {
		file << f.name << ";" << f.price << ";" << f.ings << "\n";
	}

	file.close();
	PrintColor("\nUgurla geyd edildi!\n", 44);
}

void addFood() {
	Food yeni;
	cout << "Yemeyin adi: ";
	getline(cin >> ws, yeni.name);
	cout << "Qiymeti: ";
	cin >> yeni.price;
	cout << "Terkibi: ";
	getline(cin >> ws, yeni.ings);

	menyu.push_back(yeni);
	cout << "Yemek elave olundu!\n";
}

void showFood() {
	cout << left << setw(5) << "ID"
		<< setw(20) << "Ad"
		<< setw(10) << "Qiymet"
		<< "Teterkibi" << endl;

	cout << string(50, '-') << endl;

	for (int i = 0; i < menyu.size(); ++i) {
		cout << left << setw(5) << i+1
			<< setw(20) << menyu[i].name
			<< setw(10) << menyu[i].price
			<< menyu[i].ings << endl;
	}

}

void editFood() {
	int index;
	showFood();
	cout << "Deyisilecey yemeyin index'i: ";
	cin >> index;

	if (index >= 0 && index < menyu.size()) {
		cout << "Yeni ad: ";
		getline(cin >> ws, menyu[index].name);
		cout << "Yeni qiymet: ";
		cin >> menyu[index].price;
		cout << "Yeni terkib: ";
		getline(cin >> ws, menyu[index].ings);
		cout << "deyisdirildi!\n";
	}
	else {
		PrintColor("\nDogru Index Daxil edin!\n", 41);
	}
}

void deleteFood() {
	int index;
	showFood();
	cout << "Silmek istediyin yemeyin indexi: ";
	cin >> index;

	if (index >= 0 && index < menyu.size()) {
		menyu.erase(menyu.begin() + index);
		cout << "Yemek silindi!\n";
	}
	else {
		PrintColor("\nDogru Index Daxil edin!\n", 41);
	}
}



#pragma endregion

int AdminMain() {
	const string filename = "Ig.txt";
	vector<Ingredients> ingridients = ReadIngredients(filename);


	while (true) {
		int index;
		CLSconsol();
		PrintMSG("Admin-Panel", 44);
		cout << "\n\n\n" << endl;
		PrintCanter("[1] Edit Products");
		PrintCanter("[2] Edit Menyu");
		PrintCanter("[3] Show analiz");
		PrintCanter("[4] Exit");
		PrintCanter("Input index: ");
		cin >> index;

		if (index == 1) {
			while (true) {
				CLSconsol();
				int index;
				PrintMSG("Edit Products", 44);
				PrintCanter("[1] Add Product");
				PrintCanter("[2] Edit Product");
				PrintCanter("[3] Delet Product");
				PrintCanter("[4] Show Product");
				PrintCanter("[5] Exit");
				PrintCanter("Input index: ", false);
				cin >> index;

				if (index == 1) {
					CLSconsol();
					PrintMSG("Add Product");

					int IgWeight;
					double IgPrice;
					string IgName;

					cout << "Name: ";
					cin >> IgName;
					cout << "Weight: ";
					cin >> IgWeight;
					cout << "Price: ";
					cin >> IgPrice;

					if (AddIngredients(ingridients, IgName, IgWeight, IgPrice)) {
						PrintColor("Movcun Ingredirnt'in cekisine elave olundu!\n", 44);
					}
					else {
						PrintColor("Elave olund!\n", 44);
					}
					EnterExit();
				}
				else if (index == 2) {
					CLSconsol();
					PrintMSG("Edit Product");
					ShowIngredients(ingridients);

					string oldName;
					string name;
					int weight;
					double price;

					cout << "Old ingredient name: ";
					cin >> oldName;
					cout << "New name: ";
					cin >> name;
					cout << "New weight: ";
					cin >> weight;
					cout << "New price: ";
					cin >> price;

					if (EditIngredients(ingridients, oldName, name, weight, price)) {
						PrintColor("\nUgurla deyisdirildi\n", 44);
					}
					else {
						PrintColor("\nIngridient tapilmadi!\n", 41);
					}
					EnterExit();
					Sleep(50);
				}
				else if (index == 3) {
					CLSconsol();
					PrintMSG("Delet Product");
					ShowIngredients(ingridients);

					string name;
					cout << "Name: ";
					cin >> name;

					if (DeleteIngredient(ingridients, name)) {
						PrintColor("\nUgurla silindi!\n", 44);
					}
					else {
						PrintColor("\nIngredient tapilmadi\n", 41);
					}

					EnterExit();
					Sleep(50);
				}
				else if (index == 4) {
					CLSconsol();
					PrintMSG("Products");
					ShowIngredients(ingridients);
					EnterExit();
				}
				else if (index == 5) {
					break;
				}
				else {
					PrintColor("Dogru index daxil edin!!", 41, true);
					Sleep(3000);
				}
			}

		}
		else if (index == 2) {

			loadFromFile();
			while (true) {
				CLSconsol();
				int index;
				PrintMSG("Edit Menyu", 44);
				PrintCanter("[1] Add food");
				PrintCanter("[2] Edit food");
				PrintCanter("[3] Delet food");
				PrintCanter("[4] Show food");
				PrintCanter("[0] Exit");
				PrintCanter("Input index: ", true);
				cin >> index;


				if (index == 1) {
					CLSconsol();
					PrintMSG("Add food");
					addFood();


					EnterExit();
				}
				else if (index == 2) {
					CLSconsol();
					PrintMSG("Edit food");
					editFood();

					EnterExit();
				}
				else if (index == 3) {
					CLSconsol();
					PrintMSG("Delet food");
					deleteFood();

					EnterExit();
				}
				else if (index == 4) {
					CLSconsol();
					PrintMSG("Whoe Foods");
					showFood();

					EnterExit();
				}
				else if (index == 0) {
					CLSconsol();
					PrintMSG("Exit");
					break;
				}
				else {
					PrintColor("\n\nDuzgun index daxil edin!\n\n", 41, true);
				}
			}

			saveToFile();


		}
		else if (index == 3) {
			CLSconsol();
			PrintMSG("Analiz", 44);
			PrintColor("\n\nHal hazirda hec bir netice yoxdur en gec 1 hefteye insAllah\n\n", 41);
			EnterExit();

		}
		else if (index == 4) {

			break;
		}
		else {
			PrintColor("Dogru index daxil edin!!", 41, true);
			Sleep(3000);
		}
	}
	CLSconsol();
	PrintMSG("Update data..");

	if (WriteAllIngredients(ingridients, filename) == 1)
	{
		PrintColor("\n\nYadda saxlanildi!\n\n", 44, true);
	}
	else {
		PrintColor("\n\nYadda saxlama mumkun olmai!\n\n", 41, true);
	}
	cout << endl;
	EnterExit();

	return 1;
}
