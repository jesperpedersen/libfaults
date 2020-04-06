# libfaults configuration

The configuration is loaded from either `$HOME/libfaults.conf` or `/tmp/libfaults.conf`.
You can also specify the path to the configuration using the `LIBFAULTS_CONFIGURATION`
environment variable.

The configuration of `libfaults` is split into sections using the `[` and `]` characters.

The main section, called `[libfaults]`, is where you configure the overall properties
of the library.

All properties are in the format `key = value`.

The characters `#` and `;` can be used for comments; must be the first character on the line.
The `Bool` data type supports the following values: `on`, `1`, `true`, `off`, `0` and `false`.

## [libfaults]

| Property | Default | Unit | Required | Description |
|----------|---------|------|----------|-------------|
| log_type | console | String | No | The logging type (console, file, syslog) |
| log_level | info | String | No | The logging level (fatal, error, warn, info, debug1, ..., debug5) |
| log_path | libfaults.log | String | No | The log file location |

## System call section

| Property | Default | Unit | Required | Description |
|----------|---------|------|----------|-------------|
| enable | | Bool | Yes | Is the rule enabled for the system call |
| return_value | | Int | Yes | The return value of the call |
| error_code | | String | Yes | The error code |
| percentage | | Int | No | The percentage of calls that should fail |

The following system calls are supported

* accept
* socket
* bind
* listen
* connect
* setsockopt
* read
* write

The following error codes are supported

* E2BIG
* EACCES
* EADDRINUSE
* EADDRNOTAVAIL
* EADV
* EAFNOSUPPORT
* EAGAIN
* EALREADY
* EBADE
* EBADF
* EBADFD
* EBADMSG
* EBADR
* EBADRQC
* EBADSLT
* EBFONT
* EBUSY
* ECHILD
* ECHRNG
* ECOMM
* ECONNABORTED
* ECONNREFUSED
* ECONNRESET
* EDEADLK
* EDEADLOCK
* EDESTADDRREQ
* EDOM
* EDOTDOT
* EDQUOT
* EEXIST
* EFAULT
* EFBIG
* EHOSTDOWN
* EHOSTUNREACH
* EIDRM
* EILSEQ
* EINPROGRESS
* EINTR
* EINVAL
* EIO
* EISCONN
* EISDIR
* EISNAM
* EL2HLT
* EL2NSYNC
* EL3HLT
* EL3RST
* ELIBACC
* ELIBBAD
* ELIBEXEC
* ELIBMAX
* ELIBSCN
* ELNRNG
* ELOOP
* EMEDIUMTYPE
* EMFILE
* EMLINK
* EMSGSIZE
* EMULTIHOP
* ENAMETOOLONG
* ENAVAIL
* ENETDOWN
* ENETRESET
* ENETUNREACH
* ENFILE
* ENOANO
* ENOBUFS
* ENOCSI
* ENODATA
* ENODEV
* ENOENT
* ENOEXEC
* ENOLCK
* ENOLINK
* ENOMEDIUM
* ENOMEM
* ENOMSG
* ENONET
* ENOPKG
* ENOPROTOOPT
* ENOSPC
* ENOSR
* ENOSTR
* ENOSYS
* ENOTBLK
* ENOTCONN
* ENOTDIR
* ENOTEMPTY
* ENOTNAM
* ENOTSOCK
* ENOTTY
* ENOTUNIQ
* ENXIO
* EOPNOTSUPP
* EOVERFLOW
* EPERM
* EPFNOSUPPORT
* EPIPE
* EPROTO
* EPROTONOSUPPORT
* EPROTOTYPE
* ERANGE
* EREMCHG
* EREMOTE
* EREMOTEIO
* ERESTART
* EROFS
* ESHUTDOWN
* ESOCKTNOSUPPORT
* ESPIPE
* ESRCH
* ESRMNT
* ESTALE
* ESTRPIPE
* ETIME
* ETIMEDOUT
* ETOOMANYREFS
* ETXTBSY
* EUCLEAN
* EUNATCH
* EUSERS
* EWOULDBLOCK
* EXDEV
* EXFULL
