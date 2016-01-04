#include <klib/io.h>

/* size of display */
#define DISPLAY_X 80
#define DISPLAY_Y 25

typedef struct _font {
	unsigned char ch;
	unsigned char attr;
} FONT;


#define POS(x, y) (y * DISPLAY_X + x)

/* Memory mapping for VRAM */
static char *fb = (char *)0xFFFFFFFF800B8000;
FONT vram_buf[DISPLAY_X * DISPLAY_Y];

static unsigned int POS_X = 0, POS_Y = 0;



static void fb_draw(FONT *buf)
{
	int i;
	FONT *f;
	for(i = 0; i < DISPLAY_X * DISPLAY_Y; i++){
		f = (FONT *)&buf[i];
		fb[i * 2] = f->ch;
		fb[i * 2 + 1] = f->attr;
	}
}

static void _itoa(char *buf, int base, int d)
{
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;

	/* If %d is specified and D is minus, put `-' in the head.  */
	if (base == 'd' && d < 0) {
		*p++ = '-';
		buf++;
		ud = -d;
	} else if (base == 'x') {
		divisor = 16;
	}

	/* Divide UD by DIVISOR until UD == 0.  */
	do {
		int remainder = ud % divisor;

		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	} while (ud /= divisor);

	/* Terminate BUF.  */
	*p = 0;

	/* Reverse BUF.  */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}


int kputchar(int c)
{
	FONT f;
	if(c == '\n'){
		POS_X = 0;
		POS_Y = POS_Y + 1;
	} else {
		f.ch = c;
		f.attr = (FB_BLACK & 0x0F) << 4 | (FB_WHITE & 0x0F);
		vram_buf[POS(POS_X, POS_Y)] = f;
		POS_X = POS_X + 1;
	}

	if(POS_X >= DISPLAY_X){
		POS_X = 0;
		POS_Y = POS_Y + 1;
	}

	if(POS_Y >= DISPLAY_Y){
		POS_Y = 0;
	}
	fb_draw(vram_buf);
	return 1;
}

int kputs(const char *s)
{
	int cnt = 0;
	while(1){
		if(s[cnt] == '\0'){
			break;
		}
		kputchar((int)s[cnt]);
		cnt++;
	}
	kputchar('\n');
	return cnt;
}
int kprintf(const char *fmt, ...)
{
	char **arg = (char **)&fmt;
	int c, i;
	char buf[20];
	int cnt = 0;

	while((c = *fmt++) != 0){
		for(i = 0; i < 20; i++){
			buf[i] = '\0';
		}
		if(c != '%'){
			kputchar(c);
			cnt++;
		} else {
			char *p;
			c = *fmt++;
			switch(c){
			case 'd':
			case 'u':
				_itoa(buf, c, *((int *)++arg));
				p = buf;
				goto string;
				break;
			case 'x':
				_itoa(buf, c, *((int *)++arg));
				p = buf;
				goto string;
				break;

			case 's':
				p = *arg++;
				if(!p){
					p = "(NULL)";
				}
			string:
				while(*p){
					kputchar(*p++);
					cnt++;
				}
				break;

			default:
				kputchar(*((int *)++arg));
				cnt++;
			}
		}
	}
	return cnt;
}
