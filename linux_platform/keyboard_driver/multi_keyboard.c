
/*
 * linux/drivers/char/mini210_buttons.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>

#include <mach/map.h>
#include <mach/gpio.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>
#include <linux/slab.h>
#include <asm-generic/ioctl.h>

#define DEVICE_NAME		"multi_buttons"

//configuration

#define KB_TIMER_SCAN	(jiffies+msecs_to_jiffies(100))
#define MULTIACTION		2


#define IOC_MAGIC  'B'
#define BTN_IOCTL_WARNING			_IO(IOC_MAGIC, 8)




static int gEmgWarning = 0;//报警标志;
//#define WARNINGTIME3S	(3000/KB_TIMER_SCAN)
#define WARNINGTIME3S	30


static int g_KeyMatrixRow[]={
	S5PV210_GPH2(0),
	S5PV210_GPH2(1),
	S5PV210_GPH2(2),
};

static int g_KeyMatrixCol[] = {
	S5PV210_GPH1(0),
	S5PV210_GPH1(1),
	S5PV210_GPH1(3),
	S5PV210_GPH3(3),
	S5PV210_GPH3(2),
	S5PV210_GPH3(1),
	S5PV210_GPH3(0),
	S5PV210_GPH2(3),
};

#define SIZE_KEYMATRIX_ROW ARRAY_SIZE(g_KeyMatrixRow)
#define SIZE_KEYMATRIX_COL ARRAY_SIZE(g_KeyMatrixCol)

static unsigned char kbd_keycode[ SIZE_KEYMATRIX_ROW ][ SIZE_KEYMATRIX_COL ] = {
	{11, 12, 13, 14, 15, 16, 17, 18 },
	{21, 22, 23, 24, 25, 26, 27, 28 },
	{31, 32, 33, 34, 35, 36, 37, 38 },
};

//dev data
struct key_action_data{
	unsigned char bPress;
	unsigned char keycode;
};

struct mini210_kbdata {
	struct timer_list timerScan;
	struct key_action_data listScanFist[ MULTIACTION ];
	int nScanFist;
	struct key_action_data listAction[ MULTIACTION ];
	int nAction;
};


static DECLARE_WAIT_QUEUE_HEAD(button_waitq);
static volatile int ev_kddata = 0;

static void PrePareScan( void )
{
	int i;
	for (i = 0; i < SIZE_KEYMATRIX_COL; i++) {
		gpio_set_value( g_KeyMatrixCol[i], 0 );
	}
}

static int GetActionCol( int nRow, int* pCol )
{
	int i;
	int szCol = 0;
	unsigned iolow;
	for (i = 0; i < SIZE_KEYMATRIX_COL; i++) {
		gpio_set_value( g_KeyMatrixCol[i], 1 );
	}
	for ( i = 0; i < SIZE_KEYMATRIX_COL; i++ ) {
		gpio_set_value( g_KeyMatrixCol[i], 0 );
		iolow = !gpio_get_value( g_KeyMatrixRow[ nRow ] );
		if( iolow )
			pCol[ szCol++ ] = i;
		gpio_set_value( g_KeyMatrixCol[i], 1 );
		if( szCol >= MULTIACTION )
            break;
	}
	PrePareScan();
	return szCol;
}

static int GetkeyActionDownList( struct mini210_kbdata *kbdata, struct key_action_data* actionList )
{
	int nActionDown = 0;
	unsigned iolow;
	int pActionCol[ SIZE_KEYMATRIX_COL ];
	int nActionRow;
	int nActionCol = 0;
	for ( nActionRow = 0; nActionRow < SIZE_KEYMATRIX_ROW; ++nActionRow ) {
		iolow = !gpio_get_value( g_KeyMatrixRow[ nActionRow ] );
		if( iolow )
		{
			nActionCol = GetActionCol( nActionRow, pActionCol );
			while( nActionCol-- )
			{
			    //printk("%d nActionCol %d\n", nActionCol, pActionCol[nActionCol] );
			    actionList[nActionDown].bPress = 1;
			    actionList[nActionDown].keycode = kbd_keycode[ nActionRow ][ pActionCol[nActionCol] ];
                ++nActionDown;
                if( nActionDown >= MULTIACTION )
                    goto get_list_leave;
			}
		}
	}
get_list_leave:
	return nActionDown;
}

static int UpdateActionList( struct mini210_kbdata *kbdata, struct key_action_data* actionList,int szList )
{
    int i,j;
    int iMov = 0;
    struct key_action_data tmpMov;
    for( i = 0; i < kbdata->nAction; ++i )
    {
        if( kbdata->listAction[i].bPress )
        {
            kbdata->listAction[i].bPress = 0;
            if( iMov != i )
            {
                tmpMov = kbdata->listAction[ iMov ];
                kbdata->listAction[ iMov ] = kbdata->listAction[i];
                kbdata->listAction[i] = tmpMov;
            }
            ++iMov;
        }
    }
    for( i = 0; i < szList; ++i )
    {
        for( j = 0; j < iMov; ++j )
        {
            if( kbdata->listAction[ j ].keycode == actionList[i].keycode )
            {
                kbdata->listAction[ j ].bPress = 1;
                break;
            }
        }
        if( j == iMov )
        {
            if( iMov < MULTIACTION )
                kbdata->listAction[ iMov++ ] = actionList[i];
            else
                goto update_leave;
        }
    }
update_leave:
    kbdata->nAction = iMov;
    return ( kbdata->nAction != 0 );
}

static int DisShakes( struct mini210_kbdata *kbdata, struct key_action_data* actionList,int szList )
{
    int i;
    //printk( "DisShakes szList:%d:\n", szList );
    for( i = 0; i < szList; ++i )
    {
        //printk( "DisShakes1:%d:\n", i );
        if( kbdata->listScanFist[ i ].keycode != actionList[ i ].keycode )
            break;
    }
    if( i == szList && kbdata->nScanFist == szList )
    {
        return szList;
    }
    else
    {
        if( i > 0 ) --i;
        for( ; i < szList; ++i )
        {
            //printk( "DisShakes2:%d:\n", i );
            kbdata->listScanFist[ i ] = actionList[ i ];
        }
        kbdata->nScanFist = szList;
        return kbdata->nScanFist;
    }
}

static void print_list( const char* str, struct key_action_data* actionList,int szList )
{
    printk( "%s,len:%d:", str,szList );
    while( szList-- )
        printk("[%d,%d],", actionList->bPress, actionList->keycode ),++actionList;
    printk( "\n" );
}


static void mini210_buttons_timer_scan(unsigned long _data)
{
	struct mini210_kbdata *kbdata = (struct mini210_kbdata*)_data;
	static int interval = 0;
	static int soundFlag = 0;
	interval++;
	if(interval == 3)//键盘扫描间隔;
	{	
		interval = 0;
		int szList = 0;
		struct key_action_data actionList[ MULTIACTION ];
		szList = GetkeyActionDownList( kbdata, actionList );
		szList = DisShakes( kbdata, actionList, szList );
		unsigned char b = kbdata->listAction[0].bPress;
		if( UpdateActionList( kbdata, actionList, szList ) /*&& ev_kddata == 0*/ )
		{
			ev_kddata = 1;
			//sound
			if( b == 0 && kbdata->listAction[0].bPress == 1)
			{
				soundFlag = 1;
			}	
			wake_up_interruptible(&button_waitq);
		}
	
		//led splash;
		static int cnt = 0;
		static int val = 0;
		cnt++;
		if(cnt==2)
		{
			cnt = 0;
			val = (val+1)%2;
			gpio_set_value( S5PV210_GPB(5), val );	
		}
	}
	
	
	//waring check;
	if(gEmgWarning)
	{
		static int soundCnt = 0;
		printk("warning check\n");
		soundCnt++;
		if(soundCnt >= WARNINGTIME3S)
		{
			soundCnt = 0;
			gEmgWarning = 0;
			printk("warning check stop\n");
		}
	}
	
	//sound
	if(soundFlag || gEmgWarning)
	{
		gpio_set_value( S5PV210_GPE1(2), 1 );	
		soundFlag = 0;
		printk("buzzer_on\n");
	}
	else
	{
		gpio_set_value( S5PV210_GPE1(2), 0 );
		//printk("buzzer_off\n");
	}
	
	mod_timer(&(kbdata->timerScan), KB_TIMER_SCAN );
}





static int mini210_buttons_open(struct inode *inode, struct file *file)
{
	struct mini210_kbdata *kbdata;
	kbdata = kzalloc(sizeof( struct mini210_kbdata )  , GFP_KERNEL);
	file->private_data = kbdata;
	kbdata->nAction = 0;
	kbdata->nScanFist = 0;
	setup_timer(&kbdata->timerScan, mini210_buttons_timer_scan, (unsigned long)kbdata);
    kbdata->timerScan.expires = KB_TIMER_SCAN;
	add_timer(&(kbdata->timerScan));
	try_module_get(THIS_MODULE);
	printk("button open\n" );
	return 0;
}

static int mini210_buttons_close(struct inode *inode, struct file *file)
{
	struct mini210_kbdata *kbdata = ( struct mini210_kbdata* )(file->private_data);
	del_timer_sync(&(kbdata->timerScan));
	kfree( kbdata );
	printk("button close\n" );
	module_put(THIS_MODULE);
	return 0;
}

static int mini210_buttons_read(struct file *filp, char __user *buff,
		size_t count, loff_t *offp)
{
	unsigned long err;
	struct mini210_kbdata *kbdata = ( struct mini210_kbdata* )(filp->private_data);
	if ( ev_kddata == 0 ) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		else
		{
		    wait_event_interruptible( button_waitq, ev_kddata);
		}
	}
	err = copy_to_user((void *)buff, (const void *)&(kbdata->listAction),
			min( kbdata->nAction * sizeof(struct key_action_data ), count));
	ev_kddata = 0;
	return err ? -EFAULT : min( kbdata->nAction * sizeof(struct key_action_data), count);
}

static unsigned int mini210_buttons_poll( struct file *file,
		struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	//struct mini210_kbdata *kbdata = ( struct mini210_kbdata* )(file->private_data);
	poll_wait(file, &button_waitq, wait);
	if ( ev_kddata )
		mask |= POLLIN | POLLRDNORM;
	return mask;
}


static long mini210_buttons_ioctl(struct file *filp, unsigned int cmd,
		unsigned long arg)
{
	switch(cmd) {
		// case BTN_IOCTL_STOP_MOTOR:
			// gEmgMotorFlag = 1;
			// break;
		case BTN_IOCTL_WARNING:
		if(arg == 0)
		{
			//关闭报警;
			gEmgWarning = 0;
			printk("gEmgWarning = 0\n" );
		}
		else
		{
			//打开报警;
			gEmgWarning = 1;
			printk("gEmgWarning = 1\n" );
		}
			break;
		default:
			return -EINVAL;
	}

	return 0;
}




static struct file_operations dev_fops = {
	.owner		    = THIS_MODULE,
	.open		    = mini210_buttons_open,
	.release	    = mini210_buttons_close,
	.read		    = mini210_buttons_read,
	.unlocked_ioctl     = mini210_buttons_ioctl,
	.poll		    = mini210_buttons_poll,
};

static struct miscdevice misc = {
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= DEVICE_NAME,
	.fops		= &dev_fops,
};

static int __init button_dev_init(void)
{
	int ret;
	int i;

	for (i = 0; i < SIZE_KEYMATRIX_COL; i++) {
		ret = gpio_request(g_KeyMatrixCol[i], "button_dev");
		if (ret) {
			printk("%s: request COL GPIO %d failed, ret = %d\n", DEVICE_NAME, i, ret);
			return ret;
		}
		gpio_set_value( g_KeyMatrixCol[i], 0 );
		s3c_gpio_cfgpin( g_KeyMatrixCol[i], S3C_GPIO_OUTPUT);
	}
	for (i = 0; i < SIZE_KEYMATRIX_ROW; i++) {
		ret = gpio_request(g_KeyMatrixRow[i], "button_dev");
		if (ret) {
			printk("%s: request ROW GPIO %d failed, ret = %d\n", DEVICE_NAME, i, ret);
			return ret;
		}
		gpio_set_value( g_KeyMatrixRow[i], 0 );
		s3c_gpio_cfgpin( g_KeyMatrixRow[i], S3C_GPIO_INPUT);
	}
	
	//sound and led;
	s3c_gpio_cfgpin( S5PV210_GPE1(2), S3C_GPIO_OUTPUT);
	s3c_gpio_cfgpin( S5PV210_GPB(5), S3C_GPIO_OUTPUT);
	s5p_gpio_set_drvstr(S5PV210_GPE1(2), S5P_GPIO_DRVSTR_LV4);
	s3c_gpio_setpull(S5PV210_GPE1(2), S3C_GPIO_PULL_UP); 
	
	PrePareScan();
	ret = misc_register(&misc);

	printk(DEVICE_NAME"\tinitialized\n");

	return ret;
}


static void __exit button_dev_exit(void)
{
	int i;
	for (i = 0; i < SIZE_KEYMATRIX_COL; i++) {
		gpio_free( g_KeyMatrixCol[i]);
	}
	for (i = 0; i < SIZE_KEYMATRIX_ROW; i++) {
		gpio_free( g_KeyMatrixRow[i]);
	}
	misc_deregister(&misc);
}

module_init(button_dev_init);
module_exit(button_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FriendlyARM Inc.");

