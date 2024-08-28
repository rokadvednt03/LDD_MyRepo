#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/uaccess.h>

#define DEV_MEM_SIZE 512 

#undef pr_fmt
#define pr_fmt(fmt) "%s: " fmt,__func__

loff_t pcd_llseek (struct file *filp, loff_t off, int whence);
ssize_t pcd_read (struct file *filp, char __user *buff, size_t count, loff_t *f_pos);
ssize_t pcd_write (struct file *filp, const char __user *buffer, size_t count, loff_t *f_pos);
int pcd_open (struct inode *inode, struct file *filp);
int pcd_release (struct inode *inode, struct file *filp);

char device_buffer[DEV_MEM_SIZE];

dev_t device_number ;
 
struct class *class_pcd ;
struct device *device_pcd ;
struct cdev cdev_pcd	;
struct file_operations eeprom_pcd = {
	.open = pcd_open ,
	.read = pcd_read , 
	.write = pcd_write ,
	.release = pcd_release ,
	.llseek = pcd_llseek 
};

static int __init charDriver_Init(void){
	pr_info("Hello World\n");

	/*
	 * 1. Dynamic Allocation of device number. 
	 */	
	alloc_chrdev_region(&device_number,0,7,"PCD_DEVICE");
	pr_info("Device number - <major>:<minor> = %d:%d",MAJOR(device_number),MINOR(device_number)) ;
	/*
	 * 2. Initialize the cdev_init structure with f_ops.
	 */
	cdev_init(&cdev_pcd,&eeprom_pcd) ;
	cdev_pcd.owner = THIS_MODULE ;

	/*
	 * 3. Register a (cdev structure) with VFS. 
	 */
	cdev_add(&cdev_pcd,device_number,1);

	/* 
	 * 4. Create device class under /sys/class/
	 */
	class_pcd = class_create("pcd_class") ;

	/*
	 * populate the sysfs with device information. 
	 */
	device_pcd = device_create(class_pcd,NULL,device_number,NULL,"pcd") ;

	pr_info("Module Init Successfully !!!!!! \n") ; 

	return 0;
}


static void __exit charDriver_exit(void){
    device_destroy(class_pcd,device_number);
	class_destroy(class_pcd) ;
	cdev_del(&cdev_pcd);
	unregister_chrdev_region(device_number,1);
	pr_info("exit with clean up successfully \n");
}


loff_t pcd_llseek (struct file *filp, loff_t off, int whence){
	pr_info("seek req. !! \n") ;
	return 0 ;
}


ssize_t pcd_read (struct file *filp, char __user *buff, size_t count, loff_t *f_pos){
	pr_info("Read requested for %zu bytes !! \n",count) ;
	pr_info("current file positions: %lld \n",*f_pos) ;
	if((*f_pos + count > DEV_MEM_SIZE)){
		count = DEV_MEM_SIZE - *f_pos ;
	}
	if(copy_to_user(buff,&device_buffer[*f_pos],count)){
		return -EFAULT ;
	}
	*f_pos += count ;
	pr_info("file position after read, current file count %zu is %lld \n",count,*f_pos) ;
	return count ;
}	

ssize_t pcd_write (struct file *filp, const char __user *buffer, size_t count, loff_t *f_pos){
	pr_info("Write req. for %zu bytes !! \n",count) ;	
	if((*f_pos + count > DEV_MEM_SIZE)){		
		count = DEV_MEM_SIZE - *f_pos ;
	}
	if(!count)
		return -ENOMEM ;
	if(copy_from_user(&device_buffer[*f_pos], buffer, count)){
		return -EFAULT ;
	}
	*f_pos += count ;
	
	return count ;
}
	
int pcd_open (struct inode *inode, struct file *filp){
	pr_info("Open Requested !! \n") ;
	return 0 ;
}
	
int pcd_release (struct inode *inode, struct file *filp){
	pr_info("close successful !! \n") ;
	return 0 ;
}



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vedant A. Rokad");
MODULE_DESCRIPTION("First Char Driver");
MODULE_INFO(board,"BBB");

module_init(charDriver_Init);
module_exit(charDriver_exit);

