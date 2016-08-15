#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <asm-generic/ioctl.h>

//IOCTLµÄÃüÁî
#define IOC_MAGIC  'A'

#define PWM_IOCTL_SET_FREQ		_IO(IOC_MAGIC, 2)
#define PWM_IOCTL_START			_IO(IOC_MAGIC, 1)
#define PWM_IOCTL_STOP			_IO(IOC_MAGIC, 0)


#define ESC_KEY 0x1b

static int getch(void)
{
    struct termios oldt,newt;
    int ch; 
#if 0
    if (!isatty(STDIN_FILENO)) {
        fprintf(stderr, "this problem should be run at a terminal\n");
        exit(1);
    } 
    // save terminal setting
    if(tcgetattr(STDIN_FILENO, &oldt) < 0) {
        perror("save the terminal setting");
        exit(1);
    } 

    // set terminal as need
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    if(tcsetattr(STDIN_FILENO,TCSANOW, &newt) < 0) {
        perror("set terminal");
        exit(1);
    }
#endif
    ch = getchar();
#if 0
    // restore termial setting
    if(tcsetattr(STDIN_FILENO,TCSANOW,&oldt) < 0) {
        perror("restore the termial setting");
        exit(1);
    }
#endif
    return ch;
}

static int fd = -1;
static void close_buzzer(void);
static void open_buzzer(void)
{
    fd = open("/dev/pwm", 0);
    if (fd < 0) {
        perror("open pwm_buzzer device");
        exit(1);
    }

    // any function exit call will stop the buzzer
    atexit(close_buzzer);
}

static void close_buzzer(void)
{
    if (fd >= 0) {
        ioctl(fd, PWM_IOCTL_STOP);
        close(fd);
        fd = -1;
    }
}


static void set_buzzer_freq(unsigned long freq)
{
	printf("the freq is %lu\n", freq);
    // this IOCTL command is the key to set frequency
    int ret = ioctl(fd, PWM_IOCTL_SET_FREQ, freq);
    if(ret < 0) {
        perror("set the frequency of the buzzer");
        exit(1);
    }
}

static void start_buzzer(void)
{
	printf("start the buzzer\n");
    int ret = ioctl(fd, PWM_IOCTL_START);
    if(ret < 0) {
        perror("start the buzzer");
        exit(1);
    }
}

static void stop_buzzer(void)
{
	printf("stop the buzzer\n");
    int ret = ioctl(fd, PWM_IOCTL_STOP);
    if(ret < 0) {
        perror("stop the buzzer");
        exit(1);
    }
}

int main(int argc, char **argv)
{
    unsigned long freq = 4800000;
    unsigned long cnt  =  2;
    unsigned char pwm_status;   

    open_buzzer();
    printf( "\nBUZZER TEST ( PWM Control )\n" );
    printf( "Press 9/8 to increase/reduce the count of the pluses\n" ) ;
    printf( "Press +/- to increase/reduce the frequency of the BUZZER\n" ) ;
    printf( "Press 'ESC' key to Exit this program\n\n" );

    set_buzzer_freq(freq);
    //set_pwm_count(cnt);

    while( 1 )
    {
        int key;
	unsigned long temp;

        key = getch();

        switch(key) { 
		case '0':
		start_buzzer();
		break;
		
        case '+':
            if( freq < 4800000 )
                freq += 6;
	    set_buzzer_freq(freq);
            break;

        case '-':
            if( freq > 6 )
                freq -= 6 ;
	    set_buzzer_freq(freq);	
            break;
		
        case ESC_KEY:
        case EOF:
            stop_buzzer();
            exit(0);
        default:
            break;
        }
    }
}
