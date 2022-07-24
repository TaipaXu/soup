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

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "config.hpp"
#include "models/account.hpp"
#include "persistence/account.hpp"
#include "manager.hpp"

#define CREATE_MANAGER Manager *manager = new Manager();
#define CLEAR_MANAGER delete manager;

int main(int argc, char const *argv[])
{
    const std::string description = "soup " + PROJECT_VERSION + " " + PROJECT_DOMAIN;
    const std::string usage = R"(Usage:
  soup -h
    Show the help messages

  soup -v
    show the version

  soup ls
    List all accounts

  soup use <account>
    Use an account

  soup add <account> -u <user> -h <host> -p pass --pw <passwork>
    Add an account

  soup update <account> [-u <user>] [-h <host>] [-p pass] [-pw <passwork>]
    Update an account

  soup rm <account>
    Remove an account)";

    bpo::positional_options_description positionalOptionsDescription;
    positionalOptionsDescription.add("command", 1).add("accounts", -1);

    bpo::options_description optionsDescription("Options");
    bpo::variables_map variablesMap;

    optionsDescription.add_options()("help", "print this help message")("version,v", "print Soup version")("command,c", bpo::value<std::string>()->required(), "add, rm, ls, update, import, export")("accounts", bpo::value<std::vector<std::string>>(), "accounts")("user,u", bpo::value<std::string>(), "set user")("host,h", bpo::value<std::string>(), "set host")("port,p", bpo::value<int>(), "set port")("pass,pw", bpo::value<std::string>(), "set password");

    try
    {
        bpo::store(
            bpo::command_line_parser(argc, argv)
                .options(optionsDescription)
                .positional(positionalOptionsDescription)
                .run(),
            variablesMap);
    }
    catch (...)
    {
        std::cout << "bad option" << std::endl;
        return EXIT_SUCCESS;
    }

    if (variablesMap.empty() || variablesMap.count("help"))
    {
        std::cout << "SOUP " << PROJECT_VERSION << " " << PROJECT_DOMAIN << std::endl
                  << std::endl
                  << usage << std::endl;
    }
    else if (variablesMap.count("version"))
    {
        std::cout << "version: " << PROJECT_VERSION << std::endl;
    }
    else if (variablesMap.count("command"))
    {
        const std::string command = variablesMap["command"].as<std::string>();

        if (variablesMap["command"].as<std::string>() == "ls")
        {
            CREATE_MANAGER
            manager->showAccounts();
            CLEAR_MANAGER
        }
        else if (variablesMap["command"].as<std::string>() == "use")
        {
            CREATE_MANAGER
            manager->useAccount(variablesMap);
            CLEAR_MANAGER
        }
        else if (variablesMap["command"].as<std::string>() == "add")
        {
            CREATE_MANAGER
            manager->addAccount(variablesMap);
            CLEAR_MANAGER
        }
        else if (variablesMap["command"].as<std::string>() == "update")
        {
            CREATE_MANAGER
            manager->updateAccount(variablesMap);
            CLEAR_MANAGER
        }
        else if (variablesMap["command"].as<std::string>() == "rm")
        {
            CREATE_MANAGER
            manager->removeAccount(variablesMap);
            CLEAR_MANAGER
        }
        else
        {
            std::cout << "bad option" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
