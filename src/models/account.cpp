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

namespace Model
{
    Account::Account(const std::string &name, const std::string &user, const std::string &host, unsigned int port, const std::string &password)
        : name(name),
          user(user),
          host(host),
          port(port),
          password(password)
    {
    }

    const std::string &Account::getName() const
    {
        return name;
    }

    void Account::setName(const std::string &name)
    {
        this->name = name;
    }

    const std::string &Account::getUser() const
    {
        return user;
    }

    void Account::setUser(const std::string &user)
    {
        this->user = user;
    }

    const std::string &Account::getHost() const
    {
        return host;
    }

    void Account::setHost(const std::string &host)
    {
        this->host = host;
    }

    unsigned int Account::getPort() const
    {
        return port;
    }

    void Account::setPort(unsigned int port)
    {
        this->port = port;
    }

    const std::string &Account::getPassword() const
    {
        return password;
    }

    void Account::setPassword(const std::string &password)
    {
        this->password = password;
    }
} // namespace Model
