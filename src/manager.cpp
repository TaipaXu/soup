/*
 * This file is part of the soup (https://github.com/TaipaXu/soup).
 * Copyright (c) 2022 Taipa Xu.
 *
 * Soup is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Soup is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with soup. If not, see <http://www.gnu.org/licenses/>.
 */

#include "./manager.hpp"
#include <iostream>
#include <boost/program_options.hpp>
#include "persistence/account.hpp"

Manager::Manager()
    : accountPersistence{Persistence::Account::getInstance()}
{
}

void Manager::showAccounts() const
{
    std::vector<Model::Account> accounts = accountPersistence->getAccounts();
    if (accounts.empty())
    {
        std::cout << "No account found" << std::endl;
    }
    else
    {
        std::cout << "Accounts:" << std::endl;
        for (auto &&account : accounts)
        {
            std::cout << "  " << account.getName() << ": " << account.getUser() << "@" << account.getHost() << ":" << account.getPort() << std::endl;
        }
    }
}

void Manager::useAccount(const bpo::variables_map &variablesMap) const
{
    std::vector<std::string> accounts = getInputAccounts(variablesMap);
    const std::string name = accounts.at(0);
    Model::Account account = accountPersistence->getAccount(name);
    const std::string user = account.getUser();
    const std::string host = account.getHost();
    const int port = account.getPort();
    const std::string password = account.getPassword();

    std::cout << "Please input the password: " << password << std::endl;
    const std::string command = "ssh -p " + std::to_string(port) + " " + user + "@" + host;
    system(command.c_str());
}

void Manager::addAccount(const bpo::variables_map &variablesMap) const
{
    std::vector<std::string> accounts = getInputAccounts(variablesMap);
    const std::string name = accounts.at(0);
    const std::string user = variablesMap["user"].as<std::string>();
    const std::string host = variablesMap["host"].as<std::string>();
    int port = variablesMap["port"].as<int>();
    const std::string password = variablesMap["pass"].as<std::string>();

    Model::Account account(name, user, host, port, password);
    accountPersistence->addAccount(account);
    std::cout << name << " added" << std::endl;
}

void Manager::updateAccount(const bpo::variables_map &variablesMap) const
{
    std::vector<std::string> accounts = getInputAccounts(variablesMap);
    const std::string name = accounts.at(0);

    Model::Account account = accountPersistence->getAccount(name);
    if (variablesMap.count("user"))
    {
        account.setUser(variablesMap["user"].as<std::string>());
    }
    if (variablesMap.count("host"))
    {
        account.setHost(variablesMap["host"].as<std::string>());
    }
    if (variablesMap.count("port"))
    {
        account.setPort(variablesMap["port"].as<int>());
    }
    if (variablesMap.count("pass"))
    {
        account.setPassword(variablesMap["pass"].as<std::string>());
    }
    accountPersistence->updateAccount(account);
    std::cout << name << " updated" << std::endl;
}

void Manager::removeAccount(const bpo::variables_map &variablesMap) const
{
    std::vector<std::string> accounts = getInputAccounts(variablesMap);
    const std::string name = accounts.at(0);

    accountPersistence->removeAccount(name);
    std::cout << name << " removed" << std::endl;
}

std::vector<std::string> Manager::getInputAccounts(const bpo::variables_map &variablesMap) const
{
    std::vector<std::string> accounts = variablesMap["accounts"].as<std::vector<std::string>>();
    return accounts;
}
