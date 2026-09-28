#include "twi.h"
#include "BIT_MATH.h" // تضمين الماكروس الخاصة بالبتات

/* ----------------- 1. دالة التهيئة (Initialization) ----------------- */

// تهيئة الماستر: ضبط السرعة وتفعيل الـ Peripheral
void TWI_Master_Init(void) {
    // 1. ضبط الـ Prescaler = 1 بتصفير بتات TWPS0 و TWPS1 في مسجل TWSR
    CLR_BIT(TWSR, TWPS0);
    CLR_BIT(TWSR, TWPS1);

    // 2. حساب وتمرير قيمة التردد إلى مسجل الـ Bit Rate (TWBR)
    TWBR = (uint8_t)(((F_CPU / scl_freq) - 16) / (2 * 1));

    // 3. تفعيل وحدة الـ TWI رفع بت TWEN في مسجل التحكم TWCR
    SET_BIT(TWCR, TWEN);
}

// تهيئة السليف: ضبط العنوان وتفعيل استقبال الاستجابة (ACK)
void TWI_Slave_Init(uint8_t my_address) {
    // 1. وضع عنوان السليف في مسجل TWAR مع التشفيت بمقدار 1 لترك البت 0 للـ General Call
    TWAR = (my_address << 1);

    // 2. تصفير مسجل قناع العنوان لتطابق العنوان بالكامل
    TWAMR = 0x00;

    // 3. تفعيل الـ TWI وتفعيل الاستجابة التلقائية (ACK)
    SET_BIT(TWCR, TWEN);
    SET_BIT(TWCR, TWEA);
}

/* ----------------- 2. الدالة المساعدة للتنفيذ (Execution Helper) ----------------- */

void TWI_Execute(uint8_t extra_flag) {
    // تصفير الـ Flag بتنزيل 1 على بت TWINT وتفعيل TWEN بالإضافة للبت الخاصة بالأمر (extra_flag)
    TWCR = (1 << TWINT) | (1 << TWEN) | extra_flag;

    // الانتظار طالما الهاردوير شغال والـ Flag لسه 0 باستخدام GET_BIT
    while (GET_BIT(TWCR, TWINT) == 0);
}

/* ----------------- 3. وظائف الإرسال والاستقبال والتحكم ----------------- */

// إرسال شرط البداية (START Condition)
void TWI_Start(void) {
    TWI_Execute(1 << TWSTA);
}

// إرسال شرط النهاية (STOP Condition)
void TWI_Stop(void) {
    // تفعيل بت TWSTO مع تصفير الـ Flag ورفع بت TWEN
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

    // الانتظار طالما بت TWSTO تساوي 1 (الهاردوير يصفّرها تلقائياً بعد إنهاء الـ STOP)
    while (GET_BIT(TWCR, TWSTO) == 1);
}

// إرسال بايت بيانات أو عنوان
void TWI_Write(uint8_t data) {
    // شحن مسجل البيانات بالبايت المراد إرساله
    TWDR = data;

    // تنفيذ الإرسال مع تفعيل الـ ACK
    TWI_Execute(1 << TWEA);
}

// قراءة بايت مع طلب بايت آخر بعده (ACK)
uint8_t TWI_Read_With_ACK(void) {
    TWI_Execute(1 << TWEA);
    return TWDR;
}

// قراءة بايت واحد وأخير (NACK)
uint8_t TWI_Read_With_NACK(void) {
    TWI_Execute(0);
    return TWDR;
}

// قراءة حالة الباص من مسجل TWSR بعد حجب بتات الـ Prescaler
uint8_t TWI_Get_Status(void) {
    return (TWSR & 0xF8);
}
