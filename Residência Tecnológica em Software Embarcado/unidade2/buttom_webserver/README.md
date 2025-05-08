# 📦 Projeto: `buttom_webserver`

Este projeto faz parte da **Unidade 2 da Residência Tecnológica em Software Embarcado** e demonstra como **monitorar o estado de um botão físico utilizando um servidor web embarcado**, com interface HTML estilizada.

## 🔧 Tecnologias Utilizadas
- ✅ Raspberry Pi Pico W (modelo 2)
- ✅ Linguagem C (usando o SDK oficial da Raspberry Pi)
- ✅ Servidor HTTP básico
- ✅ HTML com estilização embutida

## 🧠 Objetivo
Permitir a leitura do estado de um botão físico conectado à Pico W, com exibição em tempo real (via atualização manual da página) por meio de uma **interface web hospedada diretamente no microcontrolador**.

## ⚙️ Funcionalidades
- Leitura digital do botão (pressionado ou não).
- Servidor web embarcado com resposta em HTML.
- Interface amigável e estilizada.
- Página acessível via navegador conectado à mesma rede Wi-Fi da placa.

## 🌐 Interface Web
A página web exibe dinamicamente o estado do botão com estilo visual simples, facilitando o entendimento e acompanhamento do funcionamento do hardware.

## 📁 Estrutura do Projeto
- `main.c`: Código principal, responsável por configurar o botão e o servidor web.
- `index_html.h`: Arquivo contendo o HTML da página web embutido como string em C.

## ▶️ Como Usar
1. Compile o projeto usando o SDK do Raspberry Pi Pico com suporte à rede (Pico W).
2. Conecte a Pico W a uma rede Wi-Fi (informações no `main.c`).
3. Acesse o IP exibido via serial para visualizar o estado do botão no navegador.

## 📸 Demonstração
![image](https://github.com/user-attachments/assets/6b8a974c-ced7-4b9b-bfa5-694591182232)

> Projeto desenvolvido durante a **Residência Tecnológica em Software Embarcado**, com foco em integração de hardware e redes em sistemas embarcados.

---
**Desenvolvido por** [Victor Sarris](https://github.com/Victor-Sarris)  
*Projeto acadêmico - EmbarcaTech 2025*
