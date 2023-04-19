#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>


using namespace std;

class BankAccount {
	int accountNumber;
	char name[50];
	char accountType;
	int moneyDeposit;

public:
	void createAccount();
	void displayAccount();
	int retacno() const {
		return accountNumber;
	}
	void report() const;
	void dep(int x) {
		moneyDeposit += x;
	}
	void draw(int x) {
		moneyDeposit -= x;
	}
	int retdeposit() const {
		return moneyDeposit;
	}
	void modify();
};

void BankAccount::createAccount() {
	system("cls");
	cout << "\t Enter the account number: ";
	cin >> accountNumber;
	cout << "\t Enter the name of the account holder: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\t Enter the type of the account: " << endl;;
	cout << "\t (S for Savings and C for Current)" << endl;
	cin >> accountType;
	accountType = toupper(accountType);
	cout << "\t Enter the initial amount (>=500 for savings and >=1000 for current): ";
	cin >> moneyDeposit;
	cout << endl;
	cout << "\t Account created." << endl;
}

void BankAccount::displayAccount() {
	cout << "\t Bank Account Number: " << accountNumber << endl;
	cout << "\t Account Holder Name: " << name << endl;
	cout << "\t Type of Account: " << accountType << endl;
	cout << "\t Balance Amount: " << moneyDeposit << endl;
}

void BankAccount::report() const {
	cout << accountNumber << setw(10) << " " << name << setw(10) << accountType << setw(6) << moneyDeposit << endl;
}

void BankAccount::modify() {
	cout << "\t Account Number: " << accountNumber << endl;
	cout << "\t Modify Account Holder Name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\t Modify Type of Account: ";
	cin >> accountType;
	accountType = toupper(accountType);
	cout << "\t Modify Balance Amount: ";
	cin >> moneyDeposit;
}

void writeAccount() {
	BankAccount ac;
	ofstream outFile;
	outFile.open("account.data", ios::binary | ios::app);
	//ac.createAccount(reinterpret_cast<char*> (&ac), sizeof(BankAccount));
	ac.createAccount();
	outFile.close();

}

void deleteAccount(int n) {
	BankAccount ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.data", ios::binary);
	if (!inFile) {
		cout << "File could not be open !! Press any key...";
		return;
	}
	outFile.open("temp.data", ios::binary);
	inFile.seekg(0, ios::beg);

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(BankAccount))) {
		if (ac.retacno() != n) {
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(BankAccount));
		}
	}
	inFile.close();
	outFile.close();
	remove("BankAccount.data");
	cout << "\t Account and Recorded were deleted." << endl;

}

void displayDetails(int n) {
	BankAccount ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.data", ios::binary);
	if (!inFile) {
		cout << "File could not be open !! Press any key...";
		return;
	}
	cout << "\t Bank Account Details" << endl;
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(BankAccount))) {
		if (ac.retacno() == n) {
			ac.displayAccount();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false) {
		cout << "\t Account number not found" << endl;

	}

}



void displayAll() {
	system("cls");
	BankAccount ac;
	ifstream inFile;
	inFile.open("account.data", ios::binary);
	if (!inFile) {
		cout << "File could not be open !! Press any key...";
		return;
	}
	cout << "\t Bank Account Holder List" << endl;
	cout << "\t -----------------------------------------" << endl;
	cout << "Account Number:			Name			Type			Balance" << endl;
	cout << "\t -----------------------------------------" << endl;
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(BankAccount))) {
		ac.report();
	}
	inFile.close();
}

void moneyDepositWithdraw(int n, int option) {
	int amount;
	bool found = false;
	BankAccount ac;
	fstream File;
	File.open("account.data", ios::binary | ios::in | ios::out);
	if (!File) {
		cout << "File could not be open !! Press any key...";
		return;
	}
	while (!File.eof() && found == false) {
		File.read(reinterpret_cast<char*> (&ac), sizeof(BankAccount));
		if (ac.retacno() == n) {
			ac.displayAccount();
			if (option == 1) {
				cout << "\t Enter the amount to be deposited";
				cin >> amount;
				ac.dep(amount);
			}
			else {
				cout << "\t Enter the amount to be withdraw: ";
				cin >> amount;
				int balance = ac.retdeposit() - amount;
				if (balance < 0) {
					cout << "\t Insufficient balance";
				}
			}
			int position = (-1) * static_cast<int>(sizeof(BankAccount)); 
			File.seekp(position, ios::cur); // move the pointer to the position of the file
			File.write(reinterpret_cast<char*> (&ac), sizeof(BankAccount)); // write the record in the file
			cout << "\t Record Updated" << endl;
			found = true;
		}
	}
	File.close();
	if (found == false) {
		cout << "\t Record Not Found" << endl;
	}
}

void updateBankAccount(int n) {
	bool found = false;
	BankAccount ac;
	fstream File;
	File.open("account.data", ios::binary | ios::in | ios::out);
	if (!File) {
		cout << "File could not be open !! Press any key...";
		return;
	}
	while (!File.eof() && found == false) {
		File.read(reinterpret_cast<char*> (&ac), sizeof(BankAccount));
		if (ac.retacno() == n) {
			ac.displayAccount();
			cout << "\t Enter the new details of the account" << endl;
			ac.modify();
			int position = (-1) * static_cast<int>(sizeof(BankAccount));
			File.seekp(position, ios::cur); // move the pointer to the position of the file
			File.write(reinterpret_cast<char*> (&ac), sizeof(BankAccount)); // write the record in the file
			cout << "\t Record Updated" << endl;
			found = true;
		}
	}
	File.close();
	if (found == false) {
		cout << "\t Record Not Found" << endl;
	}
}

int main() {
	char ch;
	int num;

	do {

		// Create a start function that does alf of this bellow that keeps running until exit is entered:
		cout << "\t -----------------------------------------" << endl;
		cout << "\t | welcome to the Bank Management System |" << endl;
		cout << "\t -----------------------------------------" << endl;

		cout << endl;
		cout << "\t --- Main Menu ---" << endl;
		cout << "\t 1. Create Account" << endl;
		cout << "\t 2. Deposit Money" << endl;
		cout << "\t 3. Withdraw Money" << endl;
		cout << "\t 4. Check Balance" << endl;
		cout << "\t 5. Account Holder List" << endl;
		cout << "\t 6. Delete an Account" << endl;
		cout << "\t 7. Edit an Account" << endl;
		cout << "\t 8. Exit" << endl;
		cout << endl;

		cout << "\t Enter Your Choice (1-8): ";
		cin >> ch;

		switch (ch) {
		case '1':
			writeAccount();
			break;
		case '2':
			system("cls");
			cout << "\t Enter the Account Number: ";
			cin >> num;
			moneyDepositWithdraw(num, 1);
			break;
		case '3':
			system("cls");
			cout << "\t Enter the Account Number: ";
			cin >> num;
			moneyDepositWithdraw(num, 2);
			break;
		case '4':
			system("cls");
			cout << "\t Enter the Account Number: ";
			cin >> num;
			displayDetails(num);
			break;
		case '5':
			break;
		case '6':
			system("cls");
			cout << "\t Enter the Account Number: ";
			cin >> num;
			deleteAccount(num);
			break;
		case '7':
			system("cls");
			cout << "\t Enter the Account Number: ";
			cin >> num;
			updateBankAccount(num);
			break;
		case '8':
			cout << "\t Thanks For Using The Bank Management System" << endl;
			return 0;
			break;


		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	

	BankAccount B;
	B.createAccount();
	B.displayAccount();
	return 0;
}

