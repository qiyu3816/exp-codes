### 内存段数据处理函数memcpy和memmove

```c
// memcpy()从源src所指的内存地址的起始位置开始拷贝N个字节到目标dst所指的内存地址的起始位置中

void *memcpy(void *dst, const void *src, size_t count);

// memmove()功能同memcpy基本一致，但是当src区域和dst内存区域重叠时，memcpy可能会出现错误，而memmove能正确进行拷贝

void *memmove(void *dst, const void *src, size_t count);

// 可见memcpy的速度比memmove快一点，如果使用者可以确定内存不会重叠，则可以选用memcpy，否则memmove更安全一些。
```

所谓src和dst内存区域重叠，即：

假设内存是一个连续数轴存储，src是0~10，目的dst是3开始，那么memcpy把0~2复制完后想复制3中的数据，却已被覆盖，引发错误。

**三种情况：**

- 当前src内存区域和dest内存区域完全不重叠
- 当src内存区域和dest内存区域重叠时且dest所在区域在src所在区域前（这种memcpy也能成功的原理：是你已经把你需要复制的都复制过了，所以被覆盖不影响）
- 当src内存区域和dest内存区域重叠时且src所在区域在dest所在区域前（memcpy在这种情况下，会有一部分数据来不及复制，就被覆盖了）

源码实现：

```c
void* MyMemcpy(void* dest, const void* src, size_t num)
{
    char* dest_tmp = (char*) dest;// 目标字符串
    const char* src_tmp = (const char*)src;// 源字符串
    assert(dest&&src);
    while(num--) {
        *dest_tmp++ = *src_tmp++;
    }
    return dest;
}


// 解决内存重叠的问题，就需要加上逆序拷贝，适用于任何类型
void* MyMemmove(void* dest, const void* src, size_t num)
{
    char* dest_tmp = (char*)dest;
    const char* src_tmp = (const char*)src;
    assert(dest && src);
    if (src_tmp > dest_tmp || src_tmp + num <= dest_tmp) // 情况1和情况2
    {
        while(num--) // 正序复制
        {
            *dest_tmp++ = *src_tmp++;
        }
    }
    else    // 情况3，逆序赋值
    {
        // 逆序打印，需要把指针调整位置
        dest_tmp += num-1;
        src_tmp += num-1;
        while (num--) {
            *(dest_tmp--) = *(src_tmp--);
        }    
    }
    return dest;
}

```

