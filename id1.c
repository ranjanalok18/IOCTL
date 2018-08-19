#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>
#include<linux/ioctl.h>

#include"lib_ioctl.h"

//int major=245;
//int minor=10;
int char_open(struct inode* , struct file*);
int char_close(struct inode* , struct file*);
//ssize_t char_read (struct file *, char __user *, size_t, loff_t *);
//ssize_t char_write (struct file *, const char __user *, size_t, loff_t *);
long my_ioctl(struct file *, unsigned int , unsigned long );
//long (*compat_ioctl) (struct file *, unsigned int, unsigned long);


dev_t devnum =-1;
struct cdev *mycdev = NULL;

int char_open(struct inode* op,struct file* op1){
	printk("Its..Open\n");
	return 0;
}

	char kbuf[40]="HEY..Its KERNEL";
	char kbuf1[40];
	int ret =-1; 
long my_ioctl(struct file * op1, unsigned int cmd, unsigned long ubuf){
	switch(cmd){
		case IOCTL_READ:
			printk("IOCTL_READ\n");
			ret=copy_to_user((char *)ubuf,kbuf,50);
			if(ret<0){
				printk("IOCTL...READ failed %d\n",ret);
				return -1;
			}
		break;
		case IOCTL_WRITE:
			printk("IOCTL_WRITE\n");
			ret=copy_from_user(kbuf1,(char *)ubuf,50);
			if(ret<0){
				printk("IOCTL...WRITE failed %d\n",ret);
				return -1;
			}
		break;
		default:
			printk("IOCTL...Invalidated\n");
	}
	
	return 0;
}

//ssize_t char_read(struct file * op1, char __user *ubuf,size_t len, ){
/*ssize_t char_read (struct file *flp, char __user *ubuf, size_t len, loff_t *off)
{	
char kbuf[20]="Hi Its Kernel";
	
	int ret =-1;
	ret=copy_to_user(ubuf,kbuf,strlen(kbuf)+1);
	if(ret>0){
		printk(KERN_ERR"Copy_to_user failed %d left data\n",ret);
		return -1;
	}
	printk("Copy_to_user Done\n");
	return 0;
}
//ssize_t char_write(struct file *op1, const char __user *ubuf,size_t len){
ssize_t char_write (struct file *flp, const char __user *ubuf, size_t len, loff_t *offp)
{	
	char kbuf[20];
	int ret =-1;
	ret=copy_from_user(kbuf,ubuf,len);
	if(ret>0){
		printk(KERN_ERR"Copy_from_user failed %d left data\n",ret);
		return -1;
	}
		printk("Copy_from_user Done %s\n", kbuf);
	return 0;
}
*/
struct file_operations myops={
	.owner=THIS_MODULE,
	.open=char_open,
	.release=char_close,
	//.read=char_read,
	//.write=char_write,
	.unlocked_ioctl=my_ioctl,
	
	};
int char_close(struct inode* op,struct file* op1){
	printk("Its..Close");
	return 0;
}
static int mkdevn_init(void)
{
	int ret =-1;
        printk("Its INIT\n");
/*        devnum=MKDEV(major,minor);
        if(devnum<0){
                printk(KERN_ERR"MKDEV failed\n");
                return -1;
        }
*/	ret=alloc_chrdev_region(&devnum,11,2,"DRIVER11");

//        ret=register_chrdev_region(devnum,2,"DRIVER1");
        if(ret<0){
                printk(KERN_ERR"Resgitration Failed\n");
                return -1;
        }
        printk("Successfully Registred\n");
	printk("Major=%d Minor=%d\n",MAJOR(devnum),MINOR(devnum));
        
	mycdev=cdev_alloc();
	if(mycdev==NULL){
		printk(KERN_NOTICE"CDEV Failed\n");
		unregister_chrdev_region(devnum,2);
		return -1;
	}
		printk("CDEV Passed\n");

	mycdev->ops=&myops;
	
	ret=cdev_add(mycdev,devnum,2);
	if(ret<0){
		printk("CDEV_ADD Failed\n");
		cdev_del(mycdev);
		unregister_chrdev_region(devnum,2);
		return -1;
	}
		printk("CDEV_ADD Pass\n");
	
	return 0;
}
static void mkdevn_exit(void)
{
	printk("It's EXIT\n");
	cdev_del(mycdev);
        unregister_chrdev_region(devnum,2);
}
module_init(mkdevn_init);
module_exit(mkdevn_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alok");
MODULE_DESCRIPTION("ioctl_module");
