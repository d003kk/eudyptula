#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/usb.h>
#include <linux/err.h>
#include <linux/hid.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

#define MY_ID "abcdefg1234"


ssize_t
hello_read (struct file * the_file, char __user * buf, size_t buf_len , loff_t * lf)
{
	int i;
	char* my_id = MY_ID;
	for(i =0; i < sizeof (my_id) && i < buf_len; i++)
		buf[i]= my_id[i];
	return (i+1);
}

ssize_t
hello_write(struct file * the_file, const char __user * buf, size_t buf_len, loff_t * lf)
{
	int i;
	char* my_id = MY_ID;
	if(buf_len  != sizeof(my_id))
		return -EINVAL;

	for(i =0; i< buf_len; i++) {

		if(my_id[i] != buf[i])
			return -EINVAL;
	}

	return 0;
}

struct file_operations hello_fops = {
.owner = THIS_MODULE,
.read = hello_read, 
.write = hello_write,
};

static struct miscdevice my_dev ={
.minor = MISC_DYNAMIC_MINOR,
.name = "eudyptula/hello",
.fops = &hello_fops
};

int init_module(void)
{
	int retval;

	retval = misc_register(&my_dev);

	if (retval) return retval;

	printk("my: got minor %i\n",my_dev.minor);
	return 0;	
}

void cleanup_module(void)
{
	misc_deregister(&my_dev);
}
MODULE_AUTHOR("ME"); 
MODULE_LICENSE("GPL");
