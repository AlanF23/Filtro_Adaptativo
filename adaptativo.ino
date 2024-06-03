#define ADC1PIN A6
#define ADC2PIN A7
#define N 100
//int adcValue;
double suma, output=0, adcValue1, adcValue2, ruido[N], w[N], sum, mu = 0.001, e;
void setup()
{  
  Serial.begin(115200);
  for (int i = 0; i < N; i++) {  // Inicializa los vectores
      ruido[i] = 0;
      w[i] = 0;
    }
}
//ADC1 = RUIDO  & ADC2 = SEÑAL
void loop()
{
  adcValue1 = analogRead(ADC1PIN);
  adcValue2 = analogRead(ADC2PIN);
  // Actualiza el vector de muestras
  for (int i = 0; i < N - 1; i++) {
      ruido[i] = ruido[i + 1];
  }
  sum = 0;
  ruido[N - 1] = ((adcValue1*3.3) / 4095);
  ruido[N - 1] -= 0.5;
  for (int i = 0; i < N; i++) {
    sum = sum + w[i] * ruido[N - 1 - i];
  }

  suma = ((adcValue2*3.3) / 4095);
  suma -= 0.5;
  e = suma - sum;

  // Aplica el algoritmo LMS
  for (int i = 0; i < N; i++) {
      w[i] = w[i] + 2 * mu * e * ruido[N - 1 - i];
  }

  e += 0.5;
  //Serial.print("ADC Value = ");
  //Serial.print(adcValue);
  //delay(1000);
  //Serial.print("  ");
  //Serial.print("Voltage = ");
  //Serial.print(voltValue);
  //Serial.println(" V");

  //Scale it as per DAC Resolution and output to DAC
  double out = e*256;
  out /= 3.3;
  int DACoutput1 = (int)out;

/*  double out2 = e*256;
  out2 /= 3.3;
  int DACoutput2 = (int)out2;
*/
  dacWrite(DAC1,DACoutput1);
  //dacWrite(DAC2,DACoutput2);
  //dacWrite(DAC1, adcValue);
  //delay(1000);
}