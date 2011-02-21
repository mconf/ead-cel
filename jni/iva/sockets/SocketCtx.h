#ifndef _SOCKET_CTX_H_
#define _SOCKET_CTX_H_

#include <errorDefs.h>
#include <ErrorData.h>
#include "SocketWrapper.h"

class SocketCtx
{
private:
    static int _lastError;
    static bool _started;

    /** \brief Inicializa o uso de sockets no sistema
     *  \return E_OK em caso de sucesso ou E_SOCKET_STARTUP em caso de erro.
     *          Se aconteceu erro, guarda internamente o erro específico, que deve
     *          ser acessado pela função 'lastError()'.
     */
    static int startup()
    {

    	if (!_started) {
            if (SocketWrapper::_startup() != 0) {
                _lastError = SocketWrapper::_getlasterror();
                NEW_ERROR(E_SOCKET_STARTUP, SocketWrapper::_errorMessage(_lastError));
                return E_SOCKET_STARTUP;
            }
            _started = true;
        }
        return E_OK;
    };

    /** \brief Finaliza o uso de sockets no sistema
     *  \return E_OK em caso de sucesso ou E_SOCKET_CLEANUP em caso de erro.
     *          Se aconteceu erro, guarda internamente o erro específico, que deve
     *          ser acessado pela função 'lastError()'.
     */
    static int cleanup()
    {
        if (_started) {
            if (SocketWrapper::_cleanup() != 0) {
                _lastError = SocketWrapper::_getlasterror();
                NEW_ERROR(E_SOCKET_CLEANUP, SocketWrapper::_errorMessage(_lastError));
                return E_SOCKET_CLEANUP;
            }
            _started = false;
        }
        return E_OK;
    };

public:

    static int lastError()
    {
        return _lastError;
    }

    static SOCKET createSocket(int family, int type, int protocol)
    {
        int result = startup();
        if (result != E_OK)
            return INVALID_SOCKET;

        SOCKET so = SocketWrapper::_open(family, type, protocol);
        if (so != INVALID_SOCKET) {
            // \todo contador de sockets pra saber quando dar cleanup!
        }
        return so;
    }

    static int closeSocket(SOCKET so)
    {
        int result = 0;
        if (so != INVALID_SOCKET)
            result = SocketWrapper::_close(so);
        if (result != 0)
            return result;
        return E_OK;
    }

};

#endif
