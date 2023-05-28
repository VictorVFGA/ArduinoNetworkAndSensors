# ArduinoNetworkAndSensors

Este proyecto utiliza un Arduino junto con un módulo Ethernet ENC28J60 y un sensor DHT11 para mostrar en tiempo real la temperatura, humedad y distancia medida por un sensor HC-SR04. Los datos se visualizan a través de una página web.

## Requisitos

- Arduino board
- Módulo Ethernet ENC28J60
- Sensor DHT11
- Sensor HC-SR04

## Conexiones

- Sensor DHT11:
  - Pin de datos -> D3
- Sensor HC-SR04:
  - Pin Trigger -> D4
  - Pin Echo -> D5
- Módulo Ethernet ENC28J60:
  - Pin CS -> 10
  - Pin SI -> 11
  - Pin SO -> 12
  - Pin SCK -> 13

## Librerías utilizadas

- DHT.h
- EtherCard.h

## Configuración de red

- Dirección IP: 192.168.1.68
- Gateway: 192.168.1.254

## Cómo usar

1. Conecta los componentes siguiendo las conexiones descritas anteriormente.
2. Carga el código en tu Arduino utilizando el IDE de Arduino.
3. Asegúrate de tener las bibliotecas necesarias instaladas.
4. Abre el Monitor Serial para ver los mensajes de depuración y verifica que la conexión Ethernet se haya establecido correctamente.
5. Abre un navegador web en tu red local e ingresa la dirección IP asignada al Arduino (por defecto: 192.168.1.68).
6. La página web se actualizará automáticamente cada 5 segundos para mostrar los últimos valores de temperatura, humedad y distancia.

## Notas

- Asegúrate de tener una fuente de alimentación adecuada para todos los componentes.
- Si experimentas problemas de conexión, verifica tus conexiones y configuración de red.

