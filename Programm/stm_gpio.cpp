/**
* @Project  Embedded C++ Kurs ET20B
* @brief    GPIO-Klasse fuer STM32F4xxx
* @file     stm_gpio.h

* @Date     2023
*
* Dies ist ein erster Ansatz die GPIO-Funktionalitaet in einer Klasse abzubilden

* Diese Klasse ist noch nicht vollstaendig und dient nur der Uebung. Die Klasse ist fuer einen
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

#include "stm_gpio.h"
#include <iostream>
using namespace std;

#if 0
/*!
* Konstruktor mit Parameterliste und Initialisierungsliste
* \param uPortCtrAddr --> Adresse des ModeRegisters des entsprechenden Ports
* \param ucPortNumber
*/
StmGpio::StmGpio(uint32_t uPortCtrAddr):uRCCAHB1ENRRegister(*(volatile uint32_t*)0x40023830),
                                      uModeRegister(*(volatile uint32_t*)uPortCtrAddr),
                                      uOutPutTypeRegister(*(volatile uint32_t*)(uPortCtrAddr+0x0004)),
                                      uOutPutSpeedRegister(*(volatile uint32_t*)(uPortCtrAddr+0x0008)),
                                      uPullUpPullDownRegister(*(volatile uint32_t*)(uPortCtrAddr+0x000C)),
                                      uInPutRegister(*(volatile uint32_t*)(uPortCtrAddr+0x0010)),
                                      uOutPutDataRegister(*(volatile uint32_t*)(uPortCtrAddr+0x0014)),
                                      uBitSetRegister(*(volatile uint16_t*)(uPortCtrAddr+0x0018)),  //Achtung das sind nur 16 bit
                                      uBitResetRegister(*(volatile uint16_t*)(uPortCtrAddr+0x001A)), //Achtung das sind nur 16 bit
                                      m_GPIOBaseRegisterAddr(0x40020000),
                                      m_RegisterOffset(0x00000400) 

{
  EnableGPIOClock();
}

#endif

/** oder wie im Skript
 *Alternative Initialisierung der Register vgl. Skript
 */
StmGpio::StmGpio(uint32_t uPortCtrAddr) : uRCCAHB1ENRRegister(*(volatile uint32_t *)0x40023830),
                                          uModeRegister(*(volatile uint32_t *)uPortCtrAddr),
                                          uOutPutTypeRegister(*(&uModeRegister + 1)),
                                          uOutPutSpeedRegister(*(&uModeRegister + 2)),
                                          uPullUpPullDownRegister(*(&uModeRegister + 3)),
                                          uInPutRegister(*(&uModeRegister + 4)),
                                          uOutPutDataRegister(*(&uModeRegister + 5)),
                                          uBitSetRegister(*(volatile uint16_t *)(uPortCtrAddr + 0x018)),   // Achtung dies sind nur 16 bit deshalb wird hier auch mit dem Parameter und Offset aus dem Datenblatt gearbeitet
                                          uBitResetRegister(*(volatile uint16_t *)(uPortCtrAddr + 0x01A)), // Achtung dies sind nur 16 bit deshalb wird hier auch mit dem Parameter und Offset aus dem Datenblatt gearbeitet

                                          m_GPIOBaseRegisterAddr(0x40020000),
                                          m_RegisterOffset(0x00000400)
{

    EnableGPIOClock();
}

/**
 * EnableGPIOClock
 * aktiviert den GPIO-Clock
 * vgl. Datenblatt STM32F4xx_RM.pdf
 * RCCAHB1ENR peripheral clock enable register
 * es wird das entsprechende Bit f?r den aktuellen Port
 * der Instanz berechnet.
 *
 * ToDo: alternativ eine Methode mit Parameter implementieren
 * welche es erlaubt den GPIO-Clock vom Anwender zu aktivieren.
 */
void StmGpio::EnableGPIOClock()
{
    uint32_t tmp = (uint32_t)&uModeRegister;
    cout << tmp << endl;
    uint32_t registerBit = ((uint32_t)&uModeRegister - m_GPIOBaseRegisterAddr) / m_RegisterOffset; // ermittlet das Bit f?r den ensprechenden GPIO-Port
    cout << registerBit << endl;
    uRCCAHB1ENRRegister |= (1ul << registerBit);
}

/**
 * Einstellen des "Betriebs"-Modes f?r einen einzelnen Pin des GPIO-Ports
 * Das Register uModeRegister ist ein 32 bit Register im Datenblatt bezeichnet als GPIOX_MODER
 * f?r die Konfiguration eines Pins werden 2 bit des Registers benoetigt.
 * \param uPin  -->  Nummer des Pins 0-15
 * \param eMode -->  einzustellender Mode stm32F4xx_RM.pdf page 198
 *                   00: Input (reset state)
 *                   01: General purpose output mode
 *                   10: Alternate function mode
 *                   11: Analog mode
 */
void StmGpio::SetPinMode(uint32_t uPin, uint32_t mode)
{
    if (mode == 0)
        uModeRegister &= ~((3ul << 2 * uPin)); // clear mode is input
    else
        uModeRegister |= ((mode << 2 * uPin)); // setze Analog-mode
}

/**
 * Einstellen des Ausgangbetriebstype, es kann gewaehlt werden zwischen
 * Output pushpull, dies entspricht auch dem resetz-Zustand und
 * den output als opendrain zu betreiben.
 * Bei diesem Register handelt es sich ebenfall um eine 32-bit Register,
 * f?r die Konfiguration eines Pins wird hier ein bit benoetigt.
 * Die bits 16-31 sind resever-bits, welche jedoch f?r den Reset benoetigt werden,
 * Reset: komplettes Regitser = 0 (0x0000 0000)
 * \param uPin  -->  Nummer des Pins 0-15
 * \param pushpull --> 0: Output push-pull (reset state)
 *                      1: Output open-drain
 */
void StmGpio::SetOTyp(uint32_t uPin, bool pushpull)
{
    // reset Register this means push-pull
    if (pushpull)
        uOutPutTypeRegister &= ~((1ul << uPin)); // push-pull
    else
        uOutPutTypeRegister |= ((1ul << uPin)); // opendrain
}

/**
* Der im Datenblatt angegeben ResetWert f?r den PortA stimmt nicht mit dem
* aus dem Register ausgelesen Wert ?berein, das muss nochmal gepr?ft werden.
* Vgl. Datenblatt stm32F4xx_RM.pdf page 199
* \param uPin  -->  Nummer des Pins 0-15
* \param pushpull --> 00: 2 MHz Low speed
                      01: 25 MHz Medium speed
                      10: 50 MHz Fast speed
                      11: 100 MHz High speed on 30 pF (80 MHz Output max speed on 15 pF)
* F?r die Konfiguration eines Pins werden 2bit benoetigt.
* Es handelt sich hier wieder um 32-bit Register.
* im Datenblatt sind folgende ResetWerte angegeben
* 0x0000 00C0 for port B
* 0x0000 0000 for other ports
* port A sieht allerdings f?r mich nach 0x0C00 0000 aus,
* dieser Wert wird mit Enable des GPIO Clocks f?r den PortA in das Registergeschrieben.
*/
void StmGpio::SetOSpeed(uint32_t uPin, uint32_t mode)
{
    uOutPutSpeedRegister &= ~((3ul << 2 * uPin)); // reset register
    uOutPutSpeedRegister |= ((mode << 2 * uPin));
}

/**
 * Konfiguration eines pullup bzw. pulldown Widerstandes f?r einen bestimmten Pin
 * dies ist ebenfalls ein 32-Bit Register, f?r die Konfitguration eines Pins werden
 * 2-Bit benoetigt.
 * f?r die unterschiedlichen Ports sind folgende ResetWerte angegeben vgl. Datenblatt page 200
 * Reset values:
 * 0x6400 0000 for port A
 * 0x0000 0100 for port B
 * 0x0000 0000 for other ports
 * PUPDRy[1:0]: Port x configuration bits (y = 0..15)
 * These bits are written by software to configure the I/O pull-up or pull-down
 * \param uPin  -->  Nummer des Pins 0-15
 * \param mode -->     00: No pull-up, pull-down push pull
 *                     01: Pull-up
 *                     10: Pull-down
 *                     11: Reserved
 */
void StmGpio::SetPullUpPullDown(uint32_t uPin, uint32_t mode)
{
    uPullUpPullDownRegister &= ~((3ul << 2 * uPin)); // reset register
    uPullUpPullDownRegister |= ((mode << 2 * uPin));
}

/**
 * GetPinOutSetting(..)
 * gibt die akutelle Einstellung des Dout-Registers f?r den entsprechenden pin
 * zur?ck
 * \param unsigned int uiPin --> PinNr.
 */
unsigned int StmGpio::GetPinOutSetting(unsigned int uiPin)
{
    return ((unsigned int)((uModeRegister >> 2 * uiPin)) & 0x0001);
}

/**
 * setzt einen Pin als Ausgang
 * \param uiPin --> Nummer des Pins vgl. Datenblatt
 */
void StmGpio::SetStandardOutPut(unsigned int uiPin)
{
    SetPinMode(uiPin, 1);
    SetOSpeed(uiPin, 1);
    SetOTyp(uiPin);
    SetPullUpPullDown(uiPin); // kein Pullup kein PullDown
}

/**
 * setzt einen Pin als Eingang
 * mit Pullup
 *\param uiPin --> Nummer des Pins vgl. Datenblatt
 */
void StmGpio::SetStandardInPut(unsigned int uiPin)
{
    SetPinMode(uiPin, 0);
    SetPullUpPullDown(uiPin);
}

/**
 * Es wird der Wert eines einzelnen Pins gelesen
 * \param uPin --> PinNummer 0-15
 * \retval 0 -->
 * \retval 1 -->
 */
uint32_t StmGpio::ReadPin(uint32_t uPin)
{
    return (uInPutRegister >> uPin) & 0x01;
}

/**
 * Ein Pin des GPIO-Ports wird geloescht, der Wert 0 wird ins Controllregister geschrieben
 * \param uPin --> PinNummer 0-15
 */
void StmGpio::ClearPin(uint32_t uPin)
{
    uBitResetRegister |= (1ul << uPin);
}

/**
 * Ein Pin des GPIO-Ports setzen
 * \param uPin --> PinNummer 0-15
 */
void StmGpio::SetPin(uint32_t uPin)
{
    uBitSetRegister |= (1ul << uPin);
}

/**
new methode to test the outputRegister offset 0x14
this will be used vor toggle bit!!
Das setzen geht auch so.
es muss noch in eine toogle umgearbeitet werden
*/
void StmGpio::SetPinViaOutPutRegister(int val, uint32_t uPin)
{

    if (val == 1)
        uOutPutDataRegister |= ((1ul << uPin) & 0xffff); // pin setzen geht  Achtun Maske, da nur 16 bit gesetzt werden d?rfen. allerdings laesst der Controller das sezten der anderen auch nicht zu
    else
        uOutPutDataRegister &= ~((1ul << uPin)); // pin loeschen
}

/**
 * Ein Pin des GPIO-Ports umschalten (toggle)
 * Der Trick: zuerst loeschen und danach mit dem Bitwert verodern.
 * Ist es 1, dann ist es ein Setzen wie zuvor gezeigt. Ist es 0, dann ergibt a | 0 = a, bleibt also zur?ckgesetzt
 * \param uPin --> PinNummer 0-15
 * ToDo.: Koennte auch einfacher geloest werden via uBitSetRegister / uBitResetRegister
 */
void StmGpio::TogglePin(uint32_t uPin)
{
    uint32_t uPinVal = (uOutPutDataRegister >> uPin) & 0x01; // aktuellen Pin lesen
    uPinVal = !uPinVal;                                      // Pin invertieren

    uOutPutDataRegister &= ~((1ul << uPin));    // bit loeschen
    uOutPutDataRegister |= ((uPinVal << uPin)); // gew?nschten wert setzen
}

/**
 * Loeschen mehrerer Bits des GPIO-Ports
 * \param uPinMask --> Bitmaske der Pins die geloescht werden sollen
 */
void StmGpio::ClearPort(uint32_t uPinMask)
{
    printf("uPinMask & ePORT_MASK; %x\n", (uPinMask & ePORT_MASK));
    uOutPutDataRegister &= ~(uPinMask & ePORT_MASK);
}

/**
 * Wert des Ports lesen
 * \retval uint32_t --> Wert des Ports
 */
uint32_t StmGpio::ReadPort()
{
    return (uInPutRegister & ePORT_MASK);
}

/**
 * Liest den aktuellen Zustand des Dout-Registers
 * \retval uint32_t --> Wert des Registers
 */
uint32_t StmGpio::GetDOut() // Liest den aktuellen Zustand des Dout-Registers
{
    return uOutPutDataRegister & ePORT_MASK;
}

/**
 * Schreiben eines uint32_t Wertes auf den GPIO-Port
 * \retval uint32_t --> Wert
 */
void StmGpio::WritePort(uint32_t uData)
{
    uOutPutDataRegister = uData & ePORT_MASK;
    return;
}
