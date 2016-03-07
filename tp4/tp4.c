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

DeclareTask(task0);
DeclareTask(task1);
DeclareResource(res);
DeclareAlarm(aT1);
DeclareAlarm(aT2);
DeclareCounter(SystemCounter);
DeclareResource(res);
DeclareAlarm(ev1);

int dist = 0;

TASK(task0)
{
    //ecrobot_init_sonar_sensor( NXT_PORT_S2 ); 
    ecrobot_set_motor_speed(NXT_PORT_A , 10);
    ecrobot_set_motor_speed(NXT_PORT_B , 10);
    GetResource(res);
    dist = ecrobot_get_sonar_sensor( NXT_PORT_S2 );    
    if (dist<20)
    {
    	 SetEvent(task1,ev1);
    }
    ReleaseResource(res);
    //ecrobot_term_sonar_sensor( NXT_PORT_S2 );
    TerminateTask();
  


}
TASK(task1)
{   
	WaitEvent(ev1);
	GetResource(res);
    while (dist<20)
    {
        ecrobot_set_motor_speed(NXT_PORT_A , 10);
        ecrobot_set_motor_speed(NXT_PORT_B , 0);
        dist = ecrobot_get_sonar_sensor( NXT_PORT_S2 ); 
	}
    ReleaseResource(res);
}

void StartupHook(void){
    ecrobot_init_sonar_sensor(NXT_PORT_S2);
}

void ShutdownHook(void){
    ecrobot_term_sonar_sensor(NXT_PORT_S2);
}


ISR(isr_button_start)
{
    
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
