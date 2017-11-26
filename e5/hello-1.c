#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/usb.h>
#include <linux/err.h>
#include <linux/hid.h>
#include <linux/device.h>

int hello_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	pr_alert("USB keyboard plugged in\n");
	return 0;
}

void hello_disconnect(struct usb_interface *intf)
{
	pr_alert("USB keyboard disconnected.\n");
}

static struct usb_device_id hello_table [] = {
	{USB_DEVICE_INFO
	(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT,
	USB_INTERFACE_PROTOCOL_KEYBOARD) },
	{ }                 /* Terminating entry */
};
MODULE_DEVICE_TABLE (usb, hello_table);

static struct usb_driver hello_driver = {
	.name = "hello",
	.id_table = hello_table,
	.probe = hello_probe,
	.disconnect = hello_disconnect,
};

int init_module(void)
{
	int result;
	printk(KERN_INFO "Hello world 1.\n");

	result = usb_register(&hello_driver);

	return 0;
}

void cleanup_module(void)
{

	printk(KERN_INFO "Goodbye world 1.\n");
	 usb_deregister(&hello_driver);
}

MODULE_LICENSE("GPL");
