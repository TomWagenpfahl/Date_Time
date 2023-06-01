/**
* @Project  Embedded C++ Kurs ET20B
* @brief    GPIO-Klasse fuer STM32F4xxx
* @file     stm_gpio.h

* @Date     2023
*
* Dies ist ein erster Ansatz die GPIO-Funktionalit?t in einer Klasse abzubilden

* Diese Klasse ist noch nicht vollst?ndig und dient nur der Uebung. Die Klasse ist fuer einen
* echten Betrieb der GPIO nicht geeignet. Weiter wird noch keine Interruptfunktionalitaet
* unterstuetzt.
* Diese Klasse darf nur innerhalb der Uebungen OOSE/Mikrocomputertechnik3 verwendet werden.

* -nicht fuer den Einsatz in echten Projekten verwendbar-

* @ToDo
* Es muss Fehlermeldungen fuer die Einzelnen public Methoden geben.
* Die Klasse GPIO arbeitet im Gegensatz zu dem C-File aus der EFM-Lib
* nicht mit Asserts!!!!
* Weitere Konfi.-Moeglichkeiten implementieren siehe Datenblatt STM32F4xx_RM.pdf
* Ausfuehlicher Test
*/

#ifndef _STM_GPIO_
#define _STM_GPIO_

#include <stdint.h>

class StmGpio
{

    // GPio-ClockRegister vgl. Datenblatt STM32F4xx_RM.pdf
    volatile uint32_t &uRCCAHB1ENRRegister; //! RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)

    // Deklaratioin der GPIO-Port Register vgl. Datenblatt STM32F4xx_RM.pdf
    volatile uint32_t &uModeRegister;           //! GPIO port X mode register
    volatile uint32_t &uOutPutTypeRegister;     //! GPIO port X output type register
    volatile uint32_t &uOutPutSpeedRegister;    //! GPIO port X output speed register
    volatile uint32_t &uPullUpPullDownRegister; //! GPIO port X pull-up/pull-down register
    const volatile uint32_t &uInPutRegister;    //! GPIO port X input data register
    volatile uint32_t &uOutPutDataRegister;     //! GPIO port X output data register

    volatile uint16_t &uBitResetRegister; //! GPIO port X bit set/reset low register
    volatile uint16_t &uBitSetRegister;   //! GPIO port X bit set/reset highe register

    // Merker
    const uint32_t m_GPIOBaseRegisterAddr; //! Merker fuer die Basisadresse
    const uint32_t m_RegisterOffset;       //! Merker fuer den Offset, ueber diese beiden Attribute kann der richtige GPIO-Clock aktiviert werden

    enum GPIO_MASK
    {
        ePORT_MASK = 0xFFFFUL
    };

    // StmGpio(); //!der Standardkonstruktor wird verboten
    void EnableGPIOClock();

public:
    StmGpio(uint32_t uPortCtrAddr); // als uebergabeparameter gilt die Basis-Adresse fuer den entsprechenden Port --> vgl. GPIO_PX_CRTL-Registeraddresse

    // Todo: private setzen!!!
    void SetPinMode(uint32_t uPin, uint32_t mode);     //(/*unsigned int  uiPin, GPIO_Mode_TypeDef eMode, int uOut=0*/);
    void SetOTyp(uint32_t uPin, bool pushpull = true); // unsigned char oType=0); //default type is push-pull, otherwise 1 = Output open drain
    void SetOSpeed(uint32_t uPin, uint32_t mode = 0);
    void SetPullUpPullDown(uint32_t uPin, uint32_t mode = 0); // defautl is push-pull

    unsigned int GetPinOutSetting(unsigned int uiPin);
    void SetStandardOutPut(unsigned int uiPin);
    void SetStandardInPut(unsigned int uiPin);

    uint32_t ReadPin(uint32_t uPin); // Parameter PinNr --> siehe Datenblatt
    void ClearPin(uint32_t uPin);    // Parameter PinNr --> siehe Datenblatt
    void SetPin(uint32_t uPin);      // Parameter PinNr --> siehe Datenblatt
    void TogglePin(uint32_t uPin);   // Parameter PinNr --> siehe Datenblatt

    void SetPinViaOutPutRegister(int val, uint32_t uPin); // new

    uint32_t ReadPort();                // lese den gesamten Port
    uint32_t GetDOut();                 // Liest den aktuellen Zustand des Dout-Registers
    void WritePort(uint32_t uData);     // schreibe auf gesamten Port
    void TogglePort(uint32_t uPinMask); // Parameter uiPin bin?rcodiert die Pins die getoggelt werden sollen

    void ClearPort(uint32_t uPinMask); // in uPinMask werden die Pins eingetragen, die geloescht werden sollen
};

#endif