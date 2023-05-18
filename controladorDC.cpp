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
int ch1 = 0;
int ch2 = 0;
int velocidade = 0;
int curva = 0;
int velocidade_motor1 = 0;
int velocidade_motor2 = 0;

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
  ch1 = pulseIn(PINO_CH1, HIGH, 50000); // 50 ms de timeout
  ch2 = pulseIn(PINO_CH2, HIGH, 50000); // 50 ms de timeout


  // Verifica se os pulsos são válidos antes de mapear
  if (ch1 != 0 && ch2 != 0) {
    // Mapeamento dos valores de 1000-2000 para a faixa de -255 a 255
    velocidade = map(ch1, 1000, 2000, -255, 255);
    curva = map(ch2, 1000, 2000, -255, 255);

    // Cálculo das velocidades dos motores com restrição de faixa
    velocidade_motor1 = constrain(velocidade - curva, -255, 255);
    velocidade_motor2 = constrain(velocidade + curva, -255, 255);
  } else {
    // Se os pulsos não são válidos, parar os motores
    velocidade_motor1 = 0;
    velocidade_motor2 = 0;
  }

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
}
