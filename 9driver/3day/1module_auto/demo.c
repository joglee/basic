/*************************************************************************
	> File Name: demo.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Tue 31 Oct 2017 03:10:30 PM CST
 ************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

#define DEVNAME "demo"

int major;
int minor = 0;
int count = 1;

dev_t devno;
struct cdev *pdev;
struct class *mclass;
struct device *mdevice;


int demo_open(struct inode* inodep, struct file* filep)
{
    printk("%s,%d\n",__func__,__LINE__);
    return 0;
}

int demo_release(struct inode* inodep,struct file* filep)
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

    //自动创建并且申请注册设备号    
    ret = alloc_chrdev_region(&devno,minor,count,DEVNAME);

    if(ret)
    {
        printk("Failed to alloc_chrdev_region.\n");
        return ret;
    }
    printk("devno:%d,major:%d,minor:%d\n",devno,MAJOR(devno),MINOR(devno));

    //分配一个cdev的结构体
    pdev = cdev_alloc();

    if(pdev == NULL)
    {
        printk("Failed to cdev_alloc.\n");
        goto err1;
    }

    //初始化字符设备
    cdev_init(pdev,&fops);

    ret = cdev_add(pdev,devno,count);
    if(ret)
    {
        printk("Failed to cdev_add.\n");
        goto err2;
    }

    //自动创建设备节点，＝＝mknod /dev/test c 500 0
    mclass = class_create(THIS_MODULE,"myclass");

    if(IS_ERR(mclass))
    {
        printk("Failed to class_create.\n");
        ret = PTR_ERR(mclass);
        goto err3;
    }

    //mknod /dev/demo0 c .....
    //mknod /dev/demo1 c .....
    mdevice = device_create(mclass,NULL,MKDEV(MAJOR(devno),MINOR(devno)),NULL,"demo");

    if(IS_ERR(mdevice))
    {
        printk("Failed to device_create.\n");
        ret = PTR_ERR(mdevice);
        goto err4;
    }

    return 0;
err4:
    class_destroy(mclass);
err3:
    cdev_del(pdev);
err2:
    kfree(pdev);
err1:
    unregister_chrdev_region(devno,count);

    return ret;
}

static void __exit demo_exit(void)
{
    printk("%s,%d\n",__func__,__LINE__);

    device_destroy(mclass,devno);
    class_destroy(mclass);
    cdev_del(pdev);
    kfree(pdev);
    unregister_chrdev_region(devno,count);

}
module_init(demo_init);
module_exit(demo_exit);
