#include "esp_console.h"
linenoiseClearScreen();
linenoiseSetMultiLine(1);
linenoiseAllowEmpty(true);
linenoiseSetMaxLineLen(2048);
esp_console_config_t cmdConf ={
        .max_cmdline_length = 256,
        .max_cmdline_args = 32,      
        .hint_color = 39,            
        .hint_bold = 0 
};