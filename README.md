# Controlador ESC Para Motores Escovados Utilizando Arduino e a Ponte H L298N

O código foi projetado para substituir os controladores ESC (Electronic Speed Controllers) de motores escovados em robôs de combate. Este código foi testado com o uso do rádio controle FlySky FS-i6.

Inicialmente, o código declara as constantes para os pinos que serão usados para ler os canais de entrada e controlar os motores. Os canais 1 e 2 (PINO_CH1 e PINO_CH2) são configurados como entrada, enquanto os pinos para os motores (PINO_MOTOR1_A, PINO_MOTOR1_B, PINO_MOTOR2_A, PINO_MOTOR2_B) são definidos como saída.

No método setup(), a comunicação serial é iniciada e os pinos de entrada e saída são configurados corretamente. Este método é executado apenas uma vez quando o Arduino é inicializado.

No método loop(), que é a parte principal do programa e é executado continuamente, o programa lê os pulsos dos canais de entrada usando a função pulseIn(). Os valores lidos variam de 1000 a 2000 e são mapeados para a faixa de -255 a 255 para se adequar à faixa de velocidade PWM dos motores.

Em seguida, o código calcula as velocidades dos dois motores com base nas leituras do controle remoto. A função constrain() é usada para garantir que as velocidades calculadas não ultrapassem os limites de -255 a 255.

Finalmente, o código controla a velocidade dos motores. Se a velocidade calculada for positiva, o pino A do motor correspondente recebe a velocidade e o pino B é definido como 0. Se a velocidade for negativa, o pino A é definido como 0 e o pino B recebe o valor absoluto da velocidade. Isso permite que os motores girem em ambas as direções, dependendo do sinal da velocidade calculada.

### Componentes usados

- Arduino Nano;

- Ponte H L298N;
- Bateria LiPo 7.4v 1500mah
- Dois motores DC 6v 600rpm
- Receptor FlySky FS-iA6B
- Rádio controle FlySky FS-i6



### Circuito

![circuito](https://i.ibb.co/H7Tw8n3/circuito.png)

### Autor

[@mauricioprb](https://github.com/mauricioprb)
