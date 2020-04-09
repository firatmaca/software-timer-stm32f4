#ifndef _EMBEDDED_TIMER_H
#define _EMBEDDED_TIMER_H


typedef struct _timer_t
{
    int value;
    int timeout_value;
    int is_timeout;
}timer_t;


void timer_ctor(timer_t* timer);


int timer_set_timeout(timer_t* timer, int timo);


int timer_is_timeout(timer_t* timer);


int timer_reset(timer_t* timer);


int timer_inc(timer_t* timer, int inc_val);




#endif
