# libfaults

`libfaults` is library that can generate a fault injection for system calls.

See [Getting Started](./doc/GETTING_STARTED.md) on how to get started with `libfaults`.

See [Configuration](./doc/CONFIGURATION.md) on how to configure `libfaults`.

Alternative, take a look at [libfiu](https://blitiri.com.ar/p/libfiu/).

## Tested platforms

* [Fedora](https://getfedora.org/) 28+
* [RHEL](https://www.redhat.com/en/technologies/linux-platforms/enterprise-linux) 7.x/8.x

## Compiling the source

`libfaults` requires

* [gcc](https://gcc.gnu.org)
* [cmake](https://cmake.org)
* [make](https://www.gnu.org/software/make/)

```sh
dnf install gcc cmake make
```

Alternative [clang](https://clang.llvm.org/) can be used.

### Release build

The following commands will install `libfaults` in the `/usr/local` hierarchy
and run the default configuration.

```sh
git clone https://github.com/jesperpedersen/libfaults.git
cd libfaults
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
make
sudo make install
LD_PRELOAD=/usr/local/lib/libfaults.so <your_application>
```

### Debug build

The following commands will create a `DEBUG` version of `libfaults`.

```sh
git clone https://github.com/jesperpedersen/libfaults.git
cd libfaults
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
cd src
LD_PRELOAD=libfaults.so <your_application>
```

Remember to set the `log_level` configuration option to `debug5`.

## Contributing

Contributions to `libfaults` are managed on [GitHub.com](https://github.com/jesperpedersen/libfaults/)

* [Ask a question](https://github.com/jesperpedersen/libfaults/issues)
* [Raise an issue](https://github.com/jesperpedersen/libfaults/issues)
* [Feature request](https://github.com/jesperpedersen/libfaults/issues)
* [Code submission](https://github.com/jesperpedersen/libfaults/pulls)

Contributions are most welcome !

## License

[BSD-3-Clause](https://opensource.org/licenses/BSD-3-Clause)
