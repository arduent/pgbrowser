# pgBrowser

This is a Qt c++ Desktop application that allows the user to browse postgresql databases / tables. It's intended as a quicky tool for research.

On FreeBSD the driver is installed by the port. (or pkg). Check the Qt documentation for more information about how to install the SQLite driver on your system. proxyweb was developed on a FreeBSD system and should run without modification on FreeBSD and other BSD systems, and GNU/Linux, Mac and MS Windows.

## Screenshots

![pgBrowser](https://raw.githubusercontent.com/arduent/pgbrowser/main/pgBrowser.png)

## Build It

To build you will need the Qt development packages installed on your system (using qmake). 

Use make distclean just in case there's some system-specific files left in the source distribution. It will likely cause an error if no extraneous files are present. This error/warning is expected and can be safely ignored.

```
# make distclean
# qmake
# make
# ./pgsqlbrowser
```


## Questions?

contact: Waitman Gobble waitman@waitman.net 

