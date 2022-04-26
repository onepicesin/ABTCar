#include "pxt.h"

using namespace pxt;
namespace ABTCar {
    bool initialized = false;

    //%
    void init() {
        if (initialized) return;

    // 使用上拉模式在引脚上安装按钮
    // 待办事项: 在DAL中解决这个问题
        #define ALLOC_PIN_BUTTON(id) new MicroBitButton(getPin(id)->name, id, MICROBIT_BUTTON_ALL_EVENTS, PullUp);
            ALLOC_PIN_BUTTON(MICROBIT_ID_IO_P13)
            ALLOC_PIN_BUTTON(MICROBIT_ID_IO_P14)
            ALLOC_PIN_BUTTON(MICROBIT_ID_IO_P15)
            ALLOC_PIN_BUTTON(MICROBIT_ID_IO_P5)
            ALLOC_PIN_BUTTON(MICROBIT_ID_IO_P11)
            ALLOC_PIN_BUTTON(MICROBIT_ID_IO_P16)
        #undef ALLOC_PIN_BUTTON

        initialized = true;
    }
}

