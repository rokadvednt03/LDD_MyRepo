#include<linux/module.h>

static int __init init_function(void){

	pr_info("Hello World\n");
	return 0 ;
}

static void __exit exit_function(void){

	pr_info("Good Bye!!!\n");
}

module_init(init_function);
module_exit(exit_function);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vedant A. Rokad");
MODULE_DESCRIPTION("First Hello world kernel module");
MODULE_INFO(board,"Beaglebone_Black_REV C");
