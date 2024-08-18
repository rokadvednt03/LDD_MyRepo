#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VEDANT");
MODULE_DESCRIPTION("First Hello world kernel module");
MODULE_INFO(board,"Beaglebone_Black_REV C");

static int __init HelloworldInitFunction(void){

	pr_info("Hello World\n");
	return 0 ;
}

static void __exit HelloWorldExitFunction(void){

	pr_info("Good Bye!!!\n");
}

module_init(HelloworldInitFunction);
module_exit(HelloWorldExitFunction);

