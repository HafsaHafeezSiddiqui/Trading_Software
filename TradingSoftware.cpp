#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct Account
{
    double balance;
    std::string transactionHistory;
    double bitcoin_holdings;
};

std::map<std::string, Account> accounts;
double bitcoin_price = 5000;
void createAccount(std::string username)
{
    if (accounts.count(username) == 0)
    {
        Account newAccount;
        newAccount.balance = 0;
        newAccount.transactionHistory = "";
        newAccount.bitcoin_holdings = 0;
        accounts[username] = newAccount;
        cout << "A new account was created successfully!" << endl;
    }
}
void deposit(std::string username)
{
    double amount;
    cout << "Enter amount to deposit: " << endl;
    cin >> amount;
    if (accounts.count(username) != 0)
    {
    }
    accounts[username].balance += amount;
    accounts[username].transactionHistory += "Deposited " + std::to_string(amount) + "\n";
    cout << "Deposited Successfully" << endl;
}

void withdraw(std::string username)
{
    double amount;
    cout << "Enter amount to withdraw: " << endl;
    cin >> amount;
    if (accounts.count(username) != 0 && accounts[username].balance >= amount)
    {
        accounts[username].balance -= amount;
        accounts[username].transactionHistory += "Withdrew " + std::to_string(amount) + "\n";
        cout << "Withdrawn Successfully" << endl;
    }
    else
    {
        cout << "Insufficient funds" << endl;
    }
}
// accounts.count(username) != 0 &&
void buyBitcoin(std::string username, double amount)
{
    if (accounts[username].balance >= amount * bitcoin_price)
    {
        accounts[username].balance -= amount * bitcoin_price;
        accounts[username].bitcoin_holdings += amount;
        accounts[username].transactionHistory += "Bought " + std::to_string(amount) + " bitcoin\n";
        cout << "Bought " << to_string(amount) << " bitcoin(s) successfully" << endl;
    }
}

void sellBitcoin(std::string username, double amount)
{
    if (accounts.count(username) != 0 && accounts[username].bitcoin_holdings >= amount)
    {
        accounts[username].balance += amount * bitcoin_price;
        accounts[username].bitcoin_holdings -= amount;
        accounts[username].transactionHistory += "Sold " + std::to_string(amount) + " bitcoin\n";
        cout << "Sold " << to_string(amount) << " bitcoin(s) successfully" << endl;
    }
}
void displayAccount(std::string username)
{
    if (accounts.count(username) != 0)
    {
        std::cout << "Balance: " << accounts[username].balance << std::endl;
        std::cout << "Bitcoin Holdings: " << accounts[username].bitcoin_holdings << std::endl;
        std::cout << "Transaction History: " << accounts[username].transactionHistory << std::endl;
    }
}
void displaySortedAccount(std::string username)
{
    if (accounts.count(username) != 0)
    {
        std::cout << "Username: " << username << std::endl;
        std::cout << "Bitcoin Holdings: " << accounts[username].bitcoin_holdings << std::endl;
    }
}

void searchAccount(std::string username)
{
    if (accounts.count(username) != 0)
    {
        cout << "Account found." << endl;
        return true;
    }
    else
    {
        cout << "Account not found." << endl;
        return false;
    }
}
void sortAccounts()
{
    std::vector<std::pair<std::string, Account>> accounts_vec;
    for (auto it = accounts.begin(); it != accounts.end(); it++)
        accounts_vec.push_back(*it);

    sort(accounts_vec.begin(), accounts_vec.end(),
         [](auto &a, auto &b)
         { return a.second.bitcoin_holdings < b.second.bitcoin_holdings; });

    cout << "Sorted Accounts based on: bitcoin_holdings" << endl;
    for (auto it = accounts_vec.begin(); it != accounts_vec.end(); it++)
        displaySortedAccount(it->first);
}

void menu()
{
    int choice;
    std::string username;
    double amount;

    while (true)
    {
        cout << "-------------------------------------------" << endl;
        cout << "--------Welcome to Trading Software-------" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Buy Cryptocurrency" << endl;
        cout << "5. Sell Cryptocurrency" << endl;
        cout << "6. Display Account Information" << endl;
        cout << "7. Search For Account" << endl;
        cout << "8. Sort Accounts" << endl;
        cout << "9. Exit" << endl;
        cout << "----------------------------------------" << endl;
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter username: ";
            cin >> username;
            if (!searchAccount(username))
            {
                cout << "Account already exists";
                break;
            }
            else
            {
                createAccount(username);
            }
            break;
        case 2:
            cout << "Enter username: ";
            cin >> username;
            deposit(username);
            break;
        case 3:
            cout << "Enter username: ";
            cin >> username;
            withdraw(username);
            break;
        case 4:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter the amount to buy: ";
            cin >> amount;
            buyBitcoin(username, amount);
            break;
        case 5:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter the amount to sell: ";
            cin >> amount;
            sellBitcoin(username, amount);
            break;
        case 6:
            cout << "Enter username: ";
            cin >> username;
            displayAccount(username);
            break;
        case 7:
            cout << "Enter username: ";
            cin >> username;
            searchAccount(username);
            break;
        case 8:
            sortAccounts();
            break;
        case 9:
            cout << "Thank you for using our trading software!" << endl;
            return;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    }
}
int main()
{
    menu();
    cout << "Do you wish to access the menu?" << endl;
    string choice;
    cin >> choice;
    if (choice == "Y")
    {
        menu();
    }
    else
    {
        cout << "Thankyou for using our trading software" << endl;
    }
}
