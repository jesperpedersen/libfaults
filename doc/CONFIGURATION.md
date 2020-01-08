# libfaults configuration

The configuration is loaded from either `$HOME/libfaults.conf` or `/tmp/libfaults.conf`.

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

* EPERM
* ENOENT
* ESRCH
* EINTR
* EIO
* ENXIO
* E2BIG
* ENOEXEC
* EBADF
* ECHILD
* EAGAIN
* ENOMEM
* EACCES
* EFAULT
* ENOTBLK
* EBUSY
* EEXIST
* EXDEV
* ENODEV
* ENOTDIR
* EISDIR
* EINVAL
* ENFILE
* EMFILE
* ENOTTY
* ETXTBSY
* EFBIG
* ENOSPC
* ESPIPE
* EROFS
* EMLINK
* EPIPE
* EDOM
* ERANGE
* EDEADLK
* ENAMETOOLONG
* ENOLCK
* ENOSYS
* ENOTEMPTY
* ELOOP
* EWOULDBLOCK
* ENOMSG
* EIDRM
* ECHRNG
* EL2NSYNC
* EL3HLT
* EL3RST
* ELNRNG
* EUNATCH
* ENOCSI
* EL2HLT
* EBADE
* EBADR
* EXFULL
* ENOANO
* EBADRQC
* EBADSLT
* EDEADLOCK
* EBFONT
* ENOSTR
* ENODATA
* ETIME
* ENOSR
* ENONET
* ENOPKG
* EREMOTE
* ENOLINK
* EADV
* ESRMNT
* ECOMM
* EPROTO
* EMULTIHOP
* EDOTDOT
* EBADMSG
* EOVERFLOW
* ENOTUNIQ
* EBADFD
* EREMCHG
* ELIBACC
* ELIBBAD
* ELIBSCN
* ELIBMAX
* ELIBEXEC
* EILSEQ
* ERESTART
* ESTRPIPE
* EUSERS
* ENOTSOCK
* EDESTADDRREQ
* EMSGSIZE
* EPROTOTYPE
* ENOPROTOOPT
* EPROTONOSUPPORT
* ESOCKTNOSUPPORT
* EOPNOTSUPP
* EPFNOSUPPORT
* EAFNOSUPPORT
* EADDRINUSE
* EADDRNOTAVAIL
* ENETDOWN
* ENETUNREACH
* ENETRESET
* ECONNABORTED
* ECONNRESET
* ENOBUFS
* EISCONN
* ENOTCONN
* ESHUTDOWN
* ETOOMANYREFS
* ETIMEDOUT
* ECONNREFUSED
* EHOSTDOWN
* EHOSTUNREACH
* EALREADY
* EINPROGRESS
* ESTALE
* EUCLEAN
* ENOTNAM
* ENAVAIL
* EISNAM
* EREMOTEIO
* EDQUOT
* ENOMEDIUM
* EMEDIUMTYPE
