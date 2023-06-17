// Declaração das constantes para os pinos
const int PINO_CH1 = 2;
const int PINO_CH2 = 3;
// Pinos PWM para o motor 1
const int PINO_MOTOR1_A = 5;
const int PINO_MOTOR1_B = 6;
// Pinos PWM para o motor 2
const int PINO_MOTOR2_A = 9;
const int PINO_MOTOR2_B = 10;

// Declaração das variáveis com valores iniciais
int ch1_samples[5];  // Array para armazenar as amostras do canal 1
int ch2_samples[5];  // Array para armazenar as amostras do canal 2
int ch1_index = 0;  // Índice atual para as amostras do canal 1
int ch2_index = 0;  // Índice atual para as amostras do canal 2
int velocidade = 0;
int curva = 0;
int velocidade_motor1 = 0;
int velocidade_motor2 = 0;

// Função para calcular a média dos últimos N valores de um array
int calcularMedia(int* samples, int index) {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += samples[i];
  }
  return sum / 5;
}

void setup() {
  Serial.begin(9600);

  pinMode(PINO_CH1, INPUT);
  pinMode(PINO_CH2, INPUT);
  pinMode(PINO_MOTOR1_A, OUTPUT);
  pinMode(PINO_MOTOR1_B, OUTPUT);
  pinMode(PINO_MOTOR2_A, OUTPUT);
  pinMode(PINO_MOTOR2_B, OUTPUT);
}

void loop() {
  // Leitura dos pulsos dos canais de entrada
  ch1_samples[ch1_index] = pulseIn(PINO_CH1, HIGH, 50000); // 50 ms de timeout
  ch2_samples[ch2_index] = pulseIn(PINO_CH2, HIGH, 50000); // 50 ms de timeout

  // Atualiza o índice das amostras circulando no array
  ch1_index = (ch1_index + 1) % 5;
  ch2_index = (ch2_index + 1) % 5;

  // Verifica se os pulsos são válidos antes de mapear
  if (ch1_samples[ch1_index] != 0 && ch2_samples[ch2_index] != 0) {
    // Calcula a média dos últimos N valores
    int ch1_filtered = calcularMedia(ch1_samples, ch1_index);
    int ch2_filtered = calcularMedia(ch2_samples, ch2_index);

    // Mapeamento dos valores de 1000-2000 para a faixa de -255 a 255
    velocidade = map(ch1_filtered, 1000, 2000, -255, 255);
    curva = map(ch2_filtered, 1000, 2000, -255, 255);

    // Cálculo das velocidades dos motores com restrição de faixa
    velocidade_motor1 = constrain(velocidade - curva, -255, 255);
    velocidade_motor2 = constrain(velocidade + curva, -255, 255);
    
    // Controle do motor 1
    if (velocidade_motor1 >= 0) {
      analogWrite(PINO_MOTOR1_A, velocidade_motor1);
      analogWrite(PINO_MOTOR1_B, 0);
    } else {
      analogWrite(PINO_MOTOR1_A, 0);
      analogWrite(PINO_MOTOR1_B, -velocidade_motor1);
    }

    // Controle do motor 2
    if (velocidade_motor2 >= 0) {
      analogWrite(PINO_MOTOR2_A, velocidade_motor2);
      analogWrite(PINO_MOTOR2_B, 0);
    } else {
      analogWrite(PINO_MOTOR2_A, 0);
      analogWrite(PINO_MOTOR2_B, -velocidade_motor2);
    }
  } else {
    // Se os pulsos não são válidos, desligar os motores
    analogWrite(PINO_MOTOR1_A, 0);
    analogWrite(PINO_MOTOR1_B, 0);
    analogWrite(PINO_MOTOR2_A, 0);
    analogWrite(PINO_MOTOR2_B, 0);
  }}
