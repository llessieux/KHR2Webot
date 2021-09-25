/*
 * File:         khr2.c
 * Date:         October 30th, 2006
 * Description:  Reading a CSV file, interpoling for the first position, 
 *               getting servos positions, and then playing the CSV file.
 *               CSV files are motion files used to control the real 
 *               Hoap-2 robot.
 * Author:       Laurent Lessieux
 *
 * Copyright (c) 2006 Cyberbotics - www.cyberbotics.com
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "rcb3_simulator.h"
#include "KHR2_Interface.h"

rcb3_simulator simulator;
KHR2_Interface *m_interface;

class MyApp:public wxApp {
  public:
    virtual bool OnInit() {
        wxgui_main();

        return true;
    } 

  private:
    void wxgui_main();    

    DECLARE_EVENT_TABLE()
};

IMPLEMENT_APP_CONSOLE(MyApp)
    BEGIN_EVENT_TABLE(MyApp, wxApp)
    END_EVENT_TABLE()

char *motion_files[] = {
    "2HV001RC_Walk_Forward.RCB",
    "2HV002RC_Step_Back.RCB",
    "2HV003RC_Walk_Left_Diag.RCB",
    "2HV004RC_Walk_Right_Diag.RCB",
    "2HV005RC_Side_Step_Left.RCB",
    "2HV006RC_Side_Step_Right.RCB",
    "2HV007RC_Turn_Left.RCB",
    "2HV008RC_Turn_Right.RCB",
    "2HV009AC_Standup_based_on_sensor.RCB",
    "2HV010RC_StandUp_Face_Down.RCB",
    "2HV011RC_Bow.RCB",
    "2HV012RC_Kick_Left.RCB",
    "2HV013RC_Kick_Right.RCB",
    "2HV014RC_Wheel_Front.RCB",
    "2HV015RC_Wheel_Back.RCB",
    "2HV016RC_Wheel_Left.RCB",
    "2HV017RC_Wheel_Right.RCB",
    "2HV018RC_PushUps.RCB",
    "2HV019RC_Punch_Right.RCB",
    "2HV020RC_Punch_Left.RCB",
    "2HV021RC_Free_all.RCB",
    "2HV022RC_Happy.RCB",
    "2HV023RC_Unhappy.RCB",
    "2HV024RC_Startup2.RCB",
    NULL
};


static void reset(void)
{
    simulator.init();
}

static int run(int ms)
{
    simulator.run();
    m_interface->Refresh();
    return ms;
}

void MyApp::wxgui_main()
{
    m_interface = new KHR2_Interface();
    simulator.SetInterface(m_interface);

    SetTopWindow(m_interface->GetWindow());

    for(int i=0;i<24;i++)
        simulator.load_motion(motion_files[i],i);

    simulator.load_scenario("demo_all.rcb",0);
    //simulator.load_motion("2HV000_StartupMotion.RCB",79);
    robot_live(reset);

    /* We wait a little bit before starting. */
    robot_step(1500);

    simulator.play_motion(23);
    simulator.play_motion(17);
    simulator.play_motion(22);
    simulator.play_motion(13);

    robot_run(run);
}
