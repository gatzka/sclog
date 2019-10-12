
#ifndef SCLOG_EXPORT_H
#define SCLOG_EXPORT_H

#ifdef SCLOG_STATIC_DEFINE
#  define SCLOG_EXPORT
#  define SCLOG_NO_EXPORT
#else
#  ifndef SCLOG_EXPORT
#    ifdef sclog_EXPORTS
        /* We are building this library */
#      define SCLOG_EXPORT 
#    else
        /* We are using this library */
#      define SCLOG_EXPORT 
#    endif
#  endif

#  ifndef SCLOG_NO_EXPORT
#    define SCLOG_NO_EXPORT 
#  endif
#endif

#ifndef SCLOG_DEPRECATED
#  define SCLOG_DEPRECATED __declspec(deprecated)
#endif

#ifndef SCLOG_DEPRECATED_EXPORT
#  define SCLOG_DEPRECATED_EXPORT SCLOG_EXPORT SCLOG_DEPRECATED
#endif

#ifndef SCLOG_DEPRECATED_NO_EXPORT
#  define SCLOG_DEPRECATED_NO_EXPORT SCLOG_NO_EXPORT SCLOG_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SCLOG_NO_DEPRECATED
#    define SCLOG_NO_DEPRECATED
#  endif
#endif

#endif /* SCLOG_EXPORT_H */
