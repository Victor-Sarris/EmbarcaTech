# 🌐 LED Control Webserver  
*Controle remoto de LEDs via interface web - Projeto da Residência em Software Embarcado (Unidade 2)*  

## 🚀 Funcionalidades  
- Controle individual de LEDs através de página web  
- Interface responsiva adaptável a dispositivos móveis  
- Comunicação cliente-servidor via protocolo HTTP  
- Visualização em tempo real do estado dos LEDs  

## 🛠️ Tecnologias  
<p align="left">
  <img src="https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32">
  <img src="https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino IDE">
  <img src="https://img.shields.io/badge/HTML5-E34F26?style=for-the-badge&logo=html5&logoColor=white" alt="HTML5">
  <img src="https://img.shields.io/badge/CSS3-1572B6?style=for-the-badge&logo=css3&logoColor=white" alt="CSS3">
  <img src="https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black" alt="JavaScript">
</p>

## 📦 Estrutura do Projeto
```
led_control_webserver/
├── firmware/           # Código Arduino (.ino)
│   ├── led_control.ino # Lógica principal
│   └── wifi_config.h   # Configurações de rede
├── web_interface/      # Front-end
│   ├── index.html      # Página web
│   ├── style.css       # Estilos
│   └── script.js       # Controle AJAX
└── README.md           # Documentação
```

## 🔌 Como Executar
```bash
# 1. Clone o repositório
git clone https://github.com/Victor-Sarris/EmbarcaTech.git

# 2. Acesse a pasta do projeto
cd EmbarcaTech/Residência Tecnológica em Software Embarcado/unidade2/led_control_webserver

# 3. Carregue o firmware no Arduino IDE
# 4. Conecte-se ao WiFi do dispositivo
# 5. Acesse no navegador: http://<IP_DO_ESP>
```

## 🖼️ Preview
*(Adicione aqui screenshot da interface web se disponível)*

## 📝 Licença
Este projeto está sob licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

---

**Desenvolvido por** [Victor Sarris](https://github.com/Victor-Sarris)  
*Parte do programa EmbarcaTech - Residência em Software Embarcado*
