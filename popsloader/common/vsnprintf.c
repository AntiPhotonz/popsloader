/*
 * This file is part of PRO CFW.

 * PRO CFW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PRO CFW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PRO CFW. If not, see <http://www.gnu.org/licenses/ .
 */

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspiofilemgr.h>

#include <stdarg.h>
#include <string.h>

#include "utils.h"

static int itostr(char *buf, int in_data, int base, int upper, int sign)
{
	int res, len, i;
	unsigned int data;
	char *str;

	if(base==10 && sign && in_data<0){
		data = -in_data;
	}else{
		data = in_data;
	}

	str = buf;
	do{
		res = data%base;
		data = data/base;
		if(res<10){
			res += '0';
		}else{
			if(upper){
				res += 'A'-10;
			}else{
				res += 'a'-10;
			}
		}
		*str++ = res;
	}while(data);
	len = str-buf;

	/* reverse digital order */
	for(i=0; i<len/2; i++){
		res = buf[i];
		buf[i] = buf[len-1-i]; 
		buf[len-1-i] = res; 
	}

	return len;
}

/*
 * vsnprintf - Format a string and place it in a buffer
 * @buf: The buffer to place the result into
 * @size: The size of the buffer, including the trailing null space
 * @fmt: The format string to use
 * @args: Arguments for the format string
 */

#define OUT_C(c) \
	if(str<end){ \
		*str++ = (c); \
	} else { \
		goto exit; \
	}

static char digital_buf[32];
int vsnprintf(char *buf, int size, char *fmt, va_list args)
{
	char ch, *s, *str, *end, *sstr;
	int zero_pad, left_adj, add_sign, field_width, sign;
	int i, base, upper, len;


	if(!buf || !fmt ||!size){
		return 0;
	}

	str = buf;
	end = buf+size;

	while(*fmt){
		if(*fmt!='%'){
			OUT_C(*fmt++);
			continue;
		}

		/* skip '%' */
		sstr = fmt;
		fmt++;

		/* %% */
		if(*fmt=='%'){
			OUT_C(*fmt++);
			continue;
		}

		/* get flag */
		zero_pad = ' ';
		left_adj = 0;
		add_sign = 0;
		while((ch=*fmt)){

			if(*fmt=='0'){
				zero_pad = '0';
			}else if(*fmt=='-'){
				left_adj = 1;
			}else if(*fmt=='#'){
			}else if(*fmt==' '){
				if(add_sign!='+')
					add_sign = ' ';
			}else if(*fmt=='+'){
				add_sign = '+';
			}else{
				break;
			}
			fmt++;
		}

		/* get field width: m.n */
		field_width = 0;
		/* get m */
		while(*fmt && *fmt>'0' && *fmt<='9'){
			field_width = field_width*10+(*fmt-'0');
			fmt++;
		}
		if(*fmt && *fmt=='.'){
			fmt++;
			/* skip n */
			while(*fmt && *fmt>'0' && *fmt<='9'){
				fmt++;
			}
		}

		/* get format char */
		upper = 0;
		base = 0;
		sign = 0;
		len = 0;
		s = digital_buf;
		while((ch=*fmt)){
			fmt++;
			switch(ch){
			/* hexadecimal */
			case 'p':
			case 'X':
				upper = 1;
			case 'x':
				base = 16;
				break;

			/* decimal */
			case 'd':
			case 'i':
				sign = 1;
			case 'u':
				base = 10;
				break;

			/* octal */
			case 'o':
				base = 8;
				break;

			/* character */
			case 'c':
				digital_buf[0] = (unsigned char) va_arg(args, int);
				len = 1;
				break;

			/* string */
			case 's':
				s = va_arg(args, char *);
				if(!s) s = "<NUL>";
				len = strlen(s);
				break;

			/* float format, skip it */
			case 'e': case 'E': case 'f': case 'F': case 'g': case 'G': case 'a': case 'A':
				va_arg(args, double);
				s = NULL;
				break;

			/* length modifier */
			case 'l': case 'L': case 'h': case 'j': case 'z': case 't':
				/* skip it */
				continue;

			/* bad format */
			default:
				s = sstr;
				len = fmt-sstr;
				break;
			}
			break;
		}

		if(base){
			i = va_arg(args, int);
			if(base==10 && sign){
				if(i<0){
					add_sign = '-';
				}
			}else{
				add_sign = 0;
			}

			len = itostr(digital_buf, i, base, upper, sign);
		}else{
			zero_pad = ' ';
			add_sign = 0;
		}

		if(s){
			if(len>=field_width){
				field_width = len;
				if(add_sign)
					field_width++;
			}
			for(i=0; i<field_width; i++){
				if(left_adj){
					if(i<len){
						OUT_C(*s++);
					}else{
						OUT_C(' ');
					}
				}else{
					if(add_sign && (zero_pad=='0' || i==(field_width-len-1))){
						OUT_C(add_sign);
						add_sign = 0;
						continue;
					}
					if(i<(field_width-len)){
						OUT_C(zero_pad);
					}else{
						OUT_C(*s++);
					}
				}
			}
		}
	}

	OUT_C(0);

exit:
	return str-buf;
}
