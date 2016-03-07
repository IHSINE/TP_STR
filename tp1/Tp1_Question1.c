/**
 * @file Tp1.c
 *
 * @section desc File description
 *
 *
 * @section copyright Copyright
 *
 *
 * @section infos File informations
 *
 * $Date$ mar. janv. 26 08:15:55 CET 2016
 * $Rev$
 * $Author$ 15009357
 * $URL$ /private/student/7/57/15009357/Tp1
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

DeclareTask(task1);

// Question 1
TASK(task1)
{
    TaskType id;
    //ecrobot_status_monitor("NXT task1!");
    GetTaskID(&id);
    display_int(id,1);
    display_update();
    display_string("Bonjour!!\n");
    display_update();
    TerminateTask();
    //ChainTask(task1);
}

PreTaskHook()
{
    TaskType id;
    //ecrobot_status_monitor("NXT task1!");
    GetTaskID(&id);
    display_int(id,1);
    display_update();
 	display_string("Debut de la tache\n");
    display_update();
}

PostTaskHook()
{
    display_string("Fin de la tache\n");
    display_update();
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

/* End of file Tp1.c */
