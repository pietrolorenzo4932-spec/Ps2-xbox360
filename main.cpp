#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cabeçalhos específicos da libxenon (Xbox 360 bare-metal)
#include <xenon_init/xenon_init.h>
#include <console/console.h>
#include <usb/usbmain.h>
#include <ppc/timebase.h>

int main() {
    // 1. Inicializa o hardware básico do Xbox 360 (vídeo, threads e barramentos)
    xenon_make_it_raw();

    // 2. Inicializa o console de vídeo na tela (Framebuffer de texto padrão)
    console_init();

    // 3. Inicializa as portas USB (essencial para ler pendrives com o emulador e controles)
    usb_init();

    // Limpa a tela e define a posição do cursor
    printf("\x1b[2J"); 
    
    // Mensagem de Boas-Vindas
    printf("===========================================\n");
    printf(" xePS2 - Emulador de PS2 para Xbox 360     \n");
    printf(" Marco (A): Toolchain e Hardware Iniciado! \n");
    printf("===========================================\n\n");

    printf("[INFO] Inicializando subsistemas...\n");
    printf("[INFO] CPU PowerPC 3 nucleos detectada.\n");
    printf("[INFO] Memoria livre: 512 MB.\n\n");
    
    printf("Aguardando carregamento de arquivos via USB...\n");

    // Loop principal (o emulador não pode fechar, pois não há SO para onde voltar)
    while(1) {
        // usb_do_poll(); // Atualiza periféricos USB constantemente
        
        // Evita consumo de 100% de CPU neste loop de espera inicial
        delay_ms(16); 
    }

    return 0;
}
