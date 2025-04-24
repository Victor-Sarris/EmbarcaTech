
Este projeto faz parte da Residência Tecnológica em Software Embarcado (Unidade 2) e tem como objetivo o controle de um LED através de um servidor web, utilizando o microcontrolador ESP32.

🔧 Tecnologias e Ferramentas Utilizadas:
- Pico W
- Linguagem C
- WebServer com HTML integrado
# ⚙️ Funcionalidade:
O projeto configura um servidor web no ESP32 que permite ao usuário ligar e desligar um LED remotamente através de uma interface HTML acessível via navegador. O servidor responde às requisições GET e atualiza o estado do LED conforme o botão clicado pelo usuário na página web.

📁 Estrutura Principal:
main.py: Script principal que inicia o servidor web e define o comportamento do LED com base nas requisições HTTP.

boot.py: Configurações iniciais do ESP32 ao iniciar, como conexão à rede Wi-Fi.

html_page: Código HTML embutido que gera a interface da página web.

📡 Conectividade:
O ESP32 conecta-se a uma rede Wi-Fi local e disponibiliza um IP. Através desse IP, qualquer dispositivo conectado à mesma rede pode acessar o painel de controle do LED via navegador.

