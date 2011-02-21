#include "SocketException.h" 

SocketException::SocketException(int error,int retValue, string fname)
{
    _errorNumber = error;
    _functionName = fname;
    _functionRetValue = retValue;
}

int SocketException::getError()
{
    return _errorNumber;
}

int SocketException::getReturnValue()
{
    return _functionRetValue;
}

string SocketException::getFunctionName()
{
    return _functionName;
}

void SocketException::printErrorMessage()
{
    cout << "Erro: " << getError() << " - Valor retornado pela função: " <<
        getReturnValue() << ". Função: " + getFunctionName() << "."<< endl;
}
