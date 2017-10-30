/*************************************************************************
	> File Name: demo.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Mon 30 Oct 2017 10:21:15 AM CST
 ************************************************************************/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");

int major = 500;
int minor = 0;
dev_t devno;
int count = 1;

struct cdev cdev;

int demo_open(struct inode* inodep, struct file* filep)
{
    printk("%s,%d\n",__func__,__LINE__);

    return 0;
}
int demo_release(struct inode* inodep, struct file* filep)
{
    printk("%s,%d\n",__func__,__LINE__);

    return 0;
}
struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = demo_open,
    .release = demo_release,
};

static int __init demo_init(void)
{
    int ret = 0;

    printk("%s,%d\n",__func__,__LINE__);

    //1.生成设备号
    devno = MKDEV(major,minor);

    //2.注册设备号
    ret = register_chrdev_region(devno,count, "demo");

    if(ret < 0){
        printk("Failed register_chrdev_region.\n");

        return ret;
    }

    //3.初始化字符设备
    cdev_init(&cdev,&fops);

    //4.向内核注册一个字符设备
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
