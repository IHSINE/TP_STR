/**
 * @file tp2.c
 *
 * @section desc File description
 *
 *
 * @section copyright Copyright
 *
 *
 * @section infos File informations
 *
 * $Date$ lun. févr.  8 17:13:36 CET 2016
 * $Rev$
 * $Author$ 15009357
 * $URL$ /private/student/7/57/15009357/tp2
 */

#include "tpl_os.h"
#include "nxt_motors.h"
#include "ecrobot_interface.h" 
#include "ecrobot_private.h"

FUNC(int, OS_APPL_CODE) main(void)
{   
    StartOS(OSDEFAULTAPPMODE);
    ShutdownOS(E_OK);
    return 0;
}


//DeclareTask(task0);
DeclareTask(task0);
DeclareTask(task1);
DeclareTask(task2);
DeclareTask(task3);
DeclareAlarm(aT1);
DeclareAlarm(aT2);
DeclareAlarm(aT3);
DeclareCounter(SystemCounter);
DeclareEvent(ev_shutdown);
TaskType id;
int next = 0;

TASK(task0)
{
    display_string("Time:");
    display_int(systick_get_ms(),1);
    display_string("\n");
    display_update();
    TerminateTask();
}

TASK(task1)
{
    display_goto_xy(0,0);
    display_string("Touch:");
    display_int(ecrobot_get_sound_sensor(1),1);
    display_string("\n");
    display_update();
    TerminateTask();
}

TASK(task2)
{   
    ecrobot_init_sonar_sensor(2); 
    display_string("Sonar:");
    display_int(ecrobot_get_sonar_sensor(2),1);
    display_string("\n");
    display_update();
    ecrobot_term_sonar_sensor(2);
    TerminateTask();
}

TASK(task3)
{   
    //attendre l'évenement 
    WaitEvent(ev_shutdown);
    //annule les alarmes qui ont été défini
    CancelAlarm(aT1);
    CancelAlarm(aT2);
    CancelAlarm(aT3);
    //effacerl'événement pour le réutiliser
    ClearEvent(ev_shutdown);
    TerminateTask();
}

ISR(isr_button_start)
{
    ecrobot_status_monitor("isr_button_start");
    //lancer l'evenement
    SetEvent(task3,ev_shutdown);    
}

ISR(isr_button_stop)
{
    ShutdownOS(E_OK);
}

ISR(isr_button_left)
{
    ecrobot_status_monitor("isr_button_left"); 

}

ISR(isr_button_right)
{
    ecrobot_status_monitor("isr_button_right");   

}

/* End of file tp2.c */
