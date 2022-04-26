#include "pxt.h"

using namespace pxt;
namespace ABTCarIR { 
int ir_code = 0x00;//数据码
int ir_addr = 0x00;//地址码
int uir_code = 0x00;//数据码反码
int uir_addr = 0x00;//地址码反码
int data;

int logic_value(){//根据频率的时长 判断逻辑值"0"和"1"子函数
    uint32_t lasttime = system_timer_current_time_us();
    uint32_t nowtime;
    while(!uBit.io.P5.getDigitalValue());//低等待
    nowtime = system_timer_current_time_us();
    if((nowtime - lasttime) > 400 && (nowtime - lasttime) < 700){//遥控上高频率对应低电平560us 因为有上拉电阻
        while(uBit.io.P5.getDigitalValue());//是高就等待
        lasttime = system_timer_current_time_us();
        if((lasttime - nowtime)>400 && (lasttime - nowtime) < 700){//遥控上低频率接着高电平560us 因为有上拉电阻
            return 0;
        }else if((lasttime - nowtime)>1500 && (lasttime - nowtime) < 1800){//遥控上低频率接着高电平1.7ms 因为有上拉电阻
            return 1;
       }
    }//低电平不是560us 所以发送的不是0 1
}


void pulse_deal(){//解析收到遥控器编码
    int i;
    ir_addr=0x00;//地址码清零
    //存入地址码
    for(i=0; i<8;i++ )
    {
      if(logic_value() == 1)
      {
        ir_addr |=(1<<i);
      }
    }
    uir_addr=0x00;//清零
    //存入地址码反码
    for(i=0; i<8;i++ )
    {
      if(logic_value() == 1)
      {
        uir_addr |=(1<<i);
      }
    }
    //解析遥控器编码数据码
    ir_code=0x00;//清零
    for(i=0; i<8;i++ )
    {
      if(logic_value() == 1)
      {
        ir_code |=(1<<i);
      }
    }
    
    //解析遥控器编码数据码反码
    uir_code=0x00;//清零
    for(i=0; i<8;i++ )
    {
      if(logic_value() == 1)
      {
        uir_code |=(1<<i);
      }
    }

}

void remote_decode(void){
    data = 0x00;
    uint32_t lasttime = system_timer_current_time_us();
    uint32_t nowtime;
    while(uBit.io.P5.getDigitalValue()){//高电平等待
        nowtime = system_timer_current_time_us();
        if((nowtime - lasttime) > 100000){//超过100 ms,表明此时没有按键按下
            ir_code = 0x00;
        }
    }
    //如果高电平持续时间不超过100ms
    lasttime = system_timer_current_time_us();
    while(!uBit.io.P5.getDigitalValue());//低等待
    nowtime = system_timer_current_time_us();
    if((nowtime - lasttime) < 10000 && (nowtime - lasttime) > 8000){//引导码高电平9ms
        while(uBit.io.P5.getDigitalValue());//高等待
        lasttime = system_timer_current_time_us();
        if((lasttime - nowtime) > 4000 && (lasttime - nowtime) < 5000){//引导码低电平4.5ms,接收到了红外协议头且是新发送的数据。开始解析逻辑0和1
            pulse_deal();
            if((ir_code+uir_code==0xff)&&(ir_addr+uir_addr==0xff)){
                data = ir_code;//ir_code;
                //uBit.serial.printf("addr=0x%X,code = 0x%X\r\n",ir_addr,ir_code);
            }else{
                data = 0x00;
            }
        }else if((lasttime - nowtime) > 2000 && (lasttime - nowtime) < 2500){//2.25ms,表示发的跟上一个包一致
            while(!uBit.io.P5.getDigitalValue());//低等待
            nowtime = system_timer_current_time_us();
            if((nowtime - lasttime) > 500 && (nowtime - lasttime) < 700){//560us
                //uBit.serial.printf("addr=0x%X,code = 0x%X\r\n",ir_addr,ir_code);
                data = ir_code;//ir_code;i
            }
        }
    }
}

 //% 
    int irCode(){
    remote_decode();
    return data;
    }
}