/**
 * @file tp3.c
 *
 * @section desc File description
 *
 *
 * @section copyright Copyright
 *
 *
 * @section infos File informations
 *
 * $Date$ mar. févr. 23 08:20:28 CET 2016
 * $Rev$
 * $Author$ 15009357
 * $URL$ /private/student/7/57/15009357/tp3
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


DeclareTask(task0);
DeclareTask(task1);
DeclareTask(task2);
DeclareAlarm(aT0);
DeclareAlarm(aT1);
DeclareAlarm(aT2);
DeclareCounter(SystemCounter);
DeclareResource(distance);
TaskType id;
int next = 0;
U32 dist;

TASK(task0)
{
    // display_string("Tache 0");
    if(ecrobot_get_touch_sensor(NXT_PORT_S1) > 0){
        // TODO : proteger la variable dist
        GetResource(distance);
        dist = 0;
        ReleaseResource(distance);
    }
    display_string("\n");
    display_update();
    TerminateTask();
}

TASK(task1)
{
    ecrobot_init_sonar_sensor(NXT_PORT_S2);
    GetResource(distance);
    dist = ecrobot_get_sonar_sensor(NXT_PORT_S2);
    display_int(dist,1);
    display_string("\n");
    display_update();
    ecrobot_term_sonar_sensor(NXT_PORT_S2);
    ReleaseResource(distance);
    TerminateTask(); 
}

TASK(task2)
{   
    GetResource(distance);
    if(dist == 0){
        ecrobot_set_motor_speed(NXT_PORT_A,0);
        ecrobot_set_motor_speed(NXT_PORT_B,0);
    }
    else if(dist > 0){
        ecrobot_set_motor_speed(NXT_PORT_A,50);
        ecrobot_set_motor_speed(NXT_PORT_B,50);

    }
    ReleaseResource(distance);
    TerminateTask();
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

/* End of file tp3.c */
