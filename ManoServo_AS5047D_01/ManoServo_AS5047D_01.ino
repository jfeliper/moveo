/* Comprobación del funcionamiento del encoder magnético AS5047D por comparación con el encoder optico acoplado al eje
 * El encoder óptico lo leemos mediante la librería quadrature https://github.com/zacsketches/Encoder.git
 * Los canales Ay B del encoder incremental se cablean a los pines que permiten interrupción externa que son el 2 y 3
 * tuve que modificar la librería para activar las resistencias de pull-up internas
 * 
 * El encoder magnético usa las funciones AS5047D_Write y AS5047D_Read definidas al final de este fichero.
 * del ejemplo de https://github.com/JanJansen47/AS5047D
 * Los pines SPI van cableados: D10 CS, D11 MOSI, D12 MISO, D13 SCK
 * 
 * La pantalla oled usa la librería https://github.com/adafruit/Adafruit_SSD1306
 * Es i2c cableada a A4 y A5
 * 
 * Para mover el motor paso a paso usamos la librería AccelStepper de http://www.airspayce.com/mikem/arduino/AccelStepper/
 * X_STEP_PIN  6             X_DIR_PIN   5               X_ENABLE_PIN  8
 * 
 * Para poder contrastar las lecturas del encoder incremental óptico y el magnético necesitamos iniciar el óptico cuando el magnético esté a 0
 * Esto lo hace la función ajusta_encoder() que va moviendo el motor hasta que lee 0. Entonces activa la variable encoder_ajustado a true y los dos cuentan desde 0
 * 
 * No se usa delay ni se escribe contínuamente en la pantalla porque interfiere con el movimiento del motor.
 * para eso usa el ejemplo de blink sin delay
 */
 
#include <SPI.h>
#include <AccelStepper.h>
#include <quadrature.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
unsigned int reading = 0;

// AS4047D Registers
#define AS5047D_select_pin 10

/** volatile **/
#define NOP 0x0000
#define ERRFL 0x0001
#define PROG   0x0003
#define DIAAGC 0x3FFC
#define CORDICMAG 0x3FFD
#define ANGLEUNC  0x3FFE
#define ANGLECOM  0x3FFF

/** non-volatile **/
#define ZPOSM 0x0016
#define ZPOSL 0x0017
#define SETTINGS1 0x0018
#define SETTINGS2 0x0019

#define RD  0x40    // bit 14 "1" is Read + parity even
#define WR  0x3F    //bit 14 ="0" is Write

//Op Arduino: D10 CS, D11 MOSI, D12 MISO, D13 SCK

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 200;           // interval at which to blink (milliseconds)
unsigned long currentMillis = millis();

void setup() {
  Serial.begin(115200);  // start serial for output
  pinMode(AS5047D_select_pin, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("ManoServo");
  display.setCursor(0, 21);
  display.print(" AS5047D");
  display.setCursor(0, 42);
  display.print(" AS5047D");
  display.display();
  delay(1000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();

  SPI.begin();
  SPI.setDataMode(SPI_MODE1); // properties chip
  SPI.setBitOrder(MSBFIRST);  //properties chip

  AS5047D_Write( AS5047D_select_pin , SETTINGS1, 0x0004);
  AS5047D_Write( AS5047D_select_pin , SETTINGS2, 0x0000);
  AS5047D_Write( AS5047D_select_pin , ZPOSM, 0x0000); // is it really possible to initially set angle at 0 degrees??
  AS5047D_Write( AS5047D_select_pin , ZPOSL, 0x0000);

}

void loop()
{
  // AS5047D_Read( AS5047D_select_pin, NOP) & 0x3FFF; // strip bit 14..15
  // AS5047D_Read( AS5047D_select_pin, ERRFL) & 0x3FFF; // strip bit 14..15
  // AS5047D_Read( AS5047D_select_pin, PROG) & 0x3FFF; // strip bit 14..15
  // AS5047D_Read( AS5047D_select_pin, DIAAGC) & 0x3FFF; // strip bit 14..15
  
  // AS5047D_Read( AS5047D_select_pin, CORDICMAG) & 0x3FFF; // strip bit 14..15
  // AS5047D_Read( AS5047D_select_pin, ANGLEUNC) & 0x3FFF; // strip bit 14..15
  // AS5047D_Read( AS5047D_select_pin, ANGLECOM) & 0x3FFF; // strip bit 14..15

  // AS5047D_Read( AS5047D_select_pin, ZPOSM) & 0x3FFF; // strip bit 14..15
  // AS5047D_Read( AS5047D_select_pin, ZPOSL) & 0x3FFF; // strip bit 14..15
  // AS5047D_Read( AS5047D_select_pin, SETTINGS1) & 0x3FFF; // strip bit 14..15
  // AS5047D_Read( AS5047D_select_pin, SETTINGS2) & 0x3FFF; // strip bit 14..15

  int angulo = AS5047D_Read( AS5047D_select_pin, ANGLECOM) & 0x3FFF;
  int grados360 = angulo / 45.511;
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval)  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(" AS5047D");
    display.setCursor(0, 21);
    display.print("CMG      ");
    display.setCursor(40, 21);
    display.print(AS5047D_Read( AS5047D_select_pin, CORDICMAG) & 0x3FFF);
    display.setCursor(0, 42);
    display.print("AS     ");
    display.setCursor(40, 42);
    display.print(grados360);
    display.display();
  }
}


// ************************Write to AS5047D **************************
void AS5047D_Write( int SSPin, int address, int value)
{
  // take the SS pin low to select the chip:
  digitalWrite(SSPin, LOW);
  Serial.println(value, HEX);
  //  send in the address via SPI:
  byte v_l = address & 0x00FF;
  byte v_h = (unsigned int)(address & 0x3F00) >> 8;
  if (parity(address & 0x3F) == 1) v_h = v_h | 0x80; // set parity bit
  //v_h = v_h & (WR | 0x80);  // its  a write command and don't change the parity bit (0x80)
  Serial.print( " parity:  "); Serial.println(parity(address & 0x3F));
  Serial.print(v_h, HEX); Serial.print(" A ");  Serial.println(v_l, HEX);
  SPI.transfer(v_h);
  SPI.transfer(v_l);
  digitalWrite(SSPin, HIGH);
  delay(2);
  digitalWrite(SSPin, LOW);
  //  send value via SPI:
  v_l = value & 0x00FF;
  v_h = (unsigned int)(value & 0x3F00) >> 8;
  if (parity(value & 0x3F) == 1) v_h = v_h | 0x80; // set parity bit
  //v_h = v_h & (WR | 0x80); // its a write command and don't change the parity bit (0x80)
  Serial.print(v_h, HEX); Serial.print(" D ");  Serial.println(v_l, HEX);
  SPI.transfer(v_h);
  SPI.transfer(v_l);
  // take the SS pin high to de-select the chip:
  digitalWrite(SSPin, HIGH);
}

//*******************Read from AS5047D ********************************
unsigned int AS5047D_Read( int SSPin, unsigned int address)
{
  unsigned int result = 0;   // result to return
  byte res_h = 0;
  byte res_l = 0;
  // take the SS pin low to select the chip:
  digitalWrite(SSPin, LOW);
  //  send in the address and value via SPI:
  byte v_l = address & 0x00FF;
  byte v_h = (unsigned int)(address & 0x3F00) >> 8;
  if (parity(address | (RD << 8)) == 1) v_h = v_h | 0x80; // set parity bit
  v_h = v_h | RD; // its  a read command
  // Serial.print( " parity:  ");Serial.println(parity(address | (RD <<8)));
  // Serial.print(v_h, HEX); Serial.print(" A ");  Serial.print(v_l, HEX);  Serial.print(" >> ");
  res_h = SPI.transfer(v_h);
  res_l = SPI.transfer(v_l);
  digitalWrite(SSPin, HIGH);
  delay(2);
  digitalWrite(SSPin, LOW);
  //if (parity(0x00 | (RD <<8))==1) res_h = res_h | 0x80;  // set parity bit
  //res_h = res_h | RD;
  res_h = (SPI.transfer(0x00));
  res_l = SPI.transfer(0x00);
  res_h = res_h & 0x3F;  // filter bits outside data
  //Serial.print(res_h, HEX);   Serial.print(" R  ");  Serial.print(res_l, HEX);   Serial.print("  ");
  digitalWrite(SSPin, HIGH);
  return (result = (res_h << 8) | res_l);
}

//*******************check parity ******************************************
int parity(unsigned int x) {
  int parity = 0;
  while (x > 0) {
    parity = (parity + (x & 1)) % 2;
    x >>= 1;
  }
  return (parity);
}

