#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>

#define DEV_MEM_SIZE 512 

char device_buffer[DEV_MEM_SIZE];

dev_t device_addr ;
 
struct cdev pseudo_eeprom_dev	;
struct file_operations pseudo_file_op ;

static int __init charDriver_Init(void){
	pr_info("Hello World\n");
	alloc_chrdev_region(&device_addr,0,5,"pcd");
	pseudo_eeprom_dev.owner = THIS_MODULE;
	cdev_init(&pseudo_eeprom_dev,&pseudo_file_op);
	cdev_add(&pseudo_eeprom_dev,device_addr,1);
	return 0;
}


static void __exit charDriver_exit(void){
        pr_info("exit\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vedant A. Rokad");
MODULE_DESCRIPTION("First Char Driver");
MODULE_INFO(board,"BBB");

module_init(charDriver_Init);
module_exit(charDriver_exit);

