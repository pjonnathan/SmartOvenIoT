# Projeto de Monitoramento IoT com ESP32

Este projeto utiliza um ESP32 para monitorar a temperatura de um sensor **DS18B20** e o valor de um potenciômetro, publicando os dados via **MQTT** para um broker externo.

## Tecnologias Utilizadas

- **ESP32**: Microcontrolador para realizar a leitura dos sensores e conexão com WiFi.
- **DS18B20**: Sensor de temperatura digital.
- **Potenciômetro**: Utilizado para simular um ajuste de potência.
- **MQTT**: Protocolo para comunicação de mensagens entre dispositivos IoT.
- **WiFi**: Conectividade de rede.
- **Wokwi**: Simulador online de projetos IoT.

## Bibliotecas

As seguintes bibliotecas são utilizadas neste projeto:

- `WiFi.h`: Para conectar o ESP32 à rede WiFi.
- `OneWire.h` e `DallasTemperature.h`: Para comunicação com o sensor DS18B20.
- `PubSubClient.h`: Para comunicação via MQTT.

## Funcionalidades

- Conecta-se a uma rede WiFi.
- Lê a temperatura do sensor DS18B20.
- Lê o valor do potenciômetro.
- Publica os dados de temperatura e potência ajustada via MQTT.

## Estrutura do Código

1. **Configuração da Rede WiFi**: O ESP32 se conecta à rede WiFi configurada nas variáveis `ssid` e `password`.
2. **Leitura dos Sensores**:
   - O sensor **DS18B20** lê a temperatura ambiente.
   - O potenciômetro fornece um valor analógico, que é convertido em um percentual de potência.
3. **Publicação via MQTT**: Os dados são enviados em formato **JSON** para o tópico MQTT configurado.

## Conexões

- **Pino D4**: Conectado ao sensor **DS18B20**.
- **Pino 32**: Conectado ao **potenciômetro**.

## Exemplo de Payload JSON

```json
{
  "Temperatura": 24.5,
  "Potenciometro": 75.3
}
````

## Exemplo de Payload JSON
![image](https://github.com/user-attachments/assets/3c5373a7-0ee2-492c-80c5-c525a884ffe5)



