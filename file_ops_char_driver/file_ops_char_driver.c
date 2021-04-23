#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

/*
** Function Prototypes
*/
static int      __init fops_char_driver_init(void);
static void     __exit fops_char_driver_exit(void);
static int      fops_char_open(struct inode *inode, struct file *file);
static int      fops_char_release(struct inode *inode, struct file *file);
static ssize_t  fops_char_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  fops_char_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations fops =
{
    .owner      = THIS_MODULE,
    .read       = fops_char_read,
    .write      = fops_char_write,
    .open       = fops_char_open,
    .release    = fops_char_release,
};

/*
** This function will be called when we open the Device file
*/
static int fops_char_open(struct inode *inode, struct file *file)
{
        pr_info("Driver Open Function Called...!!!\n");
        return 0;
}

/*
** This function will be called when we close the Device file
*/
static int fops_char_release(struct inode *inode, struct file *file)
{
        pr_info("Driver Release Function Called...!!!\n");
        return 0;
}

/*
** This function will be called when we read the Device file
*/
static ssize_t fops_char_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        pr_info("Driver Read Function Called...!!!\n");
	char data[100]= "hi kishan i am fine";
	copy_to_user(buf, data, len);
        return 0;
}

/*
** This function will be called when we write the Device file
*/
static ssize_t fops_char_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        pr_info("Driver Write Function Called...!!!\n");
	char *data=NULL;
	data = (char *)vzalloc(len);
	copy_from_user(data, buf, len);
	printk("data from user space: %s", data);
	vfree(data);
        return len;
}

/*
** Module Init function
*/
static int __init fops_char_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "file_ops_char_Dev")) <0){
                pr_err("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));

        /*Creating cdev structure*/
        cdev_init(&etx_cdev,&fops);

        /*Adding character device to the system*/
        if((cdev_add(&etx_cdev,dev,1)) < 0){
            pr_err("Cannot add the device to the system\n");
            goto r_class;
        }

        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"file_ops_char_class")) == NULL){
            pr_err("Cannot create the struct class\n");
            goto r_class;
        }

        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"file_ops_char_device")) == NULL){
            pr_err("Cannot create the Device 1\n");
            goto r_device;
        }
        pr_info("Device Driver Insert...Done!!!\n");
      return 0;

r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}

/*
** Module exit function
*/
static void __exit fops_char_driver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!!\n");
}

module_init(fops_char_driver_init);
module_exit(fops_char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kisan yadav");
MODULE_DESCRIPTION("file_ops_char_driver");
MODULE_VERSION("1.3");
