#include "MyCache.h"
#include <cstring>

MyCache::MyCache() : pBuffer(nullptr), bufSize(0), pos(0), mCount(0)
{
}

MyCache::~MyCache()
{
    deinit();
}

void MyCache::init(const size_t mSize)
{
    deinit();
    bufSize = mSize;
    pBuffer = new char[bufSize]();
}

void MyCache::deinit()
{
    if (pBuffer != nullptr) {
        delete [] pBuffer;
        pBuffer = nullptr;
    }
}



ssize_t MyCache::read(void *pBuf, size_t cnt)
{
    ssize_t rsize = 0;

    if (cnt <= 0) {
        return 0;
    } else if (mCount == 0) {
        return -1;
    } else if (cnt >= mCount) {
        rsize = processRead((char *)pBuf, mCount);
    } else {
        rsize = processRead((char *)pBuf, cnt);
    }

    return rsize;
}

ssize_t MyCache::write(const void *pBuf, size_t cnt)
{
    if (bufSize - mCount < cnt) {
        return -1;
    }

    const char *pChar = (const char *)pBuf;

    //缓存区中空闲的第一个位置；
    size_t np = (pos + mCount) % bufSize;

    //判断到缓存区尾部的空间是否可容纳下数据
    if (np + cnt <= bufSize) {
        memcpy(pBuffer + np, pChar, cnt);
    } else {
        size_t firsWriteSize = bufSize - np;
        memcpy(pBuffer + np, pChar, firsWriteSize);

        size_t secWriteSize = cnt - firsWriteSize;
        memcpy(pBuffer, pChar + firsWriteSize, secWriteSize);
    }

    mCount += cnt;

    return cnt;
}

ssize_t MyCache::processRead(char *pChar, size_t cnt)
{
    if (cnt > mCount) {
        return -1;
    }

    //要求读取数据区尾部开区间值，作判断用，
    //该值大于bufSize说明有部分数据存放于缓存区首部
    size_t tailPos = pos + cnt;
    if (tailPos <= bufSize) {
        memcpy(pChar, pBuffer + pos, cnt);
        pos += cnt;
        if (pos == bufSize)         //循环使用缓存区
            pos = 0;
    } else {

        //1.读取缓存区尾部数据
        size_t firstReadSize = bufSize - pos;
        memcpy(pChar, pBuffer + pos, firstReadSize);
        pos = 0;

        //2.读取缓存区首部数据。
        size_t secReadSize = cnt - firstReadSize;
        memcpy(pChar + firstReadSize, pBuffer + pos, secReadSize);
        pos += secReadSize;
    }

    mCount -= cnt;

    return (ssize_t)cnt;
}

