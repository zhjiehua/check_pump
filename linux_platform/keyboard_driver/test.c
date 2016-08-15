#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

//#define TEST_KBIO

#ifdef TEST_KBIO
char *dev = "/dev/keyboardIO";
#else
char *dev = "/dev/multi_buttons";
#endif

//dev data
struct key_action_data{
	unsigned char bPress;
	unsigned char keycode;
};

struct key_action_data keyData[2];

int main(void)
{
    int fd;
    int nread,i;
    char buff[]="Hello\n";
	char cmd = -1;
	char arg;

	fd = open( dev, O_RDWR );
    if (-1 == fd)
    {
		perror( dev );
		return(-1);
	}
#ifdef TEST_KBIO
	while( 1 )
	{
		printf("input set the io hight or low[1/0]:\n");
		cmd = getchar();
		getchar();
		if( cmd != '1' && cmd != '0' )
		{
			printf("error cmd!\n");
			break;
		}
		printf("get input:%c\n",cmd);
		for( arg = 0; arg < 11; ++arg )
			ioctl( fd, cmd - '0', arg );
		/*if( arg >= '0' && arg <= '9' )
		{
			ioctl( fd, cmd - '0', arg - '0' );
		}else if( arg >= 'a' && arg <= 'f' )
			ioctl( fd, cmd - '0', arg - 'a' );
		else
		{
			printf("error arg!\n");
			break;
		}*/
	};
#else
	while( nread = read( fd, keyData, sizeof( keyData ) ) )
	{
        printf( "nread:\t%d", nread );
		nread /= sizeof(struct key_action_data);
		for( i = 0; i < nread; ++i )
			printf("%d key action: press=%d; keycode=%d\n", i, keyData[i].bPress, keyData[i].keycode );
	}
#endif

    close(fd);
    return 0;
}

