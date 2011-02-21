#ifndef Socket_Exception_Class
#define Socket_Exception_Class

/**
 *  C++ exception specification ignored except to indicate a function is not 
 *  __declspec(nothrow).
 *
 *  Warning serve somente para dizer que o tipo da exceção não é utilizado na
 *  implementação, serve só para indicar o tipo para o programador saber o que
 *  tratar.
 */
#pragma warning( disable : 4290 )

#include <iostream>
#include <string>
using namespace std;

/**  
 *  Classe responsável por carregar as execeções da classe Socket
 */
class SocketException
{
private:
    string _functionName;
    int _errorNumber;
    int _functionRetValue;

public:
    SocketException(int error,int retValue, string fname);
    int getError();
    int getReturnValue();
    string getFunctionName();
    void printErrorMessage();
};

#endif
