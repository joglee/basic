/*************************************************************************
	> File Name: demo.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Mon 30 Oct 2017 11:32:30 AM CST
 ************************************************************************/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<asm/uaccess.h>

MODULE_LICENSE("GPL");


int major = 500;
int minor = 0;

dev_t devno;
int count = 1;

struct cdev cdev;

int counter = 0;
char kbuf[1024] = {};

//硬件初始化
int demo_open (struct inode* inodep, struct file* filep)
{
    printk("%s,%d\n",__func__,__LINE__);

    return 0;
}

int demo_release(struct inode* inodep, struct file* filep)
{
    printk("%s,%d\n",__func__,__LINE__);

    return 0;
}
//read (fd,buf,N) ---->sys_read() --->demo_read();
ssize_t demo_read(struct file*filep,char __user *buf, size_t size,loff_t *offlen)
{
    if(size < 0)
    {
        return -EINVAL;
    }
    if(size > counter)
    {
        size = counter;
    }
    if(copy_to_user(buf, kbuf, size) != 0)
    {
        printk("Failed to copy_to_user.\n");
        return -1;
    }
    counter = 0;
    return size;
}

//write(fd,buf,N)
ssize_t demo_write(struct file* filep,const char __user* buf,size_t size, loff_t* offlen)
{
    if(size < 0)
    {
        return -EINVAL;
    }
    if(size > 1024)
    {
        return -ENOMEM;
    }
    if(copy_from_user(kbuf,buf,size) !=0 )
    {
        printk("Failed to copy_from_user.\n");

        return -1;
    }
    printk("kbuf:%s\n",kbuf);
    counter = size;

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
//1.生成设备号
    devno = MKDEV(major,minor);
//2.注册设备号
    ret = register_chrdev_region(devno,count,"demo");

    if(ret)
    {
        printk("Failed register_chrdev_region.\n");

        return ret;
    }
//3.初始化字符设备
    cdev_init(&cdev,&fops);
//4.向内核注册一个cdev设备
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
