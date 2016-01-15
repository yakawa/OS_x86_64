#include <kernel.h>
#include <klib/io.h>
#include <klib/serial.h>

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

int kputchar(int c)
{
	FONT f;
#ifdef DEBUG
	writeSerial(c);
#endif

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

static int kputs(const char *s)
{
	int cnt = 0;
	while(1){
		if(s[cnt] == '\0'){
			break;
		}
		kputchar((int)s[cnt]);
		cnt++;
	}
	return cnt;
}

static void kprint4(unsigned int v)
{
	char s[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	if( v < 0 || v > 16){
		return;
	}
	kputchar(s[v]);
}


void kprinthexc(unsigned char v)
{
	char str[2];
	int i;

	for(i = 0; i < 2; i++){
		str[1 - i] = v % 16;
		v = v / 16;
	}

	for(i = 0; i < 2; i++){
		kprint4(str[i]);
	}
}

void kprinthexs(unsigned short v)
{
	char str[4];
	int i;

	for(i = 0; i < 4; i++){
		str[3 - i] = v % 16;
		v = v / 16;
	}

	for(i = 0; i < 4; i++){
		kprint4(str[i]);
	}
}

void kprinthexi(unsigned int v)
{
	char str[8];
	int i;

	for(i = 0; i < 8; i++){
		str[7 - i] = v % 16;
		v = v / 16;
	}

	for(i = 0; i < 8; i++){
		kprint4(str[i]);
	}
}
void kprinthexl(unsigned long v)
{
	char str[16];
	int i;

	for(i = 0; i < 16; i++){
		str[15 - i] = v % 16;
		v = v / 16;
	}

	for(i = 0; i < 16; i++){
		kprint4(str[i]);
	}
}

static void kmsg_prefix(const unsigned char msgLebel)
{
	switch(msgLebel){
	case KM_NONE:
		break;
	case KM_DEBUG:
		kputs("[DEBUG ]");
		break;
	case KM_INFO:
		kputs("[INFO  ]");
		break;
	case KM_NOTICE:
		kputs("[NOTICE]");
		break;
	case KM_WARNING:
		kputs("[WARN  ]");
		break;
	case KM_ERROR:
		kputs("[ERROR ]");
		break;
	case KM_CRITICAL:
		kputs("[CRIT  ]");
		break;
	case KM_ALERT:
		kputs("[ALERT ]");
		break;
	case KM_EMERG:
		kputs("[EMERG ]");
		break;
	default:
		break;
	}
}

void kmsg(const unsigned char msgLebel, const char *fmt)
{
	if(msgLebel < sys_info.log_level){
		return;
	}
	kmsg_prefix(msgLebel);
	kputs(fmt);
	kputchar('\n');
}

void kmsg_lls(const unsigned char msgLebel, const char *fmt, unsigned long p1, unsigned long p2, char *p3)
{
	unsigned char c;
	unsigned char ch;

	if(msgLebel < sys_info.log_level){
		return;
	}
	kmsg_prefix(msgLebel);
	while((c = *fmt++) != 0){
		if(c != '%'){
			kputchar(c);
		} else {
			c = *fmt++;
			switch(c){
			case 0:
				goto _exit;
			case '%':
				kputchar('%');
				break;
			case '0':
				kprinthexl(p1);
				break;
			case '1':
				kprinthexl(p2);
				break;
			case '2':
				while((ch = *p3++) != 0){
					kputchar(ch);
				}
				break;
			default:
				break;
			}
		}
	}
	_exit:
	kputchar('\n');
}
void kmsg_lll(const unsigned char msgLebel, const char *fmt, unsigned long p1, unsigned long p2, unsigned long p3)
{
	unsigned char c;

	if(msgLebel < sys_info.log_level){
		return;
	}
	kmsg_prefix(msgLebel);
	while((c = *fmt++) != 0){
		if(c != '%'){
			kputchar(c);
		} else {
			c = *fmt++;
			switch(c){
			case 0:
				goto _exit;
			case '%':
				kputchar('%');
				break;
			case '0':
				kprinthexl(p1);
				break;
			case '1':
				kprinthexl(p2);
				break;
			case '2':
				kprinthexl(p3);
				break;
			default:
				break;
			}
		}
	}
	_exit:
	kputchar('\n');
}
void kmsg_iii(const unsigned char msgLebel, const char *fmt, unsigned int p1, unsigned int p2, unsigned int p3)
{
	unsigned char c;

	if(msgLebel < sys_info.log_level){
		return;
	}
	kmsg_prefix(msgLebel);
	while((c = *fmt++) != 0){
		if(c != '%'){
			kputchar(c);
		} else {
			c = *fmt++;
			switch(c){
			case 0:
				goto _exit;
			case '%':
				kputchar('%');
				break;
			case '0':
				kprinthexi(p1);
				break;
			case '1':
				kprinthexi(p2);
				break;
			case '2':
				kprinthexi(p3);
				break;
			default:
				break;
			}
		}
	}
	_exit:
	kputchar('\n');
}
