#include "tasks.h"
#include "relay.h"
#include "command_parser.h"
#include "configs.h"
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <stdio.h>

relay_t relay;

void tasks_init() {
    relay_init(&relay, RELAY_PIN);

    xTaskCreate(command_parser_task, "CmdParser", 256, nullptr, 2, nullptr);
}
