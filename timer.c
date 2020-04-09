#include "timer.h"
#include "stm32f4xx.h"               

void timer_ctor(timer_t* timer)
{
	timer->is_timeout=0;
	timer->timeout_value=0;
	timer->value=0;	
}

int timer_set_timeout(timer_t* timer, int timo)
{
    timer->timeout_value = timo;
}

int timer_is_timeout(timer_t* timer)
{	
	return timer->is_timeout;
}

int timer_reset(timer_t* timer)
{
	timer->is_timeout=0;
	timer->value=0;
	return 0;
}

int timer_inc(timer_t* timer, int inc_val)
{
    if(timer->value < timer->timeout_value)
    {
        timer->value += inc_val;

        if(timer->value >= timer->timeout_value)
        {
            timer->is_timeout = 1;
        }
    }

    return 0;
 }
