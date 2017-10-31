/*************************************************************************
	> File Name: demo.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Tue 31 Oct 2017 09:36:50 AM CST
 ************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");

int major = 500;
int minor = 0;

dev_t devno;
int count = 1;

struct cdev cdev;

int counter = 0;
char kbuf[1024] = {};

int demo_open(struct inode* inodep, struct file* filep)
{
    printk("%s,%d\n",__func__,__LINE__);

    return 0;
}

int demo_release(struct inode* inodep,struct file*filep)
{
    printk("%s,%d\n",__func__,__LINE__);

    return 0;
}

int mycopy(char* to, char*from, int n)
{
    if(n <= 0)
    {
        return -1;
    }
    while(n--)
        *to++ = *from++;

    return 0;
}

ssize_t demo_read(struct file*filep, char __user *buf, size_t size,loff_t*offlen)
{
    if(size < 0)
    {
        return -EINVAL;
    }
#if 0
    //原始的写法，比较繁琐，下面是简化的写法
    if(size > counter)
    {
        size = counter;

        if( copy_to_user(buf,kbuf,size) !=0 )
        {
            printk("failed to copy_to_user.\n");
            return -1;
        }
    }
    if(size < counter)
    {
        if(copy_to_user(buf,kbuf,size)!=0)
        {
            printk("Failed to copy_to_user.\n");
            return -1;
        }
        mycopy(kbuf,kbuf+size, counter-size);
    }
#endif
    if(size > counter)
    {
        size = counter;
    }
    if(copy_to_user(buf,kbuf,size) != 0)
    {
        printk("Failed to copy_to_user.\n");
        return -1;
    }
    mycopy(kbuf,kbuf+size,counter-size);

    counter -= size;
    
    return size;
}
ssize_t demo_write(struct file*filep, const char __user* buf,size_t size,loff_t* offlen)
{
    if(size < 0)
    {
        return -EINVAL;
    }
    if(size > 1024 - counter)
    {
        return -ENOMEM;
    }
    if(copy_from_user(kbuf+counter,buf,size)!=0)
    {
        printk("Failed to copy_from_user.\n");
        return -1;
    }
    printk("kbuf:%s\n",kbuf);
    counter += size;

    return size;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = demo_open,
    .release = demo_release,
    .read = demo_read,
    .write = demo_write,
};

static int __init demo_init(void)
{
    int ret = 0;
    
    printk("%s,%d\n",__func__,__LINE__);

    devno = MKDEV(major,minor);
//生成设备号
    ret = register_chrdev_region(devno,count,"demo");
//注册设备号
    if(ret)
    {
       printk("Failed register_chrdev_region.\n") ;

        return ret;
    }
//初始化字符设备
    cdev_init(&cdev,&fops);

//向内核注册一个cdev设备
    ret = cdev_add(&cdev,devno,count);
    if(ret)
    {
        unregister_chrdev_region(devno,count);
        return ret;
    }

    return 0;
}
static void __exit demo_exit(void)
{
    printk("%s,%d\n",__func__,__LINE__);
    cdev_del(&cdev);
    unregister_chrdev_region(devno,count);
}
module_init(demo_init);
module_exit(demo_exit);
