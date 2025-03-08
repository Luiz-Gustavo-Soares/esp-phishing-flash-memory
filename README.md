# Captive Portal ESP32

Este projeto tem como objetivo a implementação de um captive portal utilizando um ESP32. O sistema cria um ponto de acesso Wi-Fi que redireciona os usuários para uma página de login e armazena os dados submetidos.

![iPhone-13-PRO-MAX-172 0 0 1](https://github.com/user-attachments/assets/ec457426-ee2a-49c9-ac24-a02825c26f85)


## Funcionalidades

- Configuração de um ponto de acesso Wi-Fi com SSID personalizado.
- Redirecionamento de requisições para um servidor web local.
- Armazenamento e gerenciamento dos dados submetidos.
- Utilização do sistema de arquivos SPIFFS para persistência de informações.
- Exibição do uso da memória do SPIFFS.

## Tecnologias Utilizadas

- **C++** para desenvolvimento do firmware.
- **Arduino Framework** para programação do ESP32.
- **DNSServer** para interceptação e redirecionamento de tráfego.
- **WebServer** para hospedagem da interface de login.
- **SPIFFS** para armazenamento de arquivos.
- **ArduinoJson** para manipulação de dados no formato JSON.

## Estrutura do Código

- `main.cpp`: Responsável pela configuração do ESP32, criação do ponto de acesso e inicialização do servidor web.
- `Victims.cpp`: Implementação do gerenciamento de dados dos usuários, incluindo operações de leitura e escrita.
- `Arquivomaneger.cpp`: Manipulação de arquivos no sistema SPIFFS.
- `data/`: Contém os arquivos estáticos utilizados pelo servidor web, incluindo:
  - `index.html`: Página principal de login.
  - `pass.html`: Formulário de exibição de credenciais e outras informações.
  - `validando.html`: Página de processamento de entrada.
  - `style.css`: Arquivo de estilos aplicado às páginas.
  - `script.js`: Implementação de funcionalidades interativas.
  - `google-icon.svg`: Ícone utilizado na interface.

## Procedimentos para Uso

1. **Configuração do ambiente:**
   - Instale o [PlatformIO](https://platformio.org/) ou utilize o Arduino IDE com as bibliotecas necessárias.
   - Conecte o ESP32 ao computador.

2. **Compilação e carregamento do código:**
   - Utilize o PlatformIO ou o Arduino IDE para compilar e enviar o firmware para o ESP32.
   - Faça o upload dos arquivos da pasta `data/` para o sistema SPIFFS do ESP32.

3. **Execução do captive portal:**
   - Conecte-se à rede Wi-Fi gerada pelo ESP32.
   - Acesse qualquer endereço de site para ser automaticamente redirecionado à página de login.

## Aviso Legal

Este projeto foi desenvolvido exclusivamente para fins educacionais. O uso inadequado para coleta não autorizada de informações pode ser considerado ilegal e antiético. O autor não se responsabiliza pelo uso indevido do código.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).

