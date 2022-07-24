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

#pragma once

#include <string>
#include <boost/program_options.hpp>
#include "models/account.hpp"

namespace bpo = boost::program_options;

namespace Persistence
{
    class Account;
} // namespace Persistence

class Manager
{
public:
    Manager();
    ~Manager() = default;

    void showAccounts() const;
    void useAccount(const bpo::variables_map &variablesMap) const;
    void addAccount(const bpo::variables_map &variablesMap) const;
    void updateAccount(const bpo::variables_map &variablesMap) const;
    void removeAccount(const bpo::variables_map &variablesMap) const;

private:
    std::vector<std::string> getInputAccounts(const bpo::variables_map &variablesMap) const;

private:
    Persistence::Account *accountPersistence;
};
