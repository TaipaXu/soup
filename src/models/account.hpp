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

namespace Model
{
    class Account
    {
    public:
        Account(const std::string &name, const std::string &user, const std::string &host, unsigned int port, const std::string &password);
        ~Account() = default;

        const std::string &getName() const;
        void setName(const std::string &name);
        const std::string &getUser() const;
        void setUser(const std::string &user);
        const std::string &getHost() const;
        void setHost(const std::string &host);
        unsigned int getPort() const;
        void setPort(unsigned int port);
        const std::string &getPassword() const;
        void setPassword(const std::string &password);

    private:
        std::string name;
        std::string user;
        std::string host;
        unsigned int port;
        std::string password;
    };
} // namespace Model
