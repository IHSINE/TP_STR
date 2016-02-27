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
#include <stdlib.h>

FUNC(int, OS_APPL_CODE) main(void)
{   
    StartOS(OSDEFAULTAPPMODE);
    ShutdownOS(E_OK);
    return 0;
}


DeclareTask(sonar);
DeclareTask(touch);
DeclareTask(move);
DeclareAlarm(aT0);
DeclareAlarm(aT1);
DeclareAlarm(aT2);
DeclareCounter(SystemCounter);
DeclareResource(distance);
U32 dist = 1;
int in = 0;
int r = 0;

TASK(touch)
{
    if(ecrobot_get_touch_sensor(NXT_PORT_S1) == 1 || ecrobot_get_touch_sensor(NXT_PORT_S3) == 1 ){
        GetResource(distance);
        dist = 0;
        ReleaseResource(distance);
    }
    display_string("\n");
    display_update();
    //SetAbsAlarm(aT1,1,100);
    TerminateTask();
}

TASK(sonar)
{
    GetResource(distance);
    dist = ecrobot_get_sonar_sensor(NXT_PORT_S2);
    ReleaseResource(distance);
    /* display_int(dist,4);
       display_string("\n");
       display_update();
       SetAbsAlarm(aT1,1,100);*/
    TerminateTask(); 
}

TASK(move)
{

    if(dist == 0){
        ecrobot_set_motor_speed(NXT_PORT_A, -100);
        ecrobot_set_motor_speed(NXT_PORT_B, -100);
    }
    else if(dist < 50){
        ecrobot_set_motor_speed(NXT_PORT_A, 50);
        ecrobot_set_motor_speed(NXT_PORT_B, -50);
    }else{
        if (in >= 10) {
            r = rand() % 100;
            ecrobot_set_motor_speed(NXT_PORT_A, r);
            ecrobot_set_motor_speed(NXT_PORT_B, -r);  
            in = 0;        
        }
        else {
            ecrobot_set_motor_speed(NXT_PORT_A, 50);
            ecrobot_set_motor_speed(NXT_PORT_B, 50);           
        }

    }
    in++;
    /*display_goto_xy(0, 0);
    display_int(in,4);
    display_update();*/
    TerminateTask();
}

void StartupHook(void){
    ecrobot_init_sonar_sensor(NXT_PORT_S2);
}

void ShutdownHook(void){
    ecrobot_term_sonar_sensor(NXT_PORT_S2);
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
