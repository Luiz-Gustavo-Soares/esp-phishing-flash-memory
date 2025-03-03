# Captive Portal com ESP32

## Introdução
Este projeto implementa um Captive Portal utilizando um ESP32. O sistema foi desenvolvido com intuito educacional, permitindo que dispositivos conectados à rede Wi-Fi do ESP32 sejam redirecionados para uma página específica ao tentar acessar a internet.

## Funcionalidade
- Cria um ponto de acesso Wi-Fi.
- Captura requisições HTTP e redireciona para uma página específica.
- Armazena informações dos dispositivos conectados.
- Gerencia arquivos relacionados ao sistema.

## Dependências
Para compilar e executar este projeto, é necessário instalar as seguintes bibliotecas:

- **WiFiMulti** - Gerencia conexões Wi-Fi.
- **DNSServer** - Manipula requisições DNS para o captive portal.
- **WebServer** - Fornece funcionalidades de servidor web para manipular requisições HTTP.
- **SPIFFS** - Permite armazenamento e gerenciamento de arquivos no ESP32.

Caso esteja utilizando o **Arduino IDE**, as bibliotecas podem ser instaladas via "Gerenciador de Bibliotecas".
Se estiver utilizando **PlatformIO**, adicione ao `platformio.ini`:

```
lib_deps =
    WiFiMulti
    DNSServer
    WebServer
    SPIFFS
```

## Como Usar
1. **Configurar o ESP32:**
   - Compile e carregue o código no ESP32 usando a IDE de sua escolha.
   - Conecte-se ao ponto de acesso gerado pelo ESP32.
   
2. **Acessar o Captive Portal:**
   - Assim que um dispositivo se conectar, ao tentar abrir qualquer site, ele será redirecionado para a página configurada no sistema.

3. **Gerenciar Dispositivos:**
   - O código inclui funcionalidades para armazenar informações dos dispositivos conectados.

## CRÉDITOS
Este projeto tem fins educacionais. Sinta-se à vontade para modificar e aprimorar o código!

## Licença
Este projeto está sob a licença MIT.

