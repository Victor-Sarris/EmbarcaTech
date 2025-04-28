# 🕹️ Joystick Control Webserver
*Sistema de controle remoto com joystick via interface web - Projeto da Residência em Software Embarcado (Unidade 2)*

## 🚀 Funcionalidades
- Leitura analógica de eixos X/Y do joystick
- Controle remoto via interface web responsiva
- Visualização em tempo real da posição do joystick
- Botões digitais programáveis
- Comunicação WebSocket para atualização em tempo real

## 🛠️ Tecnologias
<p align="left">
  <img src="https://img.shields.io/badge/PICOW-E7352C?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32">
  <img src="https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino IDE">
  <img src="https://img.shields.io/badge/WebSocket-010101?style=for-the-badge&logo=websocket&logoColor=white" alt="WebSocket">
  <img src="https://img.shields.io/badge/Chart.js-FF6384?style=for-the-badge&logo=chart.js&logoColor=white" alt="Chart.js">
  <img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black" alt="JavaScript">
</p>

## 📦 Estrutura do Projeto
```
joystick_control_webserver/
├── firmware/
│   ├── joystick_control.ino  # Lógica principal
│   ├── websocket_server.h    # Configuração WebSocket
│   └── wifi_config.h         # Credenciais WiFi
├── web_interface/
│   ├── index.html            # Interface de controle
│   ├── dashboard.js          # Visualização dos dados
│   ├── style.css             # Estilos CSS
│   └── favicon.ico           # Ícone da página
├── schematics/               # Diagramas elétricos
│   └── joystick_wiring.png   # Esquema de conexões
└── README.md                 # Documentação
```

## 🔌 Hardware Necessário
- Placa ESP32 ou ESP8266
- Módulo Joystick Analógico (e.g., KY-023)
- Protoboard e jumpers
- Fonte de alimentação 5V

## 💻 Como Executar
```bash
# Clone o repositório
git clone https://github.com/Victor-Sarris/EmbarcaTech.git

# Acesse a pasta do projeto
cd EmbarcaTech/Residência\ Tecnológica\ em\ Software\ Embarcado/unidade2/joystick_control_webserver

# Carregue o firmware na Arduino IDE:
# 1. Selecione a placa ESP32
# 2. Configure as credenciais WiFi em wifi_config.h
# 3. Faça o upload do código
```

## 🌐 Acesso à Interface
1. Conecte-se à rede WiFi criada pelo ESP32
2. Acesse no navegador: `http://joystick-control.local` ou IP do dispositivo
3. Interface mostrará:
   - Gráfico de posição do joystick
   - Valores numéricos dos eixos
   - Status dos botões

## 🖼️ Demonstração

![image](https://github.com/user-attachments/assets/53624349-8268-495d-bf83-6c1f7218d607)

![image](https://github.com/user-attachments/assets/aa69e7fe-9b89-46be-a0ce-02611ee0d55c)



## 📝 Licença
Distribuído sob licença MIT. Veja [LICENSE](LICENSE) para detalhes.

---

**Desenvolvido por** [Victor Sarris](https://github.com/Victor-Sarris)  
*Projeto acadêmico - EmbarcaTech 2023*
