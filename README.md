# soup

An ssh account manager.

## Usage

List all accounts

```sh
$ soup ls
Accounts:
  localhost: root@127.0.0.1:22
```

Use an account

```sh
$ soup use localhost
Please input the password: 1
localhost@127.0.0.1's password:
```

Add an account

```sh
$ soup add x -u localhost -h 127.0.0.1 -p 22 --pw 123456
localhost added
```

Update an account

```sh
$ soup update localhost --pw 654321
localhost updated
```

Remove an account

```sh
$ soup rm localhost
localhost removed
```

## Building

### Linux & macOS

```sh
$ git clone https://github.com/TaipaXu/soup.git && cd soup
$ mkdir build && cd build
$ cmake ..
$ make
```

## License

[GPL-3.0](LICENSE)
