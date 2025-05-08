# 🕹️ Joystick Control Webserver
*Sistema de controle remoto com joystick via interface web - Projeto da Residência em Software Embarcado (Unidade 2)*

## 🚀 Funcionalidades
- Leitura analógica de eixos X/Y do joystick
- Controle remoto via interface web responsiva
- Visualização em tempo real da posição do joystick

## 🛠️ Tecnologias
<p align="left">
  <img src="https://img.shields.io/badge/PICOW-E7352C?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32">
  <img src="https://img.shields.io/badge/HTML-00979D?style=for-the-badge&logo=HTML&logoColor=white" alt="HTML">
</p>

## 📁 Estrutura do Projeto
- `main.c`: Código principal, responsável por configurar o botão e o servidor web.
- `index_html.h`: Arquivo contendo o HTML da página web embutido como string em C.


## 🔌 Hardware Necessário
- Placa Pico W
- Módulo Joystick Analógico (e.g., KY-023)
- Fonte de alimentação 5V

## 💻 Como Executar
```bash
# Clone o repositório
git clone https://github.com/Victor-Sarris/EmbarcaTech.git

# Acesse a pasta do projeto
cd EmbarcaTech/Residência\ Tecnológica\ em\ Software\ Embarcado/unidade2/joystick_control_webserver

# Carregue o firmware na Arduino IDE:
# 1. Selecione a placa Pico W
# 2. Configure as credenciais WiFi em wifi_config.h
# 3. Faça o upload do código
```

## 🌐 Acesso à Interface
1. Conecte-se à rede WiFi criada pelo Pico W
2. Acesse no navegador: `http://joystick-control.local` ou IP do dispositivo
3. Interface mostrará:
   - Gráfico de posição do joystick
   - Valores numéricos dos eixos
   - Status dos botões

## 🖼️ Demonstração

![image](https://github.com/user-attachments/assets/53624349-8268-495d-bf83-6c1f7218d607)

![image](https://github.com/user-attachments/assets/aa69e7fe-9b89-46be-a0ce-02611ee0d55c)



---

**Desenvolvido por** [Victor Sarris](https://github.com/Victor-Sarris)  
*Projeto acadêmico - EmbarcaTech 2025*
