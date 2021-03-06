
#include <stdio.h>
#include <wintf/wcrt.h>

#if _MSC_VER < 1900
struct _iobuf {
    char *_ptr;
    int   _cnt;
    char *_base;
    int   _flag;
    int   _file;
    int   _charbuf;
    int   _bufsiz;
    char *_tmpfname;
};

QUARK_LINKAGE FILE * __iob_func(void);

QKCAPI FILE *  __qkc_iob_func__(unsigned idx)
{
    return &__qkc_iob_func__()[idx];
}
#endif

char *tmpnam_r (char *s)
{
    return tmpnam_s(s) ;
}

int fcloseall (void)
{
    return _fcloseall() ;
}

FILE *fdopen (int fd , const char *modes)
{
    return _fdopen(fd , modes) ;
}

int getw (FILE *stream)
{
    return _getw(stream) ;
}

int putw (int w , FILE *stream)
{
    return _putw(w , stream) ;
}

int fseeko (FILE *stream , off_t off , int whence)
{
    return _fseeki64(stream , off , whence) ;
}

off_t ftello (FILE *stream)
{
    return _ftelli64(stream) ;
}


void flockfile (FILE *stream)
{
    _lock_file(stream) ;
}

void funlockfile (FILE *stream)
{
    _unlock_file(stream) ;
}

#if _MSC_VER < 1912
int snprintf (char * s , size_t maxlen , const char * format , ...)
{
    va_list arg ;
    int done = 0 ;

    va_start(arg , format) ;
    done = _vsnprintf(s , maxlen , format , arg) ;
    va_end(arg) ;
    return done ;
}
#endif
