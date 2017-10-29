/*************************************************************************
	> File Name:demo.c 
	> Author: joglee
	> Mail: li15041829350@163.com
	> Created Time: Sun 29 Oct 2017 03:39:06 PM CST
 ************************************************************************/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

int intval = 0;
module_param(intval, int, 0664);
MODULE_PARM_DESC(intval, "This is a integer.");

char *p;
module_param(p, charp, 0664);
MODULE_PARM_DESC(p, "This is a pointer of string.");

int array[3] = {};
int num = 3;

module_param_array(array, int, &num, 0664);
MODULE_PARM_DESC(array, "This is a array.");

char str[12] = {};
module_param_string(str1, str, sizeof(str), 0664);
MODULE_PARM_DESC(str1, "This is a char str[12].");


static int __init demo_init(void)
{
    int i = 0;

    printk("%s,%d\n",__func__,__LINE__);

    printk("intval:%d\n",intval);
    printk("p:%s\n",p);

    for(i = 0; i <= num; i++){
        printk("array[%d] = %d\n",i, array[i]);
    }

    printk("str:%s\n",str);

    return 0;
}

static void __exit demo_exit(void)
{
    printk("%s,%d\n",__func__,__LINE__);
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_AUTHOR("joglee");
MODULE_DESCRIPTION("This is a param demo test.");
