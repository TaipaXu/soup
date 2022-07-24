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

#include "./account.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <boost/json/src.hpp>

namespace Persistence
{
    namespace fs = std::filesystem;

    Account::Account()
        : Persistence()
    {
        accountsFilePath = getAccountsFilePath();
        checkAccountsFileExist();
    }

    Account *Account::getInstance()
    {
        static Account instance;
        return &instance;
    }

    std::vector<Model::Account> Account::getAccounts() const
    {
        std::vector<Model::Account> accounts;
        std::string content = getAccountsContent();
        boost::json::value json = boost::json::parse(content);
        boost::json::array accountsJson = json.as_array();
        for (auto &accountJson : accountsJson)
        {
            const std::string name = accountJson.at("name").as_string().c_str();
            const std::string user = accountJson.at("user").as_string().c_str();
            const std::string host = accountJson.at("host").as_string().c_str();
            const int port = accountJson.at("port").as_int64();
            const std::string password = accountJson.at("password").as_string().c_str();
            Model::Account account(name, user, host, port, password);
            accounts.push_back(account);
        }
        return accounts;
    }

    Model::Account Account::getAccount(const std::string name) const
    {
        std::vector<Model::Account> accounts;
        std::string content = getAccountsContent();
        boost::json::value json = boost::json::parse(content);
        boost::json::array accountsJson = json.as_array();
        for (auto &accountJson : accountsJson)
        {
            const std::string nameJson = accountJson.at("name").as_string().c_str();
            if (nameJson == name)
            {
                const std::string user = accountJson.at("user").as_string().c_str();
                const std::string host = accountJson.at("host").as_string().c_str();
                const int port = accountJson.at("port").as_int64();
                const std::string password = accountJson.at("password").as_string().c_str();
                Model::Account account(name, user, host, port, password);
                return account;
            }
        }
    }

    void Account::addAccount(const Model::Account &account)
    {
        std::string content = getAccountsContent();
        boost::json::value json = boost::json::parse(content);
        boost::json::array accountsJson = json.as_array();

        boost::json::object accountJsonObject;
        accountJsonObject["name"] = account.getName();
        accountJsonObject["user"] = account.getUser();
        accountJsonObject["host"] = account.getHost();
        accountJsonObject["port"] = account.getPort();
        accountJsonObject["password"] = account.getPassword();
        accountsJson.push_back(accountJsonObject);

        json = accountsJson;
        saveAccountsContent(boost::json::serialize(json));
    }

    void Account::updateAccount(const Model::Account &account)
    {
        std::string content = getAccountsContent();
        boost::json::value json = boost::json::parse(content);
        boost::json::array accountsJson = json.as_array();
        for (size_t i = 0; i < accountsJson.size(); i++)
        {
            boost::json::object accountJson = accountsJson[i].as_object();
            const std::string nameJson = accountJson.at("name").as_string().c_str();
            if (account.getName() == nameJson)
            {
                accountJson["name"] = account.getName();
                accountJson["user"] = account.getUser();
                accountJson["host"] = account.getHost();
                accountJson["port"] = account.getPort();
                accountJson["password"] = account.getPassword();
                accountsJson[i] = accountJson;
                break;
            }
        }
        json = accountsJson;
        saveAccountsContent(boost::json::serialize(json));
    }

    void Account::removeAccount(const std::string name)
    {
        std::string content = getAccountsContent();
        boost::json::value json = boost::json::parse(content);
        boost::json::array accountsJson = json.as_array();
        for (size_t i = 0; i < accountsJson.size(); i++)
        {
            boost::json::object accountJson = accountsJson[i].as_object();
            const std::string nameJson = accountJson.at("name").as_string().c_str();
            if (name == nameJson)
            {
                accountsJson.erase(accountsJson.begin() + i);
                break;
            }
        }
        json = accountsJson;
        saveAccountsContent(boost::json::serialize(json));
    }

    std::string Account::getAccountsFilePath() const
    {
        return dataDirPath + "/accounts.json";
    }

    void Account::checkAccountsFileExist() const
    {
        if (!fs::exists(accountsFilePath))
        {
            std::cout << "not exists" << std::endl;
            fs::create_directories(dataDirPath);
            std::ofstream ofs(accountsFilePath);
            ofs << "[]";
            ofs.close();
        }
        else
        {
        }
    }

    std::string Account::getAccountsContent() const
    {
        std::ifstream ifs(accountsFilePath);
        if (!ifs.is_open())
        {
            std::cout << "Failed to open accounts file" << std::endl;
            return "[]";
        }
        std::stringstream stream;
        stream << ifs.rdbuf();
        ifs.close();
        return stream.str();
    }

    void Account::saveAccountsContent(const std::string &content) const
    {
        std::ofstream ofs(accountsFilePath);
        if (!ofs.is_open())
        {
            std::cout << "Failed to open accounts file" << std::endl;
            return;
        }

        ofs << content;
        ofs.close();
    }
} // namespace Persistence
