# OrbitClean Edge — Sistema Embarcado de Evasão Orbital Autônoma

## 🪐 Descrição do Projeto
O OrbitClean Edge é uma solução tecnológica em software embarcado voltada para a resiliência e proteção de satélites ativos situados na Órbita Baixa da Terra (LEO). O sistema foca em resolver o problema crítico da latência de comunicação entre as estações em solo e os ativos espaciais, mitigando o risco de colisões em cadeia geradas pela Síndrome de Kessler.

## 🎯 Objetivo da Solução
Nossa solução implementa uma lógica de tomada de decisão descentralizada diretamente na borda (Edge Computing). Ao detectar a aproximação de lixo espacial, o processador embarcado calcula de forma autônoma o vetor de risco em milissegundos e aciona propulsores de manobra mecânica de emergência, garantindo a integridade do satélite sem depender de comandos de subida enviados da Terra.

## 🛠️ Componentes Utilizados
* **1x Arduino Uno R3** (Unidade de processamento de borda)
* **1x Sensor de Distância Ultrassônico HC-SR04** (Simulador do Radar/LIDAR de aproximação)
* **2x Micro Servo-motores** (Simuladores dos atuadores mecânicos dos propulsores RCS nos eixos X e Y)
* **1x Sensor de Temperatura NTC** (Telemetria do ambiente térmico espacial)
* **1x Display LCD 16x2 I2C** (Painel de monitoramento e diagnóstico de bordo)
* **1x Buzzer Piezoelétrico** (Alarme sonoro para simulação em bancada)
* **3x LEDs Comuns** (Indicadores físicos de status: Vermelho, Amarelo e Verde)

## ⚙️ Explicação do Funcionamento
O algoritmo monitora constantemente a distância do objeto mais próximo em centímetros e a temperatura do hardware através da lógica de borda, alternando o painel de LEDs de acordo com o nível de risco:
1. **Acima de 150cm (Órbita Segura):** O LED Verde acende. O sistema opera em modo de cruzeiro estável ("STATUS: SECURE") e os propulsores permanecem em ângulo neutro (90°).
2. **Entre 150cm e 50cm (Aproximação):** O LED Amarelo acende. O sistema entra em estado de atenção, emitindo bipes sonoros intermitentes e exibindo a proximidade do detrito no LCD.
3. **Abaixo de 50cm (Risco Iminente):** O LED Vermelho acende. Ativa-se o protocolo emergencial de evasão. O buzzer emite um alarme contínuo, o LCD estampa o aviso técnico "ALERTA ERRO 1202" e os servo-motores deslocam-se para 45° e 135°, alterando a atitude do satélite para desviar da colisão.

## 📐 Estrutura do Circuito e Conexões
* **Sensor Ultrassônico HC-SR04:** VCC -> 5V | Trig -> Pino 12 | Echo -> Pino 11 | GND -> GND
* **Display LCD 16x2 I2C:** GND -> GND | VCC -> 5V | SDA -> Pino A4 | SCL -> Pino A5
* **Servo Motor X (Esquerda):** Signal -> Pino 9 | Power -> 5V | Ground -> GND
* **Servo Motor Y (Direita):** Signal -> Pino 10 | Power -> 5V | Ground -> GND
* **Sensor de Temperatura NTC:** VCC -> 5V | SIG/OUT -> Pino A0 | GND -> GND
* **Buzzer:** Positivo -> Pino 13 | Negativo -> GND
* **LEDs de Status (Anodos):** Vermelho -> Pino A1 | Amarelo -> Pino A2 | Verde -> Pino A3 (Todos os Catodos no GND)

## 🚀 Instruções de Execução
1. Acesse o link da simulação fornecido na seção abaixo.
2. Clique no botão **"Start Simulation"** no ambiente do simulador Wokwi.
3. Clique sobre o componente do **Sensor Ultrassônico** para abrir o controlador de distância interativo.
4. Movimente o ponto do objeto simulado para aproximá-lo e afastá-lo do sensor e observe a troca automática dos LEDs de status, as mensagens no display LCD, o acionamento do buzzer e a movimentação síncrona dos servo-motores em cada faixa de distância.

## 🔗 Link da Simulação
* Acesse a simulação funcional completa no Wokwi aqui: **https://wokwi.com/projects/465294642790262785**

## 👥 Integrantes do Grupo
* **Gabriel Juarez** - RM: 563680
* **Andrey Luigi** - RM: 569575
* **Lucas Trevisan** - RM: 569731
* **Nicolas Moreira** - RM: 571510
* **Henrique da Silva** - RM: 569137
