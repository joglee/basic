/*************************************************************************
	> File Name: demo.c
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Tue 31 Oct 2017 10:07:36 PM CST
 ************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

struct node {
    int a;
    char ch;
    short d;
    int f;
};

static int __init demo_init(void)
{
    struct node buf;
    struct node *p;

    printk("%s,%d\n",__func__,__LINE__);

    buf.a = 100;
    buf.ch = 'x';
    buf.d = 20;
    buf.f = 300;

    p = container_of(&(buf.d),struct node,d);

    printk("&buf:%p,p:%p\n",&buf,p);

    printk("a:%d, ch:%c, d:%d, f:%d",p->a,p->ch,p->d,p->f);

    return 0;
}
static void __exit demo_exit(void)
{
    printk("%s,%d\n",__func__,__LINE__);
}
module_init(demo_init);
module_exit(demo_exit);

