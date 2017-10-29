/*************************************************************************
	> File Name: demo.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Sun 29 Oct 2017 12:03:12 PM CST
 ************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

static int __init demo_init(void)
{
    printk("%s,%d\n",__func__,__LINE__);

    return 0;
}

static void __exit demo_exit(void)
{
    printk("%s,%d\n",__func__,__LINE__);
}
module_init(demo_init);
module_exit(demo_exit);
