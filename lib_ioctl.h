#include<linux/ioctl.h>

#define IOCTL_READ _IOR('g',1,char)

#define IOCTL_WRITE _IOW('g',1,char)

#define IOCTL_EXCHANGE _IOWR('g',1,char)

#define IOCTL_NONE _IO('g',1)

#define IOCTL_SETFONT _IOR('g',1,int)

#define IOCTL_GETFONT _IOW('g',1,int)




