#ifndef CLOCK_H
#define CLOCK_H

/*
 * 現在時刻をもとに挨拶文字列を返す。
 *   0〜11時 : "Good morning"
 *  12〜17時 : "Good afternoon"
 *  18〜23時 : "Good evening"
 */
const char *clock_get_greeting(void);

#endif /* CLOCK_H */
