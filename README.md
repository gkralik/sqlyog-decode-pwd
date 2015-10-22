# sqlyog-decode-pwd

## Description

This little tool decodes passwords saved in SQLYog's connection store.

The connection store is usually saved in `USERDIR\Application Data\SQLyog\sqlyog.ini`. A connection entry might look like this (only relevant parts shown):

```ini
[Connection 1]
Name=Test Connection
Host=localhost
User=username
StorePassword=1
Password=OLC5ubu3OTI=
Port=3306
Database=
[...]
```

The encoded password is saved with the `Password` key.

## Usage
To decode the encoded password, copy the encoded string (`OLC5ubu3OTI=` from above) and pass it as the first argument to the tool:

```sh
$ ./sqlyog-decode-pwd OLC5ubu3OTI=
password
```

## Build

Simply use the provided `Makefile` to build the tool:

```sh
$ make
```
