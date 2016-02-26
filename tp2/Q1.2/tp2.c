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

TaskType id;
//DeclareTask(task0);
DeclareTask(task1);
DeclareAlarm(aT1);
DeclareCounter(SystemCounter);

/*TASK(task0)
{
    display_string("Bjr activ T1 !!\n");
    display_update();
    SetAbsAlarm(aT1,1,1000);
    TerminateTask();
} */

TASK(task1)
{
    GetTaskID(&id);
    display_string("Tache ID :");
    display_int(id,1);
    display_string("\n");
    display_string("Temps systeme :");
    display_int(systick_get_ms(),1);
    display_string("\n");
    display_update();
    TerminateTask();
    //ChainTask(task1);
}

ISR(isr_button_start)
{
    ecrobot_status_monitor("isr_button_start");
    
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
