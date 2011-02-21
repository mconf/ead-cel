#include <CommonLeaks.h>
#include "NetHeaderAttr.h"
#include <cmath>
#include <CommonLeaksCpp.h>

NetHeaderAttr::NetHeaderAttr(unsigned int size, int pointer)
{
    _pair = make_pair(size, pointer);
}

NetHeaderAttr::~NetHeaderAttr()
{
}

void NetHeaderAttr::setSize(unsigned int value)
{
    _pair.first = value;
}

void NetHeaderAttr::setPointer(int value)
{
    _pair.second = value;
}

unsigned int NetHeaderAttr::getSize()
{
    return _pair.first;
}

int NetHeaderAttr::getPointer()
{
    return _pair.second;
}
/*
void NetHeaderAttr::copyData(unsigned char * data)
{
    if (_pair.second) {
        memcpy(_pair.second, data, _pair.first);
    }
}*/

void NetHeaderAttr::setData(unsigned char * buffer, uint32_t data)
{
    int start, byte, offset;
    uint32_t actual, newdata;
    if (buffer) {
        clearData(buffer);

        start = (int)floor(_pair.second / 32.0);
        byte = start * 4; // byte inicial

        if (_pair.first == 32) {
            uint32_t * pt = (uint32_t *)(buffer + byte);
            *pt = data;
            //memcpy(buffer + byte, &data, 4);

        } else {
            // guarda valor atual que está no buffer
            memcpy(&actual, buffer + byte, 4);

            // desloca os bits pra posição em que serão setados dentro do uint32
            newdata = data;
            offset = _pair.second - (start * 32); // bits de deslocamento dentro do uint32
            newdata = (newdata << (32 - _pair.first - offset));

            // seta novos dados no buffer
            actual = actual | newdata; 
            memcpy(buffer + byte, &actual, 4);
        }
    }
}

void NetHeaderAttr::clearData(unsigned char * buffer)
{
    int start, byte, offset;
    uint32_t actual, zeromask;
    if (buffer) {
        start = (int)floor(_pair.second / 32.0);
        byte = start * 4; // byte inicial

        if (_pair.first == 32) {
            memset(buffer + byte, 0, 4);
        } else {
            // gera máscara para setar apenas os bits desse atributo
            zeromask = (uint32_t)((1 << _pair.first) - 1);
            offset = _pair.second - (start * 32); // bits de deslocamento dentro do uint32
            zeromask = ~(zeromask << (32 - _pair.first - offset));

            // zera bits e seta no buffer
            memcpy(&actual, buffer + byte, 4);
            actual = actual & zeromask;
            memcpy(buffer + byte, &actual, 4);
        }
    }
}

uint32_t NetHeaderAttr::getData(unsigned char * buffer)
{
    uint32_t ret = 0;
    int start, byte, offset;
    uint32_t actual, mask;
    if (buffer) {
        start = (int)floor(_pair.second / 32.0);
        byte = start * 4; // byte inicial

        // guarda valor atual que está no buffer
        memcpy(&actual, buffer + byte, 4);

        if (_pair.first == 32) {
            ret = actual;
        } else {
            // gera máscara para buscar apenas os bits desse atributo
            mask = (uint32_t)((1 << _pair.first) - 1);
            offset = _pair.second - (start * 32); // bits de deslocamento dentro do uint32
            mask = (mask << (32 - _pair.first - offset));

            // desloca os bits pra posição correta no uint32 de retorno
            actual = actual & mask;
            ret = (actual >> (32 - _pair.first - offset));
        }
    }
    return ret;
}

