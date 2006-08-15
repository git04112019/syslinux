/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2006 Erwan Velu - All Rights Reserved
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,
 *   Boston MA 02111-1307, USA; either version 2 of the License, or
 *   (at your option) any later version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

/*
 * dmitest.c
 *
 * DMI demo program using libcom32
 */

#include <string.h>
#include <stdio.h>
#include <console.h>
#include "dmi/dmi.h"

char display_line;

void display_bios(s_dmi *dmi) {
 moreprintf("BIOS\n");
 moreprintf("\tVendor:   %s\n",dmi->bios.vendor);
 moreprintf("\tVersion:  %s\n",dmi->bios.version);
 moreprintf("\tRelease:  %s\n",dmi->bios.release_date);
 moreprintf("\tBios Revision     %s\n",dmi->bios.bios_revision);
 moreprintf("\tFirmware Revision %s\n",dmi->bios.firmware_revision);
 moreprintf("\tAddress:  0x%04X0\n",dmi->bios.address);
 moreprintf("\tRuntime address: %u %s\n",dmi->bios.runtime_size,dmi->bios.runtime_size_unit);
 moreprintf("\tRom size: %u %s\n",dmi->bios.rom_size,dmi->bios.rom_size_unit);
 display_bios_characteristics(dmi);
}

void display_system(s_dmi *dmi) {
 moreprintf("\nSystem\n");
 moreprintf("\tManufacturer %s\n",dmi->system.manufacturer);
 moreprintf("\tProduct Name %s\n",dmi->system.product_name);
 moreprintf("\tVersion      %s\n",dmi->system.version);
 moreprintf("\tSerial       %s\n",dmi->system.serial);
 moreprintf("\tUUID         %s\n",dmi->system.uuid);
 moreprintf("\tWakeup Type  %s\n",dmi->system.wakeup_type);
 moreprintf("\tSKU Number   %s\n",dmi->system.sku_number);
 moreprintf("\tFamily       %s\n",dmi->system.family);
}

void display_base_board(s_dmi *dmi) {
 moreprintf("Base board\n");
 moreprintf("\tManufacturer %s\n",dmi->base_board.manufacturer);
 moreprintf("\tProduct Name %s\n",dmi->base_board.product_name);
 moreprintf("\tVersion      %s\n",dmi->base_board.version);
 moreprintf("\tSerial       %s\n",dmi->base_board.serial);
 moreprintf("\tAsset Tag    %s\n",dmi->base_board.asset_tag);
 moreprintf("\tLocation     %s\n",dmi->base_board.location);
 moreprintf("\tType         %s\n",dmi->base_board.type);
 display_base_board_features(dmi);
}

void display_chassis(s_dmi *dmi) {
 moreprintf("\nChassis\n");
 moreprintf("\tManufacturer %s\n",dmi->chassis.manufacturer);
 moreprintf("\tType	   %s\n",dmi->chassis.type);
 moreprintf("\tLock	   %s\n",dmi->chassis.lock);
 moreprintf("\tVersion      %s\n",dmi->chassis.version);
 moreprintf("\tSerial       %s\n",dmi->chassis.serial);
 moreprintf("\tAsset Tag    %s\n",dmi->chassis.asset_tag);
 moreprintf("\tBoot up state %s\n",dmi->chassis.boot_up_state);
 moreprintf("\tPower supply state %s\n",dmi->chassis.power_supply_state);
 moreprintf("\tThermal state %s\n",dmi->chassis.thermal_state);
 moreprintf("\tSecurity Status    %s\n",dmi->chassis.security_status);
 moreprintf("\tOEM Information    %s\n",dmi->chassis.oem_information);
 moreprintf("\tHeight       %u\n",dmi->chassis.height);
 moreprintf("\tNB Power Cords     %u\n",dmi->chassis.nb_power_cords);
}

void display_cpu(s_dmi *dmi) {
 moreprintf("\nCPU\n");
 moreprintf("\tSocket Designation %s\n",dmi->processor.socket_designation);
 moreprintf("\tType         %s\n",dmi->processor.type);
 moreprintf("\tFamily       %s\n",dmi->processor.family);
 moreprintf("\tManufacturer %s\n",dmi->processor.manufacturer);
 moreprintf("\tVersion      %s\n",dmi->processor.version);
 moreprintf("\tExternal Clock    %u\n",dmi->processor.external_clock);
 moreprintf("\tMax Speed         %u\n",dmi->processor.max_speed);
 moreprintf("\tCurrent Speed     %u\n",dmi->processor.current_speed);
 moreprintf("\tCpu Type     %u\n",dmi->processor.signature.type);
 moreprintf("\tCpu Family   %u\n",dmi->processor.signature.family);
 moreprintf("\tCpu Model    %u\n",dmi->processor.signature.model);
 moreprintf("\tCpu Stepping %u\n",dmi->processor.signature.stepping);
 moreprintf("\tCpu Minor Stepping %u\n",dmi->processor.signature.minor_stepping);
 moreprintf("\tVoltage      %f\n",dmi->processor.voltage);
 moreprintf("\tStatus       %s\n",dmi->processor.status);
 moreprintf("\tUpgrade      %s\n",dmi->processor.upgrade);
 moreprintf("\tCache L1 Handle %s\n",dmi->processor.cache1);
 moreprintf("\tCache L2 Handle %s\n",dmi->processor.cache2);
 moreprintf("\tCache L3 Handle %s\n",dmi->processor.cache3);
 moreprintf("\tSerial       %s\n",dmi->processor.serial);
 moreprintf("\tPart Number  %s\n",dmi->processor.part_number);
 moreprintf("\tID           %s\n",dmi->processor.id);
 display_processor_flags(dmi);
}

int main(void)
{
  char buffer[1024];
  s_dmi dmi;
  openconsole(&dev_stdcon_r, &dev_stdcon_w);

  if ( ! dmi_interate() ) {
	  printf("No DMI Structure found\n");
	  return -1;
  }

  parse_dmitable(&dmi);

  for (;;) {
    printf("Available commands are system, chassis, base_board, cpu, bios, all, exit\n");
    printf("dmi: ");
    fgets(buffer, sizeof buffer, stdin);
    if ( !strncmp(buffer, "exit", 4) )
      break;
    if ( !strncmp(buffer, "system", 6) )
	    display_system(&dmi);
    if ( !strncmp(buffer, "chassis", 6) )
	    display_chassis(&dmi);
    if ( !strncmp(buffer, "base_board", 10) )
	    display_base_board(&dmi);
    if ( !strncmp(buffer, "cpu", 3) )
	    display_cpu(&dmi);
    if ( !strncmp(buffer, "bios", 4) )
	    display_bios(&dmi);
    if ( !strncmp(buffer, "all", 3) ) {
	    display_bios(&dmi);
	    display_system(&dmi);
	    display_chassis(&dmi);
	    display_base_board(&dmi);
	    display_cpu(&dmi);
    }
  }

  return 0;
}
