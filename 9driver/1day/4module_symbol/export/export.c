/*************************************************************************
	> File Name: export.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Sun 29 Oct 2017 04:21:27 PM CST
 ************************************************************************/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include"../sym.h"
MODULE_LICENSE("GPL");

int func(void)
{
    printk("++++++++\n");

    return 0;
}
struct object obj = {
    .val = 100,
    .show = func,
};

EXPORT_SYMBOL_GPL(obj);

static int __init export_init(void)
{
    printk("%s,%d\n",__func__,__LINE__);

    return 0;
}
static void __exit export_exit(void)
{
    printk("%s,%d\n",__func__,__LINE__);
}

module_init(export_init);
module_exit(export_exit);
