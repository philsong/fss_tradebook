# Trade Book

Trade Book is a simple book of records system for commodity futures trades.

## Dependencies

+ **PostgreSQL** - Database System  
  Install from a package manager in UNIX-like operating systems or from [the official download page](http://www.postgresql.org/download/)
+ **libpqxx** - Database client library for C++  
  Available in package manager or [here](http://pqxx.org/download/software/libpqxx/)
+ **Qt 4** or higher version
+ **Doxygen**  
  For documentation generation. Available in package manager or [here](http://www.stack.nl/~dimitri/doxygen/download.html)

## Building

The application is built by running these commands from the root directory of this project:
```sh
qmake
make
```

## Running

The application is run with this command:
```sh
./tradebook
```
