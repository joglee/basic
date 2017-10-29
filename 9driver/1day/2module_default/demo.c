/*************************************************************************
	> File Name: demo.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Sun 29 Oct 2017 03:15:45 PM CST
 ************************************************************************/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
//模块加载
int __init_module(void)
{
    printk("%s,%d\n",__func__,__LINE__);

    return 0;
}
void __exit cleanup_module(void)
{
    printk("%s,%d\n",__func__,__LINE__);
}
