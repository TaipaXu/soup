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

#include <vector>
#include "./persistence.hpp"
#include "models/account.hpp"

namespace Persistence
{
    class Account : public Persistence
    {
    public:
        static Account *getInstance();
        ~Account() = default;

        std::vector<Model::Account> getAccounts() const;
        Model::Account getAccount(const std::string name) const;
        void addAccount(const Model::Account &account);
        void updateAccount(const Model::Account &account);
        void removeAccount(const std::string name);

    private:
        Account();
        Account(const Account &) = delete;
        Account &operator=(const Account &) = delete;

        std::string getAccountsFilePath() const;
        void checkAccountsFileExist() const;
        std::string getAccountsContent() const;
        void saveAccountsContent(const std::string &content) const;

    private:
        std::string accountsFilePath;
    };
} // namespace Persistence
