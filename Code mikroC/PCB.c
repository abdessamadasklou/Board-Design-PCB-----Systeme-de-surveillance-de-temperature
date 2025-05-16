//Configuration des broches du LCD (affectation aux broches du port C)
sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC2_bit;
sbit LCD_D5 at RC3_bit;
sbit LCD_D6 at RC4_bit;
sbit LCD_D7 at RC5_bit;

//Configuration des directions (entrée/sortie) des broches LCD
sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC2_bit;
sbit LCD_D5_Direction at TRISC3_bit;
sbit LCD_D6_Direction at TRISC4_bit;
sbit LCD_D7_Direction at TRISC5_bit;

//Déclaration des variables
char txt[16];              // Chaine de caractères pour afficher la température
unsigned int adc_value;    // Valeur lue par le convertisseur analogique/numérique (ADC)
float temperature;         // Température en degrés Celsius

void main() {
  ADCON1 = 0x80;           // Configure AN0 (RA0) comme entrée analogique
  TRISA = 0xFF;            // Configure tout le port A en entrée (pour capteur LM35)
  TRISC = 0x00;            // Configure tout le port C en sortie (pour le LCD)

  Lcd_Init();              // Initialise le LCD
  Lcd_Cmd(_LCD_CLEAR);     // Efface l’écran du LCD
  Lcd_Cmd(_LCD_CURSOR_OFF);// Désactive le curseur clignotant

  while(1) {
    adc_value = ADC_Read(0); // Lire la valeur analogique sur AN0
    temperature = (adc_value * 5.0 / 1023.0) * 100.0; // Conversion en °C selon la formule du LM35

    FloatToStr(temperature, txt); // Convertit la température (float) en texte
    Lcd_Cmd(_LCD_CLEAR);          // Efface l’écran du LCD
    Lcd_Out(1, 1, "Temp: ");      // Affiche "Temp: " sur la première ligne
    Lcd_Out(1, 7, txt);           // Affiche la température convertie
    Lcd_Out(1, 13, "C");          // Affiche le symbole °C

    Delay_ms(1000); // Attendre 1 seconde avant la prochaine lecture
  }
}
