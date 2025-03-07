# Captive Portal ESP32

Este projeto implementa um captive portal em um ESP32 usando um ponto de acesso Wi-Fi falso, redirecionando os usuários para uma página de login. Além disso, o sistema armazena os dados submetidos pelos usuários.

## 📌 Funcionalidades

- Criação de um ponto de acesso Wi-Fi com um nome personalizado.
- Redirecionamento de requisições para um servidor web local.
- Armazenamento de credenciais enviadas pelos usuários.
- Gerenciamento de arquivos usando SPIFFS.

## 🛠️ Tecnologias Utilizadas

- **C++** para programação do ESP32.
- **Arduino Framework** para desenvolvimento no ESP32.
- **DNSServer** para redirecionamento de tráfego.
- **WebServer** para hospedagem da página de login falsa.
- **SPIFFS** para armazenamento de dados.
- **ArduinoJson** para manipulação de JSON.

## 📂 Estrutura do Código

- `main.cpp`: Configuração do ESP32, criação do ponto de acesso e servidor web.
- `Victims.cpp`: Gerenciamento dos dados das vítimas, incluindo leitura e escrita de credenciais.
- `Arquivomaneger.cpp`: Manipulação de arquivos usando SPIFFS.
- `data/`: Contém os arquivos estáticos usados pelo servidor web, incluindo:
  - `index.html`: Página de login falsa exibida para os usuários.
  - `pass.html`: Página de inserção de credenciais.
  - `validando.html`: Página de carregamento ou processamento.
  - `style.css`: Estilos CSS aplicados às páginas.
  - `script.js`: Scripts JavaScript para interação com a página.
  - `google-icon.svg`: Ícone usado na interface.

## 🚀 Como Usar

1. **Configurar o ambiente:**
   - Instale o [PlatformIO](https://platformio.org/) ou use o Arduino IDE com as bibliotecas adequadas.
   - Conecte o ESP32 ao computador.

2. **Compilar e carregar o código:**
   - Use o PlatformIO ou o Arduino IDE para compilar e enviar o firmware para o ESP32.
   - Faça o upload dos arquivos da pasta `data/` para o sistema SPIFFS do ESP32.

3. **Acessar o Captive Portal:**
   - Conecte-se ao Wi-Fi criado pelo ESP32.
   - Acesse qualquer site para ser redirecionado à página de login.

## ⚠️ Aviso

Este projeto é apenas para fins educacionais. O uso indevido para capturar credenciais de usuários sem consentimento pode ser ilegal e antiético. Use com responsabilidade!

## 📜 Licença

Este projeto está licenciado sob a [MIT License](LICENSE).

