#ifndef MYCACHE_H
#define MYCACHE_H

#include <cstddef>
#include <sys/types.h>

class MyCache
{
    public:
        using size_t = std::size_t;

        MyCache();
        virtual ~MyCache();

        // 初始化缓存区，要求显示调用。
        void init(const size_t mSize);
        void deinit();

        //参数设置：(pBuf, cnt: 需要写入的数据的首地址，以及字节数)
        //函数返回值为成功写入字节数，失败情况下返回-1;
        ssize_t write(const void *pBuf, size_t cnt);

        // 参数设置：(pBuf, cnt: 从缓存中读取数据后存放的数据区首地址，
        //                       及要求获取的字节数，若缓存区中有效数据小于要求的字节数，
        //                       则只返回缓存区的有效数据大小)
        //函数返回值为成功读取的字节数，读取失败返回-1；
        ssize_t read(void *pBuf, size_t cnt);

    private:
        //处理读操作
        ssize_t processRead(char *pChar, size_t cnt);

    private:
        char *pBuffer;       //缓存区首地址
        size_t bufSize;      //缓存区大小
        size_t pos;          //缓存区有效数据区首位置
        size_t mCount;       //缓存区当前存储字节数
};

#endif // MYCACHE_H
