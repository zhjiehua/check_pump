/*
 * linux/drivers/char/mini210_pwm.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/backlight.h>
#include <linux/err.h>
#include <linux/pwm.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>

#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <asm/uaccess.h>
#include <asm-generic/ioctl.h>

#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>


#define DEVICE_NAME			"pwm"
#define ENABLE_INT 			0

//IOCTL的命令
#define IOC_MAGIC  'A'
#define PWM_IOCTL_GET_IO		_IO(IOC_MAGIC, 7)
#define PWM_IOCTL_CLS_IO		_IO(IOC_MAGIC, 6)
#define PWM_IOCTL_SET_IO		_IO(IOC_MAGIC, 5)
#define PWM_IOCTL_GET_STA		_IO(IOC_MAGIC, 4)
#define PWM_IOCTL_SET_CNT		_IO(IOC_MAGIC, 3)
#define PWM_IOCTL_SET_FREQ		_IO(IOC_MAGIC, 2)
#define PWM_IOCTL_START			_IO(IOC_MAGIC, 1)
#define PWM_IOCTL_STOP			_IO(IOC_MAGIC, 0)


//IO掩码
#define IO_PUL_MASK				((unsigned long)1<<0)
#define IO_DIR_MASK				((unsigned long)1<<1)
#define IO_RST_MASK				((unsigned long)1<<2)
#define IO_COIL_MASK				((unsigned long)1<<3)
#define IO_CTL0_MASK				((unsigned long)1<<4)
#define IO_CTL1_MASK				((unsigned long)1<<5)

#define IO_DIN1_MASK				((unsigned long)1<<6)
#define IO_DIN2_MASK				((unsigned long)1<<7)
#define IO_DIN3_MASK				((unsigned long)1<<8)
#define IO_DIN4_MASK				((unsigned long)1<<9)
#define IO_DIN5_MASK				((unsigned long)1<<10)
#define IO_DIN6_MASK				((unsigned long)1<<11)

#define NS_IN_1HZ			(1000000000UL)
#define BUZZER_PWM_ID			0


struct pwm_io_desc
{
	char *name;
	int gpio;
	int type;
	unsigned long mask;
	int init_level;
};

static struct pwm_io_desc pwm_io[] =
{
	{"BUZZER_PMW_GPIO", S5PV210_GPD0(0), S3C_GPIO_OUTPUT, IO_PUL_MASK, 0},
	{"BUZZER_DIR_GPIO", S5PV210_GPJ3(7), S3C_GPIO_OUTPUT, IO_DIR_MASK, 1},
	{"BUZZER_RST_GPIO", S5PV210_GPJ3(6), S3C_GPIO_OUTPUT, IO_RST_MASK, 1},
	{"BUZZER_COIL_GPIO", S5PV210_GPG2(4), S3C_GPIO_OUTPUT, IO_COIL_MASK, 0},
	
	{"CTL0_GPIO", S5PV210_GPG2(5), S3C_GPIO_OUTPUT, IO_CTL0_MASK, 1},
	{"CTL1_GPIO", S5PV210_GPG2(6), S3C_GPIO_OUTPUT, IO_CTL1_MASK, 0},//!!!!!!!!!!!
	
	{"DIN1_GPIO", S5PV210_GPE0(2), S3C_GPIO_INPUT, IO_DIN1_MASK, 0},
	{"DIN2_GPIO", S5PV210_GPA0(6), S3C_GPIO_INPUT, IO_DIN2_MASK, 0},
	{"DIN3_GPIO", S5PV210_GPG2(0), S3C_GPIO_INPUT, IO_DIN3_MASK, 0},
	{"DIN4_GPIO", S5PV210_GPG2(2), S3C_GPIO_INPUT, IO_DIN4_MASK, 0},
	{"DIN5_GPIO", S5PV210_GPG2(1), S3C_GPIO_INPUT, IO_DIN5_MASK, 0},
	{"DIN6_GPIO", S5PV210_GPG2(3), S3C_GPIO_INPUT, IO_DIN6_MASK, 0},
};

static struct pwm_device *pwm4buzzer;

static struct semaphore lock;

static unsigned long freqence;
static unsigned long _pwm_cnt;
static unsigned long pwm_count;
static unsigned char pwm_status;

//static unsigned long io_status;

static void pwm_set_freq(unsigned long freq) {
	int period_ns = NS_IN_1HZ / freq;

	pwm_config(pwm4buzzer, period_ns / 2, period_ns);

	//printk("pwm set freq\n");
}

static void pwm_start(void)
{
	s3c_gpio_cfgpin(pwm_io[0].gpio, S3C_GPIO_SFN(2));
	
	pwm_enable(pwm4buzzer);

	printk("start the pwm\n");

	pwm_status = 1;
}


static void pwm_stop(void) {
	s3c_gpio_cfgpin(pwm_io[0].gpio, S3C_GPIO_OUTPUT);

	pwm_config(pwm4buzzer, 0, NS_IN_1HZ / 100);
	pwm_disable(pwm4buzzer);

	printk("pwm stop\n");
	_pwm_cnt = 0;
	pwm_status = 0;
}

static irqreturn_t timer0_interrupt(int irq, void *dev_id)
{
	printk("interupt!!!!!\n");
	
	_pwm_cnt++;
	if(_pwm_cnt >= pwm_count)
	{
		pwm_stop();
		//_pwm_cnt = 0;
	}

	return IRQ_HANDLED;
}

static int mini210_pwm_open(struct inode *inode, struct file *file) {
	if (!down_trylock(&lock))
		return 0;
	else
		return -EBUSY;
}

static int mini210_pwm_close(struct inode *inode, struct file *file) {
	up(&lock);
	return 0;
}

#if 0
static int mini210_pwm_read(struct file *filp, char __user *buff,
		size_t count, loff_t *offp)
{
	unsigned long err;

	err = copy_to_user((void *)buff, (const void *)(&pwm_status),
			sizeof(unsigned char));

	return err ? -EFAULT : sizeof(unsigned char);
}
#endif

static long mini210_pwm_ioctl(struct file *filep, unsigned int cmd,
		unsigned long arg)
{
	int i = 0;
	unsigned long temp = 0;
	unsigned long _arg = 0;
	//printk("the cmd is %ud\n", cmd);
	//printk("the arg is %lu\n", arg);
	//printk("pwm_status is %d\n", pwm_status);
	switch (cmd) {
		case PWM_IOCTL_SET_IO:
			printk("the PWM_IOCTL_SET_IO arg is %lu\n", arg);
			for(i=0;i<ARRAY_SIZE(pwm_io);i++)
			{
				if(arg & pwm_io[i].mask){
					//gpio_set_value(pwm_io[i].gpio, 1);
					gpio_direction_output(pwm_io[i].gpio, 1);
					//io_status |= pwm_io[i].mask;
					printk("set io %d\n", i);
				}
			}	
			break;
			
		case PWM_IOCTL_CLS_IO:
			printk("the PWM_IOCTL_CLS_IO arg is %lX\n", arg);
			for(i=0;i<ARRAY_SIZE(pwm_io);i++)
			{
				if(arg & pwm_io[i].mask){
					//gpio_set_value(pwm_io[i].gpio, 0);
					gpio_direction_output(pwm_io[i].gpio, 0);
					//io_status &= (~pwm_io[i].mask);
					printk("cls io %d\n", i);
				}
			}	
			break;
			
		case PWM_IOCTL_GET_IO:
			printk("the GET_IO  ----which io to get---arg is %lX\n", *(unsigned long*)arg);
			//copy_from_user((void *)(&_arg), (const void *)(arg), sizeof(unsigned long);
			for(i=0;i<ARRAY_SIZE(pwm_io);i++)//遍历所有IO
			{
				if(*(unsigned long*)(arg) & pwm_io[i].mask)//该IO需要读
				{
					printk("get-- io %d\n", i);
					//temp |= (io_status & pwm_io[i].mask);
					if(gpio_get_value(pwm_io[i].gpio))//如果是高电平
					{
						temp |= pwm_io[i].mask;//对应为置一
					}
				}
			}
			printk("the temp is %lX\n", temp);
			if(copy_to_user((void *)arg, (const void *)(&temp), sizeof(unsigned long)) != 0)
				return -EFAULT;

			printk("the GET_IO  -------arg is %lX\n", *(unsigned long*)arg);

			break;
			
		case PWM_IOCTL_GET_STA:
			if(copy_to_user((void *)arg, (const void *)(&pwm_status), sizeof(unsigned char)) != 0)
				return -EFAULT;
			break;
			
		case PWM_IOCTL_SET_CNT:
			if (arg == 0)
				return -EINVAL;
			pwm_count = arg;
			break;
			
		case PWM_IOCTL_SET_FREQ:
			if (arg == 0)
				return -EINVAL;
			//pwm_set_freq(arg);
			freqence = arg;
			break;
			
		case PWM_IOCTL_START:
			pwm_set_freq(freqence);
			pwm_start();
			break;
			
		case PWM_IOCTL_STOP:
		default:
			pwm_stop();
			break;
	}

	return 0;
}


static struct file_operations mini210_pwm_ops = {
	.owner			= THIS_MODULE,
	.open			= mini210_pwm_open,
	.release			= mini210_pwm_close, 
//	.read				= mini210_pwm_read,
	.unlocked_ioctl		= mini210_pwm_ioctl,
};

static struct miscdevice mini210_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &mini210_pwm_ops,
};

static int __init mini210_pwm_dev_init(void) {
	int ret;
	int i = 0;

	for(i=0;i<ARRAY_SIZE(pwm_io);i++)
	{
		ret = gpio_request(pwm_io[i].gpio, DEVICE_NAME);
		if (ret) {
			printk("request GPIO %s failed\n", pwm_io[i].name);
			i--;
			goto ret1;
		}
		
		if(pwm_io[i].type == S3C_GPIO_OUTPUT)
		{
			gpio_set_value(pwm_io[i].gpio, pwm_io[i].init_level);
			s3c_gpio_cfgpin(pwm_io[i].gpio, S3C_GPIO_OUTPUT);
		}
		else
		{
			s3c_gpio_cfgpin(pwm_io[i].gpio, S3C_GPIO_INPUT);
		}
	}

	pwm4buzzer = pwm_request(BUZZER_PWM_ID, DEVICE_NAME);
	if (IS_ERR(pwm4buzzer)) {
		printk("request pwm %d for %s failed\n", BUZZER_PWM_ID, DEVICE_NAME);
		ret =  -ENODEV;
		goto ret1;
	}

#if ENABLE_INT
	ret = request_irq(IRQ_TIMER0, timer0_interrupt, IRQ_TYPE_EDGE_BOTH, //中断方式上升和下降沿                        
	"TIMER0", 0);
	if (ret) {
		printk("request irq %d for timer0 failed\n", IRQ_TIMER0);
		goto ret2;
	}
#endif

	pwm_stop();

	sema_init(&lock, 1);
	ret = misc_register(&mini210_misc_dev);

	printk(DEVICE_NAME "\tinitialized\n");
ret2:
	pwm_free(pwm4buzzer);
ret1:
	for(;i<=0;i--)
	{
		gpio_free(pwm_io[i].gpio);
	}
	return ret;
}

static void __exit mini210_pwm_dev_exit(void) {
	int i =0;
	pwm_stop();

	misc_deregister(&mini210_misc_dev);

#if ENABLE_INT	
	free_irq(IRQ_TIMER0, 0);
#endif

	pwm_free(pwm4buzzer);

	for(i=0;i<ARRAY_SIZE(pwm_io);i++)
	{
		gpio_free(pwm_io[i].gpio);
	}
}

module_init(mini210_pwm_dev_init);
module_exit(mini210_pwm_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FriendlyARM Inc.");
MODULE_DESCRIPTION("S5PV210 PWM Driver");

