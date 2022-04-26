
/**
* ABTCar 阿斑兔实战项目
* 定义块链接：https://makecode.com/defining-blocks
* 颜色参考链接：http://xh.5156edu.com/page/z1015m9220j18754.html
*/
//% color=#ee0e3d weight=20 icon="\uf1b9" block="ABTCar"
//% groups=['ABT_display','ABT_music','ABT_sensor','ABT_Handle','ABT_electricmachinery','ABT_CarControl']
namespace ABTCar {
    //灯光显示 
    let yahStrip: neopixel.Strip;
    /**
     * 七彩灯
     */
    
    //%  block="七彩流光灯"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_display"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    export function RGB_Car_Program(): neopixel.Strip {

        if (!yahStrip) {
            yahStrip = neopixel.create(DigitalPin.P8, 4, NeoPixelMode.RGB);
        }
        return yahStrip;
    }

    export enum ABT_color {
        //% blockId="OFF" block="灭"
        OFF,
        //% blockId="Red" block="红色" 
        Red,
        //% blockId="Green" block="绿色"
        Green,
        //% blockId="Blue" block="蓝色"
        Blue,
        //% blockId="White" block="白色"	//蓝+绿+红
        White,
        //% blockId="Cyan" block="青色"	    //蓝+绿
        Cyan,
        //% blockId="Pinkish" block="品红"  //蓝+红
        Pinkish,
        //% blockId="Yellow" block="黄色"   //红+绿
        Yellow
    }
    export enum ABT_LED {

        //% blockId="OFF" block="灭"
        OFF = 0,
        //% blockId="ON" block="亮"
        ON = 1
    }
    export enum ABT_LED1 {

        //% blockId="left" block="左灯"
        left = 0,
        //% blockId="right" block="右灯"
        right = 1,
        //% blockId="all" block="全部"
        all = 2
    }
    /**
     * 控制引脚灯亮灭
     */
    //% blockId=ABT_LED0 block="LED1|pin %pin|value %value"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_display"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=1
    export function LED1(pin: DigitalPin, value: ABT_LED): void {
        pins.digitalWritePin(pin, value);
    }

    /**
     * 控制引脚灯亮度
     */
    //% blockId=ABT_LED1 block="LED2|pin %pin|value %value"
    //% weight=4
    //% blockGap=8
    //% color="#ee0e3d"
    //% value.min=0 value.max=255
    //% group="ABT_display"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=2
    export function LED2(pin: AnalogPin, value: number): void {
        pins.analogWritePin(pin, value * 1024 / 256);
    }

    /**
     * 呼吸灯
     */
    //% blockId=ABT_BreathLED block="BreathLED|pin %pin"
    //% weight=3
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_display"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=3
    export function BreathLED(pin: AnalogPin): void {
        for (let i: number = 0; i < 1023; i++) {
            pins.analogWritePin(pin, i);
            //basic.pause(1);
            control.waitMicros(1000);
        }
        basic.pause(10);
        for (let i: number = 1023; i > 0; i--) {
            pins.analogWritePin(pin, i);
            //basic.pause(1);
            control.waitMicros(1000);
        }
    }

    /**
     * 控制灯的颜色亮度
     */
    //% blockId=ABT_RGB block="RGB|pin1 %pin1|value1 %value1|pin2 %pin2|value2 %value2|pin3 %pin3|value3 %value3"
    //% weight=2
    //% blockGap=8
    //% color="#ee0e3d"
    //% value1.min=0 value1.max=255 value2.min=0 value2.max=255 value3.min=0 value3.max=255
    //% group="ABT_display"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    export function RGB(pin1: AnalogPin, value1: number, pin2: AnalogPin, value2: number, pin3: AnalogPin, value3: number): void {
        pins.analogWritePin(pin1, value1 * 1024 / 256);
        pins.analogWritePin(pin2, value2 * 1024 / 256);
        pins.analogWritePin(pin3, value3 * 1024 / 256);
    }

    /**
     * 控制灯的颜色
     */
    //% blockId=ABT_RGB1 block="RGB|pin1 %pin1|pin2 %pin2|pin3 %pin3|value %value"
    //% weight=1
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_display"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=5
    export function RGB1(pin1: DigitalPin, pin2: DigitalPin, pin3: DigitalPin, value: ABT_color): void {
        switch (value) {
            case ABT_color.OFF: {
                pins.digitalWritePin(pin1, 0);
                pins.digitalWritePin(pin2, 0);
                pins.digitalWritePin(pin3, 0);
            }; break;
            case ABT_color.Red: {
                pins.digitalWritePin(pin1, 1);
                pins.digitalWritePin(pin2, 0);
                pins.digitalWritePin(pin3, 0);
            }; break;
            case ABT_color.Green: {
                pins.digitalWritePin(pin1, 0);
                pins.digitalWritePin(pin2, 1);
                pins.digitalWritePin(pin3, 0);
            }; break;
            case ABT_color.Blue: {
                pins.digitalWritePin(pin1, 0);
                pins.digitalWritePin(pin2, 0);
                pins.digitalWritePin(pin3, 1);
            }; break;
            case ABT_color.White: {
                pins.digitalWritePin(pin1, 1);
                pins.digitalWritePin(pin2, 1);
                pins.digitalWritePin(pin3, 1);
            }; break;
            case ABT_color.Cyan: {
                pins.digitalWritePin(pin1, 0);
                pins.digitalWritePin(pin2, 1);
                pins.digitalWritePin(pin3, 1);
            }; break;
            case ABT_color.Pinkish: {
                pins.digitalWritePin(pin1, 1);
                pins.digitalWritePin(pin2, 0);
                pins.digitalWritePin(pin3, 1);
            }; break;
            case ABT_color.Yellow: {
                pins.digitalWritePin(pin1, 1);
                pins.digitalWritePin(pin2, 1);
                pins.digitalWritePin(pin3, 0);
            }; break;
        }
    }

    //音乐
    export enum ABTBuzzer {
        //% blockId="noring" block="不响"
        noring = 0,
        //% blockId="ring" block="响"
        ring
    }
    /**
     * 控制蜂鸣器的开关
     */
    //% blockId=ABT_Buzzer block="Buzzer|pin %pin|value %value"
    //% weight=96
    //% blockGap=8
    //% group="ABT_music"
    //% value.min=0 value.max=1
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=8
    export function Buzzer(pin: DigitalPin, value: ABTBuzzer): void {
        pins.setPull(pin, PinPullMode.PullNone);
        pins.digitalWritePin(pin, value);
    }

    export enum ABTMusic {
        //% blockId="dadadum" block="dadadum"
        dadadum = 0,
        //% blockId="entertainer" block="entertainer"
        entertainer,
        //% blockId="prelude" block="prelude"
        prelude,
        //% blockId="ode" block="ode"
        ode,
        //% blockId="nyan" block="nyan"
        nyan,
        //% blockId="ringtone" block="ringtone"
        ringtone,
        //% blockId="funk" block="funk"
        funk,
        //% blockId="blues" block="blues"
        blues,
        //% blockId="birthday" block="birthday"
        birthday,
        //% blockId="wedding" block="wedding"
        wedding,
        //% blockId="funereal" block="funereal"
        funereal,
        //% blockId="punchline" block="punchline"
        punchline,
        //% blockId="baddy" block="baddy"
        baddy,
        //% blockId="chase" block="chase"
        chase,
        //% blockId="ba_ding" block="ba_ding"
        ba_ding,
        //% blockId="wawawawaa" block="wawawawaa"
        wawawawaa,
        //% blockId="jump_up" block="jump_up"
        jump_up,
        //% blockId="jump_down" block="jump_down"
        jump_down,
        //% blockId="power_up" block="power_up"
        power_up,
        //% blockId="power_down" block="power_down"
        power_down
    }

    /**
     * 播放音乐
     */
    //% blockId=ABT_Music block="Music|%index|"
    //% weight=96
    //% blockGap=8
    //% group="ABT_music"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=6
    export function Music(mc: ABTMusic): void {
        switch (mc) {
            case ABTMusic.dadadum: music.beginMelody(music.builtInMelody(Melodies.Dadadadum), MelodyOptions.Once); break;
            case ABTMusic.birthday: music.beginMelody(music.builtInMelody(Melodies.Birthday), MelodyOptions.Once); break;
            case ABTMusic.entertainer: music.beginMelody(music.builtInMelody(Melodies.Entertainer), MelodyOptions.Once); break;
            case ABTMusic.prelude: music.beginMelody(music.builtInMelody(Melodies.Prelude), MelodyOptions.Once); break;
            case ABTMusic.ode: music.beginMelody(music.builtInMelody(Melodies.Ode), MelodyOptions.Once); break;
            case ABTMusic.nyan: music.beginMelody(music.builtInMelody(Melodies.Nyan), MelodyOptions.Once); break;
            case ABTMusic.ringtone: music.beginMelody(music.builtInMelody(Melodies.Ringtone), MelodyOptions.Once); break;
            case ABTMusic.funk: music.beginMelody(music.builtInMelody(Melodies.Funk), MelodyOptions.Once); break;
            case ABTMusic.blues: music.beginMelody(music.builtInMelody(Melodies.Blues), MelodyOptions.Once); break;
            case ABTMusic.wedding: music.beginMelody(music.builtInMelody(Melodies.Wedding), MelodyOptions.Once); break;
            case ABTMusic.funereal: music.beginMelody(music.builtInMelody(Melodies.Funeral), MelodyOptions.Once); break;
            case ABTMusic.punchline: music.beginMelody(music.builtInMelody(Melodies.Punchline), MelodyOptions.Once); break;
            case ABTMusic.baddy: music.beginMelody(music.builtInMelody(Melodies.Baddy), MelodyOptions.Once); break;
            case ABTMusic.chase: music.beginMelody(music.builtInMelody(Melodies.Chase), MelodyOptions.Once); break;
            case ABTMusic.ba_ding: music.beginMelody(music.builtInMelody(Melodies.BaDing), MelodyOptions.Once); break;
            case ABTMusic.wawawawaa: music.beginMelody(music.builtInMelody(Melodies.Wawawawaa), MelodyOptions.Once); break;
            case ABTMusic.jump_up: music.beginMelody(music.builtInMelody(Melodies.JumpUp), MelodyOptions.Once); break;
            case ABTMusic.jump_down: music.beginMelody(music.builtInMelody(Melodies.JumpDown), MelodyOptions.Once); break;
            case ABTMusic.power_up: music.beginMelody(music.builtInMelody(Melodies.PowerUp), MelodyOptions.Once); break;
            case ABTMusic.power_down: music.beginMelody(music.builtInMelody(Melodies.PowerDown), MelodyOptions.Once); break;
        }
    }

    //传感器
    /**
     * 声音传感器 判断是否有声音
     */
    export enum ABTVoice {
        //% blockId="Voice" block="有声音"
        Voice = 0,
        //% blockId="NoVoice" block="无声音"
        NoVoice = 1
    }
    //% blockId=ABT_Voice_Sensor block="Voice_Sensor|pin %pin|value %value"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_sensor"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=7
    export function Voice_Sensor(pin: DigitalPin, value: ABTVoice): boolean {
        pins.setPull(pin, PinPullMode.PullUp);
        if (pins.digitalReadPin(pin) == value) {
            return true;
        }
        else {
            return false;
        }
    }
   

    /**
     * 声音传感器 返回声音大小
     */
    
    //% blockId=ABT_Voice_Sound block="Sound|pin %pin"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_sensor"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=7
    export function Sound(pin: AnalogPin): number {
        let value: number;
        value = pins.analogReadPin(pin);
        return value;
    }

    /**
     * 光敏传感器 返回监测到的亮度
     */
    //% blockId=ABT_Sensor_Light block="Light|pin %pin"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_sensor"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=7
    export function Light(pin: AnalogPin): number {
        let value: number;
        value = pins.analogReadPin(pin);
        return value;
    }

 
    export enum ABTsensor {
        //% blockId="MicroSeconds" block="μs"
        MicroSeconds = 0,
        //% blockId="Centimeters" block="cm"
        Centimeters,
        //% blockId="inches" block="inches"
        Inches
    }
     /**
     * 超声波传感器
     */
    //% blockId=ABT_ping block="ABT_ping sendout %sendout|receive %receive|distanceunit %distanceunit"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_sensor"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=8
    export function ping(sendout: DigitalPin, receive: DigitalPin, distanceunit: ABTsensor): number {
        // send pulse
        pins.setPull(sendout, PinPullMode.PullNone);
        pins.digitalWritePin(sendout, 0);
        control.waitMicros(2);
        pins.digitalWritePin(sendout, 1);
        control.waitMicros(10);
        pins.digitalWritePin(sendout, 0);
        // read pulse
        const d = pins.pulseIn(receive, PulseValue.High, 50000);
        switch (distanceunit) {
            case ABTsensor.Centimeters: return Math.idiv(d, 58);//340m每秒*1/2T
            case ABTsensor.Inches: return Math.idiv(d, 148);
            default: return d;
        }
    }


    export enum ABTIR {
        //% blockId="test" block="检测到"
        testing = 0,
        //% blockId="Note" block="未检测"
        Notesting = 1
    }
    function IR_send_38k() {
        for (let i: number = 0; i < 8; i++) {
            pins.digitalWritePin(DigitalPin.P1, 1);
            control.waitMicros(13);
            pins.digitalWritePin(DigitalPin.P1, 0);
            control.waitMicros(13);
        }
    }
    /**
     * 红外传感器检查是否接收返回信号
     */
    //% blockId=ABT_IR_Sensor block="IR_Sensor|pin %pin|or %value|障碍物"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_sensor"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    export function IR_Sensor(pin: DigitalPin, value: ABTIR): boolean {
        pins.setPull(pin, PinPullMode.PullUp);
        //IR_send_38k();
        if (pins.digitalReadPin(pin) == value) {
            return true;
        }
        else {
            return false;
        }
    }
    /**
     * 红外传感器 发送红外信号
     */
    //% blockId=ABT_IR_Send block="IR_Send"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_sensor"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    export function IR_Send(): void {
        IR_send_38k();
    }

    /**
     * 震动传感器 摇动时触发
     */
    //% blockId=ABT_Sensor_Vibration block="Vibration|pin %pin|get "
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_sensor"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    export function Vibration(pin: DigitalPin, handle: () => void): void {
        let Pin = 0;
        pins.setPull(pin, PinPullMode.PullUp);
        // pins.setEvents(pin, PinEventType.Pulse);
        // pins.onPulsed(pin, PulseValue.High, handle);
        pins.setEvents(pin, PinEventType.Edge);
        control.onEvent(pin, DAL.MICROBIT_PIN_EVT_FALL, handle);
    }
    /**
     * 霍尔传感器 磁铁靠近时触发
     */
    
    //% blockId=ABT_Sensor_Hall block="Hall|pin %pin|get "
     //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_sensor"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=4
    export function Hall(pin: DigitalPin, handle: () => void): void {
        pins.setPull(pin, PinPullMode.PullUp);
        // pins.setEvents(pin, PinEventType.Pulse);
        // pins.onPulsed(pin, PulseValue.High, handle);
        pins.setEvents(pin, PinEventType.Edge);
        control.onEvent(pin, DAL.MICROBIT_PIN_EVT_FALL, handle);

    }



    //手柄
    export enum ABT_Key {
        //% blockId="key_A" block="A"
        key_A = DigitalPin.P5,
        //% blockId="key_B" block="B"
        key_B = DigitalPin.P11,
        //% blockId="key_C" block="C"
        key_C = DigitalPin.P13,
        //% blockId="key_D" block="D"
        key_D = DigitalPin.P14,
        //% blockId="key_L" block="L"
        key_L = DigitalPin.P15,
        //% blockId="key_R" block="R"
        key_R = DigitalPin.P16,
    }
    export enum ABT_KeyState {
        //% block="按下"
        click = 0,
        //% block="松开"
        pressed = 1
    }
    /**
     * 判断是否按键按下
     */
    //% blockId=ABT_Button block="Button|key %key|value %value"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_Handle"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=5
    export function Button(key: ABT_Key, value: ABT_KeyState): boolean {
        let pin = <DigitalPin><number>key;
        pins.setPull(pin, PinPullMode.PullUp);
        if (pins.digitalReadPin(pin) == value) {
            return true;
        }
        else {
            return false;
        }

    }
    export enum ABT_Key2 {
        //% blockId="key_A1" block="A"
        key_A1 = DAL.MICROBIT_ID_IO_P5,
        //% blockId="key_B1" block="B"
        key_B1 = DAL.MICROBIT_ID_IO_P11,
        //% blockId="key_C1" block="C"
        key_C1 = DAL.MICROBIT_ID_IO_P13,
        //% blockId="key_D1" block="D"
        key_D1 = DAL.MICROBIT_ID_IO_P14,
        //% blockId="key_L1" block="L"
        key_L1 = DAL.MICROBIT_ID_IO_P15,
        //% blockId="key_R1" block="R"
        key_R1 = DAL.MICROBIT_ID_IO_P16,
    }
    export enum ABT_KeyState2 {
        //% blockId="click" block="点击"
        click = DAL.MICROBIT_BUTTON_EVT_CLICK,
        //% blockId="pressed" block="摁下"
        pressed = DAL.MICROBIT_BUTTON_EVT_DOWN,
        //% blockId="released" block="松开"
        released = DAL.MICROBIT_BUTTON_EVT_UP,
    }
    let posi_init = 0;

    function InitialPosition(): void {
        posi_init = 1;
        return;
    }

    //% shim=ABTCar::init
    function init(): void {
        return;
    }
     /**
     * 当按键按下松开点击发生什么
     */
    //% blockId=ABT_OnKey1
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_Handle"
    //% block="on key %key| is %keyEvent"
    export function OnKey1(key: ABT_Key2, keyEvent: ABT_KeyState2, handler: Action) {
        if (!posi_init) {
            InitialPosition();
        }
        init();
        control.onEvent(<number>key, <number>keyEvent, handler); // register handler
    }
     /**
     * 判断是否按键按下
     */
    //% blockId=ABT_KeyPressed1
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_Handle"
    //% block="key %key| is pressed"
    export function KeyPressed1(key: ABT_Key2): boolean {
        const pin = <DigitalPin><number>key;
        pins.setPull(pin, PinPullMode.PullUp);
        return pins.digitalReadPin(<DigitalPin><number>key) == 0;
    }

    export enum ABTHandle {
        //% blockId="UpLeft" block="左转"
        UpLeft = 0,
        //% blockId="Up" block="↑前进"
        Up,
        //% blockId="UpRight" block="右转"
        UpRight,
        //% blockId="Left" block="←原地左转"
        Left,
        //% blockId="Middle" block="无"
        Middle,
        //% blockId="Right" block="→原地右转"
        Right,
        //% blockId="LowerLeft" block="后左转"
        LowerLeft,
        //% blockId="Down" block="↓后退"
        Down,
        //% blockId="LowerRight" block="后右转"
        LowerRight
    }

    const x0 = 517;
    const y0 = 520;
    const z0 = 240;
     /**
     * 控制手柄的上下左右斜向操作
     */
    //% blockId=ABT_ABTHandleControl 
    //% block="Handle_Control %direction|"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_Handle"
    export function ABTHandleControl(direction: ABTHandle): boolean {
        let x = pins.analogReadPin(AnalogPin.P1) - x0;
        let y = pins.analogReadPin(AnalogPin.P2) - y0;
        let z = Math.round(Math.sqrt(Math.abs(x * x) + Math.abs(y * y)));
        const value1 = Math.round(z * 0.38);//360/8=45 sin22.5 cos67.5
        const value2 = Math.round(z * 0.92);
        let getPosition = ABTHandle.Middle;
        if (z > z0) {
            if (x > 0 && y > 0) {
                if (y < value1) {
                    getPosition = ABTHandle.Right;
                } else if (y > value2) {
                    getPosition = ABTHandle.Up;
                } else {
                    getPosition = ABTHandle.UpRight;
                }
            }
            else if (x > 0 && y < 0) {
                if (x < value1) {
                    getPosition = ABTHandle.Down;
                } else if (x > value2) {
                    getPosition = ABTHandle.Right;
                } else {
                    getPosition = ABTHandle.LowerRight;
                }
            }
            else if (x < 0 && y > 0) {
                if (y < value1) {
                    getPosition = ABTHandle.Left;
                } else if (y > value2) {
                    getPosition = ABTHandle.Up;
                } else {
                    getPosition = ABTHandle.UpLeft;
                }
            }
            else if (x < 0 && y < 0) {
                y = Math.abs(y);
                if (y < value1) {
                    getPosition = ABTHandle.Left;
                } else if (y > value2) {
                    getPosition = ABTHandle.Down;
                } else {
                    getPosition = ABTHandle.LowerLeft;
                }
            } else {
                getPosition = ABTHandle.Middle;
            }
        }
        if (getPosition == direction) {
            return true;
        } else {
            return false;
        }
    }
    /**
    * 是否打开震动
    */
    //% blockId=ABT_shock
    //% block="vibration %shock|"
    //% shock.shadow="toggleOnOff"
    //% shock.defl="true"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_Handle"
    export function shock(shock: boolean) {
        if (shock) {
            pins.digitalWritePin(DigitalPin.P8, 1);
        } else {
            pins.digitalWritePin(DigitalPin.P8, 0);
        }
    }
     /**
     * 判断是否按键按下
     */
    //% blockId=ABT_Input_Button block="Button|pin %pin|value %value"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_Handle"
    export function Button2(pin: DigitalPin, value: ABT_KeyState): boolean {
        pins.setPull(pin, PinPullMode.PullUp);
        return pins.digitalReadPin(pin) == value;
    }


    //电机
     /**
     * 电扇灭火器
     */
    
    //% blockId=ABT_Fan block="Fan|pin %pin|speed %value"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% value.min=0 value.max=255
    //% group=ABT_electric machinery
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=9
    export function Fan(pin: AnalogPin, value: number): void {
        pins.analogWritePin(pin, Math.map(value, 0, 255, 0, 1024));
    }
    /**
     * 舵机
     */
    //% blockId=ABT_Servo block="Servo|pin %pin|value %value"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% value.min=0 value.max=180
    //% value.defl=90
    //% group=ABT_electric machinery
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=9
    export function Servo(pin: AnalogPin, value: number): void {
        pins.servoWritePin(pin, value);
    }

    /**
     * 直流电机 控制电机速度0~1024
     */
    //% blockId=ABT_MotorRun block="Motor|%pin|speed %speed"
     //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% speed.min=0 speed.max=1023
    //% group=ABT_electric machinery
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=5
    export function MotorRun(pin: AnalogPin, speed: number): void {
        pins.analogWritePin(pin, speed);
    }
    /**
     * 控制电机停止
     */
    //% blockId=ABT_MotorStop block="MotorStop |pin %pin"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group=ABT_electric machinery
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=5
    export function MotorStop(pin: AnalogPin): void {
        pins.analogWritePin(pin, 0);
    }


    //小车控制
    export enum ABTLinesensor {
        //% block="白线"
        white = 0,
        //% block="黑色"
        black,
    }
    export enum ABTKeyState {
        //% block="左边状态"
        leftstate = 0,
        //% block="右边状态"
        rightstate,
    }
    /**
     * 寻迹小车
     */
    //% blockId=ABT_LineSenor block="ABT_Lineping direct %direct|or LineC %LineC"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_CarControl"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=9
    export function LineSensor(direct: ABTKeyState, LineC: ABTLinesensor): boolean {
        let temp: boolean = false;
        pins.setPull(DigitalPin.P1, PinPullMode.PullNone);
        pins.setPull(DigitalPin.P2, PinPullMode.PullNone);
        if (direct == ABTKeyState.leftstate) {
            if (LineC == ABTLinesensor.black) {
                if (pins.analogReadPin(AnalogPin.P1) < 500) {
                    temp = true;
                }
                else {
                    temp = false;
                }
            }
            else if (LineC == ABTLinesensor.white) {
                if (pins.analogReadPin(AnalogPin.P1) < 500) {
                    temp = false;
                }
                else {
                    temp = true;
                }
            }
        }
        if (direct == ABTKeyState.rightstate) {
            if (LineC == ABTLinesensor.black) {
                if (pins.analogReadPin(AnalogPin.P2) < 500) {
                    temp = true;
                }
                else {
                    temp = false;
                }
            }
            else if (LineC == ABTLinesensor.white) {
                if (pins.analogReadPin(AnalogPin.P2) < 500) {
                    temp = false;
                }
                else {
                    temp = true;
                }
            }

        }
        return temp;
    }

    /**
     * 返回超声波距离
     */
    //% blockId=ABT_ping_Car block="ultrasonic return distance(cm)"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_CarControl"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=10
    export function ping_Car(): number {
        let list: Array<number> = [0, 0, 0, 0, 0];
        for (let i = 0; i < 5; i++) {
            pins.setPull(DigitalPin.P11, PinPullMode.PullNone);
            pins.digitalWritePin(DigitalPin.P11, 0);
            control.waitMicros(2);
            pins.digitalWritePin(DigitalPin.P11, 1);
            control.waitMicros(15);
            pins.digitalWritePin(DigitalPin.P11, 0);
            let d = pins.pulseIn(DigitalPin.P12, PulseValue.High, 50000);
            list[i] = Math.floor(d / 58);
        }
        list.sort();
        let length = (list[1] + list[2] + list[3]) / 3;
        return Math.floor(length);
    }

    /**
     * 返回声音传感器返回的声音大小
     */
    //% blockId=ABT_Voice_Sensor2 block="Voice Sensor return"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_CarControl"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=7
    export function Voice_Sensor2(): number {
        let temp = pins.analogReadPin(AnalogPin.P2);
        return temp;
    }


    export enum Controldirection {
        //%block="前进"
        forward,
        //%block="右转"
        r_forward,
        //%block="原地右转"
        right,
        //%block="后右转"
        r_backward,
        //%block="后退"
        backward,
        //%block="后左转"
        l_backward,
        //%block="原地左转"
        left,
        //%block="左转"
        l_forward,
        //%block="停止"
        stop
    }


    let L_forward = AnalogPin.P13;
    let L_backward = AnalogPin.P14;
    let R_backward = AnalogPin.P15;
    let R_forward = AnalogPin.P16;
    /**
    * 设置ABTCar的电机速度
    */
    //% blockId=move
    //% block="ABTCar: LEFT: $left \\%, FIGHT: $right \\%"
    //% left.shadow="speedPicker"
    //% right.shadow="speedPicker"
    //% group="ABT_CarControl"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    export function move(left: number, right: number) {
        if (left >= 0) {
            pins.analogWritePin(L_backward, 0);
            pins.analogWritePin(L_forward, Math.map(left, 0, 100, 0, 1023));
        } else if (left < 0) {
            pins.analogWritePin(L_backward, Math.map(Math.abs(left), 0, 100, 0, 1023));
            pins.analogWritePin(L_forward, 0);
        }
        if (right >= 0) {
            pins.analogWritePin(R_backward, 0);
            pins.analogWritePin(R_forward, Math.map(right, 0, 100, 0, 1023));
        } else if (right < 0) {
            pins.analogWritePin(R_backward, Math.map(Math.abs(right), 0, 100, 0, 1023));
            pins.analogWritePin(R_forward, 0);
        }
    }

    /**
    * ABTCar 停止
    */
    //% blockId=stop
    //% block="BitCar: stop"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_CarControl"
    export function stop() {
        pins.analogWritePin(L_backward, 0);
        pins.analogWritePin(L_forward, 0);
        pins.analogWritePin(R_backward, 0);
        pins.analogWritePin(R_forward, 0);
    }

    /**
    * 当ABTCar静止不动时，让它从地面站起来，然后停下来，如果没有这样做，尝试调整电机速度和通电时间
    */
    //% blockId=standup_still
    //% block="ABTCar: stand up with speed $speed \\% charge $charge|(ms)"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% speed.defl=100
    //% speed.min=0 speed.max=100
    //% charge.defl=250
    //% group="ABT_CarControl"
    export function standup_still(speed: number, charge: number) {
        move(-speed, -speed);
        basic.pause(200);
        move(speed, speed);
        basic.pause(charge);
        stop();
    }

    
    /**
    * ABTCar 方向运动
    */
    //% blockId=ABT_ABTCar block="ABTCar direction %direction|"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_CarControl"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=7
    export function ABTCar(direction: Controldirection) {
        switch (direction) {
            case Controldirection.forward: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, 1023);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, 1023);
            }; break;

            case Controldirection.r_forward: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, 1023);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.right: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, 1023);
                pins.analogWritePin(R_backward, 1023);
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.r_backward: {
                pins.analogWritePin(L_backward, 1023);
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.backward: {
                pins.analogWritePin(L_backward, 1023);
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 1023);
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.l_backward: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 1023);
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.left: {
                pins.analogWritePin(L_backward, 1023);
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, 1023);
            }; break;
            case Controldirection.l_forward: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, 1023);
            }; break;
            case Controldirection.stop: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, 0);
            }; break;
        }
    }
     /**
    * ABTCar 方向运动可调速
    */
    //% blockId=ABT_ABTCar1 block="ABTCar1 direction %direction|value %value|"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_CarControl"
    //%value.min=0 value.max=255
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=7
    export function ABTCar1(direction: Controldirection, value: number) {
        switch (direction) {
            case Controldirection.forward: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, Math.map(value, 0, 255, 0, 1023));
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, Math.map(value, 0, 255, 0, 1023));
            }; break;

            case Controldirection.r_forward: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, Math.map(value, 0, 255, 0, 1023));
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.right: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, Math.map(value, 0, 255, 0, 1023));
                pins.analogWritePin(R_backward, Math.map(value, 0, 255, 0, 1023));
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.r_backward: {
                pins.analogWritePin(L_backward, Math.map(value, 0, 255, 0, 1023));
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.backward: {
                pins.analogWritePin(L_backward, Math.map(value, 0, 255, 0, 1023));
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, Math.map(value, 0, 255, 0, 1023));
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.l_backward: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, Math.map(value, 0, 255, 0, 1023));
                pins.analogWritePin(R_forward, 0);
            }; break;
            case Controldirection.left: {
                pins.analogWritePin(L_backward, Math.map(value, 0, 255, 0, 1023));
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, Math.map(value, 0, 255, 0, 1023));
            }; break;
            case Controldirection.l_forward: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, Math.map(value, 0, 255, 0, 1023));
            }; break;
            case Controldirection.stop: {
                pins.analogWritePin(L_backward, 0);
                pins.analogWritePin(L_forward, 0);
                pins.analogWritePin(R_backward, 0);
                pins.analogWritePin(R_forward, 0);
            }; break;
        }
    }

    export enum Electricmachinery {
        //%block="左电机"
        left = 0,
        //%block="右电机"
        right,
        //%block="全部"
        all
    }
    export enum Electricdirection {
        //%block="正转"
        forword = 0,
        //%block="返转"
        back,
        //%block="停止"
        stop
    }
     /**
    * ABTCar 单个电机方向运动
    */
    //% blockId=ABT_ABTCar2 block="ABTCar onec %onec|direction %direction|"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_CarControl"
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=7
    export function ABTCar2(onec: Electricmachinery, direction: Electricdirection) {
        if (onec == Electricmachinery.left) {
            switch (direction) {
                case Electricdirection.forword: {
                    pins.analogWritePin(AnalogPin.P13, 1023);
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
                case Electricdirection.back: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 1023);
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
                case Electricdirection.stop: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
            }
        } else if (onec == Electricmachinery.right) {
            switch (direction) {
                case Electricdirection.forword: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 1023);
                }; break;
                case Electricdirection.back: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, 1023);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
                case Electricdirection.stop: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
            }
        } else if (onec == Electricmachinery.all) {
            switch (direction) {
                case Electricdirection.forword: {
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 1023);
                    pins.analogWritePin(AnalogPin.P13, 1023);
                    pins.analogWritePin(AnalogPin.P14, 0);
                }; break;
                case Electricdirection.back: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 1023);
                    pins.analogWritePin(AnalogPin.P15, 1023);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
                case Electricdirection.stop: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
            }
        }
    }
    /**
    * ABTCar 单个电机方向运动 可调速
    */
    //% blockId=ABT_ABTCar3 block="ABTCar3 onec1 %onec1|direction1 %direction1|value %value|"
    //% weight=5
    //% blockGap=8
    //% color="#ee0e3d"
    //% group="ABT_CarControl"
    //%value.min=0 value.max=255
    //% name.fieldEditor="gridpicker" name.fieldOptions.columns=8
    export function ABTCar3(onec1: Electricmachinery, direction1: Electricdirection, value: number) {
        if (onec1 == Electricmachinery.left) {
            switch (direction1) {
                case Electricdirection.forword: {
                    pins.analogWritePin(AnalogPin.P13, Math.map(value, 0, 255, 0, 1023));
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
                case Electricdirection.back: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, Math.map(value, 0, 255, 0, 1023));
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
            }
        } else if (onec1 == Electricmachinery.right) {
            switch (direction1) {
                case Electricdirection.forword: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, Math.map(value, 0, 255, 0, 1023));
                }; break;
                case Electricdirection.back: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, Math.map(value, 0, 255, 0, 1023));
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
            }
        } else if (onec1 == Electricmachinery.all) {
            switch (direction1) {
                case Electricdirection.forword: {
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, Math.map(value, 0, 255, 0, 1023));
                    pins.analogWritePin(AnalogPin.P13, Math.map(value, 0, 255, 0, 1023));
                    pins.analogWritePin(AnalogPin.P14, 0);
                }; break;
                case Electricdirection.back: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, Math.map(value, 0, 255, 0, 1023));
                    pins.analogWritePin(AnalogPin.P15, Math.map(value, 0, 255, 0, 1023));
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
                case Electricdirection.stop: {
                    pins.analogWritePin(AnalogPin.P13, 0);
                    pins.analogWritePin(AnalogPin.P14, 0);
                    pins.analogWritePin(AnalogPin.P15, 0);
                    pins.analogWritePin(AnalogPin.P16, 0);
                }; break;
            }
        }
    }



}
//% color=#0cd7e9 weight=30 icon="\uf1eb" block="ABTIR"
namespace ABT_IR {
    export enum irButton {
        //% blockId="SWITCH" block="开关"
        SWITCH = 69,
        //% blockId="MENU" block="菜单"
        MENU = 71,
        //% blockId="TEST" block="TEST"
        TEST = 68,
        //% blockId="RETURN" block="返回"
        RETURN = 67,
        //% blockId="Pausestart" block="暂停开始"
        Pausestart = 21,
        //% blockId="ADD" block="+"
        ADD = 64,
        //% blockId="reduce" block="—"
        reduce = 25,
        //% blockId="LEFT" block="左"
        LEFT = 7,
        //% blockId="RIGHT" block="右"
        RIGHT = 9,
        //% blockId="C" block="C"
        C = 13,
        //% blockId="NUM0" block="0"
        NUM0 = 22,
        //% blockId="NUM1" block="1"
        NUM1 = 12,
        //% blockId="NUM2" block="2"
        NUM2 = 24,
        //% blockId="NUM3" block="3"
        NUM3 = 94,
        //% blockId="NUM4" block="4"
        NUM4 = 8,
        //% blockId="NUM5" block="5"
        NUM5 = 28,
        //% blockId="NUM6" block="6"
        NUM6 = 90,
        //% blockId="NUM7" block="7"
        NUM7 = 66,
        //% blockId="NUM8" block="8"
        NUM8 = 82,
        //% blockId="NUM9" block="9"
        NUM9 = 74,
        //% blockId="NU" block="空"
        NU = 0
    }
    let state: number;
    let data1: number;
    let irstate: number;
    let irData: number = -1;

    //% shim=ABTCarIR::irCode
    function irCode(): number {
        return 0;
    }
    /**
    * 键接收到红外信号后的操作
    */
    //% blockId="ABT_IR_received"
    //% weight=5
    //% blockGap=8
    //% color="#0cd7e9"
    //% block="if|received|data|is %irbutton"
    export function IR_received(irbutton: irButton): boolean {
        pins.setPull(DigitalPin.P5, PinPullMode.PullUp)
        if (valuotokeyConversion() == <number>irbutton) {
            return true;
        }
        return false;
    }

    /**
    * 返回发射红外键的值 可判断进行操作
    */
    //% blockId="IR_read3"
    //% weight=5
    //% blockGap=8
    //% color="#0cd7e9"
    //% block="read IR key value"
    export function IR_read(): number {
        pins.setPull(DigitalPin.P5, PinPullMode.PullUp)
        return valuotokeyConversion();
    }

    // //% blockId="IR_callbackUser"
    // //% weight=50
    // //% block="on IR received"
    // //% draggableParameters
    // export function IR_callbackUser(cb: (message: number) => void) {
    //     pins.setPull(DigitalPin.P5, PinPullMode.PullUp)
    //     state = 1;
    //     control.onEvent(11, 22, function () {//当注册事件发生时运行一些代码。
    //         cb(data1)

    //     })
    // }

    // basic.forever(() => {
    //     if (state == 1) {
    //         irstate = irCode();
    //         if (irstate != 0) {
    //             data1 = irstate & 0xff;
    //             control.raiseEvent(11, 22)//宣布某个事件源发生了某事。
    //         }
    //     }

    //     basic.pause(50);
    // })

    function valuotokeyConversion(): number {
        //serial.writeValue("x", irCode() )
        let data = irCode();
        if (data == 0) {
        } else {
            irData = data & 0xff;
        }
        return irData;
    }
}