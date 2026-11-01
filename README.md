# Banking System

## What it does

A menu-driven educational simulation with separate Customer, Account and Transaction classes. It creates and renames customers, opens and closes accounts, deposits and withdraws funds, transfers funds, shows account details, and displays each account's ten latest transactions.

## Classes and storage

| Class | Data |
| --- | --- |
| Customer | Customer ID and name |
| Account | Account ID, customer ID and balance in paisa |
| Transaction | Transaction ID, type, source, destination and amount |
| Bank | Customer, account and transaction vectors; menu operations |

One customer can own multiple accounts. IDs are generated automatically and are not reused during the session. Transaction history is kept in a vector and displayed newest first. History entries are retained internally if an empty account is closed. All data is cleared when the program exits; persistence is not part of this version.

## Example demonstration

Follow the prompts in this order:

1. Choose 1, enter `Ali`. Customer ID is 1.
2. Choose 1, enter `Sara`. Customer ID is 2.
3. Choose 2, enter customer ID `1`. Account ID is 1001.
4. Choose 2, enter customer ID `2`. Account ID is 1002.
5. Choose 3, enter account `1001`, then amount `1000.50`.
6. Choose 4, enter account `1001`, then amount `100`.
7. Choose 5, enter source `1001`, destination `1002`, amount `200.25`.
8. Choose 6 and enter `1001`: balance is PKR 700.25.
9. Choose 6 and enter `1002`: balance is PKR 200.25.
10. Choose 7 and enter either account ID to see its related transactions.
11. Choose 0 to exit.

A transfer creates one shared transaction record that is visible in both accounts' histories. Deposits use source ID 0; withdrawals use destination ID 0. ID 0 means external cash, not a customer account.

## Code explained simply

`Bank` groups the account operations. `findAccount()` and `findCustomer()` search the vectors by ID. `readInt()` validates menu choices and IDs. `readMoney()` converts decimal text into whole paisa: PKR 10.25 becomes 1025. Using integer money avoids decimal floating-point rounding errors.

`changeBalance()` handles both deposits and withdrawals. `transfer()` verifies both accounts, sufficient funds and the destination limit before changing either balance. `showHistory()` scans backwards and stops after ten matching records. `closeAccount()` only removes accounts with zero balance.

## Input rules and scope

- Names must contain a non-whitespace character.
- Amounts must be positive with at most two decimal places. Use `1000.50`, without commas or a currency label.
- Each transaction and each account balance is capped at PKR 1,000,000,000.00.
- Rejects unknown accounts/customers, self-transfers, insufficient funds, excessive balances and closing a funded account.
- This is a local practice program without authentication, interest, fees, database persistence or real banking integration. Do not enter real financial data.

## Run

```sh
g++ -std=c++11 main.cpp -o banking
```

Run `./banking` on Linux/macOS or `banking.exe` on Windows. See the package README for Visual Studio steps.

## Video outline

Introduce the three required classes. Demonstrate two customers and accounts, then deposit, withdraw and transfer. Show both balances and histories. Finally, attempt an excessive withdrawal and explain why validation prevents it.
