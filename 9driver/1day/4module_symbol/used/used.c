/*************************************************************************
	> File Name: used.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Sun 29 Oct 2017 04:31:37 PM CST
 ************************************************************************/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include"../sym.h"

MODULE_LICENSE("GPL");

extern struct object obj;

static int __init used_init(void)
{
    printk("%s,%d\n",__func__,__LINE__);

    printk("val:%d\n",obj.val);

    obj.show();

    return 0;
}

static void __exit used_exit(void)
{
    printk("%s,%d\n",__func__,__LINE__);
}
module_init(used_init);
module_exit(used_exit);
