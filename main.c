#include "md5.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



#define READ_DATA_SIZE	1024
#define MD5_SIZE		16
#define MD5_STR_LEN		(MD5_SIZE * 2)

int Compute_file_md5(const char *file_path, char *value);

int main(int argc, char *argv[])
{
    struct MD5Context context;
    unsigned char checksum[16];
    int i;
    unsigned int ret, fd;
    unsigned char data[READ_DATA_SIZE]={0};

    char *file_path = "../test.txt";
    fd = open(file_path, O_RDONLY);
    if (-1 == fd)
    {
        perror("open");
        return -1;
    }
    MD5Init (&context);
    while (1)
    {
        ret = read(fd, data, READ_DATA_SIZE);
//        printf("ret:%d\n", ret);
//        printf("data:%s\r\n",data);
        if (-1 == ret)
        {
            perror("read");
            return -1;
        }
        // 对大小为ret的data进行处理，获得标准block大小
        MD5Update(&context, data, ret);
        if (0 == ret || ret < READ_DATA_SIZE)
        {
            break;
        }
    }
    close(fd);
    MD5Final (checksum, &context);
    for (i = 0; i < 16; i++)
    {
        printf ("%02x", (unsigned int) checksum[i]);
    }
    printf ("\n");

//    char *raw_str = "zouyuchi123";
//    MD5Init (&context);
//    MD5Update (&context, raw_str, strlen (raw_str));
//    MD5Final (checksum, &context);
//    for (i = 0; i < 16; i++)
//    {
//        printf ("%02x", (unsigned int) checksum[i]);
//    }
//    printf ("\n");
    return 0;
}

/*
 *
 */
int Compute_file_md5(const char *file_path, char *md5_str)
{
    int i;
    int fd;
    int ret;
    unsigned char data[READ_DATA_SIZE]={0};
    unsigned char md5_value[MD5_SIZE]={0};
    MD5_CTX md5;
    fd = open(file_path, O_RDONLY);
    if (-1 == fd)
    {
        perror("open");
        return -1;
    }
    // init md5
    MD5Init(&md5);
    while (1)
    {
        ret = read(fd, data, READ_DATA_SIZE);
        printf("ret:%d\n", ret);
        if (-1 == ret)
        {
            perror("read");
            return -1;
        }
        // 对大小为ret的data进行处理，获得标准block大小
        MD5Update(&md5, data, ret);
        if (0 == ret || ret < READ_DATA_SIZE)
        {
            break;
        }
    }
    close(fd);
    MD5Final(&md5, md5_value);
    for(i = 0; i < MD5_SIZE; i++)
    {
        snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
    }
    md5_str[MD5_STR_LEN] = '\0'; // add end
    printf("md5_str:%s\r\n", md5_str);
    return 0;
}
