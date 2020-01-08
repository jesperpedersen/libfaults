# Getting started with libfaults

First of all, make sure that you know where the `libfaults` library is installed.

If you don't have `libfaults` on your system see [README](../README.md) on how to
compile and install `libfaults`.

## Configuration

Lets create a simple configuration file called `libfaults.conf` with the content

```
[libfaults]
log_type = console
log_level = info

[accept]
enable = true
return_value = -1
error_code = EMFILE
```

and save it in your home directory (`$HOME/libfaults.conf`).

In our main section called `[libfaults]` we setup the logging of `libfaults` to
be performed at `info` level and sent to the console.

Next we create a section called `[accept]` which controls the outcome of system calls
to the `accept` function. In this case it will fail, since it has a return value of of
`-1` and it will have the `errno` variable set to `EMFILE` which means that the process
has run out of file descriptors for the process.

We are now ready to use `libfaults`.

See [Configuration](./CONFIGURATION.md) for all configuration options.

## Using `libfaults`

We will use `libfaults` using the command

```
LD_PRELOAD=/usr/local/lib/libfaults.so <your_application>
```

When ever `<your_application>` calls `accept` it will generate the error we specified
above.

This will make it easier to verify that your error paths are correct.

## Closing

The [libfaults](https://github.com/jesperpedersen/libfaults) community hopes that you find
the project interesting.

Feel free to

* [Ask a question](https://github.com/jesperpedersen/libfaults/issues)
* [Raise an issue](https://github.com/jesperpedersen/libfaults/issues)
* [Submit a feature request](https://github.com/jesperpedersen/libfaults/issues)
* [Write a code submission](https://github.com/jesperpedersen/libfaults/pulls)

All contributions are most welcome !
