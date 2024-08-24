#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>

#define MY_MAJOR 50

/*Meta Information*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vedant A. Rokad") ;
MODULE_DESCRIPTION("Char manual registration!!");
MODULE_INFO(board,"BBB");

/*
 * @brief This function is called when device file called
 * */

static int driver_open(struct inode* device_file, struct file* ins){
	pr_info("dev_nr open was called\n");	
	return 0 ;
}

static int driver_close(struct inode* device_file, struct file* ins){
        pr_info("dev_nr close was called\n");
		return 0 ;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close
};



static int __init pcd_init_function(void){
	int retval ;
	pr_info("pcd_init module called\n");
	retval = register_chrdev(MY_MAJOR,"dev_number",&fops);
	if(retval == 0) {
		printk("dev_num - registered: Major: %d, Minor=%d\n",MY_MAJOR,0);
	}
	else if (retval > 0){
		printk("dev_num - registered: Major: %d, Minor=%d\n",retval>>20 ,retval&0xfffff);
	}
	else{
		printk("ERROR!\n") ;
		return -1 ;

	}

	return 0;

}

static void __exit pcd_cleanup_function(void){
	pr_info("PCD_Cleanup function call!!");
	unregister_chrdev(MY_MAJOR,"dev_number");
	pr_info("GoodBye!!");

}


module_init(pcd_init_function);
module_exit(pcd_cleanup_function);


